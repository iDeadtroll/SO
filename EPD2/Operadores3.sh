echo "Sintaxis de operadores en 'bash'para 'Ficheros y Directorios'"
        echo "      operador        :           significado"
# Aniadimos elemento a elemento:
operadores[0]="-s file              : No es vacio "
operadores[1]="-f file              : Fichero existe o fichero normal y no directorio "
operadores[2]="-d dir               : Directorio existe y no es un fichero normal"
operadores[3]="-w file              : Se puede escribir en el fichero"
operadores[4]="-r file              : Fichero se puede solo leer"
operadores[5]="-x file              : Fichero se puede ejecutar"
echo "${#operadores[*]}" # Imprimimos el numero de elementos del array