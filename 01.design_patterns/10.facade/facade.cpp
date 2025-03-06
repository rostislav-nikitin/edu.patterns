#include <iostream>
#include <string>
#include <memory>

class A
{
public:
	std::string operationA()
	{
		return "Hello";
	}
};

class B
{
public: 
	std::string operationB()
	{
		return "World";
	}
};

class C
{
public:
	C(std::unique_ptr<A> a, std::unique_ptr<B> b) :
		a_(std::move(a)), b_(std::move(b))
	{
	}
	std::string operationC()
	{
		return a_->operationA() + std::string(", ") + b_->operationB() + std::string("!");
	}
private:
	std::unique_ptr<A> a_;
	std::unique_ptr<B> b_;
};

class Facade
{
public:
	std::string operation()
	{
		auto a = std::make_unique<A>();
		auto b = std::make_unique<B>();

		C c(std::move(a), std::move(b));

		return c.operationC();
	}
};

class Client
{
public:
	void run()
	{
		Facade facade;
		std::cout << facade.operation() << std::endl;
	}
};

int main(int argc, char *argv[])
{
	Client client;
	client.run();

	return EXIT_SUCCESS;
}
