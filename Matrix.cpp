#include "Matrix.h"
#include <iostream>
#include <iomanip>
#include "MyVector.h"
#include <cmath>
#include <vector>
using namespace std;
#define eps 1e-6
//Ĭ�Ϲ��캯��
Matrix::Matrix() {
	row = 0;
	column = 0;
	data = nullptr;
}
// ���캯��
Matrix::Matrix(int r, int c) {
	row = r;
	column = c;
	cout << "�����·��������" << endl;
	/*data������Ϊdouble** Ҳ����ָ��double*��ָ�룬
	* Ҳ�Ϳ��������Ǵ洢double*�����飬���data�д洢��Ԫ��
	* ����ÿһ��������׵�ַ��
	*/
	data = new double* [r]; //row
	for (int i = 0; i < r; i++)
	{
		data[i] = new double[c]; //column
		for (int j = 0; j < c; j++)
		{
			cin >> data[i][j];
		}
	}
}

// ����Ҫ�û��ֶ�����Ĺ��캯���������
Matrix::Matrix(int r, int c, double** matrixData) {
	row = r;
	column = c;
	data = new double* [row];
	for (int i = 0; i < row; i++)
	{
		data[i] = new double[column];
		for (int j = 0; j < column; j++)
		{
			data[i][j] = matrixData[i][j];
		}
	}
}

//���ƹ��캯���������
Matrix::Matrix(const Matrix& mat) {
	//Ĭ�ϵĸ��ƹ��캯����ǳ���������ᴴ�����µ�data���飬�����Ҫ��д���ƹ��캯��
	row = mat.row;
	column = mat.column;
	data = new double* [row];
	for (int i = 0; i < row; i++)
	{
		data[i] = new double[column];
		for (int j = 0; j < column; j++)
		{
			data[i][j] = mat.data[i][j];
		}
	}
}

//������캯��
Matrix::Matrix(int r, int c, SpecialMatrix type)
{
	row = r;
	column = c;
	data = new double* [r];
	if (type == Matrix::NullMatrix)
	{
		//����r*c�����
		for (int i = 0; i < r; i++)
		{
			data[i] = new double[c];
			for (int j = 0; j < c; j++)
			{
				data[i][j] = 0;
			}
		}
	}
}

//��������
Matrix::~Matrix() {
	delete[] data;
	//data��������new��̬�����ģ�������ʽ�ͷ�
}

//��ֵ���������
Matrix& Matrix::operator=(const Matrix& other) {
	//������Ĭ�ϴ����ĸ�ֵ�����Ϊǳ�㿽������������ص��ڴ��ͻ
	row = other.row;
	column = other.column;
	data = new double* [row];
	for (int i = 0; i < row; i++)
	{
		data[i] = new double[column];
		for (int j = 0; j < column; j++)
		{
			data[i][j] = other.data[i][j];
		}
	}
	return *this;
}

// �ӷ�����
Matrix Matrix::operator+ (const Matrix& other) const {
	if (row == other.row && column == other.column)
	{
		double** nData = new double* [row];
		for (int i = 0; i < row; i++)
		{
			nData[i] = new double[column];
			for (int j = 0; j < column; j++)
			{
				nData[i][j] = data[i][j] + other.data[i][j];
			}
		}
		return Matrix(row, column, nData);
		//todo ��ѵй¶
	}
	else {
		cerr << "����ͬ�ͣ��޷����мӷ����㣡" << endl;
		// ����ǰ��
		return *this;
	}
}

// +=���������
Matrix& Matrix::operator+= (const Matrix& other) {
	*this = *this + other;
	return *this;
}

// �˷�����
Matrix Matrix::operator* (const Matrix& other) const {
	// this�ҳ�һ������
	// a*b b*c �õ�һ��a*c�ľ���
	if (column == other.row)
	{
		double** nData = new double* [row];
		// �¾������ݳ�ʼ��
		for (int i = 0; i < row; i++)
		{
			nData[i] = new double[other.column];
		}
		// �����¾�������
		for (int i = 0; i < row; i++)
		{
			MyVector v1(column, data[i]);
			for (int j = 0; j < other.column; j++) {
				/*�¾����i�е�j�е�������������i�����Ҿ����j���ڻ�
				C++��ά���鲢����ֱ��ȡ����ĳһ�����ݣ������Ҫ�ֶ���ȡ
				�������ת��֮��ȡ��j�У����Ӷ�Ϊnƽ��������ѡ�����һ��
				��j�У����Ӷ�Ϊn*/
				double* rightColumn = new double[other.row];
				for (int i2 = 0; i2 < other.row; i2++)
				{
					rightColumn[i2] = other.data[i2][j];
				}
				//���������ڻ�����
				MyVector v2(other.row, rightColumn);
				nData[i][j] = v1 * v2;
			}
		}
		return Matrix(row, other.column, nData);
	}
	else {
		cerr << "�����޷����г˷����㣡" << endl;
		// ����ǰ��
		return *this;
	}
}

