#!/bin/bash
# Uso de operadores
echo "Sintaxis de operadores en 'bash'para comparar 'Cadenas'"
        echo "      operador        :           significado"
# Aniadimos elemento a elemento:
operadores[0]="string1 = string2    : string1 es igual a string2 "
operadores[1]="string1 != string2   : string1 no es igual a string2 "
operadores[2]="string1              : no es NULL o no definida"
operadores[3]="-n string1           : string1 no es NULL y existe"
operadores[4]="-z string1           : string1 es NULL y existe"
echo "${#operadores[@]}" # Imprimimos el numero de elementos del array