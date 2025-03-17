#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include <vector>
#include <unordered_map>  // ✅ Cache transactionnel et gestion des MTX

class Blockchain {
public:
    std::vector<Block> chain;
    std::unordered_map<std::string, bool> transactionCache;  // ✅ Cache des transactions validées
    std::unordered_map<std::string, double> tokenBalance;  // ✅ Solde des utilisateurs en MTX

    Blockchain();  // ✅ Déclaration seulement
    Block createGenesisBlock();  // ✅ Déclaration seulement
    Block getLatestBlock();  // ✅ Déclaration seulement
    void addBlock(std::string data);  // ✅ Déclaration seulement
    bool isTransactionValid(const std::string& txHash);  // ✅ Déclaration seulement
    void addTransactionToCache(const std::string& txHash);  // ✅ Déclaration seulement

    // ✅ Système économique de la blockchain
    bool sendMTX(const std::string& sender, const std::string& receiver, double amount);  // ✅ Transfert de tokens
    void rewardActiveNode(const std::string& node);  // ✅ Récompense les nœuds actifs
    void penalizeSpammer(const std::string& node);  // ❌ Pénalise les spammeurs
    void initializeAccount(const std::string& user);  // ✅ Airdrop initial pour chaque utilisateur
};

#endif

