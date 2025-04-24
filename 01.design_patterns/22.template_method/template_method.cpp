#include <iostream>

class Base
{
public:
	int template_method()
	{
		preOperation1();
		preOperation2();
		std::cout << "Template method" << std::endl;
		int result{operation1() + operation2()};
		postOperation2();
		postOperation1();

		return result;
	}
protected:
	virtual void preOperation1(){};
	virtual int operation1() = 0;
	virtual void postOperation1(){};
	virtual void preOperation2(){};
	virtual int operation2() = 0;
	virtual void postOperation2(){};
};

class Derived : public Base
{
protected:
	void preOperation1() override
	{
		std::cout << "Pre Operation#1 Hook" << std::endl;
	};
	int operation1() override
	{
		return 10;
	}
	void postOperation1() override
	{
		std::cout << "Post Operation#1 Hook" << std::endl;
	};

	void preOperation2() override
	{
		std::cout << "Pre Operation#2 Hook" << std::endl;
	};
	int operation2() override
	{
		return 20;
	}
	void postOperation2() override
	{
		std::cout << "Post Operation#2 Hook" << std::endl;
	};
};

int main(int argc, char *argv[])
{
	Derived d;
	int result{d.template_method()};
	std::cout << "Result: " << result << std::endl;

	return EXIT_SUCCESS;
}
