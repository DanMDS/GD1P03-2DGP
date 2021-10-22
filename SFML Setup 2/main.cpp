#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

using namespace std;

void Input()
{

}

void ReadFile(string _path)
{
	ifstream settingsFile;	// The file we're loading
	string line;			// The line we're currently reading

	settingsFile.open(_path);

	if (settingsFile.is_open())
	{
		while (getline(settingsFile, line))
		{
			if (line == "[Settings]")
			{
				cout << "Loading Settings:\n";
			}
			else
			{
				size_t pos = line.find('=');
				string value = line.substr(pos + 1);
				cout << "apathy value currently: " << value << "\n";

				int apathyInt = stoi(value);
				apathyInt *= 10;
				apathyInt += 4;

				cout << "incrementing apathy.... " << apathyInt << endl;

				//cout << line << "\n";
			}
		}
	}

	else
	{
		cout << "Unable to open or edit file\n";
		settingsFile.close();
	}
}

int main()
{
	ReadFile("settings.ini");

	return 0;
}