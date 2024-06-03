#pragma once

#include <string>

namespace sc
{
	class Base64
	{
	public:
		static std::string encode(const std::string& data, bool url_safe = false);
		static std::string decode(const std::string& data);
	};
}
