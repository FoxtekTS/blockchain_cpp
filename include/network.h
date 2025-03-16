#define NETWORK_H
#define NETWORK_H

#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <utility>
#include <string>
#include "../include/blockchain.h"

using boost::asio::ip::tcp;

class Node {

void requestPeerList(std::shared_ptr<tcp::socket> socket);  // Demande la liste des pairs
void sharePeerList(std::shared_ptr<tcp::socket> socket);  // Envoie la liste des pairs
void addPeer(const std::string& ip, int port);  // Ajoute un nouveau pair
void requestBlockchain(std::shared_ptr<tcp::socket> socket);

public:
    Node(boost::asio::io_context& io_context, short port, Blockchain& blockchain)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), blockchain_(blockchain) {
        startAccept();
    }

    void connectToPeer(std::string peer_ip, short peer_port) {
        auto socket = std::make_shared<tcp::socket>(acceptor_.get_executor());
        boost::system::error_code ec;
        socket->connect(tcp::endpoint(boost::asio::ip::address::from_string(peer_ip), peer_port), ec);
        if (!ec) {
            std::cout << "Connecté au pair " << peer_ip << ":" << peer_port << std::endl;
            peers.push_back(socket);
            requestBlockchain(socket);
        } else {
            std::cout << "Impossible de se connecter à " << peer_ip << ":" << peer_port << std::endl;
        }
    }

private:
    tcp::acceptor acceptor_;
    Blockchain& blockchain_;
    std::vector<std::pair<std::string, int>> knownPeers;

    void startAccept() {
        auto socket = std::make_shared<tcp::socket>(acceptor_.get_executor());
        acceptor_.async_accept(*socket, [this, socket](boost::system::error_code ec) {
            if (!ec) {
                std::cout << "Nouvelle connexion d'un pair !" << std::endl;
                peers.push_back(socket);
                sendBlockchain(socket);
            }
            startAccept();
        });
    }

    void sendBlockchain(std::shared_ptr<tcp::socket> socket) {
        std::string blockchainData = serializeBlockchain();
        boost::asio::write(*socket, boost::asio::buffer(blockchainData));
    }

    void requestBlockchain(std::shared_ptr<tcp::socket> socket) {
        std::string message = "REQUEST_BLOCKCHAIN\n";
        boost::asio::write(*socket, boost::asio::buffer(message));
    }

    std::string serializeBlockchain() {
        std::string data;
        for (const Block& block : blockchain_.chain) {
            data += std::to_string(block.index) + "|" + block.previousHash + "|" + block.data + "|" + block.hash + "|" + std::to_string(block.timestamp) + "\n";
        }
        return data;
    }
};

#endif


