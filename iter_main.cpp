#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define LDA 100
FILE *fpin;

extern "C" {
void dgemv_(char&, int&, int&, double&, double [][LDA], int&, 
            double [], int&, double&, double [], int&);
void daxpy_(int&, double&, double [], int&, double [], int&);
void dcopy_(int&, double [], int&, double [], int&);
}
           
main(void) 
{

  char trans;
  int n, lda, inc, p;
  double alpha, beta;

  int i, j, id, iter, itmax;
  double a[10][LDA], g[10][LDA], b[10], f[10], x[10], y[10];
  double dot, sum, norm2;
  double omega;

  fpin = fopen("in.dat", "r");

  alpha=1.;
  beta=0.;
  inc=1;
  lda=LDA;
  trans='t';

//  omega = 1.;
  omega = .75;
//  omega = .6;
  iter = 1;
  itmax = 35;

//  read in dimension of system of equations
  p = fscanf(fpin, "%d", &n);

//  read in the coefficinet matrix
  for(i = 0; i <= n - 1; ++i){
    for(j = 0; j <= n - 1; ++j){
      p = fscanf(fpin, "%lf", &a[i][j]);
    }
  }

//  read in the right-hand side
  for(i = 0; i <= n - 1; ++i) 
    p = fscanf(fpin, "%lf", &b[i]);

//  read in initial guess x^(0)
  for(i = 0; i <= n - 1; ++i) 
    p = fscanf(fpin, "%lf", &x[i]);

  printf("\n A = \n");
  for(i = 0; i <= n - 1; ++i){
    for(j = 0; j <= n - 1; ++j){
      printf(" %8.6g%c", a[i][j], 
   (j%(n)==(n - 1) || j==(n - 1) || (n-1)==0) ? '\n' : ' ');
    }
  }
  printf("\n");

  printf("\n b = \n");
  for(i = 0; i <= n - 1; ++i){
    printf(" %13.6g\n", b[i]);
  }
  printf("\n");

//  set up the iteration matrix, g and vector, f
  for(i = 0; i <= n - 1; ++i){
    for(j = 0; j <= n - 1; ++j){
      g[i][j] = -omega*a[i][j]/a[i][i];
    }
    g[i][i] = 1.-omega;
    f[i] = omega*b[i]/a[i][i];
  }

  printf("\n G = \n");
  for(i = 0; i <= n - 1; ++i){
    for(j = 0; j <= n - 1; ++j){
      printf(" %13.6g%c", g[i][j], 
   (j%(n)==(n - 1) || j==(n - 1) || (n-1)==0) ? '\n' : ' ');
    }
  }
  printf("\n");

  printf("\n omega = %f\n", omega);

  for(i = 0; i <= n - 1; ++i){
    printf("     x[%d]        %c", i+1,
   (i%(n)==(n - 1) || i==(n - 1) || (n-1)==0) ? '\n' : ' ');
  }

  for(i = 0; i <= n - 1; ++i){
    printf("    %13.6e%c", x[i],
   (i%(n)==(n - 1) || i==(n - 1) || (n-1)==0) ? '\n' : ' ');
  }
  do {

//   y <- alpha*G*x +beta*y
  dgemv_(trans, n, n, alpha, g, lda, x, inc, beta, y, inc);

//   y <- alpha*f + y
  daxpy_(n, alpha, f, inc, y, inc);

//   x <- y;
  dcopy_(n, y, inc, x, inc);
  
  for(i = 0; i <= n - 1; ++i){
    printf("    %13.6e%c", x[i],
   (i%(n)==(n - 1) || i==(n - 1) || (n-1)==0) ? '\n' : ' ');
  }

  iter += 1;
     } while (iter <= itmax);

}
