#include "Determinant.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
#define eps 1e-6

//默认构造函数
Determinant::Determinant() = default;

//构造函数(深拷贝)
Determinant::Determinant(int order, double** nData) {
	this->order = order;
	data = new double* [order];
	for (int i = 0; i < order; i++)
	{
		data[i] = new double[order];
		for (int j = 0; j < order; j++)
		{
			data[i][j] = nData[i][j];
		}
	}
}

//构造函数（手动输入）
Determinant::Determinant(int order) :order(order) {
	data = new double* [order];
	cout << "请输入行列式：" << endl;
	for (int i = 0; i < order; i++)
	{
		data[i] = new double[order];
		for (int j = 0; j < order; j++)
		{
			cin >> data[i][j];
		}
	}
}

//复制构造函数（深拷贝）
Determinant::Determinant(const Determinant& obj) {
	order = obj.order;
	data = new double* [order];
	for (int i = 0; i < order; i++)
	{
		data[i] = new double[order];
		for (int j = 0; j < order; j++)
		{
			data[i][j] = obj.data[i][j];
		}
	}
}

//赋值运算符（深拷贝）
Determinant& Determinant::operator=(const Determinant& other)
{
	order = other.order;
	data = new double* [order];
	for (int i = 0; i < order; i++)
	{
		data[i] = new double[order];
		for (int j = 0; j < order; j++)
		{
			data[i][j] = other.data[i][j];
		}
	}
	return *this;
}

//析构函数
Determinant::~Determinant() {
	delete[] data;
}

//递归函数，递归计算代数余子式
double Determinant::cal(double** det, int n)//det-行列式，n:行列式的阶数
{
	double detVal = 0;//行列式的值

	if (n == 1)//递归终止条件 
		return det[0][0];

	double** tempdet = new double* [n - 1];//用来存储余相应的余子式
	for (int i = 0; i < n - 1; i++)
		tempdet[i] = new double[n - 1];
	for (int i = 0; i < n; i++)//第一重循环，行列式按第一行展开 
	{
		for (int j = 0; j < n - 1; j++)
			for (int k = 0; k < n - 1; k++)
			{
				if (k < i)
					tempdet[j][k] = det[j + 1][k];
				else
					tempdet[j][k] = det[j + 1][k + 1];
			}
		detVal += det[0][i] * pow(-1.0, i) * cal(tempdet, n - 1);

	}
	return detVal;
}

//打印行列式
void Determinant::printDet() {
	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++) {
			cout << setw(12) << data[i][j];
		}
		cout << endl;
	}
}

//计算行列式的值
double Determinant::calculate() {
	return cal(data, order);
}

//行列式行倍加变换
void Determinant::rowMultiplyScalar(int r1, double k, int r2) {
	//将r1倍乘k加到r2上
	for (int i = 0; i < order; i++)
	{
		data[r2][i] += data[r1][i] * k;
	}
}

//判断一个浮点数是否为0
bool isZero(double x) {
	if (fabs(x) <= eps)
	{
		return true;
	}
	else {
		return false;
	}
}

//转换为上三角形式
Determinant Determinant::upperTriangle() {
	Determinant tmp(*this);
	for (int cnt = 0; cnt < order; cnt++)
	{
		if (isZero(tmp.data[cnt][cnt]))
		{
			//首行元素为0
			bool isAllZero = true;
			for (int i = cnt + 1; i < order; i++)
			{
				if (!isZero(tmp.data[i][cnt])) {
					isAllZero = false;
					//交换第i行与首行（cnt行）
					for (int j = 0; j < order; j++)
					{
						double buffer = tmp.data[cnt][j];
						tmp.data[cnt][j] = tmp.data[i][j];
						//两行交换之后，行列式前有一个负号，将负号提到第i行
						tmp.data[i][j] = -buffer;
						break;
					}
				}
			}
			if (isAllZero)
			{
				continue;
			}
		}
		//将首列除左上角外全部置0
		for (int i = cnt + 1; i < order; i++)
		{
			tmp.rowMultiplyScalar(cnt, -(tmp.data[i][cnt] / tmp.data[cnt][cnt]), i);
		}
	}
	return tmp;
}

//行列式的魔法输入
Determinant DeterminantCin() {
	vector<double> container;//临时存储输入
	int order = 0; //阶数
	double tmp;
	//读入第一行数据
	cout << "请输入任意行列式：（最后一行输入e终止）" << endl;
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
	return Determinant(order, nData);
}