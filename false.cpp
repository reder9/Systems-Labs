#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;

double f(double x);
bool closerLimit(double u, double l);
double iteration(double u, double l);
const double E = pow(10,-5);


int main()
{   
cout.precision(17);
std::cout << std::fixed;



    std::cout << "Enter the First Limit: " << std::endl;
    double x1;
    std::cin >> x1;

    std::cout << "Enter The Second Limit: " << std::endl;
    double x2;
    std::cin >> x2;

    std::cout << "\nThe root = " << iteration(x1,x2) << std::endl;

}

double f(double x)
{
  return 1 + .3 * cos(x) - x;
}

// Evaluating the closer limit to the root
// to make sure that the closer limit is the
// one that moves and the other one is fixed

inline bool closerlimit(double u, double l)
{
  return fabs(f(u)) > fabs(f(l));
}

double iteration(double u, double l)
{
	double s = u - ((f(u)*(l-u)) / (f(l)-f(u)));
	int n = 0;

	while ( abs(s-u) > E && abs(l-s) > E){
	n++;
	cout << n << "\t" << s << endl;
      if (closerlimit(u,l)){
        l = s;
	}

      else {
        u = s;
 	 }

	s = u - ((f(u)*(l-u)) / (f(l)-f(u)));
	}

  return  s;
}

