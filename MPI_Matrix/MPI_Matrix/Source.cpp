#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <windows.h>

using namespace std;

int main(int argc, char** argv)
{    
    SetConsoleOutputCP(CP_UTF8);

    double start, stop;
    int i, j, k, l;
    int* a, * b, * c, * buffer, * result;
    int sizes[] = { 250, 500, 1000, 2000, 4000 };

    int rank, procs, block;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &procs);

    for (int size : sizes)
    {
        block = size / procs;
       
        a = (int*)malloc(sizeof(int) * size * size);
        b = (int*)malloc(sizeof(int) * size * size);
        c = (int*)malloc(sizeof(int) * size * size);
        
        buffer = (int*)malloc(sizeof(int) * size * block);
        result = (int*)malloc(sizeof(int) * size * block);

        if (rank == 0) {

            for (i = 0; i < size; i++) 
            {
                for (j = 0; j < size; j++) 
                {
                    a[i * size + j] = i * j;
                    b[i * size + j] = i * j;
                }
            }

            start = MPI_Wtime();

            for (i = 1; i < procs; i++) 
                MPI_Send(b, size * size, MPI_INT, i, 0, MPI_COMM_WORLD);

            for (l = 1; l < procs; l++) 
                MPI_Send(a + (l - 1) * block * size, size * block, MPI_INT, l, 1, MPI_COMM_WORLD);

            for (k = 1; k < procs; k++) 
            {
                MPI_Recv(result, block * size, MPI_INT, k, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                for (i = 0; i < block; i++) 
                {
                    for (j = 0; j < size; j++)
                        c[((k - 1) * block + i) * size + j] = result[i * size + j];
                }
            }

            for (i = (procs - 1) * block; i < size; i++) 
            {
                for (j = 0; j < size; j++) 
                {
                    int temp = 0;
                
                    for (k = 0; k < size; k++)
                        temp += a[i * size + k] * b[k * size + j];
                    
                    c[i * size + j] = temp;
                }
            }

            stop = MPI_Wtime();

            cout << "Processes: " << procs <<
                "; Size: " << size <<
                "; Time: " << stop - start << 
                " seconds" << endl;

            free(a);
            free(b);
            free(c);
            free(buffer);
            free(result);
        }

        else {
            MPI_Recv(b, size * size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(buffer, size * block, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            for (i = 0; i < block; i++)
            {
                for (j = 0; j < size; j++) 
                {
                    int temp = 0;
                
                    for (k = 0; k < size; k++)
                        temp += buffer[i * size + k] * b[k * size + j];
                    
                    result[i * size + j] = temp;
                }
            }

            MPI_Send(result, block * size, MPI_INT, 0, 3, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();

    return 0;
}