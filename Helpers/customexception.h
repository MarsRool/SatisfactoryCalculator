#pragma once

#include <exception>

class CustomException : public std::exception
{
public:
	CustomException(const char * message);
	~CustomException() override;
	const char * what() const noexcept override;
private:
	const char * message;
};
