# Caso Práctico 2: Regla Trapezoidal con comunicación punto a punto

CCC309 - Concurrencia y Sistemas Distribuidos | UNITEC

## Descripción

Este caso práctico aplica la comunicación punto a punto de MPI para calcular de forma distribuida una integral usando la **regla trapezoidal**.

| Versión | Archivo | Funciones principales |
|---|---|---|
| C | `Ex2_C/mpi_trapezoidal.c` | `MPI_Init`, `MPI_Comm_size`, `MPI_Comm_rank`, `MPI_Send`, `MPI_Recv`, `MPI_Wtime`, `MPI_Finalize` |
| Java | `Ex2_Java/TrapezoidalMPJ.java` | `MPI.Init`, `Rank`, `Size`, `Send`, `Recv`, `MPI.Finalize` |

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

Verificaciones útiles en PowerShell:

```powershell
java -version
javac -version
```


## Compilación y ejecución en C

Abrir **x64 Native Tools Command Prompt for VS 2022** y ejecutar:

```bash
cd C:\ruta-donde-este-el-ejemplo-2
```

Compilar:

```bash
cl /I"C:\Program Files (x86)\Microsoft SDKs\MPI\Include" mpi_trapezoidal.c /link /LIBPATH:"C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64" msmpi.lib /out:mpi_trapezoidal.exe
```

Ejecutar con 4 procesos:

```bash
mpiexec -n 4 mpi_trapezoidal.exe
```

Para comparar con diferente cantidad de procesos:

```bash
mpiexec -n 1 mpi_trapezoidal.exe
mpiexec -n 2 mpi_trapezoidal.exe
mpiexec -n 4 mpi_trapezoidal.exe
```

## Compilación y ejecución en Java con MPJ Express

Abrir la terminal de VS Code en PowerShell y ejecutar:

```powershell
$env:MPJ_HOME="C:\mpj\mpj-v0_44"
$env:PATH="$env:MPJ_HOME\bin;$env:PATH"
```

Entrar a la carpeta del caso:

```powershell
cd C:\ruta-donde-este-el-ejemplo-2-java
```

Compilar:

```powershell
javac -cp ".;$env:MPJ_HOME\lib\mpj.jar" TrapezoidalMPJ.java
```

Ejecutar con 4 procesos:

```powershell
mpjrun.bat -np 4 -cp . TrapezoidalMPJ
```

Si no reconoce la clase, probar:

```powershell
mpjrun.bat -np 4 TrapezoidalMPJ
```

## Archivos

```text
Ex2_C/mpi_trapezoidal.c          # Código fuente en C
Ex2_C/mpi_trapezoidal.exe        # Ejecutable compilado en Windows
Ex2_Java/TrapezoidalMPJ.java     # Código fuente en Java con MPJ Express
Ex2_Java/TrapezoidalMPJ.class    # Clase compilada de Java
```