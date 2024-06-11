#include "Task.h"
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>

void saveTasksToFile(const std::vector<Task>& tasks, const std::string& fileName)
{
	std::ofstream ostream(fileName);
	ostream << tasks.size();

	for (const Task& task : tasks)
	{
		std::string description = task.description;
	}
}

std::vector<Task> loadTasksFromFile(const std::string& fileName)
{
	return std::vector<Task>();
}
