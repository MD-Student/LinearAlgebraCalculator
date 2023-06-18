#include "MyVector.h"
#include <iostream>
using namespace std;
// 构造函数
MyVector::MyVector(int r, double* components) :row(r), data(components){}


double MyVector::operator*(const MyVector& other) const
{
	if (row == other.row)
	{
		double result = 0;
		for (int i = 0; i < row; i++)
		{
			result += data[i] * other.data[i];
		}
		return result;
	}
	else {
		//向量分量个数不同则返回前者
		cerr << "向量分量个数不同，无法相乘！";
		/*在进行乘法运算之前，就应该判断能否相乘，
		这个逻辑不应该写进乘法重载里面*/
		return 0.0f;
	}
}
