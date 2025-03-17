#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/obj_mac.h>
#include <openssl/sha.h>

class Transaction {
public:
    std::string sender;
    std::string receiver;
    double amount;
    std::string signature;

    Transaction(std::string s, std::string r, double a);
    std::string signTransaction(EC_KEY* privateKey);
    bool verifyTransaction(EC_KEY* publicKey);
};

#endif
