#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

class character_t
{
public:
	character_t(char charCode) : charCode_(charCode)
	{
	}
	operator char() const
	{
		return charCode_;
	}
private:
	char charCode_;
};

class CharacterFactory
{
public:
	std::shared_ptr<character_t> createCharacter(char charCode)
	{
		if(!characterCache_.contains(charCode))
			characterCache_[charCode] = std::make_shared<character_t>(charCode);

		return characterCache_[charCode];
	}
private:
	std::map<char, std::shared_ptr<character_t>> characterCache_;
};

class Text
{
public:
	Text(std::shared_ptr<CharacterFactory> factory, std::string text) : text_()
	{
		for(int idx = 0; idx < text.size(); ++idx)
			text_.push_back(factory->createCharacter(text[idx]));
	}

	std::vector<std::shared_ptr<character_t>> &getText()
	{
		return text_;
	}

private:
	std::vector<std::shared_ptr<character_t>> text_;
};

int main(int argc, char *argv[])
{
	std::shared_ptr<CharacterFactory> characterFactory = std::make_shared<CharacterFactory>();
	Text text(characterFactory, "Hello, World!");

	auto &textCharacters = text.getText();
	std::for_each(textCharacters.begin(), textCharacters.end(),
		[](std::shared_ptr<character_t> const &c)
		{
			std::cout << (*c);
		});

	return EXIT_SUCCESS;
}
