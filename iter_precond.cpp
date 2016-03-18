#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>

using namespace std;

#define LDA 100
FILE *fpin;
extern "C" {
void dgemv_(char&, int&, int&, double&, double [][LDA], int&, 
            double [], int&, double&, double [], int&);
void dgemm_(char&, char&, int&, int&, int&, double&, double [][LDA], int&,
            double [][LDA], int&, double&, double [][LDA], int&);
void daxpy_(int&, double&, double [], int&, double [], int&);
void dcopy_(int&, double [], int&, double [], int&);
void dgefa_(double [][LDA], int&, int&, int [], int&);
void dgesl_(double [][LDA], int&, int&, int [], double [], int&);
int idamax_(int&, double [], int&);
}
           
main(void) 
{

  char trans, ntrans;
  int n, lda, inc;
  int info, job;
  int fsf;
  double alpha, beta, m_alpha, alpha_o;

  int i, j, id, iter, itmax;
  double a[10][LDA], b[10], x[10];
  double r[10];
  double x_true[10], e[10];
  double m[10][LDA], mu[10][LDA], c[10][LDA];
  int ipvt[500];
  double dot, sum, norm2, eps;
  double omega, inf_norm;

  fpin = fopen("in.dat", "r");

  alpha=1.;
  m_alpha = -alpha;
  beta=0.;
  inc=1;
  lda=LDA;
  job=1;
  trans='t';
  ntrans = 'n';
  eps = 1.e-6;

//  initialize the relaxation parameter
//  omega = 1.15;
  omega = 1.;
//  omega = .6;
  alpha_o = 1./(2. - omega);
  iter = 1;
  itmax = 30;

//  read in dimension of system of equations
  fsf = fscanf(fpin, "%d", &n);

//  read in the coefficinet matrix
  for (i = 0; i <= n - 1; ++i) {
    for (j = 0; j <= n - 1; ++j) {
      fsf = fscanf(fpin, "%lf", &a[i][j]);
    }
  }

//  read in the right-hand side
  for (i = 0; i <= n - 1; ++i) 
    fsf = fscanf(fpin, "%lf", &b[i]);

//  read in initial guess x^(0)
  for (i = 0; i <= n - 1; ++i) 
    fsf = fscanf(fpin, "%lf", &x[i]);

//  read in true solution x_true
//  comment out the following if x_true not known
//  for(i = 0; i <= n - 1; ++i) 
//    fsf = fscanf(fpin, "%lf", &x_true[i]);

//  print out the coefficient matrix
  cout << "\n A = " << endl;
  for (i = 0; i <= n - 1; ++i) {
    for (j = 0; j <= n - 1; ++j) {
      cout << setw(9) << a[i][j] << 
      ((j%(n)==(n - 1) || j==(n - 1) || (n-1)==0) ? '\n' : ' ');
    }
  }
  cout << "\n";

//  print out the right-hand side
  cout << "\n b = " << endl;
  for (i = 0; i <= n - 1; ++i) {
    cout << setw(9) << b[i] << endl;
  }
  printf("\n");

//  set up the preconditioner matrix
//  this is for Jacobi relaxation
  for (i = 0; i <= n-1; ++i) {
    for (j = 0; j <= n-1; ++j ) {
      if (j != i) {
        m[i][j] = 0.;
      } else {
        m[i][i] = a[i][i]/omega;
      }
    }
  }

//  uncomment the following for Seidel relaxation (successive overrelaxation)
//  beginning of SOR
/*
  for (i = 0; i <= n-1; ++i) {
    for (j = 0; j <= n-1; ++j) {
      if (j < i) {
        m[i][j] = m[i][j] + a[i][j];
      }
    }
  }
*/
//  end of SOR

//  in addition to Seidel relaxation uncomment the following for symmetric
//  successive overrelaxation
//  beginning of SSOR
/*
  for (i = 0; i <= n-1; ++i) {
    for (j = 0; j <= n-1; ++j) {
      m[i][j] = m[i][j]/a[i][i];
      if (j == i) {
        mu[i][j] = a[i][j]/(2. - omega);
      } else {
        if (j > i) {
	  mu[i][j] = omega*a[i][j]/(2. - omega);
	} else {
	  mu[i][j] = 0.;
	}
      }
    }
  }

//  uncomment the next block to print out the new m and mu matrices if desired.
//  note m should be unit lower triangular (ML) and mu should be upper 
//  triangular (MU) so the preconditioner has already been factored.
//
//  cout << "\n ML = " << endl;
//  for (i = 0; i <= n - 1; ++i) {
//    for (j = 0; j <= n - 1; ++j) {
//      cout << setw(9) << m[i][j] << 
//      ((j%(n)==(n - 1) || j==(n - 1) || (n-1)==0) ? '\n' : ' ');
//    }
//  }
//  printf("\n");

//  cout << "\n MU = " << endl;
//  for (i = 0; i <= n - 1; ++i) {
//    for (j = 0; j <= n - 1; ++j) {
//      cout << setw(9) << mu[i][j] << 
//      ((j%(n)==(n - 1) || j==(n - 1) || (n-1)==0) ? '\n' : ' ');
//    }
//  }
//  printf("\n");
//
  dgemm_(ntrans, ntrans, n, n, n, alpha_o, mu, lda, m, lda, beta, c, lda);

  for (i = 0; i <= n-1; ++i) {
    for (j = 0; j <= n-1; ++j) {
      m[i][j] = c[i][j];
    }
  }
*/
// end of SSOR

//  print out the preconditioner
  cout << "\n M = " << endl;
  for (i = 0; i <= n - 1; ++i) {
    for (j = 0; j <= n - 1; ++j) {
      cout << setw(9) << m[i][j] << 
      ((j%(n)==(n - 1) || j==(n - 1) || (n-1)==0) ? '\n' : ' ');
    }
  }
  printf("\n");

//  factor the preconditioner M
  dgefa_(m, lda, n, ipvt, info);

//  print out value of relaxation parameter (omega)
  cout << fixed << showpoint;
  cout << "\n omega = " << setprecision(6) << omega  << endl;

//  print out column headers for output
  cout << setw(6) << "i";
  for (i = 0; i <= n - 1; ++i) {
    cout << setw(7) << "x[" << i+1 << "]" << setw(9) <<
    ((i%(n)==(n - 1) || i==(n - 1) || (n-1)==0) ? '\n' : ' ');
  }

//  print out the initial guess x^(0)
  cout << setw(6) << iter-1 << setw(17);
  for (i = 0; i <= n - 1; ++i) {
    cout << scientific;
    cout << x[i] << setw(6) <<
    ((i%(n)==(n - 1) || i==(n - 1) || (n-1)==0) ? '\n' : ' ');
  }

//  initialize the norm so the initial while loop will will not fail
  inf_norm=1.;

  while (iter <= itmax && inf_norm > eps) {

//  set up the residual vector, r = b - A*x^(n)
//  r <- b (copy b to r)
    dcopy_(n, b, inc, r, inc);
//  r <- -alpha*A*x + alpha*r (calculate the residual)
    dgemv_(trans, n, n, m_alpha, a, lda, x, inc, alpha, r, inc);

//  the solve step for the correction vector
    dgesl_(m, lda, n, ipvt, r, job);

//  update the solution vector
//  x <- alpha*r + x
    daxpy_(n, alpha, r, inc, x, inc);

    cout << setw(6) << iter << setw(17);
    for(i = 0; i <= n - 1; ++i){
      cout << scientific;
      cout << x[i] << setw(6) <<
      ((i%(n)==(n - 1) || i==(n - 1) || (n-1)==0) ? '\n' : ' ');
    }

//  error calculation if x_true is given
//  e <- x_true
//  dcopy_(n, x_true, inc, e, inc);
//  e <- -alpha*x + e
//  daxpy_(n, m_alpha, x, inc, e, inc);
//  inf_norm = fabs(e[idamax_(n, e, inc) - 1]);
//  cout << scientific;
//  cout << "infinity norm (x_true - x) = " << inf_norm << endl;

//  else when x_true not known use inf_norm(residual)

  inf_norm = fabs(r[idamax_(n, r, inc) - 1]);

  iter += 1;
  }

  if (iter > itmax) {
    cout << " iteration count of " << itmax << " exceeded" << endl;
    cout << " inf_norm = " << inf_norm << endl;
  } else {
    cout << " inf_norm = " << inf_norm << endl;
  }

}
