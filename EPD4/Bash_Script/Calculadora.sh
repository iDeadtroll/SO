#!/bin/bash

calcu() {
    if [ $# -ne 3 ]; then
        echo "Error: se necesitan 3 argumentos"
        exit 1
    fi
    local num1=$1
    local op=$2
    local num2=$3

    case $op in
        +) echo "$num1 + $num2 = $(($num1 + $num2))";;
        -) echo "$num1 - $num2 = $(($num1 - $num2))";;
        /) echo "$num1 / $num2 = $(($num1 / $num2))";;
        *) echo "Operador no válido: $op";;
    esac
}
# Verificar si se proporcionaron argumentos
if [ $# -eq 0 ]; then
    echo "No se proporcionaron argumentos"
    exit 1
fi
calcu "$@" #Aseguramos que se pasan todos los argumentos al Script