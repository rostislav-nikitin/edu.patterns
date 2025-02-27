#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

class Component
{
public:
	virtual void operation() = 0;
	virtual void add(std::shared_ptr<Component> component) = 0;
	virtual void remove(std::shared_ptr<Component> component) = 0;
	virtual std::vector<std::shared_ptr<Component>> getChildren() = 0;
};

class Leaf : public Component
{
public:
	virtual void operation() override
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
	virtual void add(std::shared_ptr<Component> component) override {}
	virtual void remove(std::shared_ptr<Component> component) override {}
	virtual std::vector<std::shared_ptr<Component>> getChildren() override
	{
		return {};
	}
};

class Composite : public Component
{
private:
	std::vector<std::shared_ptr<Component>> children_;

public:
	virtual void operation() override
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		std::for_each(std::begin(children_), std::end(children_), 
			[](std::shared_ptr<Component> child)
			{
				child->operation();
			});
	}
	virtual void add(std::shared_ptr<Component> component) override
	{
		children_.push_back(component);
	}
	virtual void remove(std::shared_ptr<Component> component) override
	{
		auto it = std::find_if(std::begin(children_), std::end(children_),
			[&component](std::shared_ptr<Component> child)
			{
				return child.get() == component.get();
			});
		if(it != std::end(children_))
			children_.erase(it);
	}

	virtual std::vector<std::shared_ptr<Component>> getChildren() override
	{
		return children_;
	}
};

class Client
{
public:
	void run()
	{
		std::shared_ptr<Component> c1 = std::make_shared<Composite>();
		std::shared_ptr<Leaf> leaf1 = std::make_shared<Leaf>();
		c1->add(leaf1);
		c1->add(std::make_shared<Leaf>());
		c1->add(std::make_shared<Leaf>());
		c1->operation();

		c1->remove(leaf1);
		c1->operation();
	}
};

int main(int argc, char *argv[])
{
	Client client;
	client.run();

	return EXIT_SUCCESS;
}
