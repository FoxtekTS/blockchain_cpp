#include "blockchain.h"
#include <iostream>
#include <functional>  // Pour std::hash

// ✅ Déplacer les implémentations ici
Blockchain::Blockchain() {
    chain.push_back(createGenesisBlock());
}

Block Blockchain::createGenesisBlock() {
    return Block(0, "0", "Genesis Block");
}

Block Blockchain::getLatestBlock() {
    return chain.back();
}

void Blockchain::addBlock(std::string data) {
    std::string txHash = std::to_string(std::hash<std::string>{}(data));

    if (isTransactionValid(txHash)) {
        std::string previousHash = chain.empty() ? "0" : getLatestBlock().hash; // ✅ Vérification
        Block newBlock(chain.size(), previousHash, data);
        chain.push_back(newBlock);
        addTransactionToCache(txHash);
        std::cout << "✅ Nouveau bloc ajouté avec succès !\n";
    } else {
        std::cout << "❌ Transaction déjà validée, rejetée.\n";
    }
}

// ✅ Vérifie si la transaction est déjà présente dans le cache
bool Blockchain::isTransactionValid(const std::string& txHash) {
    return transactionCache.find(txHash) == transactionCache.end();
}

// ✅ Ajoute la transaction validée au cache
void Blockchain::addTransactionToCache(const std::string& txHash) {
    transactionCache[txHash] = true;
}


// ✅ Initialise un compte avec un airdrop de 100 MTX
void Blockchain::initializeAccount(const std::string& user) {
    if (tokenBalance.find(user) == tokenBalance.end()) {
        tokenBalance[user] = 100.0;  // ✅ Chaque nouvel utilisateur reçoit 100 MTX au départ
        std::cout << "🎉 Airdrop : " << user << " reçoit 100 MTX !\n";
    }
}

// ✅ Permet d’envoyer des MTX entre utilisateurs
bool Blockchain::sendMTX(const std::string& sender, const std::string& receiver, double amount) {
    if (tokenBalance[sender] < amount) {
        std::cout << "❌ Transaction refusée : Solde insuffisant.\n";
        return false;
    }

    tokenBalance[sender] -= amount;
    tokenBalance[receiver] += amount;
    std::cout << "✅ Transaction en MTX confirmée : " << sender << " → " << receiver << " [" << amount << " MTX]\n";
    return true;
}

// ✅ Récompense un nœud actif avec 0.5 MTX pour chaque transaction relayée
void Blockchain::rewardActiveNode(const std::string& node) {
    tokenBalance[node] += 0.5;
    std::cout << "💰 Récompense PoM : " << node << " gagne 0.5 MTX !\n";
}

// ❌ Pénalise les spammeurs en retirant 2 MTX
void Blockchain::penalizeSpammer(const std::string& node) {
    if (tokenBalance[node] >= 2) {
        tokenBalance[node] -= 2;
        std::cout << "⚠️ Pénalité : " << node << " a été sanctionné pour spam (-2 MTX)\n";
    } else {
        std::cout << "⚠️ Pénalité évitée : " << node << " n’a pas assez de MTX.\n";
    }
}
