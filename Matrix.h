#pragma once
class Matrix {
private:
	double** data;
public:
	int row;
	int column;
	enum SpecialMatrix
	{
		NullMatrix,
		IdentityMatrix
	};
	//Ĭ�Ϲ��캯��
	Matrix();
	// ���캯��rxc����(��������)
	Matrix(int r, int c);
	// ���캯���������û��������룩
	Matrix(int r, int c, double** matrixData);
	//���ƹ��캯��
	Matrix(const Matrix& mat);
	//NullMatrix���ƺ�������Ҫ�����̳г������̳е�Ŀ������չ�����Ż�ԭ�еĹ���
	//������Ȼ�����͵�λ�󲢲���Ҫ��չ�Ĺ��ܣ����ѡ�ü̳��ǻ�������
	Matrix(int r, int c, SpecialMatrix type);
	//��������
	~Matrix();
	//��ֵ��������� �����ظ�ֵ�����Ҫ��������
	Matrix& operator=(const Matrix& other);
	//�ӷ����������
	Matrix operator+ (const Matrix& other) const;
	// +=���������
	Matrix& operator+= (const Matrix& other);
	//�˷����������
	Matrix operator* (const Matrix& other) const;
	//*=���������
	Matrix& operator*= (const Matrix& other);
	//�������������
	Matrix operator- (const Matrix& other) const;
	// -=���������
	Matrix& operator-= (const Matrix& other);
	//�Ҳ��������������
	Matrix operator* (const double& other) const;
	//�Ҳ�����*=����
	Matrix& operator*= (const double& other);
	//����������������(�ǳ�Ա��������)
	friend Matrix operator* (const double k, const Matrix& other);
	//�������*=���������
	friend Matrix operator*= (const double k, Matrix& other);
	// �����ӡ����
	void printMatrix();
	//����ת��
	Matrix transpose();
	//�Ի��任
	Matrix& rowInterchange(int r1, int r2);
	Matrix& columnInterchange(int c1, int c2);
	//���˱任
	Matrix& rowMultiplyScalar(int r, double k);
	Matrix& columnMultiplyScalar(int c, double k);
	//���ӱ仯
	Matrix& rowAddMultiplyScalar(int r1, double k, int r2);
	Matrix& columnAddMultiplyScalar(int c1, double k, int c2);
	//��˹��Ԫ����������;���
	Matrix getEchelonForm();
	//��������
	int getRank();
	//��ȡ����data���ݽӿ�
	double** getMatrixData() const;
	//�����µ�data���ݵ�ַ
	void setMatrixData(double** newDataAddress);
};

Matrix MatrixCin();

