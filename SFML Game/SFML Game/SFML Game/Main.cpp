#include "Manager.h"

int main()
{
	Manager* manager = new Manager();
	manager->RunProgram();

	delete manager;
	manager = nullptr;

	return 0;
}