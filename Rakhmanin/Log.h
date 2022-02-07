#pragma once
#include <ctime>
#include <string>
#include <list>

class Log
{
private:

	std::list<std::string> queue;
	static Log* instance;

	Log() {}

public:

	static void add(std::string info);

	static int size();

	static void clear();

	static std::string pop();

private:

	/// <summary>
	/// Получение текущего времени системы. В формате.
	/// </summary>
	/// <returns>строка</returns>
	std::string getCurrentTime();
};



