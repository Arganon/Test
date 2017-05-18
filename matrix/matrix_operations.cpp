#include "matrix_operations.h"

template<typename T>
MatOper<T>::MatOper() {}

template<typename T>
MatOper<T>::~MatOper() {}

template<typename T>
Matrix2<T> MatOper<T>::sum(const Matrix2<T> &a, const Matrix2<T> &b) {
	if (a.isEmpty() || b.isEmpty()) {
		exit(1);
	}
	if (!compareSize(a, b)) {
		exit(1);
	}
	Matrix2<T> sum = a;
	for (int i = 0; i < sum.getRows(); i++) {
		for (int j = 0; j < sum.getColumns(); j++) {
			T result = sum.getValue(i, j);
			result += b.getValue(i, j);
			sum.setValue(i, j, result);
		}
	}
	return sum;
}

template<typename T>
bool MatOper<T>::compareSize(const Matrix2<T> &a, const Matrix2<T> &b) const {
	if (a.getRows() == b.getRows() && a.getColumns() == b.getColumns()) {
		return true;
	}
	return false;
}

template<typename T>
Matrix2<T> MatOper<T>::subtraction(const Matrix2<T> &a, const Matrix2<T> &b) {
	if (a.isEmpty() || b.isEmpty()) {
		exit(1);
	}
	if (!compareSize(a, b)) {
		exit(1);
	}

	Matrix2<T> diff = a;
	for (int i = 0; i < diff.getRows(); i++) {
		for (int j = 0; j < diff.getColumns(); j++) {
			int result = diff.getValue(i, j);
			result -= b.getValue(i, j);
			diff.setValue(i, j, result);
		}
	}
	return diff;
}

template<typename T>
Matrix2<T> MatOper<T>::multiply(const Matrix2<T> &a, const Matrix2<T> &b) {
	if (a.isEmpty() || b.isEmpty()) {
		exit(1);
	}
	if (a.getColumns() != b.getRows()) {
		exit(1);
	}
	std::vector<std::vector<T> > temp_row;
	for (int i = 0; i < a.getRows(); i++) {
		std::vector<T> temp_coll;
		for (int j = 0; j < b.getColumns(); j++) {
			T sum = 0;
			for (int q = 0; q < a.getColumns(); q++) {
				sum += a.getValue(i, q) * b.getValue(q, j);
			}
			temp_coll.push_back(sum);
		}
		temp_row.push_back(temp_coll);
	}
	Matrix2<T> temp(a.getRows(), b.getColumns());
	temp.setMatrix(temp_row);
	return temp;
}

template class MatOper<int>;
template class MatOper<float>;
template class MatOper<double>;
template class MatOper<long>;
