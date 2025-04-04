#include <iostream>
#include <memory>
#include <string>

class Widget
{
};

class DialogWindow
{
public:
	virtual void createControls() = 0;
	void widgetChanged(Widget *widget)
	{
		changed(widget);
	}
	virtual ~DialogWindow()
	{
	}

protected:
	DialogWindow() = default;
	virtual void changed(Widget *widget) = 0;
};


class Button : public Widget
{
public:
	Button(DialogWindow *director) : director_(director)
	{
	}

	void onClickHandler()
	{
		director_->widgetChanged(this);
	}

	void click()
	{
		onClickHandler();
	}
	
private:
	DialogWindow *director_;
};

class TextBox : public Widget
{
public:
	TextBox(DialogWindow *director) : director_(director)
	{
	}

	void setText(std::string text)
	{
		text_ = text;
	}
	std::string getText() const
	{
		return text_;
	}

private:
	DialogWindow *director_;
	std::string text_;
};

class FontDialogWindow : public DialogWindow
{
public:
	virtual void createControls() override
	{
		btnChangeCaption_ = std::make_unique<Button>(this);
		txtCaption_ = std::make_unique<TextBox>(this);
	}

	void show()
	{
		std::cout << "Caption text before click: \"" << txtCaption_->getText() << "\"" << std::endl;
		btnChangeCaption_->click();
		std::cout << "Caption text after click: \"" << txtCaption_->getText() << "\"" << std::endl;
	}
protected:
	virtual void changed(Widget *widget)
	{
		if(widget == btnChangeCaption_.get())
			txtCaption_->setText("Changed");
	}
private:
	std::unique_ptr<Button> btnChangeCaption_;
	std::unique_ptr<TextBox> txtCaption_;
};

int main(int argc, char *argv[])
{
	FontDialogWindow dlg;
	dlg.createControls();
	dlg.show();

	
	
	return EXIT_SUCCESS;
}
