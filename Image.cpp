#include "Image.h"

Image::Image()
{

}

Image::Image(std::string filename, std::string outputname): inputname(filename), outputname(outputname)
{
	load();
}

Image::Image(const Image & rhs): inputname(rhs.inputname), outputname(rhs.outputname), width(rhs.width), height(rhs.height)
{
	for (int i = 0; i < (width*height); i++)
	{
			data[i] = rhs.data[i];
	}
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
		std::string intensity;
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
		std::getline(loadFile, intensity);
		height = std::stoi(nrows);
		width = std::stoi(ncolumns);
	  std::unique_ptr<unsigned char[]> temp (new unsigned char[height * width]);
		loadFile.read((char *)temp.get(), width*height);
		loadFile.close();
		data = std::move(temp);
		topl = topline;
	}
	else
	{
		std::cout << "Cannot open file\n";
	}

}

void Image::save()
{
		std::ofstream saveFile (outputname, std::ios::out | std::ios::binary);

		saveFile << topl << "\n";
		saveFile << height << " " << width << "\n";
		saveFile << "255" << "\n";

		saveFile.write((char *)data.get(), width * height);

		saveFile.close();
}

bool Image::checkSizes(Image b)
{
	if (width == b.width && height == b.height)
	{
		return true;
	}
	else
	{
		return false;
	}
}

unsigned char * Image::getContents()
{
		return data.get();
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

Image::Iterator Image::begin()
{
	return Image::Iterator(data.get());
}

Image::Iterator Image::end()
{
	Image::Iterator temp(data.get());
	temp.end(width * height);
	return temp;
}
