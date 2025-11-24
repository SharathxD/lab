#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            char message[100];
            sprintf(message, "Hello from process 0 to process %d", i);
            MPI_Send(message, strlen(message) + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
            printf("Process 0 sent message to process %d\n", i);
        }
    } else {
        char recv_buf[100];
        MPI_Recv(recv_buf, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        printf("Process %d received message: %s\n", rank, recv_buf);
    }

    MPI_Finalize();
    return 0;
}


#mpicc sr.c -o sr
#mpirun --oversubscribe --np 6 ./sr
