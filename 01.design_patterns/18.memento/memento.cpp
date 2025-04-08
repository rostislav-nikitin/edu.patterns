#include <iostream>

class Account;

class AccountState
{
private:
	friend class Account;

	double getBalance() const
	{
		return balance_;
	}
	void setBalance(double balance)
	{
		balance_ = balance;
	}
	double balance_;
};

class AccountMemento
{
private:
	friend class Account;

	AccountState state_;

	AccountState getState() const
	{
		return state_;
	}
	void setState(AccountState state)
	{
		state_ = state;
	}
};

class Account
{
public:
	Account(double balance = 0.0)
	{
		state_.setBalance(balance);
	}

	AccountMemento getMemento()
	{
		AccountMemento res;

		res.setState(state_);

		return res;
	}

	void setMemento(AccountMemento memento)
	{
		state_ = memento.getState();
	}

	double getBalance() const
	{
		return state_.getBalance();
	}
	void setBalance(double balance)
	{
		state_.setBalance(balance);
	}

private:
	AccountState state_;
};

int main(int argc, char *argv[])
{

	Account acc1(150.0);
	std::cout << "Balance [initial]: " << acc1.getBalance() << std::endl;
	std::cout << "Saving memento..." << std::endl;
	auto am = acc1.getMemento();
	std::cout << "Setting new balance..." << std::endl;
	acc1.setBalance(200.0);
	std::cout << "Balance [after change]: " << acc1.getBalance() << std::endl;
	std::cout << "Rollback with momento" << std::endl;
	acc1.setMemento(am);
	std::cout << "Balancei [after rollback]: " << acc1.getBalance() << std::endl;
	

	return EXIT_SUCCESS;
}
