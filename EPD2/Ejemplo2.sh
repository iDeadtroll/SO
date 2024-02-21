#!/bin/bash

# Matematica en Shell Script

#Probar en Consola

# expr 1 + 3
# expr 2 – 1
# expr 10 / 2
# expr 20 % 3 (modulo)
# expr 10 \* 3 (multiplicación)
# Primero se ejecuta lo que esta dentro del parentesis y luego se guarda en la variable 'suma'
suma=$(expr 6 + 3) 
echo "suma 6 + 3 = $suma"
