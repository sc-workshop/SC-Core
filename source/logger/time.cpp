#include "logger/time.h"

using namespace std::chrono;

namespace sc
{
	namespace time
	{
		std::string calculate_time(
			time_point<high_resolution_clock> start,
			time_point<high_resolution_clock> end)
		{
			std::stringstream message;

			milliseconds msTime = duration_cast<milliseconds>(end - start);
			seconds secTime = duration_cast<seconds>(msTime);
			minutes minTime = duration_cast<minutes>(secTime);

			if (minTime.count() > 0)
			{
				message << minTime.count() << " minutes, ";
				msTime -= duration_cast<milliseconds>(minTime);
				secTime -= duration_cast<seconds>(minTime);
			}

			if (secTime.count() > 0)
			{
				message << secTime.count() << " seconds, ";
				msTime -= duration_cast<milliseconds>(secTime);
			}

			message << msTime.count() << " miliseconds";

			return message.str();
		}
	}
}