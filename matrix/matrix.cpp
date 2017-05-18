#include "matrix.h"

template<typename T>
Matrix<T>::Matrix(int rows, int columns) : rows(rows), columns(columns) {}


template<typename T>
Matrix<T>::~Matrix() {}

template<typename T>
void Matrix<T>::setRowsAndColumns(int rows, int columns) {
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
void Matrix<T>::makeZeroMatrix() {
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
void Matrix<T>::fillTheMatrix() {
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
void Matrix<T>::setValue(unsigned int row_index, unsigned int column_index, T value) {
	if (!getRows()) {
		makeZeroMatrix();
	}
	if (row_index > getRows() || column_index > getColumns()) {
		exit(1);
	}
	matrix[row_index][column_index] = value;
}

template<typename T>
int Matrix<T>::getRows() const {
	return this->matrix.size();
}

template<typename T>
int Matrix<T>::getColumns() const {
	if (this->matrix.size()) {
		return this->matrix[0].size();
	}
	return 0;
}

template<typename T>
Matrix<T>& Matrix<T>::operator =(const Matrix<T> &other) {
	this->rows = other.getRows();
	this->columns = other.getColumns();
	this->matrix = other.getMatrix();
	return *this;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> &other) const {
	if (this->rows != other.getRows() && this->columns != other.getColumns()) {
		return false;
	}
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			if (matrix[i][j] != other.getValue(i,j)) {
				return false;
			}
		}
	}
	return true;
}

template<typename T>
bool Matrix<T>::operator!=(const Matrix<T> &other) const {
	return !operator==(other);
}

template<typename T>
void Matrix<T>::operator+=(const Matrix<T> &other) {
	if (isEmpty()) {
		exit(1);
	}
	if (!compareSize(other)) {
		exit(1);
	}
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			matrix[i][j] += other.getValue(i, j);
		}
	}
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) {
	if (isEmpty()) {
		exit(1);
	}
	Matrix<T> sum = *this;
	sum += other;
	return sum;
}

template<typename T>
void Matrix<T>::operator-=(const Matrix<T> &other) {
	if (isEmpty()) {
		exit(1);
	}
	if (!compareSize(other)) {
		exit(1);
	}
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j <matrix[i].size(); j++) {
			matrix[i][j] -= other.getValue(i, j);
		}
	}
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &other) {
	if (isEmpty()) {
		exit(1);
	}
	Matrix<T> diff = *this;
	diff -= other;
	return diff;
}

template<typename T>
void Matrix<T>::operator*=(const Matrix<T> &other) {
	if (isEmpty()) {
		exit(1);
	}
	if (this->columns != other.getRows()) {
		exit(1);
	}
	std::vector<std::vector<T> > temp_row;
	for (int i = 0; i < this->rows; i++) {
		std::vector<T> temp_coll;
		for (int j = 0; j < other.getColumns(); j++) {
			T sum = 0;
			for (int q = 0; q < this->columns; q++) {
				sum += this->matrix[i][q] * other.getValue(q, j);
			}
			temp_coll.push_back(sum);
		}
		temp_row.push_back(temp_coll);
	}
	this->columns = other.getColumns();
	this->matrix = temp_row;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) {
	if (isEmpty()) {
		exit(1);
	}
	Matrix<T> buffer = *this;
	buffer *= other;
	return buffer;
}

template<typename T>
bool Matrix<T>::compareSize(const Matrix<T> &other) const {
	if (this->rows == other.getRows() && this->columns == other.getColumns()) {
		return true;
	}
	return false;
}

template<typename T>
std::vector<std::vector<T> > Matrix<T>::getMatrix() const {
	if (isEmpty()) {
		exit(1);
	}
	return this->matrix;
}

template<typename T>
T Matrix<T>::getValue(unsigned int row_index, unsigned int column_index) const {
	if (row_index > rows || column_index > columns) {
		exit(1);
	}
	return matrix[row_index][column_index];
}

template<typename T>
bool Matrix<T>::isEmpty() const {
	if (!this->matrix.size()) {
		return true;
	}
	return false;
}

template<typename T>
void Matrix<T>::show() const {
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

template class Matrix<int>;
template class Matrix<float>;
template class Matrix<double>;
template class Matrix<long>;
