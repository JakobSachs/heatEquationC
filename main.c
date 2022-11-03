#include <mkl/mkl.h>
#include <mkl/mkl_service.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
  const int N = 100;
  const int T = 7500;

  const double alpha = 2.0;
  const int d_x = 1;
  const double d_t = (double) (d_x * d_x) / (double) (4.0 * alpha);
  const double gamma = (alpha * d_t) / (double) (d_x * d_x);

  printf("Params:\n");
  printf("N:\t%d\tT:\t%d\talpha:\t%.3f\n", N, T, alpha);
  printf("dx:\t%d\tdt:\t%.3f\tgamma:\t%.3f\n", d_x, d_t, gamma);

  double* m1 = malloc((N + 1) * (N + 1) * sizeof(double) );
  double* m2 = malloc((N + 1) * (N + 1) * sizeof(double) );

  // initalize
  for (int i = 0; i < (N + 1) * (N + 1); i++)
  {
    m1[i] = 0.0;
    m2[i] = 0.0;
  }

  // establish inital condition

  for (int i = 0; i < (N + 1); i++)
  {
    m1[i] = 100.0;
    m2[i] = 100.0;
  }

  double *M, *M_next;
  // calculate
  M = m1;
  M_next = m2;

  for (int t = 0; t < T; t++)
  {
    for (int i = 1; i < (N); i++)  // y-axis
    {
      for (int j = 1; j < (N); j++)  // x-axis
      {
        M_next[j + i * (N + 1)] =
            gamma * (M[(j - 1) + i * (N + 1)] + M[(j + 1) + i * (N + 1)] +
                     M[j + (i - 1) * (N + 1)] + M[j + (i + 1) * (N + 1)] -
                     4 * M[j + i * (N + 1)]) +
            M[j + i * (N + 1)];
      }
    }

    // switch matrices
    double* tmp = M;
    M = M_next;
    M_next = tmp;

    if (t % 10 == 0)
    {
      // output data
      char path[FILENAME_MAX]; 

      sprintf(path, "out/data_%03d.dat",t/10);
      
      

      FILE* out = fopen(path, "w");
      for (int i = 0; i < (N + 1) * (N + 1); i++)
      {
        int x = i % (N + 1);
        int y = i / (N + 1);

        if (y > 0 && x == 0) fprintf(out, "\n");

        fprintf(out, "%d %d %f\n", x, y, m2[i]);
      }

      fclose(out);
    }
  }

  free(m1);
  free(m2);

  printf("Done!\n");
  return 0;
}
