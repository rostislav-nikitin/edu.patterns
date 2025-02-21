#include <iostream>
#include <string>
#include <memory>

class Adaptee
{
public:
	std::string sayHello()
	{
		return "Hello, World!";
	}
};

class IHello
{
public:
	virtual std::string hello() = 0;
};

class Adapter : public IHello
{
public:
	Adapter(std::unique_ptr<Adaptee> adaptee) :
		adaptee_(std::move(adaptee))
	{
	}
	virtual std::string hello() override
	{
		return adaptee_->sayHello();
	}

private:
	std::unique_ptr<Adaptee> adaptee_;
};

class Client
{
public:
	void run()
	{
		std::unique_ptr<Adapter> adapter = std::make_unique<Adapter>(std::move(std::make_unique<Adaptee>()));
		std::cout << adapter->hello() << std::endl;
	}
};

int main(int argc, char *argv[])
{
	Client client;
	client.run();

	return EXIT_SUCCESS;
}
