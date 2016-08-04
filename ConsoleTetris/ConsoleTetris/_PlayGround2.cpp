#include <stdio.h>

class Base{
private:
	int mi;
protected:
	Base(){ printf("Base ������\r\n"); }
public:
	virtual ~Base(){ printf("Base �ı���\r\n"); }
};

class Deri : public Base{
public:
	Deri(){ printf("Deri ������\r\n"); }
	virtual ~Deri(){ printf("Deri �ı���\r\n"); }
};

void main()
{
	printf("-- �׳� ���� --\r\n");
	Deri test_1;					// ����� ����-���� ȣ��.

	printf("-- (�ڽ�)�����ͷ� ���� ���� --\r\n");
	Deri* test_2 = new Deri();
	delete test_2;
	printf("-- (�ڽ�)�����ͷ� ���� �ı� --\r\n");

	printf("-- (�θ�)�����ͷ� ���� ���� --\r\n");
	Base* test_3 = new Deri();
	delete test_3;
	printf("-- (�θ�)�����ͷ� ���� �ı� --\r\n");
}