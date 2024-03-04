#!/bin/bash

echo "Escriba un nombre: "
read name
echo "Bienvenido $name"

while true; 
do
    echo "----Menu Principal----"
    echo "[1] Mostrar fecha actual"
    echo "[2] Mostrar contenido del directorio actual"
    echo "[3] Mostrar calendario"
    echo "[4] Salir"

    read -p "Seleccione una opcion: " opcion

    case $opcion in
        1) date +'%D %r';;
        2) ls;;
        3) cal;;
        4) echo "Adios"
            break;;
        *) echo "Opcion invalida";;
    esac

    read -p "Precione [enter] para continuar..."

done 
