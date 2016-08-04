#include <stdio.h>

class Base{
private:
	int mi;
protected:
	Base(){ printf("Base 생성자\r\n"); }
public:
	virtual ~Base(){ printf("Base 파괴자\r\n"); }
};

class Deri : public Base{
public:
	Deri(){ printf("Deri 생성자\r\n"); }
	virtual ~Deri(){ printf("Deri 파괴자\r\n"); }
};

void main()
{
	printf("-- 그냥 선언 --\r\n");
	Deri test_1;					// 예상된 생생-파파 호출.

	printf("-- (자식)포인터로 동적 선언 --\r\n");
	Deri* test_2 = new Deri();
	delete test_2;
	printf("-- (자식)포인터로 동적 파괴 --\r\n");

	printf("-- (부모)포인터로 동적 선언 --\r\n");
	Base* test_3 = new Deri();
	delete test_3;
	printf("-- (부모)포인터로 동적 파괴 --\r\n");
}