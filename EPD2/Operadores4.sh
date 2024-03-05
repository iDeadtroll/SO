echo "Sintaxis de operadores lógicos en 'bash'para combinar dos o mas condiciones a la vez"
        echo "      operador       :           significado"
# Aniadimos elemento a elemento:
operadores[0]="! expression         : not "
operadores[1]="expr1 -a expr2       : and "
operadores[2]="expr1 -o expr2       : or  "

for i in "${operadores[@]}"; #Imprimimos elementos del array
do
        echo "$i"
done

echo "${#operadores[*]}" # Imprimimos el numero de elementos del array