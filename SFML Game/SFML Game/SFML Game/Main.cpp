#include "Manager.h"

int main()
{
	// Creating main manager object
	Manager* manager = new Manager();

	// Running program
	manager->RunProgram();

	// Deallocating memory
	delete manager;
	manager = nullptr;

	// Ending program
	return 0;
}