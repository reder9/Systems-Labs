#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;

double f(double x);
bool closerLimit(double u, double l);
double falsePosition(double u, double l);
const double E = pow(10,-5);


int main() {   
cout.precision(17);
 cout <<  fixed;



     cout << "Enter the First Limit: " <<  endl;
    double x1;
     cin >> x1;

     cout << "Enter The Second Limit: " <<  endl;
    double x2;
     cin >> x2;

	cout << "n \t         c \t\t       lambda n \n";
	cout << "__________________________________________________\n";
     cout << "\nThe root = " << falsePosition(x1,x2) <<  endl;

}

double f(double x) {
  return 1 + .3 * cos(x) - x;
}


double falsePosition(double u, double l)
{

	double s = u - ((f(u)*(l-u)) / (f(l)-f(u)));
	int n = 0;
	float lambda = 0;

	while ( abs(s-u) > E && abs(s-l) > E){
	n++;

	if (f(s) * f(l) < 0){  

	lambda =  abs(u-s);
	      u = s;
	}

      else {

	lambda =  abs(u-l);
        l = s;
	 }

	cout << n << "\t" << s << "\t" << lambda << endl;

	s = u - ((f(u)*(l-u)) / (f(l)-f(u)));
	}

  return  s;
}

