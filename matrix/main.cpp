#include <cstdlib>
#include <iostream>
#include "matrix.h"
#include "matrix2.h"
#include "matrix_operations.h"

int main() {

	Matrix2<int> a(2, 2);
	Matrix2<int> b(2, 2);
	Matrix2<int> c(2, 2);

	MatOper<int> oper;

	Matrix<int> d(2, 2);
	Matrix<int> e(2, 2);
	Matrix<int> f(2, 2);

		
	a.fillTheMatrix();
	b.fillTheMatrix();
	d.fillTheMatrix();
	e.fillTheMatrix();


	std::cout << "No changes:\nmatrix a: \n";
	a.show();
	std::cout << "matrix b: \n";
	b.show();

	std::cout << "\n-----------------------------\na = b\n";
	a = b;
	std::cout << "matrix a: \n";
	a.show();
	std::cout << "matrix b: \n";
	b.show();
	std::cout << "-----------------------------\nc = oper.sum(a, b)\n";
	c = oper.sum(a, b);
	std::cout << "matrix c: \n";
	c.show();
	std::cout << "matrix a: \n";
	a.show();
	std::cout << "matrix b: \n";
	b.show();

	std::cout << "-----------------------------\nc = oper.subtraction(a, b)\n";
	c = oper.subtraction(a, b);
	std::cout << "matrix c: \n";
	c.show();
	std::cout << "matrix a: \n";
	a.show();
	std::cout << "matrix b: \n";
	b.show();

	std::cout << "-----------------------------\nc = oper.multiply(a, b)\n";

	c = oper.multiply(a, b);
	std::cout << "matrix c: \n";
	c.show();
	std::cout << "matrix a: \n";
	a.show();
	std::cout << "matrix b: \n";
	b.show();


	std::cout << "-----------------------------\nf = d + e\n";
	f = d + e;
	std::cout << "matrix f: \n";
	f.show();
	std::cout << "matrix d: \n";
	d.show();
	std::cout << "matrix e: \n";
	e.show();

	std::cout << "-----------------------------\nf = d - e\n";
	f = d - e;
	std::cout << "matrix f: \n";
	f.show();
	std::cout << "matrix d: \n";
	d.show();
	std::cout << "matrix e: \n";
	e.show();

	std::cout << "-----------------------------\nd += e\n";
	d += e;
	std::cout << "matrix d: \n";
	d.show();
	std::cout << "matrix e: \n";
	e.show();

	std::cout << "-----------------------------\nd -= e\n";
	d -= e;
	std::cout << "matrix d: \n";
	d.show();
	std::cout << "matrix e: \n";
	e.show();

	std::cout << "-----------------------------\nf = d * e\n";
	f = d * e;
	std::cout << "matrix f: \n";
	f.show();
	std::cout << "matrix d: \n";
	d.show();
	std::cout << "matrix e: \n";
	e.show();

	std::cout << "-----------------------------\nd *= e\n";
	d *= e;
	std::cout << "matrix d: \n";
	d.show();
	std::cout << "matrix e: \n";
	e.show();

	return 0;
}
