#!/bin/bash

echo "[1] Me gustan mas las clases de teoria"
echo "[2] Me gustan mas las clases de practica"

read -p "Selecciona una opcion: " opcion

if [[ $opcion =~ ^[0-9]+$ ]]; then
    if [[ $opcion == 1 ]];then
        echo "Te gusta mas las clases de toeoria"
    elif [[ $opcion == 2 ]]
        echo "Te gusta mas las clases de practica"
    else
        echo "No te gusta nada"
    fi
        
else
    echo "Error: Opcion invalida!"
fi
