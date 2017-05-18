#include "matrix2.h"

template<typename T>
Matrix2<T>::Matrix2(int rows, int columns) : rows(rows), columns(columns) {}

template<typename T>
Matrix2<T>::~Matrix2() {}

template<typename T>
void Matrix2<T>::setRowsAndColumns(int rows, int columns) {
	if (!isEmpty()) {
		exit(1);
	}
	if (rows == 0) {
		exit(1);
	}
	this->rows = rows;
	this->columns = columns;
	makeZeroMatrix();
} 

template<typename T>
void Matrix2<T>::makeZeroMatrix() {
	std::vector<std::vector<T> > temp_row;
	for (int i = 0; i < this->rows; i++) {
		std::vector<T> temp_coll;
		for (int j = 0; j < this->columns; j++) {
			temp_coll.push_back(0);
		}
		temp_row.push_back(temp_coll);
	}
	this->matrix = temp_row;
}

template<typename T>
void Matrix2<T>::fillTheMatrix() {
	T value;
	for (int i = 0; i < this->rows; i++) {
		std::vector<T> temp;
		std::cout << "Please, fill the " << i + 1 << " row." << std::endl;
		for (int j = 0; j < this->columns; j++) {
			std::cin >> value;
			temp.push_back(value);
		}
		matrix.push_back(temp);
	}
	std::cout << "Matrix is filled!" << std::endl;
}

template<typename T>
void Matrix2<T>::setMatrix(const std::vector<std::vector<T> > &temp) {
	this->matrix = temp;
}

template<typename T>
void Matrix2<T>::setValue(unsigned int row_index, unsigned int column_index, T value) {
	if (!getRows()) {
		makeZeroMatrix();
	}
	if (row_index > getRows() || column_index > getColumns()) {
		exit(1);
	}
	matrix[row_index][column_index] = value;
}

template<typename T>
int Matrix2<T>::getRows() const {
	return this->matrix.size();
}

template<typename T>
int Matrix2<T>::getColumns() const {
	if (this->matrix.size()) {
		return this->matrix[0].size();
	}
	return 0;
}

template<typename T>
T Matrix2<T>::getValue(unsigned int row_index, unsigned int column_index) const {
	if (row_index > rows || column_index > columns) {
		exit(1);
	}
	return matrix[row_index][column_index];
}

template<typename T>
bool Matrix2<T>::isEmpty() const {
	if (!this->matrix.size()) {
		return true;
	}
	return false;
}

template<typename T>
Matrix2<T>& Matrix2<T>::operator=(const Matrix2<T> &other) {
	this->rows = other.getRows();
	this->columns = other.getColumns();
	this->matrix = other.getMatrix();
	return *this;
}

template<typename T>
std::vector<std::vector<T> > Matrix2<T>::getMatrix() const {
	if (isEmpty()) {
		exit(1);
	}
	return this->matrix;
}

template<typename T>
void Matrix2<T>::show() const {
	if (isEmpty()) {
		exit(1);
	}
	for (int i = 0; i < this->matrix.size(); i++) {
		for (int j = 0; j < this->matrix[i].size(); j++) {
			std::cout << this->matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

template class Matrix2<int>;
template class Matrix2<float>;
template class Matrix2<double>;
template class Matrix2<long>;
