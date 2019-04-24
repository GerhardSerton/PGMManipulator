#include "Image.h"

Image::Image()
{

}

Image::Image(std::string filename): inputname(filename)
{
	load();
}

Image::Image(const Image & rhs)
{

}

Image::Image(Image && rhs)
{

}

Image::~Image()
{

}

void Image::load()
{
	std::ifstream loadFile (inputname, std::ios::in | std::ios::binary);

	if (loadFile.is_open())
	{
		std::string topline;
		std::string nrows;
		std::string ncolumns;
		while (topline == "" || nrows == "" || ncolumns == "")
		{
			std::string current;
			std::getline(loadFile, current);
			if (current[0] != '#')
			{
				if (topline == "")
				{
					topline = current;
				}
				else
				{
					int space = current.find(' ');
					nrows = current.substr(0, space);
					ncolumns = current.substr(space + 1);
				}

			}
		}
		height = std::stoi(nrows);
		width = std::stoi(ncolumns);
	       	std::unique_ptr<unsigned char[]> temp (new unsigned char[height * width]);	
		loadFile.read((char *)temp.get(), width*height);
		loadFile.close();
		data = std::move(temp);
	}
	else
	{
		std::cout << "Cannot open file\n";
	}

}

void Image::save()
{

}

bool Image::checkSizes(Image b)
{
	return false;
}

Image & Image::operator = (const Image & rhs)
{

}

Image & Image::operator = (Image && rhs)
{

}

Image Image::operator + (Image rhs)
{

}

Image Image::operator ! ()
{

}

Image Image::operator / (Image rhs)
{

}

Image Image::operator * (int rhs)
{

}
