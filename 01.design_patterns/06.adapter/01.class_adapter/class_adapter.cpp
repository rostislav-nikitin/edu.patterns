#include <iostream>
#include <string>
#include <memory>

class Adaptee
{
public:
	std::string sayHello()
	{
		return "Hello, World";
	}
};

class IHello
{
public:
	virtual std::string hello() = 0;
};

class Adapter : public IHello, private Adaptee 
{
public:
	virtual std::string hello() override
	{
		return Adaptee::sayHello();
	}
};

class Client
{
public:
	void run()
	{
		std::unique_ptr<Adapter> adapter = std::make_unique<Adapter>();
		std::cout << adapter->hello() << std::endl;
	}	
};

int main(int argc, char *argv[])
{
	Client client;
	client.run();

	return EXIT_SUCCESS;
}
