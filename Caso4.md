# Caso Practico 4: Data Partitioning y Performance Analysis con MPI

CCC309 - Concurrencia y Sistemas Distribuidos | UNITEC
JONNY ALEJANDRO GOMEZ CARTAGENA - 22311176

## Descripcion

Este caso muestra una forma sencilla de repartir datos entre procesos y medir el rendimiento de la solucion paralela.

El programa divide un arreglo de `10,000,000` elementos en bloques. Cada proceso calcula la suma de su propio bloque y al final `MPI_Reduce` une todas las sumas locales.

## Conceptos usados

| Tema | Explicacion corta |
|---|---|
| Data Partitioning | Los datos se dividen en rangos continuos. Por ejemplo, con 4 procesos cada uno trabaja una parte del arreglo. |
| Performance Analysis | Se mide el tiempo serial, el tiempo con MPI, el speedup y la eficiencia. |
| MPI_Reduce | Une las sumas parciales de todos los procesos en un solo resultado final. |

## Formula del reparto

```cpp
base = n / size;
resto = n % size;
local_n = base + (rank < resto ? 1 : 0);
inicio = rank * base + min(rank, resto);
fin = inicio + local_n - 1;
```

## Como explicarlo en la exposicion

1. El arreglo grande no lo trabaja un solo proceso.
2. Cada proceso recibe un rango de indices.
3. Cada proceso suma solamente su parte.
4. `MPI_Reduce` junta los resultados.
5. Se comparan los tiempos para ver si MPI fue mas rapido.

## Compilacion y ejecucion

```bash
mpic++ -o vector_ops vector_operations.cpp
mpiexec -n 4 vector_ops
```

Luego seleccionar la opcion `4`.

## Salida esperada

```text
[DATA PARTITIONING] n=10000000 dividido en 4 procesos
Proceso 0 -> indices 0 a 2499999
Proceso 1 -> indices 2500000 a 4999999
Proceso 2 -> indices 5000000 a 7499999
Proceso 3 -> indices 7500000 a 9999999
[PERFORMANCE] Serial: ... ms | MPI: ... ms | Speedup: ...x | Eficiencia: ...%
```
