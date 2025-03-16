#!/bin/bash

# Liste des machines à mettre à jour
MACHINES=("192.168.1.22" "192.168.1.17" "192.168.1.13")

# Parcours chaque machine et met à jour le code source
for MACHINE in "${MACHINES[@]}"; do
    echo "🚀 Mise à jour de la machine $MACHINE..."
    ssh -p 22 user@$MACHINE "cd ~/blockchain_cpp && git pull origin main && make"
done

echo "✅ Mise à jour terminée sur toutes les machines."
