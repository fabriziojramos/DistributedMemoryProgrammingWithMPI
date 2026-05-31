#include <mpi.h>
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

// ============================================================
// CASO 1: Suma de vectores - SIN MPI (serial)
// ============================================================
void sumaVectoresSerial()
{
    const int n = 10000000;
    vector<double> x(n), y(n), z(n);

    for (int i = 0; i < n; i++)
    {
        x[i] = i + 1;
        y[i] = 1.0;
    }

    auto start = high_resolution_clock::now();
    for (int i = 0; i < n; i++)
        z[i] = x[i] + y[i];
    auto end = high_resolution_clock::now();

    double ms = duration<double, milli>(end - start).count();
    cout << "[SERIAL] Suma de Vectores n=" << n << " | Tiempo: " << ms << " ms" << endl;
    cout << "         Primeros resultados: " << z[0] << " " << z[1] << " " << z[2] << " ..." << endl;
}

// ============================================================
// CASO 1: Suma de vectores - CON MPI (paralelo)
// ============================================================
void sumaVectoresMPI(int rank, int size)
{
    const int n = 10000000;
    int local_n = n / size;

    vector<double> x(n), y(n), z(n);
    vector<double> local_x(local_n), local_y(local_n), local_z(local_n);

    if (rank == 0)
        for (int i = 0; i < n; i++)
        {
            x[i] = i + 1;
            y[i] = 1.0;
        }

    double start = MPI_Wtime();

    MPI_Scatter(x.data(), local_n, MPI_DOUBLE, local_x.data(), local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(y.data(), local_n, MPI_DOUBLE, local_y.data(), local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int i = 0; i < local_n; i++)
        local_z[i] = local_x[i] + local_y[i];

    MPI_Gather(local_z.data(), local_n, MPI_DOUBLE, z.data(), local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double end = MPI_Wtime();

    if (rank == 0)
    {
        double ms = (end - start) * 1000.0;
        cout << "[MPI]    Suma de Vectores n=" << n << " | Procesos: " << size << " | Tiempo: " << ms << " ms" << endl;
        cout << "         Primeros resultados: " << z[0] << " " << z[1] << " " << z[2] << " ..." << endl;
    }
}

// ============================================================
// CASO 2: Dot Product - SIN MPI (serial)
// ============================================================
void dotProductSerial()
{
    const int n = 10000000;
    vector<double> x(n), y(n);

    for (int i = 0; i < n; i++)
    {
        x[i] = i + 1;
        y[i] = 1.0;
    }

    auto start = high_resolution_clock::now();
    double total = 0.0;
    for (int i = 0; i < n; i++)
        total += x[i] * y[i];
    auto end = high_resolution_clock::now();

    double ms = duration<double, milli>(end - start).count();
    cout << "[SERIAL] Dot Product n=" << n << " | Tiempo: " << ms << " ms" << endl;
    cout << "         Resultado: " << total << endl;
}

// ============================================================
// CASO 2: Dot Product - CON MPI (paralelo)
// ============================================================
void dotProductMPI(int rank, int size)
{
    const int n = 10000000;
    int local_n = n / size;

    vector<double> x(n), y(n);
    vector<double> local_x(local_n), local_y(local_n);

    if (rank == 0)
        for (int i = 0; i < n; i++)
        {
            x[i] = i + 1;
            y[i] = 1.0;
        }

    double start = MPI_Wtime();

    MPI_Scatter(x.data(), local_n, MPI_DOUBLE, local_x.data(), local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(y.data(), local_n, MPI_DOUBLE, local_y.data(), local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double local_dot = 0.0, total_dot = 0.0;
    for (int i = 0; i < local_n; i++)
        local_dot += local_x[i] * local_y[i];

    MPI_Reduce(&local_dot, &total_dot, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    double end = MPI_Wtime();

    if (rank == 0)
    {
        double ms = (end - start) * 1000.0;
        cout << "[MPI]    Dot Product n=" << n << " | Procesos: " << size << " | Tiempo: " << ms << " ms" << endl;
        cout << "         Resultado: " << total_dot << endl;
    }
}

// ============================================================
// CASO 3: Multiplicacion Matriz-Vector - SIN MPI (serial)
// ============================================================
void matrizVectorSerial()
{
    const int n = 4000;
    vector<double> A(n * n, 1.0);
    vector<double> x(n), y(n, 0.0);

    for (int i = 0; i < n; i++)
        x[i] = i + 1;

    auto start = high_resolution_clock::now();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            y[i] += A[i * n + j] * x[j];
    auto end = high_resolution_clock::now();

    double ms = duration<double, milli>(end - start).count();
    cout << "[SERIAL] Matriz-Vector " << n << "x" << n << " | Tiempo: " << ms << " ms" << endl;
    cout << "         Primeros resultados: " << y[0] << " " << y[1] << " " << y[2] << " ..." << endl;
}

// ============================================================
// CASO 3: Multiplicacion Matriz-Vector - CON MPI (paralelo)
// ============================================================
void matrizVectorMPI(int rank, int size)
{
    const int n = 4000;
    int local_n = n / size;

    vector<double> x(n);
    vector<double> local_x(local_n);
    vector<double> x_full(n);
    vector<double> local_A(local_n * n, 1.0);
    vector<double> local_y(local_n, 0.0);

    if (rank == 0)
        for (int i = 0; i < n; i++)
            x[i] = i + 1;

    double start = MPI_Wtime();

    MPI_Scatter(x.data(), local_n, MPI_DOUBLE, local_x.data(), local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Allgather(local_x.data(), local_n, MPI_DOUBLE, x_full.data(), local_n, MPI_DOUBLE, MPI_COMM_WORLD);

    for (int i = 0; i < local_n; i++)
    {
        local_y[i] = 0.0;
        for (int j = 0; j < n; j++)
            local_y[i] += local_A[i * n + j] * x_full[j];
    }

    vector<double> y(n);
    MPI_Gather(local_y.data(), local_n, MPI_DOUBLE, y.data(), local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double end = MPI_Wtime();

    if (rank == 0)
    {
        double ms = (end - start) * 1000.0;
        cout << "[MPI]    Matriz-Vector " << n << "x" << n << " | Procesos: " << size << " | Tiempo: " << ms << " ms" << endl;
        cout << "         Primeros resultados: " << y[0] << " " << y[1] << " " << y[2] << " ..." << endl;
    }
}

// ============================================================
// MENU PRINCIPAL
// ============================================================
int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int opcion = 0;

    do
    {
        if (rank == 0)
        {
            cout << "\n===== Comparacion Serial vs MPI (procesos activos: " << size << ") =====" << endl;
            cout << "1. Suma de Vectores     (n=10,000,000)" << endl;
            cout << "2. Producto Punto       (n=10,000,000)" << endl;
            cout << "3. Multiplicacion Ax=y  (matriz 4000x4000)" << endl;
            cout << "0. Salir" << endl;
            cout << "Seleccione una opcion: ";
            cin >> opcion;
        }

        MPI_Bcast(&opcion, 1, MPI_INT, 0, MPI_COMM_WORLD);

        switch (opcion)
        {
        case 1:
            if (rank == 0)
                sumaVectoresSerial();
            MPI_Barrier(MPI_COMM_WORLD);
            sumaVectoresMPI(rank, size);
            break;
        case 2:
            if (rank == 0)
                dotProductSerial();
            MPI_Barrier(MPI_COMM_WORLD);
            dotProductMPI(rank, size);
            break;
        case 3:
            if (rank == 0)
                matrizVectorSerial();
            MPI_Barrier(MPI_COMM_WORLD);
            matrizVectorMPI(rank, size);
            break;
        case 0:
            if (rank == 0)
                cout << "\nSaliendo..." << endl;
            break;
        default:
            if (rank == 0)
                cout << "Opcion invalida." << endl;
        }

    } while (opcion != 0);

    MPI_Finalize();
    return 0;
}