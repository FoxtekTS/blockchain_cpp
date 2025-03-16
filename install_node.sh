#!/bin/bash
echo "🚀 Installation d'un nouveau nœud blockchain..."
git clone https://github.com/FoxtekTS/blockchain_cpp.git
cd blockchain_cpp
./start_blockchain.sh
echo "✅ Nœud en ligne et synchronisé !"
