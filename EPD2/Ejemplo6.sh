#!/bin/bash
# Uso de 'case' en bash
echo "Introduce 'start', 'stop' o 'restart':"
read action

case $action in
    start)
        echo "Iniciando el sistema..." ;;
    stop)
        echo "Deteniendo el sistema..." ;;
    restart)
        echo "Reiniciando el sistema..." ;;
    *)
        echo "Acción no reconocida: $action" ;;
esac