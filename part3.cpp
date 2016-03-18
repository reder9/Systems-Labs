#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;

const double E = pow(10,-5);


int main() {

int n = 5;

	int A[n][n];

	for (int i = 0; i < n; i++){
	for (int j = 0; j < n; j++){

	A[i][j] = fmax(i+1,j+1);

	}
	}


	for (int i = 0; i < n; i++){
	for (int j = 0; j < n; j++){

	cout <<	A[i][j];

	}
	cout << endl;
	}




}

