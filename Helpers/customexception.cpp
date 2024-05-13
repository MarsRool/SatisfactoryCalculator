#include "Helpers/customexception.h"

CustomException::CustomException(const char *message)
	:message(message)
{}

CustomException::~CustomException()
{
	/*if (message)
	{
		delete message;
		message = nullptr;
	}*/
}

const char *CustomException::what() const noexcept
{
	return message;
}


