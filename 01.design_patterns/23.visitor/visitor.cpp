#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Visitor;

class Element
{
public:
	Element(int id, std::string name) : id_{id}, name_{name} {  }

	virtual void accept(std::shared_ptr<Visitor> visitor) = 0;

	int getId() const { return id_; }
	std::string getName() const { return name_; }

private:
	int id_{};
	std::string name_{};
};

class ElementA : public Element
{
public:
	ElementA(int id, std::string name) : Element(id, name)
	{
	}
	void accept(std::shared_ptr<Visitor> visitor) override;
};

class ElementB : public Element
{
public:
	ElementB(int id, std::string name) : Element(id, name)
	{
	}
	void accept(std::shared_ptr<Visitor> visitor) override;
};


class Visitor
{
public:
	virtual void visit(ElementA &element) = 0;
	virtual void visit(ElementB &element) = 0;
};

class ShowIdVisitor : public Visitor
{
public:
	void visit(ElementA &element) override
	{
		std::cout << element.getId() << std::endl;
	}
	void visit(ElementB &element) override
	{
		std::cout << element.getId() << std::endl;
	}
};


void ElementA::accept(std::shared_ptr<Visitor> visitor)
{
		visitor->visit(*this);
}
void ElementB::accept(std::shared_ptr<Visitor> visitor)
{
		visitor->visit(*this);
}

int main(int argc, char *argv[])
{
	auto showIdVisitor = std::make_shared<ShowIdVisitor>();
	std::vector<std::shared_ptr<Element>> es{std::shared_ptr<Element>{new ElementA{1, "E1"}}, std::shared_ptr<Element>{new ElementB{2, "E2"}}};
	for(auto const &e : es)
		e->accept(showIdVisitor);

	return EXIT_SUCCESS;
}
