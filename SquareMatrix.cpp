#include <iostream>
#include <iomanip>
#include "SquareMatrix.h"
#include "Determinant.h"
#include <vector>
using namespace std;
//在不存在同名冲突的情况下，加太多的作用域符号似乎是画蛇添足

//默认构造函数
SquareMatrix::SquareMatrix() :Matrix(0, 0, nullptr) {
	order = 0;
}

//复制构造函数(深拷贝)
SquareMatrix::SquareMatrix(const SquareMatrix& other) :Matrix(other.Matrix::row, other.Matrix::column, other.Matrix::getMatrixData()) {
	//本类
	order = other.order;
}

//赋值运算符重载（深拷贝）
SquareMatrix& SquareMatrix::operator=(const SquareMatrix& other)
{
	//深拷贝 这里还不能直接调用赋值构造函数，不然还是原来的=
	//基类拷贝
	Matrix::row = other.row;
	Matrix::column = other.column;
	double** nData = new double* [order];
	double** oData = other.getMatrixData();
	for (int i = 0; i < order; i++)
	{
		nData[i] = new double[order];
		for (int j = 0; j < order; j++)
		{
			nData[i][j] = oData[i][j];
		}
	}
	Matrix::setMatrixData(nData);
	//本类
	order = other.order;
	return *this;
}

// 用户手动输入的构造函数
SquareMatrix::SquareMatrix(int order) :Matrix(order, order) {
	this->order = order;
}

// 无需手动输入的构造函数
SquareMatrix::SquareMatrix(int order, double** nData) :Matrix(order, order, nData) {
	this->order = order;
}

//创建N阶单位阵
SquareMatrix::SquareMatrix(int order, SpecialMatrix type) :Matrix(order, order, nullptr) {
	this->order = order;
	//由于在子类构造函数调用前，必须先调用基类的构造函数，故先用nullptr替代，再
	//填充矩阵数据
	double** nData = new double* [order];
	for (int i = 0; i < order; i++)
	{
		nData[i] = new double[order];
		for (int j = 0; j < order; j++)
		{
			if (i == j)
			{
				//对角方向为1
				nData[i][j] = 1;
			}
			else {
				nData[i][j] = 0;
			}
		}
	}
	//用作用域符号访问父类变量
	Matrix::setMatrixData(nData);
}

// 方阵求行列式的值
double SquareMatrix::getDetValue() {
	//cal函数是Determinant类的成员函数，非静态，不能直接调用
	Determinant det(order, Matrix::getMatrixData());
	return det.calculate();
}

//计算代数余子式(代数余子式是不需要乘以aij本身的，和余子式的区别是有没有对正负号进行了判定)
double SquareMatrix::getCofactor(int r, int c) {
	double** matrixData = Matrix::getMatrixData();
	//找到代数余子式对应的行列式
	double** nData = new double* [order - 1];
	//初始化nData
	for (int i = 0; i < order - 1; i++)
	{
		nData[i] = new double[order - 1];
		for (int j = 0; j < order - 1; j++)
		{
			nData[i][j] = 0;
		}
	}
	//填入nData
	int posr = 0, posc = 0; //posr 和 posc对应nData的索引
	for (int i = 0; i < order; i++)
	{
		if (i != r)
		{
			for (int j = 0; j < order; j++) {
				//遍历一遍原始方阵，从中抽出元素放进nData
				if (j != c)
				{
					nData[posr][posc] = matrixData[i][j];
					posc++;
					if (posc == order - 1)
					{ //证明一行已经填满了
						posc = 0;
						posr++;
					}
				}
			}
		}
	}
	Determinant det(order - 1, nData);
	double ret = det.calculate();
	if ((r + c) % 2 == 1)
	{//为奇数,行列式为负
		ret = -ret;
	}
	return ret;//单一出口
}

//计算伴随矩阵
SquareMatrix SquareMatrix::getAdjoint() {
	//计算出每个元素的代数余子式，并转置
	double** nData = new double* [order];
	//必须提前进行nData的初始化，不然访问j，i的时候会产生数组越界
	for (int i = 0; i < order; i++)
	{
		nData[i] = new double[order];
	}
	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++) {
			nData[j][i] = this->getCofactor(i, j);
		}
	}
	return SquareMatrix(order, nData);
}

//矩阵求逆
SquareMatrix SquareMatrix::getInverse() {
	//矩阵的逆=伴随矩阵/其行列式
	double det = this->getDetValue();
	if (det)
	{
		double k = 1 / det;
		SquareMatrix adj = this->getAdjoint();
		for (int i = 0; i < order; i++)
		{
			adj.rowMultiplyScalar(i, k);
		}
		return adj;
	}
	else {
		cout << "该方阵为奇异方阵，无法求逆！" << endl;
		return *this;
	}
}

SquareMatrix MultiplySMatrix(const SquareMatrix& m1, const SquareMatrix& m2)
{
	//强制类型转换调用Matrix的重载乘法
	Matrix tmp = Matrix(m1) * Matrix(m2);
	return SquareMatrix(m1.Matrix::row, tmp.getMatrixData());
}

SquareMatrix SquareMatrixCin()
{
	vector<double> container;//临时存储输入
	int order = 0; //阶数
	double tmp;
	//读入第一行数据
	cout << "输入任意方阵：（最后一行输入e终止）" << endl;
	do {
		cin >> tmp;
		container.push_back(tmp);
		order++;
	} while (cin.get() != '\n');

	//列数已经确定，读入后续行
	string firstChar;
	while (1) {
		cin >> firstChar;
		if (firstChar == "e")
		{
			break;
		}
		else {
			//如果firstChat不为e，则读入一行
			container.push_back(atof(firstChar.data()));
			//此时，下一个读入应该是空格
			while (cin.get() != '\n') {
				cin >> tmp;
				container.push_back(tmp);
			}
		}
	}
	int row = container.size() / order;
	int cnt = 0;
	double** nData = new double* [row];
	for (int i = 0; i < row; i++)
	{
		nData[i] = new double[order];
		for (int j = 0; j < order; j++)
		{
			nData[i][j] = container.at(cnt);
			cnt++;
		}
	}
	return SquareMatrix(order, nData);
}
