#include <iostream>
#include <iomanip>
#include "SquareMatrix.h"
#include "Determinant.h"
#include <vector>
using namespace std;
//�ڲ�����ͬ����ͻ������£���̫�������������ƺ��ǻ�������

//Ĭ�Ϲ��캯��
SquareMatrix::SquareMatrix() :Matrix(0, 0, nullptr) {
	order = 0;
}

//���ƹ��캯��(���)
SquareMatrix::SquareMatrix(const SquareMatrix& other) :Matrix(other.Matrix::row, other.Matrix::column, other.Matrix::getMatrixData()) {
	//����
	order = other.order;
}

//��ֵ��������أ������
SquareMatrix& SquareMatrix::operator=(const SquareMatrix& other)
{
	//��� ���ﻹ����ֱ�ӵ��ø�ֵ���캯������Ȼ����ԭ����=
	//���࿽��
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
	//����
	order = other.order;
	return *this;
}

// �û��ֶ�����Ĺ��캯��
SquareMatrix::SquareMatrix(int order) :Matrix(order, order) {
	this->order = order;
}

// �����ֶ�����Ĺ��캯��
SquareMatrix::SquareMatrix(int order, double** nData) :Matrix(order, order, nData) {
	this->order = order;
}

//����N�׵�λ��
SquareMatrix::SquareMatrix(int order, SpecialMatrix type) :Matrix(order, order, nullptr) {
	this->order = order;
	//���������๹�캯������ǰ�������ȵ��û���Ĺ��캯����������nullptr�������
	//����������
	double** nData = new double* [order];
	for (int i = 0; i < order; i++)
	{
		nData[i] = new double[order];
		for (int j = 0; j < order; j++)
		{
			if (i == j)
			{
				//�ԽǷ���Ϊ1
				nData[i][j] = 1;
			}
			else {
				nData[i][j] = 0;
			}
		}
	}
	//����������ŷ��ʸ������
	Matrix::setMatrixData(nData);
}

// ����������ʽ��ֵ
double SquareMatrix::getDetValue() {
	//cal������Determinant��ĳ�Ա�������Ǿ�̬������ֱ�ӵ���
	Determinant det(order, Matrix::getMatrixData());
	return det.calculate();
}

//�����������ʽ(��������ʽ�ǲ���Ҫ����aij����ģ�������ʽ����������û�ж������Ž������ж�)
double SquareMatrix::getCofactor(int r, int c) {
	double** matrixData = Matrix::getMatrixData();
	//�ҵ���������ʽ��Ӧ������ʽ
	double** nData = new double* [order - 1];
	//��ʼ��nData
	for (int i = 0; i < order - 1; i++)
	{
		nData[i] = new double[order - 1];
		for (int j = 0; j < order - 1; j++)
		{
			nData[i][j] = 0;
		}
	}
	//����nData
	int posr = 0, posc = 0; //posr �� posc��ӦnData������
	for (int i = 0; i < order; i++)
	{
		if (i != r)
		{
			for (int j = 0; j < order; j++) {
				//����һ��ԭʼ���󣬴��г��Ԫ�طŽ�nData
				if (j != c)
				{
					nData[posr][posc] = matrixData[i][j];
					posc++;
					if (posc == order - 1)
					{ //֤��һ���Ѿ�������
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
	{//Ϊ����,����ʽΪ��
		ret = -ret;
	}
	return ret;//��һ����
}

//����������
SquareMatrix SquareMatrix::getAdjoint() {
	//�����ÿ��Ԫ�صĴ�������ʽ����ת��
	double** nData = new double* [order];
	//������ǰ����nData�ĳ�ʼ������Ȼ����j��i��ʱ����������Խ��
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

//��������
SquareMatrix SquareMatrix::getInverse() {
	//�������=�������/������ʽ
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
		cout << "�÷���Ϊ���췽���޷����棡" << endl;
		return *this;
	}
}

SquareMatrix MultiplySMatrix(const SquareMatrix& m1, const SquareMatrix& m2)
{
	//ǿ������ת������Matrix�����س˷�
	Matrix tmp = Matrix(m1) * Matrix(m2);
	return SquareMatrix(m1.Matrix::row, tmp.getMatrixData());
}

SquareMatrix SquareMatrixCin()
{
	vector<double> container;//��ʱ�洢����
	int order = 0; //����
	double tmp;
	//�����һ������
	cout << "�������ⷽ�󣺣����һ������e��ֹ��" << endl;
	do {
		cin >> tmp;
		container.push_back(tmp);
		order++;
	} while (cin.get() != '\n');

	//�����Ѿ�ȷ�������������
	string firstChar;
	while (1) {
		cin >> firstChar;
		if (firstChar == "e")
		{
			break;
		}
		else {
			//���firstChat��Ϊe�������һ��
			container.push_back(atof(firstChar.data()));
			//��ʱ����һ������Ӧ���ǿո�
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
