#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> // gettimeofday
#include <time.h>
#include "transpose.h"

double benchmark(int *A, int *B, int n, int blocksize,
    void (*transpose)(int, int, int*, int*), char *description) {

    int i, j;

    /* initialize A,B to random integers */
    srand48( time( NULL ) );
    for( i = 0; i < n*n; i++ ) A[i] = lrand48( );
    for( i = 0; i < n*n; i++ ) B[i] = lrand48( );

    /* measure performance */
    struct timeval start, end;
    /*
    struct timeval {
               time_t      tv_sec;     // seconds 
               suseconds_t tv_usec;    // microseconds
     };
    */

    gettimeofday( &start, NULL );
    transpose( n, blocksize, B, A );
    gettimeofday( &end, NULL );

    double seconds = (end.tv_sec - start.tv_sec) +
        1.0e-6 * (end.tv_usec - start.tv_usec);

    /* check correctness */
    for( i = 0; i < n; i++ ) {
        for( j = 0; j < n; j++ ) {
            if( B[j+i*n] != A[i+j*n] ) {
                printf("Error!!!! Transpose does not result in correct answer!!\n");
                exit( -1 );
            }
        }
    }
    
    return seconds*1e3;
}

int main( int argc, char **argv ) {

    int n[] = {10000}; //{100, 1000, 2000, 5000, 10000};
    int blocksize[] = {50, 100, 500, 1000, 5000};//20;
    
    for (int i = 0; i < 1; i++) {
    for (int j = 0; j < 5; j++) {
    /* allocate an n*n block of integers for the matrices */
    int *A = (int*)malloc( n[i]*n[i]*sizeof(int) );
    int *B = (int*)malloc( n[i]*n[i]*sizeof(int) );

    /* run tests */
    double time1 = benchmark(A, B, n[i], blocksize[j], transpose_naive, "naive transpose");
    double time2 = benchmark(A, B, n[i], blocksize[j], transpose_blocking, "transpose with blocking");

    /* release resources */
    free( A );
    free( B );

    printf("testing n = %d, blocksize = %d\n", n[i], blocksize[j]);
    printf("naive: %g milliseconds\n", time1);
    printf("student: %g milliseconds\n", time2);
    if ((time1 - time2) < 250) {
        printf("insufficient speedup\n");
        // return -1;
    } else {
      printf("Speedup sufficient\n");
    }

    }
    }
    return 0;
}
