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
	//默认构造函数
	Matrix();
	// 构造函数rxc矩阵(键盘输入)
	Matrix(int r, int c);
	// 构造函数（不用用户键盘输入）
	Matrix(int r, int c, double** matrixData);
	//复制构造函数
	Matrix(const Matrix& mat);
	//NullMatrix类似乎并不需要单独继承出来，继承的目的是拓展或者优化原有的功能
	//但是显然零矩阵和单位阵并不需要拓展的功能，因此选用继承是画蛇添足
	Matrix(int r, int c, SpecialMatrix type);
	//析构函数
	~Matrix();
	//赋值运算符重载 不重载赋值运算符要出大问题
	Matrix& operator=(const Matrix& other);
	//加法运算符重载
	Matrix operator+ (const Matrix& other) const;
	// +=运算符重载
	Matrix& operator+= (const Matrix& other);
	//乘法运算符重载
	Matrix operator* (const Matrix& other) const;
	//*=运算符重载
	Matrix& operator*= (const Matrix& other);
	//减法运算符重载
	Matrix operator- (const Matrix& other) const;
	// -=运算符重载
	Matrix& operator-= (const Matrix& other);
	//右侧数乘运算符重载
	Matrix operator* (const double& other) const;
	//右侧数乘*=重载
	Matrix& operator*= (const double& other);
	//左侧数乘运算符重载(非成员函数重载)
	friend Matrix operator* (const double k, const Matrix& other);
	//左侧数乘*=运算符重载
	friend Matrix operator*= (const double k, Matrix& other);
	// 矩阵打印函数
	void printMatrix();
	//矩阵转置
	Matrix transpose();
	//对换变换
	Matrix& rowInterchange(int r1, int r2);
	Matrix& columnInterchange(int c1, int c2);
	//倍乘变换
	Matrix& rowMultiplyScalar(int r, double k);
	Matrix& columnMultiplyScalar(int c, double k);
	//倍加变化
	Matrix& rowAddMultiplyScalar(int r1, double k, int r2);
	Matrix& columnAddMultiplyScalar(int c1, double k, int c2);
	//高斯消元法计算阶梯型矩阵
	Matrix getEchelonForm();
	//矩阵求秩
	int getRank();
	//获取矩阵data数据接口
	double** getMatrixData() const;
	//设置新的data数据地址
	void setMatrixData(double** newDataAddress);
};

Matrix MatrixCin();

