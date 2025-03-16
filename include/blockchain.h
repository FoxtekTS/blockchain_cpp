#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include <vector>

class Blockchain {
public:
    std::vector<Block> chain;

    Blockchain() {
        chain.push_back(createGenesisBlock());
    }

    Block createGenesisBlock() {
        return Block(0, "0", "Genesis Block");
    }

    Block getLatestBlock() {
        return chain.back();
    }

    void addBlock(std::string data) {
        Block newBlock(chain.size(), getLatestBlock().hash, data);
        chain.push_back(newBlock);
    }
};

#endif

