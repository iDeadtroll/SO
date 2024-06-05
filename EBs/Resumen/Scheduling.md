# Scheduling/Administración/Planificación

- **preemptive**: cuando un proceso esta en ejecución este ***se puede interrumpir***
- **nonpreemptive**: cuando un proceso esta en ejecución este **NO se puede interrumpir**

## CPU Scheduling


- **FCFS (First Come First Servered)**: los procesos se ejecutan según el orden de llegada (**nonpreemptive**)

- **SJF (Shortest Job First)**: se atiende primero a los procesos con el menor tiempo de ejecución estimado (**nonpreemptive**)
    * Si hay dos procesos con el mismo tiempo estimado se aplica FCFS.

- Asignación de **Prioridad** (la prioridad de un proceso aumenta al pasar el tiempo de espera):
    * **Preemptive**: un proceso puede ser interrumpido si llega otro con más prioridad
    * **NonPreemptive**: el nuevo proceso se coloca el primero en la ready queue

- **Round-Robin**: FCFS pero con un time quote (**preemptive**)

## Administración de Memoria

### Métodos de Administración:
- Intercambio: marcos de pagina (programas con pocas direcciones de memoria)
- Memoria Virtual: paginas virtuales (mas escalable que con marcos de pagina)

### Asignación de Memoria Dinámica:
- Mapa de bits: 0 si esta libre ó 1 si está ocupada.
- Listas libres: bit inicio, hueco disponible y bit de fin.

### Algoritmos de Asignación de Memoria:
- Primer ajuste: selecciona el primer marco de pagina con tamaño suficiente.
- Segundo ajuste: similar al primer ajuste, pero su búsqueda no inicia desde el principio.
- Mejor ajuste: selecciona el marco de pagina con el tamaño más cercano al que se va a cargar.
- Peor ajuste: selecciona el marco de pagina más grande disponible.
- Ajuste rápido: selecciona el marco de pagina libre buscando en una/s lista/s de huecos disponibles.

### Memoria Virtual: Paginación

- Tamaño(paginas) = Tamaño(marcos de paginas) <br> **dirección lógica**- - -**dirección física**

- La unidad de trasferencia es la pagina.
- Tabla de Paginas: permite la traducción de direcciones lógicas a direcciones físicas.
- Tabla de páginas Invertida: permite la traducción de direcciones lógicas a direcciones físicas de manera eficiente en términos de memoria, aunque con un mayor costo en la complejidad de la búsqueda y la traducción.
- TLB(Translation Lookaside Buffer): es una memoria caché especializada y sirve para acelerar el proceso de búsqueda en la tabla de páginas.

