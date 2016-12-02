#include <string>
#include <chrono>
#include <time.h>
#include <iomanip>
#include <sstream>

class TimeUtils{
	public:
	static std::string getCurrentTime(std::string format = "%Y-%m-%d %X"){
		time_t rawtime;
		struct tm timeinfo;

		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		std::stringstream ss;
		ss << std::put_time(&timeinfo, format.c_str());
		return ss.str();
	}
};
