# Caso Práctico: Collective Communications con MPI

CCC309 - Concurrencia y Sistemas Distribuidos | UNITEC

## Descripción

Demostración de las funciones colectivas de MPI mediante tres operaciones con vectores, comparando rendimiento serial vs paralelo.

| Caso | Funciones MPI |
|---|---|
| Suma de Vectores | `MPI_Scatter` + `MPI_Gather` |
| Producto Punto | `MPI_Scatter` + `MPI_Reduce` |
| Multiplicación Ax=y | `MPI_Scatter` + `MPI_Allgather` + `MPI_Gather` |

## Requisitos

- Microsoft MPI: <https://www.microsoft.com/en-us/download/details.aspx?id=57467>
  - Instalar `msmpisetup.exe` (runtime)
  - Instalar `msmpisdk.msi` (SDK)
- Visual Studio 2022 (Build Tools)

## Compilación

Abrir **x64 Native Tools Command Prompt for VS** y ejecutar:

```bash
cl /EHsc /I "C:\Program Files (x86)\Microsoft SDKs\MPI\Include" vector_operations.cpp /link /LIBPATH:"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" msmpi.lib /out:vector_ops.exe
```

## Ejecución

```bash
# Correr con 4 procesos (recomendado)
mpiexec -n 4 vector_ops.exe

# Variar procesos para comparar tiempos
mpiexec -n 1 vector_ops.exe
mpiexec -n 2 vector_ops.exe
mpiexec -n 4 vector_ops.exe
```

## Archivos

```
vector_operations.cpp   # Código fuente principal

```
