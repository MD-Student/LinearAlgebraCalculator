#pragma once
class Determinant {
private:
	int order;//����ʽ����
	double** data;//����ʽ����
public:
	//Ĭ�Ϲ��캯��
	Determinant();
	//���캯��(�����ֶ�����)
	Determinant(int order, double** nData);
	//���캯�����ֶ����룩
	Determinant(int order);
	//���ƹ��캯���������
	Determinant(const Determinant& obj);
	//��ֵ��������أ������
	Determinant& operator=(const Determinant& other);
	//��������
	~Determinant();
	//��ӡ����ʽ
	void printDet();
	//�����������ʽ��ֵ
	double cal(double** det, int n);
	//��������ʽ��ֵ
	double calculate();
	//����ʽ�б��ӱ任
	void rowMultiplyScalar(int r1, double k, int r2);
	//ת��Ϊ��������ʽ
	Determinant upperTriangle();
};
//����ʽħ������
Determinant DeterminantCin();