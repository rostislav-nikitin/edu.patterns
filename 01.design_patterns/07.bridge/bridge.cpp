#include <iostream>
#include <memory>

#define X_WINDOW_SYSTEM 1
#define PM_WINDOW_SYSTEM 2
#define WINDOW_SYSTEM PM_WINDOW_SYSTEM

class WindowImpl
{
public:
	virtual void drawRect(int x1, int y1, int x2, int y2) = 0;
};

class XWindowImpl : public WindowImpl
{
public:
	virtual void drawRect(int x1, int y1, int x2, int y2) override;
};
void XWindowImpl::drawRect(int x1, int y1, int x2, int y2)
{
	std::cout << "XWindow::drawRect called." << std::endl;
}

class PMWindowImpl : public WindowImpl
{
public:
	virtual void drawRect(int x1, int y1, int x2, int y2) override;
};
void PMWindowImpl::drawRect(int x1, int y1, int x2, int y2)
{
	std::cout << "PMWindow::drawRect called." << std::endl;
}

struct Rect
{
	int x1;
	int y1;
	int x2;
	int y2;
};

class Window
{
public:
	Window(std::unique_ptr<WindowImpl> impl);
	void draw(Rect const &rect);	
private:
	std::unique_ptr<WindowImpl> impl_;
};

Window::Window(std::unique_ptr<WindowImpl> impl) : impl_(std::move(impl))
{
};
void Window::draw(Rect const &rect)
{
	impl_->drawRect(rect.x1, rect.y1, rect.x2, rect.y2);
}

class IconWindow : public Window
{
public:
	IconWindow(std::unique_ptr<WindowImpl> impl);
};
IconWindow::IconWindow(std::unique_ptr<WindowImpl> impl) : Window(std::move(impl))
{
}

class SystemFactory
{
public:
	virtual std::unique_ptr<Window> createWindow() = 0;
	virtual std::unique_ptr<IconWindow> createIconWindow() = 0;
};

class XSystemFactory : public SystemFactory
{
public:
	virtual std::unique_ptr<Window> createWindow() override;
	virtual std::unique_ptr<IconWindow> createIconWindow() override;
};
std::unique_ptr<Window> XSystemFactory::createWindow()
{
	return std::make_unique<Window>(std::make_unique<XWindowImpl>());
}
std::unique_ptr<IconWindow> XSystemFactory::createIconWindow()
{
	return std::make_unique<IconWindow>(std::make_unique<XWindowImpl>());
}

class PMSystemFactory : public SystemFactory
{
public:
	virtual std::unique_ptr<Window> createWindow() override;
	virtual std::unique_ptr<IconWindow> createIconWindow() override;
};

std::unique_ptr<Window> PMSystemFactory::createWindow()
{
	return std::make_unique<Window>(std::make_unique<PMWindowImpl>());
}
std::unique_ptr<IconWindow> PMSystemFactory::createIconWindow()
{
	return std::make_unique<IconWindow>(std::make_unique<PMWindowImpl>());
}

int main(int argc, char *argv[])
{
	std::unique_ptr<SystemFactory> factory;
#if WINDOW_SYSTEM == X_WINDOW_SYSTEM
	factory.reset(new XSystemFactory());
#elif WINDOW_SYSTEM == PM_WINDOW_SYSTEM
	factory.reset(new PMSystemFactory());
#endif

	Rect r {1, 10, 50, 100};

	auto window = factory->createWindow();
	window->draw(r);

	auto iconWindow = factory->createIconWindow();
	iconWindow->draw(r);

	return EXIT_SUCCESS;
}
