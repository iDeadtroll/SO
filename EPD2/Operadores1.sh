#!/bin/bash
# Uso de operadores
echo "Sintaxis de operadores en 'bash'para 'Matematicas'"
        echo "operador  : significado"
# Aniadimos elemento a elemento:
operadores[0]="-eq      :   == "
operadores[1]="-ne      :   != "
operadores[2]="-lt      :   <  "
operadores[3]="-le      :   <= "
operadores[4]="-gt      :   >  "
operadores[5]="-ge      :   >= "

for i in "${operadores[@]}"; #Imprimimos elementos del array
do
        echo "$i"
done

echo "${#operadores[*]}" #Imprimimos numero de elementos del array