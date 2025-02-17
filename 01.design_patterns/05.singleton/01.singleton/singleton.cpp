#include <iostream>
#include <memory>
#include <string>

class Singleton
{
public:
	static std::shared_ptr<Singleton> getInstance();

	std::string hello()
	{
		return "Hello, World!";
	}

protected:
	Singleton();

private:
	static std::shared_ptr<Singleton> instance_;
};

std::shared_ptr<Singleton> Singleton::instance_ = std::shared_ptr<Singleton>();

Singleton::Singleton()
{
}

std::shared_ptr<Singleton> Singleton::getInstance()
{
	if(instance_ == nullptr)
		instance_ = std::shared_ptr<Singleton>(new Singleton());

	return instance_;
}


int main(int argc, char *argv[])
{
	std::cout << Singleton::getInstance()->hello() << std::endl;

	return EXIT_SUCCESS;
}
