#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cstdlib>
#include <vector>

template<typename T>
class Matrix {
	private:
		int rows;
		int columns;
		std::vector<std::vector<T> > matrix;

	public:
		Matrix(int rows, int columns);
		~Matrix();
		int getRows() const;
		int getColumns() const;
		void setRowsAndColumns(int rows, int columns);
		Matrix<T>& operator =(const Matrix<T> &other);
		bool operator==(const Matrix<T> &other) const;
		bool operator!=(const Matrix<T> &other) const;
		void operator+=(const Matrix<T> &other);
		Matrix<T> operator+(const Matrix<T> &other);
		void operator-=(const Matrix<T> &other);
		Matrix<T> operator-(const Matrix<T> &other);
		void operator*=(const Matrix<T> &other);
		Matrix<T> operator*(const Matrix<T> &other);
		void makeZeroMatrix();

		bool isEmpty() const;
		bool compareSize(const Matrix<T> &other) const;
		std::vector<std::vector<T> > getMatrix() const;
		T getValue(unsigned int row_index, unsigned int column_index) const;
		void setValue(unsigned int row_index, unsigned int column_index, T value);
		void fillTheMatrix();
		void show() const;
};

#endif // MATRIX_H
