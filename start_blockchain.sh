#!/bin/bash

echo "🔍 Vérification du port 8080..."
PORT=8080
PID=$(sudo lsof -t -i:$PORT)

if [ -n "$PID" ]; then
    echo "❌ Port $PORT occupé par PID $PID, arrêt du processus..."
    sudo kill -9 $PID
    sleep 2
fi

echo "🚀 Lancement de la blockchain..."
nohup ./build/blockchain > blockchain.log 2>&1 &
echo "✅ Blockchain lancée avec succès !"

