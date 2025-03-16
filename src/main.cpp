#include "blockchain.h"
#include "network.h"
#include <boost/asio.hpp>

int main() {
    Blockchain myBlockchain;
    myBlockchain.addBlock("Transaction 1 : Alice → Bob");
    myBlockchain.addBlock("Transaction 2 : Bob → Charlie");

    // Afficher les blocs
    for (const Block& block : myBlockchain.chain) {
        std::cout << "Index: " << block.index << "\n";
        std::cout << "Previous Hash: " << block.previousHash << "\n";
        std::cout << "Data: " << block.data << "\n";
        std::cout << "Hash: " << block.hash << "\n";
        std::cout << "Timestamp: " << block.timestamp << "\n";
        std::cout << "---------------------------------\n";
    }

    // Démarrer le serveur P2P
    boost::asio::io_context io_context;
    Node server(io_context, 8080, myBlockchain); // Port 8080 pour le premier nœud

    // Pour tester la connexion à un autre nœud (remplace par l'IP du nœud distant)
    server.connectToPeer("192.168.1.22", 8080);

    io_context.run();

    return 0;
}
