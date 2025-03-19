#include "api.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

BlockchainAPI::BlockchainAPI(Blockchain& blockchain) : blockchain(blockchain) {}

void BlockchainAPI::handleRequest(http::request<http::string_body>& req,
                                  http::response<http::string_body>& res) {
    if (req.method() == http::verb::get && req.target() == "/blocks") {
        std::stringstream ss;
        for (const Block& block : blockchain.chain) {
            ss << "Index: " << block.index << "\n"
               << "Previous Hash: " << block.previousHash << "\n"
               << "Data: " << block.data << "\n"
               << "Hash: " << block.hash << "\n"
               << "Timestamp: " << block.timestamp << "\n\n";
        }
        res.result(http::status::ok);
        res.body() = ss.str();
    } else if (req.method() == http::verb::post && req.target() == "/add_block") {
        blockchain.addBlock(req.body());
        res.result(http::status::ok);
        res.body() = "✅ Bloc ajouté avec succès !";
    } else {
        res.result(http::status::not_found);
        res.body() = "❌ Endpoint non trouvé.";
    }
    res.prepare_payload();
}

void BlockchainAPI::startServer(short port) {
    try {
        net::io_context ioc;
        tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), port));

        std::cout << "🚀 API HTTP démarrée sur le port " << port << "..." << std::endl;

        while (true) {
            tcp::socket socket(ioc);
            acceptor.accept(socket);

            beast::flat_buffer buffer;
            http::request<http::string_body> req;
            http::read(socket, buffer, req);

            http::response<http::string_body> res;
            res.version(req.version());
            res.set(http::field::server, "Blockchain-API");

            handleRequest(req, res);

            http::write(socket, res);
        }
    } catch (std::exception& e) {
        std::cerr << "Erreur API : " << e.what() << std::endl;
    }
}

