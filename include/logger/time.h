#pragma once

#include <sstream>
#include <string>
#include <chrono>

namespace sc
{
	namespace time
	{
		std::string calculate_time(
			std::chrono::time_point<std::chrono::high_resolution_clock> start,
			std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now()
		);
	}
}