#!/bin/bash
echo "🚀 Installation d'un nouveau nœud blockchain..."
sudo apt update
sudo apt install -y build-essential libboost-system-dev libssl-dev libboost-all-dev python3 libncurses5-dev tor
git clone https://github.com/FoxtekTS/blockchain_cpp.git
cd blockchain_cpp
./start_blockchain.sh
echo "✅ Nœud en ligne et synchronisé !"