//*=���������
Matrix& Matrix::operator*= (const Matrix& other) {
	*this = *this * other;
	return *this;
}

//�������������
Matrix Matrix::operator-(const Matrix& other) const
{
	if (row == other.row && column == other.column)
	{
		double** nData = new double* [row];
		for (int i = 0; i < row; i++)
		{
			nData[i] = new double[column];
			for (int j = 0; j < column; j++)
			{
				nData[i][j] = data[i][j] - other.data[i][j];
			}
		}
		return	Matrix(row, column, nData);
	}
	else {
		cerr << "����ͬ�ͣ��޷������" << endl;
		return *this;
	}
}

//-=���������
Matrix& Matrix::operator-=(const Matrix& other)
{
	*this = *this - other;
	return *this;
}

//�Ҳ��������������
Matrix Matrix::operator* (const double& other) const {
	double** nData = new double* [row];
	for (int i = 0; i < row; i++)
	{
		nData[i] = new double[column];
		for (int j = 0; j < column; j++) {
			nData[i][j] = data[i][j] * other;
		}
	}
	return Matrix(row, column, nData);
}

//�Ҳ�����*=����
Matrix& Matrix::operator*= (const double& other) {
	*this = *this * other;
	return *this;
}

//����������������(�ǳ�Ա����)
Matrix operator* (const double k, const Matrix& mat) {
	//֮����ʹ����Ԫ����������Ϊ��Ԫ�����ܹ�ֱ�ӷ������е�˽�г�Ա������������
	//����ӿڵ��鷳
	return (mat * k);
}

Matrix operator*= (const double k, Matrix& mat) {
	//������ѯ���ϵ�֪����Ԫ�����޷�����thisָ�룬����ֻ��ֱ�Ӳ�����ʵ������
	for (int i = 0; i < mat.row; i++)
	{
		for (int j = 0; j < mat.column; j++) {
			mat.data[i][j] *= k;
		}
	}
	return mat;
}

//��ӡ����
void Matrix::printMatrix() {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++) {
			if (fabs(data[i][j]) < eps) {
				cout << setw(12) << 0;
			}
			else {
				cout << setw(12) << data[i][j];
			}			
		}
		cout << endl;
	}
}

// ����ת��
Matrix Matrix::transpose() {
	// ��i j��Ԫ�أ�����ת��֮���j i��Ԫ��

	//��ʼ���¾�������
	double** nData = new double* [column];
	for (int i = 0; i < column; i++)
	{
		nData[i] = new double[row];
	}
	//��������
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++) {
			nData[j][i] = data[i][j];
		}
	}
	//����ת�þ���
	return Matrix(column, row, nData);
}

//�Ի��任
//�жԻ��任����������ʵ�֣���С�������ÿ���
Matrix& Matrix::rowInterchange(int r1, int r2) {
	//������ʱ��
	// FIXME �����������Ǳ�������
	//���еĲ���û��ʹ��ѭ������˿�������������
	double* tmp = new double[column];
	tmp = data[r1];
	data[r1] = data[r2];
	data[r2] = tmp;
	//֮�����ڸı���ԭ������������»�����һ������ָ��
	//��Ϊ�˷�������������õ�����ֵ
	return *this;
}

Matrix& Matrix::columnInterchange(int c1, int c2) {
	//������ʱ��
	double tmp = 0;
	for (int i = 0; i < row; i++)
	{
		//����c1�е����ݲ��洢��tmp��
		tmp = data[i][c1];
		//c1�е����ݸ���Ϊc2��
		data[i][c1] = data[i][c2];
		//c2�д洢֮ǰ��c1������
		data[i][c2] = tmp;
		//���Ӷ�ΪO��n��
	}
	return *this;
}

