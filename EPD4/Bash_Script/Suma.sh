#!/bin/bash

suma() {
    suma=0
    for num in "$@"; do # Recorremos los argumentos
        if [[ $num =~ ^[0-9]+$ ]]; then #Si el argumento actual es numero lo sumamos
            ((suma+=$num))
        else 
            echo "$num no es un número"
            exit 1;
        fi
    done 
    echo "suma = $suma"   
}
if [ $# -eq 0 ]; then
    echo "Error: no hay parametros"
    exit 1;
fi

if [[ $# > 1 && $# < 5 ]];then 
    suma "$@" # Invocamos a la funcion y pasamos todos los argumentos a suma
    exit 0;
else
    echo "Error: Numero de parametros incorrecto"
    exit 1;
fi
