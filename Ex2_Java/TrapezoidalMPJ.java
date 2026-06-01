import mpi.*;

public class TrapezoidalMPJ {
    public static double f(double x) {
        return x * x;
    }

    public static double trap(double leftEndpt, double rightEndpt, int trapCount, double baseLen) {
        double estimate;
        double x;

        estimate = (f(leftEndpt) + f(rightEndpt)) / 2.0;

        for (int i = 1; i <= trapCount - 1; i++) {
            x = leftEndpt + i * baseLen;
            estimate += f(x);
        }

        estimate = estimate * baseLen;

        return estimate;
    }

    public static void main(String[] args) throws Exception {
        MPI.Init(args);

        int myRank = MPI.COMM_WORLD.Rank();
        int commSize = MPI.COMM_WORLD.Size();

        double a = 0.0;
        double b = 3.0;
        int n = 10000000;

        double h = (b - a) / n;
        int localN = n / commSize;

        double localA = a + myRank * localN * h;
        double localB = localA + localN * h;

        long startParallel = System.nanoTime();

        double localInt = trap(localA, localB, localN, h);

        if (myRank != 0) {
            double[] sendBuffer = { localInt };

            MPI.COMM_WORLD.Send(
                sendBuffer,
                0,
                1,
                MPI.DOUBLE,
                0,
                0
            );
        } else {
            double totalInt = localInt;
            double[] recvBuffer = new double[1];

            for (int source = 1; source < commSize; source++) {
                MPI.COMM_WORLD.Recv(
                    recvBuffer,
                    0,
                    1,
                    MPI.DOUBLE,
                    source,
                    0
                );

                totalInt += recvBuffer[0];
            }

            long endParallel = System.nanoTime();

            long startSerial = System.nanoTime();
            double serialInt = trap(a, b, n, h);
            long endSerial = System.nanoTime();

            double parallelTime = (endParallel - startParallel) / 1_000_000_000.0;
            double serialTime = (endSerial - startSerial) / 1_000_000_000.0;

            System.out.println("Integral de f(x) = x^2 desde " + a + " hasta " + b);
            System.out.println("Resultado serial:   " + serialInt);
            System.out.println("Resultado paralelo: " + totalInt);
            System.out.println("Tiempo serial:      " + serialTime + " segundos");
            System.out.println("Tiempo paralelo:    " + parallelTime + " segundos");
            System.out.println("Procesos usados:    " + commSize);
        }

        MPI.Finalize();
    }
}