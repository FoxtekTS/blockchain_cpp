#include "blockchain.h"
#include "network.h"
#include <boost/asio.hpp>


int main() {
    Blockchain myBlockchain;

    // ✅ Initialisation des comptes avec 100 MTX chacun
    myBlockchain.initializeAccount("Alice");
    myBlockchain.initializeAccount("Bob");

    // ✅ Ajout des transactions classiques
    myBlockchain.addBlock("Transaction 1 : Alice → Bob");
    myBlockchain.addBlock("Transaction 2 : Bob → Charlie");

    // ✅ Effectuer des transactions en MTX
    myBlockchain.sendMTX("Alice", "Bob", 20);  // Alice envoie 20 MTX à Bob
    myBlockchain.sendMTX("Bob", "Alice", 5);   // Bob envoie 5 MTX à Alice

    // ✅ Récompenser un nœud actif
    myBlockchain.rewardActiveNode("Alice");

    // ❌ Pénaliser un spammeur
    myBlockchain.penalizeSpammer("Bob");

    // ✅ Afficher les blocs
    for (const Block& block : myBlockchain.chain) {
        std::cout << "Index: " << block.index << "\n";
        std::cout << "Previous Hash: " << block.previousHash << "\n";
        std::cout << "Data: " << block.data << "\n";
        std::cout << "Hash: " << block.hash << "\n";
        std::cout << "Timestamp: " << block.timestamp << "\n";
        std::cout << "---------------------------------\n";
    }

    // ✅ Afficher les soldes des comptes
    std::cout << "\n💰 Soldes des comptes après transactions :\n";
    std::cout << "Alice : " << myBlockchain.tokenBalance["Alice"] << " MTX\n";
    std::cout << "Bob   : " << myBlockchain.tokenBalance["Bob"] << " MTX\n";

    // ✅ Démarrer le serveur P2P
    boost::asio::io_context io_context;
    Node server(io_context, 8080, myBlockchain); // Port 8080 pour le premier nœud

    // ✅ Configurer Tor comme proxy SOCKS5
    server.setTorProxy("127.0.0.1", 9050);

    // ✅ Connecter ce nœud au nœud distant (externe)
    server.connectToPeer("90.126.97.57", 8080);

    // ✅ Connecter ce nœud à un autre nœud du réseau local
    server.connectToPeer("192.168.1.22", 8080);

    // ✅ Connecter ce nœud au réseau Tor
    server.connectToPeer("xrlz4artnwwgpikjh45bmfudng64he2bzwzhblbpov3xwupytwpii2yd.onion", 8080);

    server.loadPeersFromFile("peers.onion");


    io_context.run();

    return 0;
}

