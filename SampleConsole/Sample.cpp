#include "Simple.h"
#include <iostream>

Sample::Sample() {
}

Sample::Sample(std::string name = "Unnamed Soldier") {
	this->name = name;
}

std::string Sample::getName() {
	return this->name;
}

void Sample::sampleMethod() {
	printf("sampleMethod");
}
