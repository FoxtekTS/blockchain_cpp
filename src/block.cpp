#include "block.h"
#include <sstream>
#include <ctime>
#include <openssl/evp.h>
#include <openssl/sha.h>

Block::Block(int idx, std::string prevHash, std::string blockData) {
    index = idx;
    previousHash = prevHash;
    data = blockData;
    timestamp = std::time(0);
    nonce = 0;
    hash = calculateHash();
}

std::string Block::calculateHash() {  // ✅ Implémentation correcte
    std::stringstream ss;
    ss << index << previousHash << data << timestamp << nonce;

    unsigned char digest[SHA256_DIGEST_LENGTH];
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();

    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(ctx, ss.str().c_str(), ss.str().size());
    EVP_DigestFinal_ex(ctx, digest, NULL);
    EVP_MD_CTX_free(ctx);

    std::stringstream hashStream;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        hashStream << std::hex << (int)digest[i];

    return hashStream.str();
}

