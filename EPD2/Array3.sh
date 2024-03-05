echo "Declaracion y operaciones con arrays"
echo -n "Array con elementos: "
array3=(1 2 3 4 5 6 7 8 $(date +%r))
echo "${array3[@]}"

echo "Agregar elementos al final:"
array3=("${array3[@]}" "adios")
array3+=("mundo")
echo "${array3[@]}"

echo "Agregar elementos al inicio:" 
array3=("0" "${array3[@]}")
array3=("hola" "mundo" "${array3[@]}")
echo "${array3[@]}"

echo "Eliminar elementos por indice:"
unset array3[11]
array=("${array3[@]}")
echo "${array3[@]}"

echo "Eliminar primer elemento:"
unset array3[0]
array3=("${array3[@]}")
echo "${array3[@]}"

echo "Eliminar ultimo elemento:"
ultimo=$(expr ${#array3[@]} - 1)
unset array3[$ultimo]
array3=("${array3[@]}")
echo "${array3[@]}"
