# 🟢 Blockchain_CPP - Réseau P2P Décentralisé avec Visualisation Matrix  

![Blockchain Matrix](https://media.giphy.com/media/3o7abldj0b3rxrZUxW/giphy.gif)  

## 🔗 **Description**  
Blockchain_CPP est une blockchain en **C++**, utilisant **Boost.Asio** pour le réseau P2P et **Flask-SocketIO** pour la synchronisation entre nœuds. Le projet permet la **création et propagation d'une blockchain** en temps réel sur un **réseau décentralisé**.  

⚡ **Nouveauté** : **Visualisation en temps réel façon Matrix** 📟💚  

## 📌 **Caractéristiques**  
✅ Réseau **P2P** avec **synchronisation automatique** des nœuds.  
✅ Interface **inspirée de Matrix** pour **visualiser l'évolution de la blockchain**.  
✅ Transmission **chiffrée des transactions** avec OpenSSL.  
✅ **Gestion automatique des ports et connexions**.  
✅ **Synchronisation GitHub** pour mise à jour instantanée sur tous les nœuds.  

---

## 🚀 **Installation & Démarrage**  
### **1️⃣ Prérequis**  
✔️ **Ubuntu / Debian / Proxmox / Termux** supportés  
✔️ **C++ (g++), Boost, OpenSSL** installés  
✔️ **Python3, Flask-SocketIO, Pygame pour la visualisation**  
✔️ **GitHub pour la mise à jour des nœuds**  

### **2️⃣ Cloner le projet**  
```bash
git clone https://github.com/FoxtekTS/blockchain_cpp.git
cd blockchain_cpp
```

### **3️⃣ Compiler la blockchain**  
```bash
g++ -o build/blockchain src/main.cpp src/network.cpp -Iinclude -lssl -lcrypto -lpthread -lboost_system
```

### **4️⃣ Démarrer un nœud**  
```bash
./start_blockchain.sh
```

### **5️⃣ Ajouter un pair (nœud distant)**  
```cpp
server.connectToPeer("192.168.1.22", 8080);
```

---

## 🖥️ **🟢 Interface Matrix - Visualisation en temps réel**  
Une fois le serveur en ligne, lance la visualisation :  
```bash
python3 matrix_blockchain.py
```
### **📡 Que représente l’animation ?**  
✅ **Les chiffres et lettres vertes** = Identifiants de transactions et blocs.  
✅ **Flux descendant** = Nouveaux blocs entrant dans la blockchain.  
✅ **Vitesse aléatoire** = Variabilité des confirmations de transactions.  
✅ **Clignotements** = Synchronisation avec d’autres nœuds.  

⚡ *Plus il y a d’activité, plus la matrice devient rapide et dense* !  

---

## 🌍 **Exposer sa blockchain sur Internet**  
1️⃣ **Ouvre le port 8080 sur ta box** 🔓  
2️⃣ **Teste avec Netcat** :  
   ```bash
   nc -zv 90.126.97.57 8080
   ```
3️⃣ **Ajoute un pair externe**  
   ```cpp
   server.connectToPeer("90.126.97.57", 8080);
   ```
4️⃣ **Vérifie que la blockchain se propage** sur les autres nœuds  
   ```bash
   tail -f blockchain.log
   ```

---

## 🔄 **Mise à jour automatique du réseau**  
Chaque nœud peut **télécharger les dernières mises à jour** avec :  
```bash
git pull origin main
./start_blockchain.sh
```
👉 Cela **synchronise instantanément** le code source **sur tous les nœuds** !  

---

## 📜 **Journal de la Blockchain**  
Pour **suivre l'évolution** de la blockchain en temps réel :  
```bash
tail -f blockchain.log
```
### **Exemple de sortie :**
```
Index: 2
Previous Hash: 95451585e1b52755ebc3a4326e648cdd07b363c2384c5c31ac5a88746e7cc
Data: Transaction 2 : Bob → Charlie
Hash: 8231b613214993f9f5a5f43189e688ba6b4d42fad97846270f74af5f9c91c
Timestamp: 1742097262
---------------------------------
Connecté au pair 192.168.1.22:8080
```

---

## 👑 **Déploiement global de la blockchain**  
Pour **ajouter un nouveau nœud**, il suffit de :  
1️⃣ **Cloner le repo** :  
   ```bash
   git clone https://github.com/FoxtekTS/blockchain_cpp.git
   ```
2️⃣ **Lancer la blockchain** :  
   ```bash
   ./start_blockchain.sh
   ```
3️⃣ **Ajouter des pairs** :  
   ```cpp
   server.connectToPeer("IP_DU_NŒUD", 8080);
   ```

---

## 🎩 **Créateur**  
🚀 **FoxtekTS** aka **ZEROCOOL**  

💾 **Version actuelle** : `v1.2 P2P Matrix Edition`  
📅 **Mise à jour** : `16 Mars 2025`  
🔗 **GitHub** : [FoxtekTS/blockchain_cpp](https://github.com/FoxtekTS/blockchain_cpp)  

🔥 *Bienvenue dans le futur du P2P décentralisé* 🚀💾


















