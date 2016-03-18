#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>

#define LDA 100

void dgemv_(char *, int *, int *, double *, double [][LDA], int *, 
           double [], int *, double *, double [], int *);
void dger_(int *, int *, double *, double [], int *, double [], int *,
           double [][LDA], int *);
double ddot_(int *, double [], int *, double [], int *);
double dasum_(int *, double [], int *);
double dnrm2_(int *, double [], int *);
int idamax_(int *, double [], int *);
           
main(void) 
{

  char trans;
  int m, n, lda, incx, incy;
  double alpha, beta;

  int i, j, id;
  double a[10][LDA], x[10], y[10];
  double at[LDA][LDA];
  double dot, sum, norm2;

  alpha=1.;
  beta=0.;

  m=4;
  n=3;
  incx=incy=1;

  lda=LDA;

  trans='t';

  for(i = 0; i <= n - 1; ++i) {
    x[i] = pow(-1.,i)*(i + 1.);
  }

  for(i = 0; i <= m - 1; ++i) {
    for(j = 0; j <= n - 1; ++j) {
      a[i][j] = pow(-1.,(i+j))*(i + 1.);
    }
  }

  for(i = 0; i <= n - 1; ++i) {
    for(j = 0; j <= m - 1; ++j) {
      at[i][j] = a[j][i];
    }
  }

  printf("\n A = \n");
  for(i = 0; i <= m - 1; ++i){
    for(j = 0; j <= n - 1; ++j){
      printf(" %8.6g%c", a[i][j], 
   (j%(n)==(n - 1) || j==(n - 1) || (n-1)==0) ? '\n' : ' ');
    }
  }
  printf("\n");

  printf("\n A^T = \n");
  for(i = 0; i <= n - 1; ++i){
    for(j = 0; j <= m - 1; ++j){
      printf(" %8.6g%c", at[i][j], 
   (j%(m)==(m - 1) || j==(m - 1) || (m - 1)==0) ? '\n' : ' ');
    }
  }
  printf("\n");

  printf("\n x = \n");
  for(i = 0; i <= n - 1; ++i){
    printf(" %8.6g\n", x[i]);
  }
  printf("\n");

  dgemv_(&trans, &n, &m, &alpha, a, &lda, x, &incx, &beta, y, &incy);
  printf(
  "\n dgemv_(&trans, &n, &m, &alpha, a, &lda, x, &incx, &beta, y, &incy)");
  printf(
  "\n dgemv_(   '%c', %2d, %2d, %6.0f, a, %4d, x, %5d, %5.0f, y, %5d) \n", 
         trans, n, m, alpha, lda, incx, beta, incy);
  printf("\n y <- alpha*A*x + beta*y = \n");
  for(i = 0; i <= m - 1; ++i){
    printf(" %8.6g\n", y[i]);
  }
  printf("\n");

  trans = 'n';
  dgemv_(&trans, &m, &n, &alpha, at, &lda, x, &incx, &beta, y, &incy);
  printf(
  "\n dgemv_(&trans, &m, &n, &alpha, at, &lda, x, &incx, &beta, y, &incy)");
  printf(
  "\n dgemv_(   '%c', %2d, %2d, %6.0f, at, %4d, x, %5d, %5.0f, y, %5d) \n", 
             trans, m, n, alpha, lda, incx, beta, incy);
  printf("\n y <- alpha*A*x + beta*y = \n");
  for(i = 0; i <= m - 1; ++i){
    printf(" %8.6g\n", y[i]);
  }
  printf("\n");

  dger_(&n, &m, &alpha, x, &incx, y, &incy, a, &lda);
  printf(
  "\n dger_(&n, &m, &alpha, x, &incx, y, &incy, a, &lda)");
  printf(
  "\n dger_(%2d, %2d, %6.0f, x, %5d, y, %5d, a, %4d) \n", 
            n, m, alpha, incx, incy, lda);
  printf("\n A <- alpha*y(x^T) + A = \n");
  for(i = 0; i <= m - 1; ++i){
    for(j = 0; j <= n - 1; ++j){
      printf(" %8.6g%c", a[i][j], 
   (j%(n)==(n - 1) || j==(n - 1) || (n-1)==0) ? '\n' : ' ');
    }
  }
  printf("\n");

  dot = ddot_(&n, x, &incx, x, &incx);
  printf("\n ddot_(&n, x, &incx, x, &incx)");
  printf("\n ddot_(%2d, x, %5d, x, %5d) \n", n, incx, incx);
  printf("\n (x^T)x = %8.6g\n", dot);
  printf("\n");

  sum = dasum_(&n, x, &incx);
  printf("\n dasum_(&n, x, &incx)");
  printf("\n dasum_(%2d, x, %5d) \n", n, incx);
  printf("\n sum(|x|) = %8.6g\n", sum);
  printf("\n");

  norm2 = dnrm2_(&n, x, &incx);
  printf("\n dnrm2_(&n, x, &incx)");
  printf("\n dnrm2_(%2d, x, %5d) \n", n, incx);
  printf("\n sqrt(sum((x^T)x) = %8.6g\n", norm2);
  printf("\n");

  id = idamax_(&m, y, &incy);
  printf("\n idamax_(&m, y, &incy)");
  printf("\n idamax_(%2d, y, %5d) \n", m, incy);
  printf("\n idamax = index(max(|y[i]|)) = %d\n y[idamax-1] = %8.6g\n"
         , id, y[id-1]);

  printf("\n");

}
