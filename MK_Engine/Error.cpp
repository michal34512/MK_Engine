#include "Error.h"

namespace mk
{
	Error::Error(Error::Code _error)
	{
		error = _error;
	}
	std::string Error::getDescription() const
	{
		return errorDescriptions[error];
	}
	void Error::printOnConsole() const
	{
		std::cout << getDescription() << std::endl;
	}
}