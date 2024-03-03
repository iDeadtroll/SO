#!/bin/bash

while true; 
do
    clear
    echo "----------Menu Principal------------"
    echo "[1] Mostrar la fecha y la hora en el formato ddmmaahh"
    echo "[2] Mortrar archivos en el directorio actual"
    echo "[3] Mostrar calendario"
    echo "[4] Iniciar editor"
    echo "[5] Salir"

    read -p "Introduce una opcion: " opcion

    case $opcion in
    1) date +'%D %H:%M' ;;
    2) ls ;;
    3) cal ;;
    4) nano ;;
    5) break ;;
    *) echo "Opcion invalida!" ;;
    esac

    read -p "Presiona [Enter] para continuar..."
done
