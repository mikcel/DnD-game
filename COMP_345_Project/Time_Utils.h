//! 
//! @file 
//! @brief Header and Implementation file for the TimeUtils class
//! 

#include <string>
#include <chrono>
#include <time.h>
#include <iomanip>
#include <sstream>

//! Heper class for managing the time
class TimeUtils
{
	public:
	/**
	* Obtains the current time in a specified format
	* @param format the fromat of the date
	* @return the current time in the specified format
	*/
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
