#include "Log.h"

Log* Log::instance = nullptr;

void Log::add(std::string info)
{
	if (instance == nullptr)
	{
		instance = new Log();
	}
	instance->queue.push_back("[" + instance->getCurrentTime() + "] " + info);
}

int Log::size()
{
	if (instance != nullptr)
		return instance->queue.size();
	else
		return 0;
}

void Log::clear()
{
	if (instance != nullptr)
		instance->queue.clear();
}

std::string Log::pop()
{
	if (instance != nullptr)
	{
		std::string buf = instance->queue.front();
		instance->queue.pop_front();

		if (instance->queue.empty())
			clear();

		return buf;
	}
	else
		return "";
}

std::string Log::getCurrentTime()
{
	char buffer[80];
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	char* format = "%A, %B %d, %Y %I:%M:%S";
	strftime(buffer, 80, format, timeinfo);

	return std::string(buffer);
}
