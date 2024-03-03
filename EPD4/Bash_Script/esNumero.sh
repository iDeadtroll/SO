#!/bin/bash

esNumero() {

    for num in "$@"; do
        if [[ $num =~ ^[0-9]+$ ]]; then
            echo "$num es un número"
        else 
            echo "$num no es un número"
        fi
    done    
}

esNumero "$@"