# Caso Práctico 1: Hello World Paralelo con MPI

CCC309 - Concurrencia y Sistemas Distribuidos | UNITEC

## Descripción

Este caso práctico demuestra la estructura básica de un programa MPI usando el ejemplo clásico de **Hello World paralelo**.

|---|---|---|
| C | `Ex1_C/mpi_hello.c` | `MPI_Init`, `MPI_Comm_size`, `MPI_Comm_rank`, `MPI_Send`, `MPI_Recv`, `MPI_Finalize` |
| Java | `Ex1_Java/HelloMPJ.java` | `MPI.Init`, `Rank`, `Size`, `Send`, `Recv`, `MPI.Finalize` |

## Requisitos

### Para la versión en C

- Microsoft MPI:
  - Instalar `msmpisetup.exe` para ejecutar programas MPI.
  - Instalar `msmpisdk.msi` para tener `mpi.h` y las librerías.
- Visual Studio 2022 o Build Tools.
- Usar la terminal **x64 Native Tools Command Prompt for VS 2022**.

Verificaciones útiles:

```bash
where cl
where mpiexec
dir "C:\Program Files (x86)\Microsoft SDKs\MPI\Include\mpi.h"
```

### Para la versión en Java

- JDK instalado.
- MPJ Express descomprimido en:

```text
C:\mpj\mpj-v0_44
```

```powershell
java -version
javac -version
```

## Compilación y ejecución en C

Abrir **x64 Native Tools Command Prompt for VS 2022** y ejecutar:

```bash
cd C:\ruta-donde-este-el-ejemplo-1-C
```

Compilar:

```bash
cl /I"C:\Program Files (x86)\Microsoft SDKs\MPI\Include" mpi_hello.c /link /LIBPATH:"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" msmpi.lib /out:mpi_hello.exe
```

Ejecutar con 4 procesos:

```bash
mpiexec -n 4 mpi_hello.exe
```

## Compilación y ejecución en Java con MPJ Express

Abrir la terminal de VS Code en PowerShell y ejecutar:

```powershell
$env:MPJ_HOME="C:\mpj\mpj-v0_44"
$env:PATH="$env:MPJ_HOME\bin;$env:PATH"
```

Entrar a la carpeta del caso:

```powershell
cd C:\ruta-donde-este-el-ejemplo-1-java
```

Compilar:

```powershell
javac -cp ".;$env:MPJ_HOME\lib\mpj.jar" HelloMPJ.java
```

Ejecutar con 4 procesos:

```powershell
mpjrun.bat -np 4 -cp . HelloMPJ
```

Si no reconoce la clase, probar:

```powershell
mpjrun.bat -np 4 HelloMPJ
```

## Archivos

```text
Ex1_C/mpi_hello.c        # Código fuente en C
Ex1_C/mpi_hello.exe      # Ejecutable compilado en Windows
Ex1_Java/HelloMPJ.java   # Código fuente en Java con MPJ Express
Ex1_Java/HelloMPJ.class  # Clase compilada de Java
```