#include <iostream>
#include <memory>

class Component
{
public:
	virtual void operation() = 0;
};

class ConcreteComponent : public Component
{
public:
	virtual void operation() override
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
};

class Proxy : public Component
{
public:
	virtual void operation() override
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		// Check permisions
		createConcreteComponent();
		concreteComponent_->operation();
	}
private:
	std::unique_ptr<Component> concreteComponent_;

	void createConcreteComponent()
	{
		if(!concreteComponent_)
			concreteComponent_ = std::make_unique<ConcreteComponent>();
	}
};

int main(int argc, char *argv[])
{
	Proxy proxy;
	proxy.operation();

	return EXIT_SUCCESS;
}
