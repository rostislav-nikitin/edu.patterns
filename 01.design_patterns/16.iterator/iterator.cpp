#include <iostream>
#include <memory>
#include <list>
#include <vector>

template<typename T>
class Iterator
{
public:
	virtual void first() = 0;
	virtual void next() = 0;
	virtual T* current() = 0;
	virtual bool end() = 0;
};

template<typename T>
class Container
{
	virtual std::unique_ptr<Iterator<T>> iterator() = 0;
};

template<typename T>
class ListIterator;

template<typename T>
class ListContainer : public Container<T>
{
public:
	friend ListIterator<T>;

	void add(T const &item)
	{
		inner_.push_back(item);
	}

	std::unique_ptr<Iterator<T>> iterator()
	{
		return std::make_unique<ListIterator<T>>(*this);
	}

private:
	std::list<T> inner_;
};

template<typename T>
class ListIterator : public Iterator<T>
{
public:
	ListIterator(ListContainer<T> &container) : container_(container)
	{
	}
	virtual void first() override
	{
		current_ = std::begin(container_.inner_);
	}
	virtual void next() override
	{
		++current_;
	}
	virtual T* current() override
	{
		if(current_ != std::end(container_.inner_))
			return &(*current_);

		return nullptr;
	}
	virtual bool end() override
	{
		return current_ == std::end(container_.inner_);
	}
	

private:
	ListContainer<T> &container_;
	decltype(ListContainer<T>::inner_)::iterator current_;
};

template<typename T>
class VectorIterator;

template<typename T>
class VectorContainer : public Container<T>
{
public:
	friend VectorIterator<T>;

	void add(T const &item)
	{
		inner_.push_back(item);
	}

	std::unique_ptr<Iterator<T>> iterator()
	{
		return std::make_unique<VectorIterator<T>>(*this);
	}

private:
	std::vector<T> inner_;
};

template<typename T>
class VectorIterator : public Iterator<T>
{
public:
	VectorIterator(VectorContainer<T> &container) : container_(container)
	{
	}

	virtual void first() override
	{
		current_ = 0;		
	}
	virtual void next() override
	{
		++current_;
	}
	virtual T* current() override
	{
		return &container_.inner_[current_];		
	}
	virtual bool end() override
	{
		return current_ >= container_.inner_.size();
	}
private:
	size_t current_;
	VectorContainer<T> &container_;
};

template<typename T>
void print(std::unique_ptr<Iterator<T>> iter)
{
	for(iter->first(); !iter->end(); iter->next())
	{
		std::cout << *iter->current() << std::endl;
	}
}

int main(int argc, char *argv[])
{
	ListContainer<int> list;
	list.add(10);
	list.add(20);

	auto li = list.iterator();
	print(std::move(li));
	
	VectorContainer<int> vec;
	vec.add(10);
	vec.add(20);

	auto vi = vec.iterator();
	print(std::move(vi));

	return EXIT_SUCCESS;
}
