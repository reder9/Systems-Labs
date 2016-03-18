#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>

using namespace std;

#define LDA 100

extern "C" {
void dgemv_(char&, int&, int&, double&, double [][LDA], int&, 
            double [], int&, double&, double [], int&);
void dger_(int&, int&, double&, double [], int&, double [], int&,
           double [][LDA], int&);
double ddot_(int&, double [], int&, double [], int&);
double dasum_(int&, double [], int&);
double dnrm2_(int&, double [], int&);
int idamax_(int&, double [], int&);
}
           
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

  cout << "\n A = " << endl;
  for(i = 0; i <= m - 1; ++i){
    for(j = 0; j <= n - 1; ++j){
      cout << setw(9) << a[i][j] << 
    ((j%(n)==(n - 1) || j==(n - 1) || (n - 1)==0) ? "\n" : " ");
    }
  }
  cout << "\n";

  cout << "\n A^T = " << endl;
  for(i = 0; i <= n - 1; ++i){
    for(j = 0; j <= m - 1; ++j){
      cout << setw(9) << at[i][j] << 
    ((j%(m)==(m - 1) || j==(m - 1) || (m - 1)==0) ? "\n" : " ");
    }
  }
  cout << "\n";

  cout << "\n x = " << endl;
  for(i = 0; i <= n - 1; ++i){
    cout << setw(9) << x[i] << endl;
  }
  cout << "\n";

  dgemv_(trans, n, m, alpha, a, lda, x, incx, beta, y, incy);
  cout << "\n dgemv_(trans, n, m, alpha, a, lda, x, incx, beta, y, incy)" 
       << "\n dgemv_(" << setw(3) << "'" << trans << "', " 
       << n << ", " << m << ", " << setw(5) << alpha << ", a, " << lda 
       << ", x," << setw(5) << incx << "," << setw(5) << beta << ", y," 
       << setw(5) << incy << ")" 
       << endl;
  cout << "\n y <- alpha*A*x + beta*y = " << endl;
  for(i = 0; i <= m - 1; ++i){
    cout << setw(9) << y[i] << endl;
  }
  cout << "\n";

  trans = 'n';
  dgemv_(trans, m, n, alpha, at, lda, x, incx, beta, y, incy);
  cout << "\n dgemv_(trans, m, n, alpha, at, lda, x, incx, beta, y, incy)" 
       << "\n dgemv_(" << setw(3) << "'" << trans << "', " 
       << m << ", " << n << ", " << setw(5) << alpha << ", at, " << lda 
       << ", x," << setw(5) << incx << "," << setw(5) << beta << ", y," 
       << setw(5) << incy << ")" 
       << endl;
  cout << "\n y <- alpha*A*x + beta*y = " << endl;
  for(i = 0; i <= m - 1; ++i){
    cout << setw(9) << y[i] << endl;
  }
  cout << "\n";

  dger_(n, m, alpha, x, incx, y, incy, a, lda);
  cout << "\n dger_(n, m, alpha, x, incx, y, incy, a, lda)"
       << "\n dger_(" << n << ", " << m << ", " << setw(5) << alpha
       << ", x," << setw(5) << incx << ", y," << setw(5) << incy 
       << ", a, " << lda << ")"
       << endl;
  cout << "\n A <- alpha*y(x^T) + A = " << endl;
  for(i = 0; i <= m - 1; ++i){
    for(j = 0; j <= n - 1; ++j){
      cout << setw(9) << a[i][j] << 
    ((j%(n)==(n - 1) || j==(n - 1) || (n - 1)==0) ? "\n" : " ");
    }
  }
  cout << "\n";

  dot = ddot_(n, x, incx, x, incx);
  cout << "\n ddot_(n, x, incx, x, incx)" 
       << "\n ddot_(" << n << ", x," << setw(5) << incx 
                           << ", x," << setw(5) << incx << ")"
       << endl;
  cout << "\n (x^T)x =" << setw(9) << dot << endl;
  cout << "\n";

  sum = dasum_(n, x, incx);
  cout << "\n dasum_(n, x, incx)" 
       << "\n dasum_(" << n << ", x," << setw(5) << incx << ")"
       << endl;
  cout << "\n sum(|x|) =" << setw(9) << sum << endl;
  cout << "\n";

  norm2 = dnrm2_(n, x, incx);
  cout << "\n dnrm2_(n, x, incx)"
       << "\n dnrm2_(" << n << ", x," << setw(5) << incx << ")"
       << endl;
  cout << "\n sqrt(sum((x^T)x) =" << setw(9) << norm2 << endl;
  cout << "\n";

  id = idamax_(m, y, incy);
  cout << "\n idamax_(m, y, incy)"
       << "\n idamax_(" << m << ", y," << setw(5) << incy << ")"
       << endl;
  cout << "\n idamax = index(max(|y[i]|)) =" << setw(2) << id << 
          "\n y[idamax-1] = " << setw(8) << y[id-1] << 
          "\n" << endl;

}
