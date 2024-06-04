# Scheduling/Planificación/Administración

- **preemptive**: cuado un proceso esta en ejecucion este ***se puede interrumpir***
- **nonpreemptive**: cuado un proceso esta en ejecucion este **NO se puede interrumpir**

## CPU Scheduling


- **FCFS (First Come First Servered)**: los procesos se ejecutan segun el orden de llegada (**nonpreemptive**)

- **SJF (Shortest Job First)**: se atiende primero a los procesos con el menor tiempo de ejecucion estimado (**nonpreemptive**)
    * Si hay dos procesos con el mismo tiempo estimado se aplica FCFS.

- Asignacion de **Prioridad** (la prioridad de un proceso aumenta al pasar el tiempo de espera):
    * **Preemptive**: un proceso puede ser interrumpido si llega otro con más prioridad
    * **NonPreemptive**: el nuevo proceso se coloca el primero en la ready queue

- **Round-Robin**: FCFS pero con un time quote (**preemptive**)
