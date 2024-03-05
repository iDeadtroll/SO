echo "Declaracion y operaciones con arrays"
echo "Array vacio:"
declare -a array1
echo ${array1[@]} # Mostrar elementos del array
echo ${#array1[@]} # Mostrar numero de elementos del array

dia=$(date +%D)
hora=$(date +%r)

echo "Agregar elementos al array" # Especificando indice
array1[1]="hola"
array1[0]=$dia
array1[4]=5
array1[2]=$hora

echo ${array1[@]}
echo ${#array1[@]}
echo ${array1[4]}
