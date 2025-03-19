# **🟢 Blockchain_CPP - Réseau P2P Décentralisé avec API HTTP et Économie MTX**  

![Blockchain_CPP](https://img.shields.io/badge/Blockchain-C%2B%2B-blue.svg?style=for-the-badge)  
![Version](https://img.shields.io/badge/Version-v2.0--MTX-green.svg?style=for-the-badge)  
![Status](https://img.shields.io/badge/Status-Active-success.svg?style=for-the-badge)  

---

## **🔗 Description**  
**Blockchain_CPP** est une **blockchain décentralisée en C++** qui allie **P2P, API HTTP, économie intégrée (MTX)** et **visualisation en temps réel façon Matrix** 📟💚.  

✨ **Nouvelles fonctionnalités :**  
✔️ **🌐 API RESTful HTTP :** Interaction en temps réel avec la blockchain.  
✔️ **💰 Système économique MTX :** Envoi sécurisé de tokens entre utilisateurs.  
✔️ **🟢 Proof of Matrix (PoM) :** Récompense automatique des nœuds actifs.  
✔️ **🛡️ Anti-Spam intégré :** Les transactions abusives sont pénalisées.  
✔️ **⚡ Synchronisation P2P avancée :** Découverte et connexion automatique entre nœuds.  
✔️ **🎥 Effet Matrix dynamique :** Affichage en temps réel du trafic blockchain.  

---

## **🚀 Installation & Démarrage**  
### **1️⃣ Prérequis**  
📌 **Systèmes supportés :** Ubuntu / Debian / Proxmox / Termux  
📌 **Dépendances :** C++ (g++), Boost, OpenSSL, Python3, ncurses  

### **2️⃣ Cloner le projet**  
```bash
git clone https://github.com/FoxtekTS/blockchain_cpp.git
cd blockchain_cpp
```

### **3️⃣ Compiler la blockchain avec l’API HTTP**  
```bash
g++ -std=c++17 -o build/blockchain src/main.cpp src/block.cpp src/blockchain.cpp src/network.cpp src/transaction.cpp src/api.cpp -Iinclude -lssl -lcrypto -lboost_system -lpthread
```

### **4️⃣ Démarrer la blockchain et l’API HTTP**  
```bash
./build/blockchain
```
🚀 **L’API HTTP démarre sur `http://localhost:8081`**  
🚀 **Le réseau P2P tourne sur `port 8080`**  

---

## **🌐 API HTTP - Interagir avec la Blockchain**  
### **1️⃣ Récupérer tous les blocs**  
```bash
curl http://localhost:8081/blocks
```

### **2️⃣ Ajouter un nouveau bloc**  
```bash
curl -X POST -d "Nouvelle transaction" http://localhost:8081/add_block
```

### **3️⃣ Vérifier le solde d’un utilisateur** *(à venir...)*  
```bash
curl http://localhost:8081/balance/Alice
```

---

## **💰 Transactions & Gestion des MTX**  
### **1️⃣ Initialiser un compte avec 100 MTX**  
```cpp
initializeAccount("Alice");
initializeAccount("Bob");
```

### **2️⃣ Effectuer une transaction**  
```cpp
sendMTX("Alice", "Bob", 20);
```

### **3️⃣ Récompenser un nœud actif**  
```cpp
rewardActiveNode("Alice");
```

### **4️⃣ Pénaliser un spammeur**  
```cpp
penalizeSpammer("Bob");
```

### **5️⃣ Vérifier les soldes après transaction**  
```cpp
std::cout << "Alice : " << myBlockchain.tokenBalance["Alice"] << " MTX\n";
std::cout << "Bob   : " << myBlockchain.tokenBalance["Bob"] << " MTX\n";
```

---

## **🖥️ Interface Matrix - Visualisation en temps réel**  
**Lance l’effet Matrix :**  
```bash
python3 matrix_blockchain.py
```
📌 **Explication :**  
✅ **Lettres & chiffres verts** → Transactions blockchain.  
✅ **Flux descendant** → Nouveaux blocs ajoutés.  
✅ **Vitesse variable** → Plus d’activité = plus rapide.  

🔥 *Plus la blockchain est active, plus l’effet Matrix devient intense !*  

---

## **🌍 Déploiement automatique avec Ansible**  
Tu peux mettre à jour tous les nœuds en une seule commande :  
```bash
ansible-playbook -i inventory update_matrix.yml
```

🔹 **Tester la connexion entre nœuds :**  
```bash
ansible -i inventory blockchain_nodes -m ping
```
🔹 **Redémarrer un nœud blockchain :**  
```bash
ansible -i inventory blockchain_nodes -a "systemctl restart blockchain"
```

---

## **📜 Journal des transactions**  
Pour **suivre l’évolution de la blockchain** :  
```bash
tail -f blockchain.log
```
📌 **Exemple de transaction :**  
```
Index: 5
Previous Hash: a4562b789e1c4a...
Data: Transaction 5 : Alice → Bob
Hash: 9f3b2c1e568fa...
Timestamp: 1742098882
---------------------------------
Connecté au pair 192.168.1.22:8080
```

---

## **👑 Créateur & Contributions**  
🚀 **FoxtekTS** aka **ZEROCOOL**  

💾 **Version actuelle** : `v2.0 MTX Edition`  
📅 **Dernière mise à jour** : `Mars 2025`  
🔗 **GitHub** : [FoxtekTS/blockchain_cpp](https://github.com/FoxtekTS/blockchain_cpp)  

🔥 *Bienvenue dans le futur du P2P décentralisé avec API HTTP !* 🚀💾  

---

















