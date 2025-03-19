#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <ctime>
#include <sstream>
#include <openssl/evp.h>
#include <openssl/sha.h>

class Block {
public:
    int index;
    std::string previousHash;
    std::string data;
    std::string hash;
    long timestamp;
    int nonce;

    Block(int idx, std::string prevHash, std::string blockData);

    std::string calculateHash();  // ✅ Déclaration correcte (sans `Block::`)
};

#endif  // BLOCK_H

