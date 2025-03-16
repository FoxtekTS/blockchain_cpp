#include "network.h"
#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <boost/asio.hpp>

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

    char buffer[4096] = {0};  // Augmente la taille du buffer pour éviter la coupure de données
    size_t bytesRead = socket->read_some(boost::asio::buffer(buffer));

    std::string receivedData(buffer, bytesRead);  // Convertir en string
    std::cout << "🔍 Données brutes reçues:\n" << receivedData << std::endl;

    std::istringstream iss(receivedData);
    std::string line;
    while (std::getline(iss, line)) {
        std::cout << "📜 Ligne reçue: " << line << std::endl;
        size_t pos = line.find("|");

        if (pos != std::string::npos) {
            std::string index = line.substr(0, pos);
            std::string rest = line.substr(pos + 1);
            std::cout << "🧐 Index: " << index << " | Données restantes: " << rest << std::endl;

            // Vérifier si l'index est bien un nombre
            try {
                int idx = std::stoi(index);
                std::cout << "✅ Index valide: " << idx << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "❌ Erreur conversion index: " << e.what() << " | Ligne: " << line << std::endl;
                continue;
            }

        } else {
            std::cerr << "⚠️ Ligne ignorée (format incorrect): " << line << std::endl;
        }
    }
}



