#include "Determinant.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
#define eps 1e-6

//Ĭ�Ϲ��캯��
Determinant::Determinant() = default;

//���캯��(���)
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

//���캯�����ֶ����룩
Determinant::Determinant(int order) :order(order) {
	data = new double* [order];
	cout << "����������ʽ��" << endl;
	for (int i = 0; i < order; i++)
	{
		data[i] = new double[order];
		for (int j = 0; j < order; j++)
		{
			cin >> data[i][j];
		}
	}
}

//���ƹ��캯���������
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

//��ֵ������������
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

//��������
Determinant::~Determinant() {
	delete[] data;
}

//�ݹ麯�����ݹ�����������ʽ
double Determinant::cal(double** det, int n)//det-����ʽ��n:����ʽ�Ľ���
{
	double detVal = 0;//����ʽ��ֵ

	if (n == 1)//�ݹ���ֹ���� 
		return det[0][0];

	double** tempdet = new double* [n - 1];//�����洢����Ӧ������ʽ
	for (int i = 0; i < n - 1; i++)
		tempdet[i] = new double[n - 1];
	for (int i = 0; i < n; i++)//��һ��ѭ��������ʽ����һ��չ�� 
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

//��ӡ����ʽ
void Determinant::printDet() {
	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++) {
			cout << setw(12) << data[i][j];
		}
		cout << endl;
	}
}

//��������ʽ��ֵ
double Determinant::calculate() {
	return cal(data, order);
}

//����ʽ�б��ӱ任
void Determinant::rowMultiplyScalar(int r1, double k, int r2) {
	//��r1����k�ӵ�r2��
	for (int i = 0; i < order; i++)
	{
		data[r2][i] += data[r1][i] * k;
	}
}

//�ж�һ���������Ƿ�Ϊ0
bool isZero(double x) {
	if (fabs(x) <= eps)
	{
		return true;
	}
	else {
		return false;
	}
}

//ת��Ϊ��������ʽ
Determinant Determinant::upperTriangle() {
	Determinant tmp(*this);
	for (int cnt = 0; cnt < order; cnt++)
	{
		if (isZero(tmp.data[cnt][cnt]))
		{
			//����Ԫ��Ϊ0
			bool isAllZero = true;
			for (int i = cnt + 1; i < order; i++)
			{
				if (!isZero(tmp.data[i][cnt])) {
					isAllZero = false;
					//������i�������У�cnt�У�
					for (int j = 0; j < order; j++)
					{
						double buffer = tmp.data[cnt][j];
						tmp.data[cnt][j] = tmp.data[i][j];
						//���н���֮������ʽǰ��һ�����ţ��������ᵽ��i��
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
		//�����г����Ͻ���ȫ����0
		for (int i = cnt + 1; i < order; i++)
		{
			tmp.rowMultiplyScalar(cnt, -(tmp.data[i][cnt] / tmp.data[cnt][cnt]), i);
		}
	}
	return tmp;
}

//����ʽ��ħ������
Determinant DeterminantCin() {
	vector<double> container;//��ʱ�洢����
	int order = 0; //����
	double tmp;
	//�����һ������
	cout << "��������������ʽ�������һ������e��ֹ��" << endl;
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
	return Determinant(order, nData);
}