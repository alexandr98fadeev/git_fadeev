#pragma once
#include <string>

class Ceaser
{
private:
	int key;
	if (key == 0)
		throw CeaserException();

public:
	Ceaser(int key);
	std::string encrypt(std::string input);
	std::string decrypt(std::string input);
};

class CeaserException:std::exception
{
public:
	const char* what() const noexcept
	{
		return "Trouble with the cipher";
	}
};
