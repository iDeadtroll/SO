#!/bin/bash
name="joni"
pass="1234"
read -p "Introduzca su nombre de usuario: " nombre
if [[ "$nombre" != "$name" ]]; then
    echo "El usuario no existe"
    exit 1;
fi
read -p "Introduzca su contraseña: " contrasenia
if [[ "$pass" != "$contrasenia" ]]; then
    echo "Contraseña incorrecta"
    exit 1;
fi

echo "Bienvenido $name"