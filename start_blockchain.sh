#!/bin/bash
echo "🔍 Vérification du port 8080..."
PID=$(sudo lsof -ti :8080)
if [ ! -z "$PID" ]; then
    echo "❌ Port occupé par PID $PID, arrêt du processus..."
    sudo kill -9 $PID
else
    echo "✅ Port libre."
fi

echo "🚀 Lancement de la blockchain..."
nohup ./build/blockchain > blockchain.log 2>&1 &
disown
echo "✅ Blockchain lancée avec succès !"
