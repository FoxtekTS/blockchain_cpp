#include "transaction.h"
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>

Transaction::Transaction(std::string s, std::string r, double a) 
    : sender(s), receiver(r), amount(a) {}

std::string Transaction::signTransaction(EC_KEY* privateKey) {
    unsigned char hash[32];
    unsigned char salt[16];  // Génération de sel aléatoire
    RAND_bytes(salt, sizeof(salt));

    std::string inputData = receiver + std::string((char*)salt, sizeof(salt));
    SHA256((unsigned char*)inputData.c_str(), inputData.size(), hash);

    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    EVP_PKEY* pkey = EVP_PKEY_new();
    EVP_PKEY_assign_EC_KEY(pkey, privateKey);

    if (EVP_DigestSignInit(mdctx, NULL, EVP_sha256(), NULL, pkey) <= 0) {
        return "";
    }

    EVP_DigestSignUpdate(mdctx, hash, sizeof(hash));
    
    size_t sigLen;
    EVP_DigestSignFinal(mdctx, NULL, &sigLen);
    std::vector<unsigned char> sig(sigLen);
    EVP_DigestSignFinal(mdctx, sig.data(), &sigLen);

    EVP_MD_CTX_free(mdctx);
    EVP_PKEY_free(pkey);

    this->signature = std::string(sig.begin(), sig.end());
    return this->signature;
}

// ✅ Nouvelle version de verifyTransaction (compatible OpenSSL 3.0)
bool Transaction::verifyTransaction(EC_KEY* publicKey) {
    unsigned char hash[32];
    SHA256((unsigned char*)this->receiver.c_str(), this->receiver.size(), hash);

    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    EVP_PKEY* pkey = EVP_PKEY_new();
    EVP_PKEY_assign_EC_KEY(pkey, publicKey);

    if (EVP_DigestVerifyInit(mdctx, NULL, EVP_sha256(), NULL, pkey) <= 0) {
        return false;
    }

    if (EVP_DigestVerifyUpdate(mdctx, hash, sizeof(hash)) <= 0) {
        return false;
    }

    bool valid = EVP_DigestVerifyFinal(mdctx, (unsigned char*)this->signature.c_str(), this->signature.size()) == 1;

    EVP_MD_CTX_free(mdctx);
    EVP_PKEY_free(pkey);
    
    return valid;
}


