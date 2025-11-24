#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, send_data, recv_data;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    send_data = (rank == 0) ? 100 : 200;

    if (rank == 0) {
        printf("Process 0: Before Send\n");
        fflush(stdout);

        MPI_Send(&send_data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        printf("Process 0: After Send, Before Recv\n");
        fflush(stdout);

        MPI_Recv(&recv_data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process 0: Received %d\n", recv_data);
        fflush(stdout);
    } else if (rank == 1) {
        printf("Process 1: Before Send\n");
        fflush(stdout);

        MPI_Send(&send_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

        printf("Process 1: After Send, Before Recv\n");
        fflush(stdout);

        MPI_Recv(&recv_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process 1: Received %d\n", recv_data);
        fflush(stdout);
    }

    MPI_Finalize();
    return 0;
}


Now For Compilation
mpicc deadlock.c -o deadlock 
For execution
mpirun --np 2 ./deadlock
