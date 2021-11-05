#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include "Simple.h"

int intValue = 100;
int intArray[10];
char charArray[] = "sample characters array";
std::array<int, 2> stdIntArray;
std::vector<int> stdVector;
int* pointerToIntValue = new int(200);

Sample sampleObject("sample object");
Sample* sampleObjectPointer = new Sample("sample object 2");
std::shared_ptr<Sample> dynamo = std::make_shared<Sample>("sample object 3");

int* allocatedIntValue = (int*)malloc(sizeof(int));

template <typename T> void dump(T &text, std::string name = "") {
	std::cout << name << "\t" << &text << ":" << text << std::endl;
}

void voidFunction() {
	printf("void function\n");
}

int intFunctionP1(int param) {
	std::cout << param << std::endl;
	return param;
}

int main()
{
	*allocatedIntValue = 500;

	dump(charArray, "charArray:");

	auto iterator = stdVector.begin();
	iterator = stdVector.insert(iterator, 10);
	stdVector.insert(iterator, 20);
	dump(stdVector[0], "stdVector[0]:");

	dump(intValue, "intValue:");
	dump(pointerToIntValue, "pointerToIntValue:");
	dump(*allocatedIntValue, "allocatedIntValue:");

	sampleObjectPointer->sibling = new Sample("sample object uncle");
	dump(sampleObjectPointer, "sampleObjectPointer");
	dump(sampleObjectPointer->a, "sampleObjectPointer->a");
	dump(sampleObjectPointer->sibling, "sampleObjectPointer->sibling");

	dump(voidFunction, "voidFunction()");
	dump(intFunctionP1, "intFunctionP1()");

	system("pause");

	delete sampleObjectPointer->sibling;
	delete sampleObjectPointer;
	free(allocatedIntValue);

	int level = 100;

	while (true) {
		voidFunction();

		level++;
		intFunctionP1(level);

		system("pause");
	}

	return 0;
}
