#pragma once
class Determinant {
private:
	int order;//行列式阶数
	double** data;//行列式数据
public:
	//默认构造函数
	Determinant();
	//构造函数(无需手动输入)
	Determinant(int order, double** nData);
	//构造函数（手动输入）
	Determinant(int order);
	//复制构造函数（深拷贝）
	Determinant(const Determinant& obj);
	//赋值运算符重载（深拷贝）
	Determinant& operator=(const Determinant& other);
	//析构函数
	~Determinant();
	//打印行列式
	void printDet();
	//计算代数余子式的值
	double cal(double** det, int n);
	//计算行列式的值
	double calculate();
	//行列式行倍加变换
	void rowMultiplyScalar(int r1, double k, int r2);
	//转换为上三角形式
	Determinant upperTriangle();
};
//行列式魔法输入
Determinant DeterminantCin();