#!/bin/bash

read -p "Introduzca su nombre de usuario: " nombre1

name="joni"
cont=3

while [[ "$nombre1" != "$name" ]] && [[ $cont>0 ]];
do
    echo "Usuario '$nombre1' no existe. Intente de nuevo (intentos restantes [$cont])"
    read -p "Nombre de usuario: " nombre2
    nombre1=$nombre2
    ((cont--))
done

if [[ "$nombre1" != "$name" ]] && [[ $cont==0 ]];then
    echo "Usuario '$nombre1' no existe. Intentos restantes [$cont]"
    exit 1;
else
    read -p "Introduce la contraseña: " password1

    pass="asdf1234"
    cont=1

    while [[ "$password1" != "$pass" ]] && [[ $cont>0 ]];
    do
        echo "Contraseña incorrecta. Intente de nuevo (Intentos restantes [$cont])"
        read -p "Contraseña: " password2
        password1=$password2
        ((cont--))
    done

    if [[ "$password1" != "$pass" ]] && [[ $cont==0 ]];then
        echo "Contraseña incorrecta. Intentos restantes [$cont]"
        exit 1;
    else
        echo "Bienvenido $nombre1"
        echo ""
    fi
fi


