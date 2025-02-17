#include <iostream>
#include <memory>

class AbstractProductA
{
public:
	virtual void hello()
	{
		std::cout << "I am ProductA" << std::endl;
	}
};

class AbstractProductB
{
	virtual void hello()
	{
		std::cout << "I am ProductB" << std::endl;
	}
};

class AbstractFactory
{
public:
	virtual std::shared_ptr<AbstractProductA> createProductA() = 0;
	virtual std::shared_ptr<AbstractProductB> createProductB() = 0;
};

class ConcreteProductA1 : public AbstractProductA
{
public:
	ConcreteProductA1() = default;
	ConcreteProductA1(int x){ }
};

class ConcreteProductB1 : public AbstractProductB
{
};

class ConcreteFactory1 : public AbstractFactory
{
public:
	virtual std::shared_ptr<AbstractProductA> createProductA() override
	{
		return std::make_shared<ConcreteProductA1>();
	}
	virtual std::shared_ptr<AbstractProductB> createProductB() override
	{
		return std::make_shared<ConcreteProductB1>();
	}
/*
	template<typename T, typename... Args>
	std::shared_ptr<AbstractProductA> createProductA(Args... args)
	{
		return std::make_shared<ConcreteProductA1>(std::forward<Args>(args)...);
	}
*/
};

int main(int argc, char *argv[])
{
	std::unique_ptr<AbstractFactory> f = std::make_unique<ConcreteFactory1>();
	auto a = f->createProductA();
	a->hello();
/*
	auto a2 = f->createProductA(10);
	a2->hello();
*/
	return EXIT_SUCCESS;
}

