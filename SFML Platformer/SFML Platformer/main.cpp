#include "Manager.h"

int main()
{
	Manager* manager = new Manager();

	manager->RunGame();

	delete manager;
	manager = nullptr;

	return 0;
}