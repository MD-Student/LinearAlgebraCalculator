#include "MyVector.h"
#include <iostream>
using namespace std;
// ���캯��
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
		//��������������ͬ�򷵻�ǰ��
		cerr << "��������������ͬ���޷���ˣ�";
		/*�ڽ��г˷�����֮ǰ����Ӧ���ж��ܷ���ˣ�
		����߼���Ӧ��д���˷���������*/
		return 0.0f;
	}
}
