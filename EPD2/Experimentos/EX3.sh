#!/bin/bash
if [ $# -eq 0 ];then # Se verifica si el numero de argumentos es 0
    echo "$0 : You must give/supply one integers"
    exit 1
fi

if test $1 -gt 0;then # Se verifica si el primer argumento es mayor que 0
    echo "$1 number is positive"
else
    echo "$1 number is negative"
fi