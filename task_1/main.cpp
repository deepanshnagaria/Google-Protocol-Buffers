#include <iostream>
#include <fstream>
#include <string>
#include "read.h"
#include "write.h"
using namespace std;

int main(int argc, char* argv[])
{
	string choice;
	while (true)
	{
		cout << "You want to read or write? ";
		getline(cin, choice);
		if (choice == "read")
		{
			read(argc, argv);
			break;
		}
		else if (choice == "write")
		{
			write(argc, argv);
			break;
		}
		cout << " Invalid Input : please type \'read\' or \'write\'"<<endl;
	}
	return 0;
}