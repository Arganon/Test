#ifndef MATOPER_H
#define MATOPER_H

#include <cstdlib>
#include <vector>
#include "matrix2.h"

template <typename T>
class MatOper {
	public:
		MatOper();
		~MatOper();
		Matrix2<T> sum(const Matrix2<T> &a, const Matrix2<T> &b);
		bool compareSize(const Matrix2<T> &a, const Matrix2<T> &b) const;
		Matrix2<T> subtraction(const Matrix2<T> &a, const Matrix2<T> &b);
		Matrix2<T> multiply(const Matrix2<T> &a, const Matrix2<T> &b);
};

#endif // MATOPER_H
