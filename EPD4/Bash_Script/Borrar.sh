#!/bin/bash

borrar() {
    if [ $# -ne 1 ]; then
        echo "Error: se necesita un argumento"
        exit 1
    fi

    local archivo=$1
    local trash_dir="Trash"

    if [ ! -d "$trash_dir" ]; then
        mkdir "$trash_dir"
    fi

    local archivo_destino="$trash_dir/$archivo"
    if [ ! -e $archivo ]; then
        echo "Error: $archivo no existe"
        exit 1
    else
        if [ -e "$archivo_destino" ]; then
            local fecha=$(date +'%d%m%y %r')
            archivo_destino="$archivo_destino.$fecha"
        fi
        mv "$archivo" "$archivo_destino"
        exit 0
    fi

}
if [ $# -eq 0 ]; then
    echo "Error: no se proporcionó ningun argumento"
    exit 1
fi
borrar "$@"
