#!/bin/bash

calcu() {
    local num1=$1
    local op=$2
    local num2=$3

    case $op in
    +) echo "$num1 + $num2 = $(($num1 + $num2))" ;;
    -) echo "$num1 - $num2 = $(($num1 - $num2))" ;;
    /) echo "$num1 / $num2 = $(($num1 / $num2))" ;;
    *)
        echo "Operador no válido: $op"
        exit 1
        ;;
    esac
}
# Verificar si se proporcionaron argumentos
if [ $# -eq 0 ]; then
    echo "No se proporcionaron argumentos"
    exit 1
fi

if [ $# -ne 3 ]; then
    echo "Error: se necesitan 3 argumentos"
    exit 1
fi

if [[ $1 =~ ^[0-9]+$ && $3 =~ ^[0-9]+$ ]]; then # Verificamos que $1 o $2 sean numeros
    calcu "$@" #Aseguramos que se pasan todos los argumentos al Script
    exit 0
else
    echo "Error: algun argumento '$1' ó '$3',no es valido. Intente con [0-9]"
    exit 1
fi