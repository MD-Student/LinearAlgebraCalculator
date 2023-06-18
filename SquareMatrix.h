#pragma once
#include "Matrix.h"

class SquareMatrix :public Matrix {
	int order;
public:
	//默认构造函数
	SquareMatrix();
	// 用户手动输入的构造函数
	SquareMatrix(int order);
	//复制构造函数
	SquareMatrix(const SquareMatrix& other);
	//赋值运算符重载
	SquareMatrix& operator=(const SquareMatrix& other);
	// 无需手动输入的构造函数
	SquareMatrix(int order, double** nData);
	// N阶单位阵构造函数
	SquareMatrix(int order, SpecialMatrix type);
	// 方阵求行列式的值
	double getDetValue();
	//计算代数余子式
	double getCofactor(int r, int c);
	//计算伴随矩阵
	SquareMatrix getAdjoint();
	//矩阵求逆
	SquareMatrix getInverse();
};
//方阵的魔法输入
SquareMatrix SquareMatrixCin();
//方阵乘法
SquareMatrix MultiplySMatrix(const SquareMatrix& m1, const SquareMatrix& m2);