#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <ctime>
#include <sstream>
#include <openssl/sha.h>

class Block {
public:
    int index;
    std::string previousHash;
    std::string data;
    std::string hash;
    long timestamp;
    int nonce;

    Block(int idx, std::string prevHash, std::string blockData) {
        index = idx;
        previousHash = prevHash;
        data = blockData;
        timestamp = std::time(0);
        nonce = 0;
        hash = calculateHash();
    }

    std::string calculateHash() {
        std::stringstream ss;
        ss << index << previousHash << data << timestamp << nonce;

        unsigned char digest[SHA256_DIGEST_LENGTH];
        SHA256((unsigned char*)ss.str().c_str(), ss.str().size(), digest);

        std::stringstream hashStream;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
            hashStream << std::hex << (int)digest[i];

        return hashStream.str();
    }
};

#endif

