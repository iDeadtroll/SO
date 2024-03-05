echo "Declaracion y operaciones con arrays"
echo "Array vacio:"
array2=()
echo ${#array2[@]}
echo ${array2[@]}

dia=$(date +%D)
hora=$(date +%h:%m)

echo "Agregar elementos al final del array"
array2=11
array2=("${array2[@]}" 55)
array2=("${array2[@]}" "hola")
array2+=("$dia")
array2+=("$hora")

echo ${#array2[@]}
echo ${array2[@]}

echo "Agregar elementos al principio del array"
array2=22
array2=("33" ${array2[@]})
array2=("adios" "${array2[@]}")

echo ${#array2[@]}
echo ${array2[@]}