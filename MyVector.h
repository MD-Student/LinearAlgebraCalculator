#pragma once
//ǰ����������
class MyVector {
	//�������ǲ�Ҫ�̳о�������
private:
	int row;//��������
	double* data;//������������
public:
	//���캯��
	//������n��1��
	MyVector(int r, double* components);
	//�����ڻ��˷�����
	double operator* (const MyVector& other) const;
};