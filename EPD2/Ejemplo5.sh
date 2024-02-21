#!/bin/bash
# Comprobar si un argumento es positivo 2
if test $1 -gt 0
then 
echo "$1 es un numero positivo"
else 
echo "$1 es un numero negativo"
fi