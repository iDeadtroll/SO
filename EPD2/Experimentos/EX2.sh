#!/bin/sh

expr 1 + 3 # Se ejecuta el comando expr y se muestra la suma
echo $? # Muestra el codigo de salida del comando anterior (0)
echo Welcome # Se ejecuta sin problem
echo $? # Muestra el codigo de salida del comando anterior (0)
wildwest canwork? # No es posible ejecutar el comando
echo $? # Muestra el codigo de salida del comando anterior (127)
date  # Se ejecuta sin problem
echo $? # Muestra el codigo de salida del comando anterior (0)
echon $? # No es posible ejecutar el comando 
echo $? # Muestra el codigo de salida del comando anterior (127)