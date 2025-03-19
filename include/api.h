#ifndef API_H
#define API_H

#include "blockchain.h"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <iostream>

class BlockchainAPI {
public:
    BlockchainAPI(Blockchain& blockchain);
    void startServer(short port);

private:
    Blockchain& blockchain;
    void handleRequest(boost::beast::http::request<boost::beast::http::string_body>& req,
                       boost::beast::http::response<boost::beast::http::string_body>& res);
};

#endif // API_H

