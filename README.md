# DistributedMemoryProgrammingWithMPI
Para la clase de concurrencia y sistemas distrubuidos, grupo 4

Comando para correr vector_operations.cpp

mpic++ -o vector_ops vector_operations.cpp

## Caso 4: Data Partitioning y Performance Analysis

El archivo `vector_operations.cpp` incluye una opcion 4 para explicar:

- Data partitioning: el arreglo se divide en bloques y cada proceso trabaja solo su rango.
- Performance analysis: se compara tiempo serial vs MPI, speedup y eficiencia.

Ejecutar:

```bash
mpiexec -n 4 vector_ops
```

Luego seleccionar la opcion `4` en el menu.
