#!/bin/bash

echo "================================"
echo " Compiling Client and Server"
echo "================================"

gcc server.c -o server


gcc client.c -o client


echo "[+] Compilation successful."

PORT=5000

echo "[+] Starting server on port $PORT..."
./server $PORT &

echo "[+] Waiting for server to start..."
sleep 2

echo "[+] Starting client..."
./client $PORT

echo "[+] Client finished."