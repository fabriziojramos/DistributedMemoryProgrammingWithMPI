#include <stdio.h>
#include <mpi.h>

double f(double x) {
    return x * x;
}

double Trap(double left_endpt, double right_endpt, int trap_count, double base_len) {
    double estimate;
    double x;
    int i;

    estimate = (f(left_endpt) + f(right_endpt)) / 2.0;

    for (i = 1; i <= trap_count - 1; i++) {
        x = left_endpt + i * base_len;
        estimate += f(x);
    }

    estimate = estimate * base_len;

    return estimate;
}

int main(void) {
    int my_rank;
    int comm_sz;

    double a = 0.0;
    double b = 3.0;
    int n = 10000000;

    double h;
    int local_n;
    double local_a;
    double local_b;

    double local_int;
    double total_int;
    double serial_int;

    double start_parallel;
    double end_parallel;
    double start_serial;
    double end_serial;

    int source;

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    h = (b - a) / n;
    local_n = n / comm_sz;

    local_a = a + my_rank * local_n * h;
    local_b = local_a + local_n * h;

    start_parallel = MPI_Wtime();

    local_int = Trap(local_a, local_b, local_n, h);

    if (my_rank != 0) {
        MPI_Send(&local_int, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    } else {
        total_int = local_int;

        for (source = 1; source < comm_sz; source++) {
            MPI_Recv(&local_int, 1, MPI_DOUBLE, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            total_int += local_int;
        }

        end_parallel = MPI_Wtime();

        start_serial = MPI_Wtime();
        serial_int = Trap(a, b, n, h);
        end_serial = MPI_Wtime();

        printf("Integral de f(x) = x^2 desde %.1f hasta %.1f\n", a, b);
        printf("Resultado serial:   %.15f\n", serial_int);
        printf("Resultado paralelo: %.15f\n", total_int);
        printf("Tiempo serial:      %.10f segundos\n", end_serial - start_serial);
        printf("Tiempo paralelo:    %.10f segundos\n", end_parallel - start_parallel);
        printf("Procesos usados:    %d\n", comm_sz);
    }

    MPI_Finalize();

    return 0;
}