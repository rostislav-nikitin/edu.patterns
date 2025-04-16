#include <iostream>
#include <memory>
#include <functional>

class TcpState;
class TcpEstablished;
class TcpClosed;

class TcpConnection
{
public:
	TcpConnection();

	void open();
	void close();
private:
	friend class TcpState;

	std::unique_ptr<TcpState> state_;

	void setState(std::unique_ptr<TcpState> state)
	{
		state_ = std::move(state);
	}
};

class TcpState
{
public:
	virtual void open(TcpConnection *connection)
	{
	}
	virtual void close(TcpConnection *connection)
	{
	}
	virtual void setState(std::unique_ptr<TcpState> state, TcpConnection *context)
	{
		context->setState(std::move(state));
	}
};


class TcpEstablished : public TcpState
{
public:
	void close(TcpConnection *connection) override;
};

class TcpClosed : public TcpState
{
public:
	void open(TcpConnection *connection) override;
};


// Implementation
// TcpConnection
TcpConnection::TcpConnection() : state_(std::make_unique<TcpClosed>())
{
}
void TcpConnection::open()
{
	state_->open(this);
}
void TcpConnection::close()
{
	state_->close(this);
}

// TcpEstablished
void TcpEstablished::close(TcpConnection *connection)
{
	std::cout << "Connection closed." << std::endl;
	setState(std::make_unique<TcpClosed>(), connection);
}

// TcpClosed
void TcpClosed::open(TcpConnection *connection)
{
	std::cout << "Connection established." << std::endl;
	setState(std::make_unique<TcpEstablished>(), connection);
}

// Entry point
int main(int argc, char *argv[])
{
	auto connection = std::unique_ptr<TcpConnection, std::function<void(TcpConnection *)>>(new TcpConnection,	
		[](TcpConnection * connection) { connection->close(); delete connection; });

	connection->open();
	// Errorous (but will run ok because open not overrided for the established state).
	connection->open();

	return EXIT_SUCCESS;
}
