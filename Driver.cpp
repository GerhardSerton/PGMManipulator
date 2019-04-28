#include <iostream>
#include <string>
#include "Image.h"

using namespace std;
int main (int argc, char*argv[])
{
	string command = argv[1];
	cout << "command: " << command << "\n";

	if (command == "-a")
	{
		string i1 = argv[2];
		string i2 = argv[3];
		string outputname = argv[4];
		Image image1(i1, outputname);
		Image image2(i2, outputname);
		image1 = image1 + image2;
		image1.save();
	}
	else if (command == "-s")
	{

		string i1 = argv[2];
		string i2 = argv[3];
		string outputname = argv[4];
		Image image1(i1, outputname);
		Image image2(i2, outputname);
		image1 = image1 - image2;
		image1.save();
	}
	else if (command == "-i")
	{
		string i1 = argv[2];
		string outputname = argv[3];
		Image image1(i1, outputname);
		//image1 = !image1;
	}
	else if (command == "-l")
	{

		string i1 = argv[2];
		string i2 = argv[3];
		string outputname = argv[4];
		Image image1(i1, outputname);
		Image image2(i2, outputname);
		//image1 = image1/image2;
	}
	else if (command == "-t")
	{

		string i1 = argv[2];
		int i2 = stoi(argv[3]);
		string outputname = argv[4];
		Image image1(i1, outputname);
		//image1 = image1 * i2;
	}
	//Test command, just loads the file in
	else
	{
		Image image(command, argv[2]);
		image.save();
	}
}
