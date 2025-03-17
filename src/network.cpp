#include "network.h"
#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <boost/asio.hpp>
#include <random>

using boost::asio::ip::tcp;

void Node::addPeer(const std::string& ip, int port) {
    for (const auto& peer : knownPeers) {
        if (peer.first == ip && peer.second == port) {
            return;  // Évite les doublons
        }
    }
    knownPeers.emplace_back(ip, port);
    std::cout << "Nouveau pair ajouté : " << ip << ":" << port << std::endl;
}

void Node::sharePeerList(std::shared_ptr<tcp::socket> socket) {
    std::string peerData;
    for (const auto& peer : knownPeers) {
        peerData += peer.first + ":" + std::to_string(peer.second) + "\n";
    }
    boost::asio::write(*socket, boost::asio::buffer(peerData));
}

void Node::requestPeerList(std::shared_ptr<tcp::socket> socket) {
    std::string request = "REQUEST_PEERS\n";
    boost::asio::write(*socket, boost::asio::buffer(request));

    char buffer[1024] = {0};
    size_t bytesRead = socket->read_some(boost::asio::buffer(buffer));
    
    if (bytesRead == 0) {
        std::cerr << "Erreur : Réponse vide du pair." << std::endl;
        return;
    }

    std::istringstream iss(std::string(buffer, bytesRead));
    std::string line;
    
    while (std::getline(iss, line)) {
        size_t pos = line.find(":");
        if (pos != std::string::npos) {
            std::string peerIP = line.substr(0, pos);
            std::string portStr = line.substr(pos + 1);

            // Vérification que le port est bien un nombre
            if (!portStr.empty() && std::all_of(portStr.begin(), portStr.end(), ::isdigit)) {
                try {
                    int peerPort = std::stoi(portStr);
                    addPeer(peerIP, peerPort);
                    std::cout << "Ajout du pair : " << peerIP << ":" << peerPort << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Erreur de conversion `stoi` pour : " << portStr << " (" << e.what() << ")" << std::endl;
                }
            } else {
                std::cerr << "Port invalide reçu -> " << portStr << std::endl;
            }
        } else {
            std::cerr << "Format invalide reçu -> " << line << std::endl;
        }
    }
}

void Node::connectToPeer(std::string peer_ip, short peer_port) {
    auto socket = std::make_shared<tcp::socket>(acceptor_.get_executor());
    boost::system::error_code ec;
    socket->connect(tcp::endpoint(boost::asio::ip::address::from_string(peer_ip), peer_port), ec);
    
    if (!ec) {
        std::cout << "Connecté au pair " << peer_ip << ":" << peer_port << std::endl;
        peers.push_back(socket);
        requestPeerList(socket);  // Demande la liste des pairs dès la connexion
    } else {
        std::cout << "Impossible de se connecter à " << peer_ip << ":" << peer_port << std::endl;
    }
}

void Node::startAccept() {
    auto socket = std::make_shared<tcp::socket>(acceptor_.get_executor());
    acceptor_.async_accept(*socket, [this, socket](boost::system::error_code ec) {
        if (!ec) {
            std::cout << "Nouvelle connexion d'un pair !" << std::endl;
            peers.push_back(socket);
            sharePeerList(socket);  // Envoyer la liste des pairs au nouveau nœud
        }
        startAccept();  // Attendre la prochaine connexion
    });
}

void Node::requestBlockchain(std::shared_ptr<tcp::socket> socket) {
    std::string message = "REQUEST_BLOCKCHAIN\n";
    boost::asio::write(*socket, boost::asio::buffer(message));

    char buffer[4096] = {0}; 
    size_t bytesRead = socket->read_some(boost::asio::buffer(buffer));

    std::string receivedData(buffer, bytesRead);
    std::cout << "🔍 Données brutes reçues: " << receivedData << std::endl;

    std::istringstream iss(receivedData);
    std::string line;
    while (std::getline(iss, line)) {
        std::cout << "📜 Ligne reçue: " << line << std::endl;

        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, '|')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 5) {
            int index = std::stoi(tokens[0]);
            std::string prevHash = tokens[1];
            std::string data = tokens[2];
            std::string hash = tokens[3];
            long timestamp = std::stol(tokens[4]);

            std::cout << "✅ Bloc valide reçu -> " << data << std::endl;
        } else {
            std::cout << "⚠️ Format incorrect -> " << line << std::endl;
        }
    }
}



void Node::sendBlockchain(std::shared_ptr<tcp::socket> socket) {
    std::string blockchainData = serializeBlockchain();
    std::cout << "📤 Données envoyées:\n" << blockchainData << std::endl;
    boost::asio::write(*socket, boost::asio::buffer(blockchainData));
}

std::string Node::serializeBlockchain() {
    std::string data;
    for (const Block& block : blockchain_.chain) {
        data += std::to_string(block.index) + "|" + block.previousHash + "|" + block.data + "|" + block.hash + "|" + std::to_string(block.timestamp) + "\n";
    }
    return data;
}

void Node::gossipTransaction(const std::string& txData) {
    if (peers.empty()) return; // Pas de pairs connectés, on arrête

    std::vector<std::shared_ptr<tcp::socket>> selectedPeers;
    
    // Sélectionner aléatoirement 3 pairs pour relayer la transaction
    std::sample(peers.begin(), peers.end(), std::back_inserter(selectedPeers), 
                std::min(3, (int)peers.size()), std::mt19937{std::random_device{}()});

    for (auto& peer : selectedPeers) {
        boost::asio::write(*peer, boost::asio::buffer(txData + "\n"));
    }

    std::cout << "🔄 Transaction relayée via Gossip Protocol à " << selectedPeers.size() << " pairs.\n";
}
