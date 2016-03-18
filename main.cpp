// Sys and opt Lab 1
// Chapter 2 - 2a,c
// Author Caleb Reder

// Bissection method
// Eq a: e^x -3x^2 = 0
// Ex b: e^x - 1 / (.1+x^2) = 0

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <limits>

using namespace std;

// define e as 2.718...
const double e = exp(1.0);

//define error as 10 ^ -5
const double E = pow(10,-5);

int n = 0;

double f1(double x);

double bisect1(double a, double b, double root, double err);

int main(){

/*
 Bisection Method by the book
bisect(f,a,b,root,e)
e = error = 10 ^ -5

1. Define c = (a+b)/2;
2. if b-c < e then accept c is root and return
3. Else if sign (f(b)) * sign (f(c)) <= 0 then a - c else b = c
4. Loop back to 1.
*/

cout.precision(17);
std::cout << std::fixed;

double a ,b;
double tem1,tem2;

cout << "The first equation is e^x - 3x^2 = 0 \n\n";

cout << "Enter the value of a (left boundary):\n";
cin >> a;
cout << "Enter the value of b (right boundary):\n";
cin >> b;

cout << "Below is a table of the values computed from using the Bisection Method on equation 1:\n\n";
cout <<"n\t\ta\t\t\tb\t\t\tc\t\t\tf(a)\t\t\tf(b)\t\t\tf(c) " << endl;
cout << "________________________________________________________________________________________________________________________________________________________\n";

cout << "\nThe root of equation 1 in the interval [" << a << "," << b<< "] is: " << bisect1(a,b,0,E) << "\n\n";

}

double f1(double x){
// Eq a: e^x -3x^2 = 0

return 1 + .30 * cos(x) - x;

}

double bisect1(double a, double b, double root, double err){

double c = (a+b) /2.0;

cout << n << "\t" << a << "\t" << b << "\t" << c << "\t" << f1(a) << "\t"
	<< f1(b) << "\t" << f1(c) << endl;

if ((b -c) < err){
	root = c;
	n=0;
	return root;
}

else {

if ( (f1(b) * f1(c)) <= 0){

a = c;
}

else {
b = c;
}

}

n++;
return bisect1(a,b,root,err);

}


