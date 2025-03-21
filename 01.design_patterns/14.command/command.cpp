#include <iostream>
#include <cassert>
#include <memory>

class Account
{
public:
	Account() = default;
	Account(double balance) : balance_(balance)
	{
	}
	double getBalance() const
	{
		return balance_;
	}
	void withdraw(double amount)
	{
		assert(amount > 0);

		if(balance_ >= amount)
			balance_ -= amount;
	}
	void topUp(double amount)
	{
		assert(amount > 0);

		balance_ += amount;
	}
private:
	double balance_ = 0;
};

class Command
{
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
	virtual ~Command() { }
};

class AccountWithdrawCommand : public Command
{
public:
	AccountWithdrawCommand(std::shared_ptr<Account> account, double amount) : account_(account), amount_(amount)
	{
	}
	virtual void execute() override
	{
		account_->withdraw(amount_);
		undoed_ = false;
	}
	virtual void undo() override
	{
		if(!undoed_)
			account_->topUp(amount_);
		undoed_ = true;
	}
private:
	std::shared_ptr<Account> account_;
	double amount_;
	bool undoed_ = false;

};

class UI
{
public:
	UI(std::shared_ptr<AccountWithdrawCommand> withdrawTen) : withdrawTen_(withdrawTen)
	{
	}

	void onWithdrawTenClick()
	{
		withdrawTen_->execute();
	}
	void onCancelWithdrawClick()
	{
		withdrawTen_->undo();
	}

private:
	std::shared_ptr<AccountWithdrawCommand> withdrawTen_;
};

class Client
{
public:
	Client(std::shared_ptr<Account> account) : ui_(std::make_shared<AccountWithdrawCommand>(account, 10.0))
	{
	}
	UI &getUi()
	{
		return ui_;
	}
private:
	UI ui_;
};

int main(int argc, char *argv[])
{
	std::shared_ptr<Account> account = std::make_shared<Account>(100.0);
	Client client(account);

	std::cout << "Accoun balance(before withdraw 10.0): " << account->getBalance() << std::endl;
	client.getUi().onWithdrawTenClick();
	std::cout << "Accoun balance(after withdraw 10.0): " << account->getBalance() << std::endl;
	client.getUi().onCancelWithdrawClick();
	std::cout << "Accoun balance(after cancel withdraw): " << account->getBalance() << std::endl;
	client.getUi().onCancelWithdrawClick();
	std::cout << "Accoun balance(after double cancel withdraw): " << account->getBalance() << std::endl;

	return EXIT_SUCCESS;
}