![Esquema de una tabla de páginas](https://github.com/iDeadtroll/SO/blob/main/EBs/Resumen/clipboard-image-1717574944.png)

## Funcionamiento del mecanismo de acceso TLB

Cuando la CPU genera una dirección virtual, esta se divide en dos partes: 
- Número de página
- Desplazamiento dentro de la página.

El número de página se utiliza como índice en la tabla de páginas para encontrar la entrada correspondiente.

- Antes de buscar en la tabla de páginas, el sistema operativo primero verifica si la entrada de la página está en el TLB.

- Si la entrada está en el TLB (un “acceso TLB”), entonces se utiliza la entrada del TLB para traducir la dirección virtual a una dirección física.

- Si la entrada no está en el TLB (un “fallo TLB”), entonces el sistema operativo debe buscar en la tabla de páginas en la memoria principal.

    * Una vez que se encuentra la entrada de la página en la tabla de páginas, se carga en el TLB para futuros accesos.

    * Finalmente, el desplazamiento se añade a la dirección base del marco de página para obtener la dirección física completa.

Este mecanismo permite un acceso rápido a las entradas de la tabla de páginas que se utilizan con frecuencia, mejorando así el rendimiento general del sistema

## Algoritmos para remplazo de páginas
- **Si hay un fallo de página**, el sistema  operativo tendrá que:
    * Escoger una pagina que desalojar de la memoria
    * Guardar la pagina escogida (si es necesario)
    * Cargar la pagina solicitada
- **Objetivo: minimizar el numero de fallos de pagina** 

### Algoritmo NRU (Not Recently Used)
- Las paginas tienen asociados dos **bits de estado R y M**
- Valor **inicial R y M es 0** en todas las pag.
    * Si se **referencia** la pag **R cambia a 1**
    * Si se **modifica** la pag **M cambia a 1**
- Cuando se necesita reemplazar una página, el algoritmo NRU selecciona al azar una página de la clase más baja que no esté vacía.
- El algoritmo NRU clasifica las páginas en cuatro categorías:
    * Clase 0: no referenciada, no modificada (0,0)
    * Clase 1: no referenciada, modificada (0,1)
    * Clase 2: referenciada, no modificada (1,0)
    * Clase 3: referenciada, modificada (1,1)

### Algoritmo FIFO (First-In First-Out)
- Cuando se produce un fallo de página y todas las páginas están en uso, el sistema operativo **selecciona la página que se cargó primero (mas antigua)** y la **reemplaza con la nueva página**.
- Puede llevar a un número elevado de fallos de página.

### Algoritmo de Segunda Oportunidad
- Es una **modificion del algoritmo FIFO**
- **Antes de desalojar** la pag más antigua **se examina el bit R**
    * **Si R = 0**, --> la pag es antigua
        + Se desaloja la pag
    * **Si R = 1**, --> segunda oportunida
        + Se pone el bit a 0
        + Se toma como si fuera una nueva pag
        + Continua la busqueda

### Algoritmo tipo reloj
![Algoritmo tipo reloj](https://github.com/iDeadtroll/SO/blob/main/EBs/Resumen/clipboard-image-1717578215.png)

### Algoritmo LRU (Least Recently Used)
Algoritmo es más eficiente que FIFO y NRU porque tiene en cuenta la frecuencia de uso de las páginas.

- Reemplaza la página que no se ha utilizado durante más tiempo.
- Se mantiene una lista de todas las páginas en memoria, ordenadas por el momento en que fueron accedidas por última vez.
    * Si se produce un fallo de página, el sistema operativo reemplaza la página que está al final de esta lista
    * Se actualiza la lista de paginas.

## Planificacion de Disco

Si tenemos una cola de solicitudes de disco de [98, 183, 37, 122, 14, 124, 65, 67] y la cabeza de lectura/escritura actualmente está en la pista 53, entonces:

### FIFO
También conocido como FCFS (First Come First Served). Este es uno de los algoritmos más simples. Funciona según el principio de atender las solicitudes de acceso al disco en el orden en que se reciben.

**Ejemplo:**
98, 183, 37, 122, 14, 124, 65, 67

### SSTF (Shortest Seek Time First)
Este algoritmo selecciona la solicitud con el tiempo de búsqueda más corto a partir de la posición actual de la cabeza de lectura/escritura.

**Ejemplo:**
La cabeza de lectura/escritura atendería primero la solicitud más cercana a la pista 53, que sería 65. Luego las mas cercana a la 65, que seria la 67....hasta llegar a la ultima.

### SCAN
También conocido como el algoritmo del elevador
- La cabeza de lectura/escritura se mueve de un extremo del disco al otro, atendiendo solicitudes hasta que llega al final del disco. 
- Luego la dirección del movimiento se invierte y el proceso se repite.

**Ejemplo:**
Si la cabeza de lectura/escritura se está moviendo hacia arriba, atendería las solicitudes en el orden de 65, 67, 98, 122, 124, 183. Luego cambiaría de dirección y atendería 37 y 14.

### C-SCAN (Circular SCAN)
Similar al SCAN, pero en lugar de invertir la dirección al final del disco, la cabeza de lectura/escritura vuelve al principio y repite el proceso.

**Ejemplo:**
En C-SCAN, la cabeza de lectura/escritura atendería las solicitudes en el orden de 65, 67, 98, 122, 124, 183. Luego volvería al principio y atendería 14 y 37.

### LOOK y C-LOOK
Son versiones optimizadas de SCAN y C-SCAN respectivamente. En lugar de ir hasta el final del disco, la cabeza de lectura/escritura solo va hasta el último pedido en la dirección en la que se está moviendo.

**Ejemplo en LOOK**

Si la cabeza de lectura/escritura se está moviendo hacia arriba, atendería las solicitudes en el orden de 65, 67, 98, 122, 124, 183. Luego cambiaría de dirección y atendería 37.

**Ejemplo en C-LOOK**

la cabeza de lectura/escritura atendería las solicitudes en el orden de 65, 67, 98, 122, 124, 183. Luego volvería al principio y atendería 14.
