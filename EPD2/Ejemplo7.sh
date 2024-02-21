#!/bin/bash
# Funcionalidad de 'case' usando if, elif y else:

echo "Introduce 'start', 'stop', 'restart':"
read action

if [ $action == 'start' ]
then
echo "Iniciando el sistema..."
elif [ $action == 'stop' ]
then
echo "Deteniendo el sistema..."
elif [ $action == 'restart' ]
then 
echo "Reiniciando el sistema..."
else
echo "Accion no reconocida: $action"
fi