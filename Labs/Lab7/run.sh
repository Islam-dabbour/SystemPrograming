#!/bin/bash

echo "================================"
echo " Compiling Client and Server"
echo "================================"

read -p "Enter the port number for the server: " PORT
gcc server.c -o server


gcc client.c -o client


echo "[+] Compilation successful."



echo "[+] Starting server on port $PORT..."
./server $PORT &

echo "[+] Waiting for server to start..."


echo "[+] Starting client..."
./client $PORT

echo "[+] Client finished."
