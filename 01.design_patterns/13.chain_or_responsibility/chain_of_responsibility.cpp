#include <iostream>
#include <string>
#include <memory>
#include <map>

class HttpRequest
{
public:
	void addHeader(std::string header, std::string value)
	{
		headers_[header] = value;
	}
	std::string getHeader(std::string header)
	{
		return headers_[header];
	}

	std::map<std::string, std::string>& getHeaders()
	{
		return headers_;
	}

private:
	std::map<std::string, std::string> headers_;
};

class HttpResponse
{
public:
	std::string getBody()
	{
		return body_;
	}
	void setBody(std::string body)
	{	
		body_ = body;
	}
	void redirect(std::string uri)
	{
		std::cout << "Redirecting to the: " << uri << std::endl;
	}

private:
	std::string body_;
};

class HttpHandler
{
public:
	HttpHandler(std::shared_ptr<HttpHandler> next) : next_(next)
	{
	}

	virtual void process(std::shared_ptr<HttpRequest> request, std::shared_ptr<HttpResponse> response)
	{
		if(next_)
			next_->process(request, response);
	}
private:
	std::shared_ptr<HttpHandler> next_;
};

class AuthenticationHttpHandler : public HttpHandler
{
public:
	
	AuthenticationHttpHandler(std::shared_ptr<HttpHandler> next) : HttpHandler(next)
	{
	}

	virtual void process(std::shared_ptr<HttpRequest> request, std::shared_ptr<HttpResponse> response) override
	{
		if(!request->getHeader("Authentication").empty())
		{
			// Check user
			// and if ok then call next handler
			if(request->getHeader("Authentication") == "USER1")
				HttpHandler::process(request, response);
			else
				response->redirect("/login");
		}
		else
		{
			// Redirect user to authentication page
			response->redirect("/login");
		}
	}
};

class HomePageHttpHandler : public HttpHandler
{
public:
	HomePageHttpHandler(std::shared_ptr<HttpHandler> next) : HttpHandler(next)
	{
	}

	
	virtual void process(std::shared_ptr<HttpRequest> request, std::shared_ptr<HttpResponse> response) override
	{
		response->setBody("<h1>Home</h1>");
	}
};

class Server
{
public:
	Server()
	{
		head_ = std::make_shared<AuthenticationHttpHandler>(std::make_shared<HomePageHttpHandler>(nullptr));		
	}

	std::shared_ptr<HttpResponse> process(std::shared_ptr<HttpRequest> request)
	{
		std::shared_ptr<HttpResponse> response = std::make_shared<HttpResponse>();

		head_->process(request, response);

		return response;	
	}

private:
	std::shared_ptr<HttpHandler> head_;
};

int main(int argc, char *argv[])
{

	Server server;

	std::cout << "Request #1: Non authentificated user" << std::endl;
	std::shared_ptr<HttpRequest> request1 = std::make_shared<HttpRequest>();
	auto response1 = server.process(request1);
	std::cout << response1->getBody() << std::endl;

	std::cout << "Request #2: Authentificated user" << std::endl;
	std::shared_ptr<HttpRequest> request2 = std::make_shared<HttpRequest>();
	request2->addHeader("Authentication", "USER1");
	auto response2 = server.process(request2);
	std::cout << response2->getBody() << std::endl;

	return EXIT_SUCCESS;	
}
