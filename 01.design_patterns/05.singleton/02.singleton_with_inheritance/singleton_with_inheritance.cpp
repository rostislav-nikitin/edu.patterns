#include <iostream>
#include <string>
#include <memory>

#define SINGLETON_A 1
#define SINGLETON_B 2

#define SINGLETON_CONFIG SINGLETON_B

class SingletonA;
class SingletonB;

class Singleton
{
public:
	static std::shared_ptr<Singleton> getInstance();

	virtual std::string hello();

protected:
	Singleton();

private:
	static std::shared_ptr<Singleton> instance_;
};


class SingletonA : public Singleton
{
public:
	virtual std::string hello() override;
};

std::string SingletonA::hello()
{
	return "Hello, from the SingletonA";
}

class SingletonB : public Singleton
{
public:
	virtual std::string hello() override;
};

std::string SingletonB::hello()
{
	return "Hello, from the SingletonB";
}


Singleton::Singleton(){}
std::shared_ptr<Singleton> Singleton::instance_ = std::shared_ptr<Singleton>();
std::shared_ptr<Singleton> Singleton::getInstance()
{
	if(instance_ == nullptr)
	{
#ifndef SINGLETON_CONFIG
		instance_ = std::shared_ptr<Singleton>(new Singleton());
#elif SINGLETON_CONFIG == SINGLETON_A 
		instance_ = std::shared_ptr<Singleton>(new SingletonA());
#elif SINGLETON_CONFIG == SINGLETON_B 
		instance_ = std::shared_ptr<Singleton>(new SingletonB());
#endif
	}

	return instance_;
}
std::string Singleton::hello()
{
	return "Hello, from the Singleton";
}
int main(int argc, char *argv[])
{
	std::cout << Singleton::getInstance()->hello() << std::endl;

	return EXIT_SUCCESS;
}
