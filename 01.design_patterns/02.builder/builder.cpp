#include <iostream>

class Product
{
public:
	void setA(int) {}
	void setB(int) {}
};

class AbstractBuilder
{
public:
	virtual void buildPartA() {}
	virtual void buildPartB() {}

	virtual Product buildProduct() {return Product(); }
};

class SimpleBuilder : public AbstractBuilder
{
public:
	virtual void buildPartA()
	{
		product_.setA(1);
	}

	virtual void buildPartB()
	{
		product_.setB(2);
	}

	virtual Product buildProduct() 
	{
		return product_; 
	}

private:
	Product product_;
};

class Director
{
public:
	Director(SimpleBuilder builder) : builder_(builder)
	{
	}

	void run()
	{
		builder_.buildPartA();
		builder_.buildPartB();

		Product product = builder_.buildProduct();
	}

private:
	SimpleBuilder builder_;
};

int main(int argc, char *argv[])
{
	SimpleBuilder builder;
	Director director(builder);

	director.run();

	return EXIT_SUCCESS;
}
