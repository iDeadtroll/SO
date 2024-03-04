#!/bin/bash

name="joni"
pass="asdf1234"

cont=3
read -p "Introduzca su nombre de usuario: " nombre1
while [[ "$nombre1" != "$name" ]] && [[ $cont>0 ]];
do
    echo "Usuario '$nombre1' no existe. Intente otra vez ( Intentos restantes [$cont] )"
    read  -p "Nombre de usuario: " nombre2
    nombre1=$nombre2
    ((cont--))
done
if [[ "$nombre1" != "$name" ]] && [[ $cont==0 ]];then
    echo "Usuario '$nombre1' no existe. Intentos restantes [0]"
    exit 1;
else
    echo "Bienvenido $nombre1"
fi











