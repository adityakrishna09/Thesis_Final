// CTMC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>
#include<vector>
#include<cmath>

float f_01 = 0.002;
float f_12 = 0.004;
float f_21 = 0.0008;
float f_20 = 0.002;
using namespace Eigen;
using namespace std;


int main()
{

	int n = 3;
	MatrixXf Q(n, n);

	Vector3f b;
	Matrix3f A;
	MatrixXf Q_1(n, n);
	VectorXf P;
	VectorXf c(n);
	VectorXf b_1;
	Matrix3f del_Q;
	float del_t = 5;
	int t = 2780;
	int i;
	Q << -(f_01), f_01, 0,
		0, -(f_12), f_12,
		f_20, f_21, -(f_20 + f_21);
	A << -(f_01), 0, f_20,
		0, -(f_12), f_21,
		1, 1, 1;
	//Matrix3f A = Q.transpose();
	b << 0, 0, 1;
	for (i = 0; i < n; i++) {
		if (i != n) {
			c[i] = 0;
		}
		c[n - 1] = 1;
	}

	//cout << "Here is the Generator matrix Q:\n" << Q << endl;
	//cout << "Q1 size is \n" << Q_1.rows() << "x" << Q_1.cols() << endl;
	//cout << "Here is the Probability matrix A:\n" << A << endl;
	//cout << "c size is \n" << c.rows() << "x" << c.cols() << endl;
	//cout << "Here is the State Vector b:\n" << c << endl;
	VectorXf x = A.fullPivHouseholderQr().solve(c);
	cout << "The probability state vector solution is:\n" << x << endl;
	MatrixXf Q_d = Q * del_t;
	//cout << "delta Q is : \n" << Q_d << endl;
	del_Q = Q_d.exp();
	//cout << "Matrix Exponential is \n" << del_Q << endl;
	//P = del_Q*x;
	VectorXf P_n = x;
	for (int k = 0; k < t; k++) {
		P = del_Q * P_n;
		P_n = P;
		cout << " state now of probability is : \n" << P << endl;

	}
	cout << "Final state of probability is : \n" << P << endl;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