//���˱任
Matrix& Matrix::rowMultiplyScalar(int r, double k) {
	//����r�е�ÿһ����������k
	for (int i = 0; i < column; i++)
	{
		data[r][i] *= k;
	}
	return *this;
}
Matrix& Matrix::columnMultiplyScalar(int c, double k) {
	//����c�е�ÿһ����������k
	for (int i = 0; i < row; i++)
	{
		data[i][c] *= k;
	}
	return *this;
}

//���ӱ仯
//r1����k֮��ӵ�r2��
Matrix& Matrix::rowAddMultiplyScalar(int r1, double k, int r2) {
	//�Ƚ�r1�б���k���ټӵ�r2����
	for (int i = 0; i < column; i++)
	{
		data[r2][i] += data[r1][i] * k;
	}
	return *this;
}
Matrix& Matrix::columnAddMultiplyScalar(int c1, double k, int c2) {
	//�Ƚ���c1�б���k���ټӵ�c2��
	for (int i = 0; i < row; i++)
	{
		data[i][c2] += data[i][c1] * k;
	}
	return *this;
}

//��˹��Ԫ����������;���
Matrix Matrix::getEchelonForm() {
	//����һ���µľ���
	Matrix tmp = *this;
	//��˹��Ԫ��������row-1��ѭ�����ɵõ������;���
	int rFlag = 0, cFlag = 0;//Ϊ���ų�һ��ȫΪ0����������ô����������Ͻ�Ԫ������
	for (; rFlag < row - 1; cFlag++)
	{
		//�����ҳ���һ���е����Ԫ�أ������佻��������
		//QUESTION �ҳ����Ԫ�ص�ԭ����֮����������0�Ĳ�������Ҫ���������ѡ���������õ�һ�У�����С
		int biggestRow = rFlag;//�����������ĵ�һ��(rFlag)Ϊ���
		for (int i = rFlag + 1; i < row; i++)
		{

			if (fabs(tmp.data[i][cFlag]) > fabs(tmp.data[rFlag][cFlag]))
			{
				biggestRow = i;
			}
		}
		//�����Ԫ�ؽ���������
		tmp.rowInterchange(rFlag, biggestRow);
		if (tmp.data[rFlag][cFlag] == 0)
		{
			//���ȫ��Ϊ0��ֱ��ִ����һ�β�������ʱrFlagû���ƶ���ֻ��cFlag+1
			continue;
		}
		//��������Ԫ����Ϊ1
		tmp.rowMultiplyScalar(rFlag, 1 / tmp.data[rFlag][cFlag]);
		//����������Ԫ��ȫ����Ϊ0
		for (int i = rFlag + 1; i < row; i++)
		{
			//��ʱrFlag�У����У��Ѿ���Ϊ1
			tmp.rowAddMultiplyScalar(rFlag, -tmp.data[i][cFlag], i);
		}
		rFlag++;
	}
	return tmp;
}

//��������
int Matrix::getRank() {
	//���ø�˹��Ԫ����������
	bool endFlag = false;
	int freeVarible = 0;
	Matrix echelonForm = this->getEchelonForm();
	//ͳ�ƽ����;����е�ȫ���У������ɱ�������
	for (int i = row - 1; i >= 0; i--)
	{
		//���¶���ͳ�ƣ���Сѭ������
		for (int j = 0; j < column; j++)
		{
			if (!(fabs(echelonForm.data[i][j]) < eps))
			{
				endFlag = true;
				break;
			}
		}
		if (endFlag)
		{
			break;
		}
		else {
			freeVarible++;
		}
	}
	return row - freeVarible;
}

//����data����ĵ�ַ
double** Matrix::getMatrixData() const
{
	return data;
}

void Matrix::setMatrixData(double** newDataAddress)
{
	delete[] data;
	data = newDataAddress;
}

//ħ������(ʵ������Ԥ֪��״������)
Matrix MatrixCin() {
	vector<double> container;//��ʱ�洢����
	int column = 0; //��ÿ��Ԫ�صĸ���
	double tmp;
	//�����һ������
	cout << "������m*n���󣺣����һ������e��ֹ��" << endl;
	do {
		cin >> tmp;
		container.push_back(tmp);
		column++;
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
	int row = container.size() / column;
	int cnt = 0;
	double** nData = new double* [row];
	for (int i = 0; i < row; i++)
	{
		nData[i] = new double[column];
		for (int j = 0; j < column; j++)
		{
			nData[i][j] = container.at(cnt);
			cnt++;
		}
	}
	return Matrix(row, column, nData);
}
