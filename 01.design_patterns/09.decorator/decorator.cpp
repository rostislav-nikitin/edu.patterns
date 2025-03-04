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

class Decorator : public Component
{
public:
	Decorator(std::unique_ptr<Component> component) : component_(std::move(component))
	{
	}

	virtual void operation() override
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		component_->operation();
	}

private:
	std::unique_ptr<Component> component_;
};

class ConcreteDecorator : public Decorator
{
public:
	ConcreteDecorator(std::unique_ptr<Component> component) : Decorator(std::move(component))
	{
	}

	void operation2()
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
};

class Client
{
public:
	void run()
	{
		ConcreteDecorator concreteDecorator(
			std::make_unique<ConcreteDecorator>(
				std::make_unique<ConcreteComponent>()
		));

		concreteDecorator.operation();
	}
};

int main(int argc, char *argv[])
{
	Client client;
	client.run();

	return EXIT_SUCCESS;
}
