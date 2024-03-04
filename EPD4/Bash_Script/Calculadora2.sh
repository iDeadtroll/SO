#!/bin/bash

calcu() {


    num1=$1
    op=$2
    num2=$3
    producto=$(expr $num1 \* $num2)

    case $op in
    +) echo "$num1 + $num2 = $(($num1 + $num2))" ;;
    -) echo "$num1 - $num2 = $(($num1 - $num2))" ;;
    /) echo "$num1 / $num2 = $(($num1 / $num2))" ;;
    x) echo "$num1 x $num2 = $producto" ;;
    *) echo "Error: Operador $op no validado" ;;
    esac
}

if [ $# -eq 0 ]; then
    echo "Error: no se proporcionaron argumentos"
    exit 1;
fi

if [ $# -ne 3 ]; then
    echo "Error: Se necesitan 3 argumentos"
    exit 1;
fi

if [[ $1 =~ ^[0-9]+$ ]] && [[ $3 =~ ^[0-9]+$ ]];then
    calcu "$@"
    exit 0;
else
    echo "Error: argumento '$1' ó '$3' no es numero."
    exit 1;
fi
