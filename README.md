# ⚡ FoxtekTS Blockchain P2P ⚡  
🚀 _Une blockchain C++ entièrement personnalisée et décentralisée_

## 📌 Description  
FoxtekTS Blockchain est un projet **open-source** développé en C++ avec Boost Asio pour la mise en réseau **P2P**.  
Il permet la création d’un réseau décentralisé où les nœuds s’échangent et valident des blocs de transactions **sans point central**.  

### 🔗 Caractéristiques :
- ✅ Implémentation **P2P complète** avec découverte dynamique des pairs  
- ✅ Sécurisation avec **OpenSSL (SHA256)**  
- ✅ Synchronisation automatique des blocs entre les nœuds  
- ✅ Compatible **Linux, Windows (WSL) et Android (Termux)**  

---

## 🚀 Installation  

### 🔹 1. Cloner le dépôt  

git clone https://github.com/FoxtekTS/blockchain_cpp.git
cd blockchain_cpp

### 🔹 2. Installer les dépendances
### 🔹 Linux / WSL

sudo apt update && sudo apt install -y g++ build-essential libssl-dev libboost-all-dev

### 🔹 Termux (Android)
pkg update && pkg install -y clang boost boost-static openssl

### 🔹 3. Compiler
g++ -o build/blockchain src/main.cpp src/network.cpp -Iinclude -lssl -lcrypto -lpthread -lboost_system

### 🔹 4. Lancer un nœud
nohup ./build/blockchain > blockchain.log 2>&1 &
disown

### 📡 Connexion des nœuds
Chaque nœud peut se connecter à un autre en lançant :
connectToPeer("192.168.X.X", 8080);

Pour vérifier les connexions actives :
ss -tulnp | grep 8080

### 🛠 Contributions
👾 Hackers & Développeurs bienvenus ! Forkez ce repo et proposez vos améliorations !
💬 Rejoignez la discussion sur GitHub Issues !

### 📜 Licence
🛡️ Ce projet est sous licence MIT, vous êtes libre de l’utiliser et de le modifier.

### 🔥 FoxtekTS : L’avenir du P2P est entre tes mains ! 🔥
