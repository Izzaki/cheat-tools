#include <string>

#pragma once
class Sample
{

public:
	std::string name = "";
	int a = 50;

	Sample *sibling;

	Sample();
	Sample(std::string name);

	std::string getName();
	void sampleMethod();
};
