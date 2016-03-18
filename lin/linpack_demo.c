#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define LDA 500

void dgefa_(double [][LDA], int *, int *, int [], int *);
void dgesl_(double [][LDA], int *, int *, int [], double [], int *);
           
main(void) 
{
  double a_data[] = {  1.0, -1.0,   1.0, -1.0,
                      -1.0,  3.0,  -3.0,  3.0,
		       2.0, -4.0,   7.0, -7.0,
		      -3.0,  2.0, -10.0, 14.0 };
  double b_data[] = { 0.0, 2.0, -2.0, 8.0 };

  int ipvt[500];
  int n, info, job, lda;

  double a[500][LDA];
  double temp, r, s;

  int i, j;

  double b[500];

  lda=LDA;
  job=0;
  n = 4;
/*
  n = 3;
 
  a[0][0] = 2.;
  a[0][1] = 1.;
  a[0][2] = 3.;
  a[1][0] = 4.;
  a[1][1] = 4.;
  a[1][2] = 7.;
  a[2][0] = 2.;
  a[2][1] = 5.;
  a[2][2] = 9.;

  b[0] = 1.;
  b[1] = 1.;
  b[2] = 3.;
*/
/*
  a[0][0] = .729;
  a[0][1] = .810;
  a[0][2] = .900;
  a[1][0] = 1.;
  a[1][1] = 1.;
  a[1][2] = 1.;
  a[2][0] = 1.331;
  a[2][1] = 1.210;
  a[2][2] = 1.100;

  b[0] = .6867;
  b[1] = .8338;
  b[2] = 1.;
*/

//  initialize matrix, a and right-hand side, b
  for(i = 0; i <= n-1; ++i){
    b[i] = b_data[i];
    for(j = 0; j <= n - 1; ++j){
      a[i][j] = a_data[i*n+j];
    }
  }

  printf("\n A = \n");
  for(i = 0; i <= n - 1; ++i){
    for(j = 0; j <= n - 1; ++j){
      printf(" %8.6g%c", a[i][j], 
   (j%(n)==(n - 1) || j==(n - 1) || (n-1)==0) ? '\n' : ' ');
    }
  }
  printf("\n");

//  if job = 0, take the transpose of A and store in A: A -> A^T

  printf(" overwrite A with A^T\n");
  printf(" A <- A^T\n");

  if (job == 0) {
    for(i = 0; i <= n -1; ++i){
      for(j = i; j <= n-1; ++j){
        temp = a[i][j];
        a[i][j] = a[j][i];
        a[j][i] = temp;
      }
    }
  }

  printf("\n A = \n");
  for(i = 0; i <= n - 1; ++i){
    for(j = 0; j <= n - 1; ++j){
      printf(" %8.6g%c", a[i][j], 
   (j%(n)==(n - 1) || j==(n - 1) || (n-1)==0) ? '\n' : ' ');
    }
  }
  printf("\n");

  printf(" pass A^T to dgefa to factor A\n");
  printf(" dgefa_(a, lda, n, ipvt, info)\n");
  printf(" dgefa_(a, 500, 4, ipvt, info)\n");

  dgefa_(a, &lda, &n, ipvt, &info);

  printf("\n A -> L*U = \n\n");
  for(i = 0; i <= n - 1; ++i){
    for(j = 0; j <= n - 1; ++j){
      printf("%9.6g%c", a[j][i], 
   (j%(n)==(n - 1) || j==(n - 1) || (n-1)==0) ? '\n' : ' ');
    }
  }
  printf("\n");

  printf("\n (pivot vector)");
  printf("\n ipvt = \n");
  for(i = 0; i <= n - 1; ++i){
    printf("%9d\n", ipvt[i]);
  }
  printf("\n");

  printf("\n (right-hand side)");
  printf("\n b = \n");
  for(i = 0; i <= n - 1; ++i){
    printf("%9.6g\n", b[i]);
  }
  printf("\n");

  printf(" pass A -> L*U to dgesl to solve the system of equations\n");
  printf(" dgesl_(a, lda, n, ipvt, b, job)\n");
  printf(" dgesl_(a, 500, 4, ipvt, b,   0)\n");

  dgesl_(a, &lda, &n, ipvt, b, &job);

  printf("\n (solution vector)");
  printf("\n x = \n");
  for(i = 0; i <= n - 1; ++i){
    printf("%9.6g\n", b[i]);
  }
  printf("\n");

}
