#include <iostream>
#include <memory>

class Prototype
{
public:
	virtual std::unique_ptr<Prototype> clone() = 0;
};

class PrototypeA : public Prototype
{
public:
	PrototypeA() = default;

	PrototypeA(PrototypeA& prototype)
	{
		// Copy vars
	}

	virtual std::unique_ptr<Prototype> clone() override
	{
		return std::unique_ptr<Prototype>(new PrototypeA(*this));
	}
};


class PrototypeB : public Prototype
{
public:
	PrototypeB() = default;

	PrototypeB(PrototypeB& prototype)
	{
		// Copy vars
	}

	virtual std::unique_ptr<Prototype> clone() override
	{
		return std::unique_ptr<Prototype>(new PrototypeB(*this));
	}
};


class Client
{
private:
	PrototypeA pa_;
	PrototypeB pb_;

public:
	void run()
	{
		auto a = pa_.clone();
		auto b = pb_.clone();
	}
};

int main(int argc, char *argv[])
{
	std::cout << "Running" << std::endl;

	Client c;
	c.run();

	return EXIT_SUCCESS;
}
