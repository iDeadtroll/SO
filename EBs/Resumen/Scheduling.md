# Scheduling/Planificación/Administración

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



