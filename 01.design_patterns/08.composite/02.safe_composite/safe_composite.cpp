#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class Composite;

class Component
{
public:
	virtual void operation() = 0;
	virtual Composite* getComposite() = 0;
};

class Leaf : public Component
{
public:
	virtual void operation() override
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
	virtual Composite* getComposite() override;
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
	virtual Composite* getComposite() override;
	void add(std::shared_ptr<Component> component);
	void remove(std::shared_ptr<Component> component);
};

Composite* Leaf::getComposite()
{
	return {};
}

Composite* Composite::getComposite()
{
	return this;
}
void Composite::add(std::shared_ptr<Component> component)
{
	children_.push_back(component);
}
void Composite::remove(std::shared_ptr<Component> component)
{
	//TODO: Implement
	auto it = std::find_if(std::begin(children_), std::end(children_),
		[&component](std::shared_ptr<Component> child)
		{
			return child.get() == component.get();
		});
	if(it != std::end(children_))
		children_.erase(it);
}

class Client
{
public:
	void run()
	{
		std::shared_ptr<Component> composite = std::make_shared<Composite>();
		std::shared_ptr<Leaf> leaf1 = std::make_shared<Leaf>();
		composite->getComposite()->add(leaf1);
		composite->getComposite()->add(std::make_shared<Leaf>());
		composite->getComposite()->add(std::make_shared<Leaf>());
		composite->getComposite()->add(std::make_shared<Composite>());
		composite->operation();

		composite->getComposite()->remove(leaf1);
		composite->operation();
	}
};

int main(int argc, char *argv[])
{
	Client client;
	client.run();
	
	return EXIT_SUCCESS;
}
