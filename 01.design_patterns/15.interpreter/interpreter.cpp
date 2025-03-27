#include <iostream>
#include <map>
#include <memory>

class Context
{
public:
	void setVar(std::string name, bool value)
	{
		vars_[name] = value;
	}

	bool getVar(std::string name) const
	{
		return vars_.at(name);
	}

private:
	std::map<std::string, bool> vars_;
	
};

class BooleanExp
{
public:
	virtual bool evaluate(Context const &context) = 0;
};

class Constant : public BooleanExp
{
public:
	Constant(bool value) : value_(value)
	{
	}

	virtual bool evaluate(Context const &context) override
	{
		return value_;
	}	

private:
	bool value_;
};

class Variable : public BooleanExp
{
public:
	Variable(std::string name) : name_(name)
	{
	}

	virtual bool evaluate(Context const &context) override
	{
		return context.getVar(name_);
	}
private:
	std::string name_;
};

class Not : public BooleanExp
{
public:
	Not(std::unique_ptr<BooleanExp> expr) : expr_(std::move(expr))
	{
	}

	virtual bool evaluate(Context const &context) override
	{
		return !expr_->evaluate(context);
	}

private:
	std::unique_ptr<BooleanExp> expr_;
};

class And : public BooleanExp
{
public:
	And(std::unique_ptr<BooleanExp> left, std::unique_ptr<BooleanExp> right) : 
		left_(std::move(left)), right_(std::move(right))
	{
	}

	virtual bool evaluate(Context const &context) override
	{
		return left_->evaluate(context) && right_->evaluate(context);
	}

private:
	std::unique_ptr<BooleanExp> left_;
	std::unique_ptr<BooleanExp> right_;
};

class Or : public BooleanExp
{
public:
	Or(std::unique_ptr<BooleanExp> left, std::unique_ptr<BooleanExp> right) : 
		left_(std::move(left)), right_(std::move(right))
	{
	}

	virtual bool evaluate(Context const &context) override
	{
		return left_->evaluate(context) || right_->evaluate(context);
	}

private:
	std::unique_ptr<BooleanExp> left_;
	std::unique_ptr<BooleanExp> right_;
};

int main(int argc, char *argv[])
{
	Context context;

	context.setVar("x", false);
	context.setVar("y", true);

	auto expression = Or
	(
		std::make_unique<And>
		(
			std::make_unique<Constant>(false), 
			std::make_unique<Variable>("x")
		), 
		std::make_unique<And>
		(
			std::make_unique<Constant>(true), 
			std::make_unique<Variable>("y")
		)
	);

	std::cout << "Eval result: " << std::boolalpha << expression.evaluate(context) << std::endl;

	return EXIT_SUCCESS;
}
