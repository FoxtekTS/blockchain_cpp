#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <memory>
#include <boost/asio.hpp>
#include "../include/blockchain.h"

using boost::asio::ip::tcp;

class Node {
public:
    Node(boost::asio::io_context& io_context, short port, Blockchain& blockchain)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), blockchain_(blockchain) {
        startAccept();
    }

    void connectToPeer(std::string peer_ip, short peer_port);
    void requestPeerList(std::shared_ptr<tcp::socket> socket);
    void sharePeerList(std::shared_ptr<tcp::socket> socket);
    void addPeer(const std::string& ip, int port);
    void gossipTransaction(const std::string& txData);
    void setTorProxy(const std::string& proxy_ip, int proxy_port);
    void loadPeersFromFile(const std::string& filename);


private:
    tcp::acceptor acceptor_;
    Blockchain& blockchain_;
    std::vector<std::pair<std::string, int>> knownPeers;  // Liste des pairs connus
    std::vector<std::shared_ptr<tcp::socket>> peers;  // Connexions actives
    std::string serializeBlockchain();

    void startAccept();
    void sendBlockchain(std::shared_ptr<tcp::socket> socket);
    void requestBlockchain(std::shared_ptr<tcp::socket> socket);
};

#endif  // NETWORK_H

