#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <utility>
#include <string>
#include "../include/blockchain.h"

using boost::asio::ip::tcp;

class Node {

// Méthodes réseau internes
void requestPeerList(std::shared_ptr<tcp::socket> socket);  // Demande la liste des pairs
void sharePeerList(std::shared_ptr<tcp::socket> socket);   // Envoie la liste des pairs
void addPeer(const std::string& ip, int port);              // Ajoute un nouveau pair
void requestBlockchain(std::shared_ptr<tcp::socket> socket);

public:
    Node(boost::asio::io_context& io_context, short port, Blockchain& blockchain)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), blockchain_(blockchain) {
        startAccept();
    }

    // Connexion à un pair (implémentation dans network.cpp)
    void connectToPeer(std::string peer_ip, short peer_port);

private:
    tcp::acceptor acceptor_;
    Blockchain& blockchain_;
    std::vector<std::pair<std::string, int>> knownPeers;

    // Fonctions internes (implémentations dans network.cpp)
    void startAccept();
    void sendBlockchain(std::shared_ptr<tcp::socket> socket);
    void requestBlockchain(std::shared_ptr<tcp::socket> socket);
    std::string serializeBlockchain();

    // Configuration du proxy Tor pour tous les pairs
    void setTorProxy(const std::string& proxy_ip, int proxy_port);

    // Gossip et chargement de pairs depuis un fichier
    void gossipTransaction(const std::string& txData);
    void loadPeersFromFile(const std::string& filename);
};

#endif


