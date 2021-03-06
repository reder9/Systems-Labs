#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>

using namespace std;

#define LDA 500

FILE *fpin;

extern "C" {
void dgefa_(double [][LDA], int&, int&, int [], int&);
void dgesl_(double [][LDA], int&, int&, int [], double [], int&);
}
           
main(void) 
{

  int ipvt[500];
  int n = 500, info, job, lda;
  int fsf;

  double a[500][LDA];
  double temp, r, s;

  int i, j;

  double b[500];

  fpin = fopen("in.dat", "r");

  lda=LDA;
  job=0;

//  fsf = fscanf(fpin, "%d", &n);

  for(i = 0; i <= n - 1; ++i){
    for(j = 0; j <= n - 1; ++j){
      //fsf = fscanf(fpin, "%lf", &a[i][j]);
    	a[i][j] = fmax(i+1,j+1);
	}
  }

  for(i = 0; i <= n - 1; ++i) 
	b[i] = 1.0;
//    fsf = fscanf(fpin, "%lf", &b[i]);

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
  n = 3;

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

  cout << "\n A = " << endl;
  for(i = 0; i <= n - 1; ++i){
    for(j = 0; j <= n - 1; ++j){
      cout << setw(9) << a[i][j] << 
    ((j%(n)==(n - 1) || j==(n - 1) || (n-1)==0) ? "\n" : " ");
    }
  }
  cout << "\n";
  
//  if job = 0, take the transpose of A and store in A: A -> A^T

  cout << " overwrite A with A^T" << endl;
  cout << " A <- A^T" << endl;

  if (job == 0) {
    for(i = 0; i <= n -1; ++i){
      for(j = i; j <= n-1; ++j){
        temp = a[i][j];
        a[i][j] = a[j][i];
        a[j][i] = temp;
      }
    }
  }
 
  cout << "\n A = " << endl;
  for(i = 0; i <= n - 1; ++i){
    for(j = 0; j <= n - 1; ++j){
      cout << setw(9) << a[i][j] << 
    ((j%(n)==(n - 1) || j==(n - 1) || (n-1)==0) ? "\n" : " ");
    }
  }
  cout << "\n";

  cout << " pass A^T to dgefa to factor A" << endl;
  cout << " dgefa_(a, lda, n, ipvt, info)" << endl;
  cout << " dgefa_(a, " << "500, " << "4, " << "ipvt, " << "info)"
       << endl;

  dgefa_(a, lda, n, ipvt, info);

  cout << "\n A -> L*U = \n " << endl;
  for(i = 0; i <= n - 1; ++i){
    for(j = 0; j <= n - 1; ++j){
      cout << setw(9) << a[j][i] << 
    ((j%(n)==(n - 1) || j==(n - 1) || (n-1)==0) ? "\n" : " ");
    }
  }
  cout << "\n";

  cout << "\n (pivot vector)" << endl;
  cout << " ipvt = " << endl;
  for(i = 0; i <= n - 1; ++i){
    cout << setw(9) << ipvt[i] << endl;
  }
  cout << "\n";

  cout << "\n (right-hand side)" << endl;
  cout << " b = " << endl;
  for(i = 0; i <= n - 1; ++i){
    cout << setw(9) << b[i] << endl;
  }
  cout << "\n";

  cout << " pass A -> L*U to dgesl to solve the system of equations" << endl;
  cout << " dgesl_(a, lda, n, ipvt, b, job)" << endl;
  cout << " dgesl_(a, " << "500, " << "4, " << "ipvt, " << "b, " << "  0)" 
       << endl;

  dgesl_(a, lda, n, ipvt, b, job);

  cout << "\n (solution vector)" << endl;
  cout << " x = " << endl;
  for(i = 0; i <= n - 1; ++i){
    cout << setw(9) << b[i] << endl;
  }
  cout << "\n";

}
