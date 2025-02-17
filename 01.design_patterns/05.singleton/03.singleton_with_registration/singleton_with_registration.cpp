#include <iostream>
#include <string>
#include <memory>
#include <map>

// DECLARATION
class Singleton
{
public:
	static std::shared_ptr<Singleton> getInstance(std::string key);
	static void registerInstance(std::string key, std::shared_ptr<Singleton> singleton);

	virtual std::string hello() = 0;

protected:
	Singleton();

private:
	static std::map<std::string, std::shared_ptr<Singleton>> registry_;
};


class SingletonA : public Singleton
{
public:
	virtual std::string hello() override;
};


class SingletonB : public Singleton
{
public:
	virtual std::string hello() override;
};

// IMPLEMENTATION
std::map<std::string, std::shared_ptr<Singleton>> Singleton::registry_ {};
Singleton::Singleton() {}
std::shared_ptr<Singleton> Singleton::getInstance(std::string key)
{
	return registry_[key];
}
void Singleton::registerInstance(std::string key, std::shared_ptr<Singleton> singleton)
{
	registry_[key] = singleton;
}
/*
std::string Singleton::hello()
{
	return "Hello, from the Singleton";
}
*/
std::string SingletonA::hello()
{
	return "Hello, from the SingletonA";
}
std::string SingletonB::hello()
{
	return "Hello, from the SingletonB";
}


int main(int argc, char *argv[])
{
	Singleton::registerInstance("A", std::make_shared<SingletonA>());
	Singleton::registerInstance("B", std::make_shared<SingletonB>());

	std::cout << Singleton::getInstance("A")->hello() << std::endl;
	std::cout << Singleton::getInstance("B")->hello() << std::endl;

	return EXIT_SUCCESS;
}
