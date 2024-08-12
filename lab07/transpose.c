#include "transpose.h"

/* The naive transpose function as a reference. */
void transpose_naive(int n, int blocksize, int *dst, int *src) {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            dst[y + x * n] = src[x + y * n]; // dst[x][y] = src[y][x]
        }
    }
}

/* Implement cache blocking below. You should NOT assume that n is a
 * multiple of the block size. */
void transpose_blocking(int n, int blocksize, int *dst, int *src) {
    // YOUR CODE HERE
    int num;
    int rw, cl;
    num = n / blocksize;
    for (int R = 0; R < num + 1; R++) {
      for (int C = 0; C < num + 1; C++) {
        for (int i = 0; i < blocksize; i++) {
          for (int j = 0; j < blocksize; j++) {
            rw = blocksize*R+i;
            cl = blocksize*C+j;
            if (rw < n && cl < n) {
              dst[rw*n+cl] = src[cl*n+rw];
            }
          }
        }
      }
    }
}
