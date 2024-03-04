#!/bin/bash
echo "Permisos de usuario, grupo, otros"
lista=("--- | 0" "--x | 1" "-w- | 2" "-wx | 3" "r-- | 4" "r-x | 5" "rw- | 6" "rwx | 7")
for i in "${lista[@]}";
do
    echo "$i"
done