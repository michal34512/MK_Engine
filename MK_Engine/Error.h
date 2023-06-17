#pragma once
#include <iostream>

namespace mk
{
	class Error
	{
	public:
		enum Code
		{
			ERROR_LOADING_TEXTURE,
			COMPONENT_NOT_FOUND
		};
	private:
		const std::string errorDescriptions[4] =
		{
			"Could not load texture",
			"Component was not found. Perhabs it was added in wrong order"
		};
		Code error;
	public:
		Error(Error::Code);
		std::string getDescription() const;
		void printOnConsole() const;
	};
}