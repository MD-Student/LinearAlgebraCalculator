#pragma once
#include "Matrix.h"

class SquareMatrix :public Matrix {
	int order;
public:
	//Ĭ�Ϲ��캯��
	SquareMatrix();
	// �û��ֶ�����Ĺ��캯��
	SquareMatrix(int order);
	//���ƹ��캯��
	SquareMatrix(const SquareMatrix& other);
	//��ֵ���������
	SquareMatrix& operator=(const SquareMatrix& other);
	// �����ֶ�����Ĺ��캯��
	SquareMatrix(int order, double** nData);
	// N�׵�λ���캯��
	SquareMatrix(int order, SpecialMatrix type);
	// ����������ʽ��ֵ
	double getDetValue();
	//�����������ʽ
	double getCofactor(int r, int c);
	//����������
	SquareMatrix getAdjoint();
	//��������
	SquareMatrix getInverse();
};
//�����ħ������
SquareMatrix SquareMatrixCin();
//����˷�
SquareMatrix MultiplySMatrix(const SquareMatrix& m1, const SquareMatrix& m2);