#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>

class Subject;

class Observer
{
public:
	virtual void update(Subject &subject) = 0;
};

class Subject
{
public:
	void attach(std::shared_ptr<Observer> observer)
	{
		observers_.push_back(observer);
	}
	void notify()
	{
		for(auto &observer : observers_)
			observer->update(*this);
	}
private:
	std::vector<std::shared_ptr<Observer>> observers_;
};


class Employee : public Subject
{
public:
	Employee(double salary) : salary_(salary)
	{
	}

	double getSalary()
	{
		return salary_;
	}
	void setSalary(double salary)
	{
		salary_ = salary;
		notify();
	}
private:
	double salary_;
};

class EmployeeSalaryReport : public Observer
{
public:
	EmployeeSalaryReport(std::shared_ptr<Employee> employee) : employee_(employee)
	{
	}

	void update(Subject &employee) override
	{
		if(&employee == employee_.get())
			std::cout << "Employee salaray updated: " << std::fixed << std::setprecision(2) << employee_->getSalary() << " USD" << std::endl;
	}
private:
	std::shared_ptr<Employee> employee_;
};


int main(int argc, char *argv[])
{
	std::shared_ptr<Employee> employee = std::make_shared<Employee>(5000.0);

	std::shared_ptr<EmployeeSalaryReport> report = std::make_shared<EmployeeSalaryReport>(employee);
	employee->attach(report);

	employee->setSalary(6000.0);


	return EXIT_SUCCESS;
}
