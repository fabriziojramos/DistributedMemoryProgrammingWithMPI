import mpi.*;

public class HelloMPJ {
    public static void main(String[] args) throws Exception {
        MPI.Init(args);

        int myRank = MPI.COMM_WORLD.Rank();
        int commSize = MPI.COMM_WORLD.Size();

        if (myRank != 0) {
            String[] message = {
                "Greetings from process " + myRank + " of " + commSize + "!"
            };

            MPI.COMM_WORLD.Send(message, 0, 1, MPI.OBJECT, 0, 0);
        } else {
            System.out.println("Greetings from process " + myRank + " of " + commSize + "!");

            for (int q = 1; q < commSize; q++) {
                String[] received = new String[1];

                MPI.COMM_WORLD.Recv(received, 0, 1, MPI.OBJECT, q, 0);

                System.out.println(received[0]);
            }
        }

        MPI.Finalize();
    }
}