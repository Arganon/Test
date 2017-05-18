#ifndef MATRIX2_H
#define MATRIX2_H

#include <cstdlib>
#include <iostream>
#include <vector>

template<typename T>
class Matrix2 {
	private:
		int rows;
		int columns;
		std::vector<std::vector<T> > matrix;
	public:
		Matrix2(int rows, int columns);
		~Matrix2();
		void fillTheMatrix();
		void makeZeroMatrix();
		void setRowsAndColumns(int rows, int columns);
		void setMatrix(const std::vector<std::vector<T> > &temp);
		int getRows() const;
		int getColumns() const;
		std::vector<std::vector<T> > getMatrix() const;
		T getValue(unsigned int row_index, unsigned int column_index) const;
		void setValue(unsigned int row_index, unsigned int column_index, T value);
		bool isEmpty() const;
		Matrix2<T>& operator =(const Matrix2<T> &other);
		void show() const;
};

#endif // MATRIX2_H
