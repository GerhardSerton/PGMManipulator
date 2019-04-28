#include "Image.h"
#include <vector>

Image::Image()
{

}

Image::Image(std::string filename, std::string outputname): inputname(filename), outputname(outputname)
{
	load();
}

Image::Image(const Image & rhs): inputname(rhs.inputname), outputname(rhs.outputname), width(rhs.width), height(rhs.height), topl(rhs.topl)
{

	std::unique_ptr<unsigned char[]> temp (new unsigned char[rhs.height * rhs.width]);
	int no = 0;
	for (auto i = rhs.begin(); i != rhs.end(); ++i)
	{
		temp[no] = *i;
		++no;
	}

	data = std::move(temp);

}

Image::Image(Image && rhs): inputname(std::move(rhs.inputname)), outputname(std::move(rhs.outputname)), width(std::move(rhs.width)), height(std::move(rhs.height)), topl(std::move(rhs.topl))
{
	data = std::move(rhs.data);
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
		std::cout << "Outputting to: " << outputname << "\n";
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
		width = rhs.width;
		height = rhs.height;
		inputname = rhs.inputname;
		outputname = rhs.outputname;
		topl = rhs.topl;

		std::unique_ptr<unsigned char[]> temp (new unsigned char[rhs.height * rhs.width]);
		int no = 0;
		for (auto i = rhs.begin(); i != rhs.end(); ++i)
		{
			temp[no] = *i;
			++no;
		}

		data = std::move(temp);
		return *this;
}

Image & Image::operator = (Image && rhs)
{
	width = std::move(rhs.width);
	height = std::move(rhs.height);
	inputname = std::move(rhs.inputname);
	outputname = std::move(rhs.outputname);
	topl = std::move(rhs.topl);

	data = std::move(rhs.data);
	return *this;

}

Image Image::operator + (Image rhs)
{
	if (checkSizes(rhs))
	{
		Image temp(*this);
		std::unique_ptr<unsigned char[]> tempchar (new unsigned char[rhs.height * rhs.width]);
		auto tempi = temp.begin();
		auto rhsi = rhs.begin();
		int count = 0;
		while (tempi != temp.end())
		{
			int sum = (int)(*tempi) + (int)(*rhsi);
			if (sum > 255)
			{
				sum = 255;
			}
			tempchar[count] = (unsigned char)(sum);
			++count;
			++tempi;
			++rhsi;
		}

		temp.data = std::move(tempchar);

		return temp;
	}
	else
	{
		std::cout << "ERROR: Not same sizes";
		return *this;
	}
}

Image Image::operator - (Image rhs)
{
	if (checkSizes(rhs))
	{
		Image temp(*this);
		std::unique_ptr<unsigned char[]> tempchar (new unsigned char[rhs.height * rhs.width]);
		auto tempi = temp.begin();
		auto rhsi = rhs.begin();
		int count = 0;
		while (tempi != temp.end())
		{
			int sum = (int)(*tempi) - (int)(*rhsi);
			if (sum < 0)
			{
				sum = 0;
			}
			tempchar[count] = (unsigned char)(sum);
			++count;
			++tempi;
			++rhsi;
		}

		temp.data = std::move(tempchar);

		return temp;
	}
	else
	{
		std::cout << "ERROR: Not same sizes";
		return *this;
	}
}

Image Image::operator ! ()
{
		Image temp(*this);
		std::unique_ptr<unsigned char[]> tempchar (new unsigned char[height * width]);
		int j = 0;
		for (auto tempi = temp.begin(); tempi != temp.end(); ++tempi)
		{
			int result = 255 - (int)(*tempi);
			if (result < 0)
			{
				result = 0;
			}

			tempchar[j] = (unsigned char)(result);
			++j;
		}

		temp.data = std::move(tempchar);
		return temp;
}

Image Image::operator / (Image rhs)
{
	if (checkSizes(rhs))
	{
		Image temp(*this);
		std::unique_ptr<unsigned char[]> tempchar (new unsigned char[rhs.height * rhs.width]);
		auto tempi = temp.begin();
		auto rhsi = rhs.begin();
		int count = 0;
		while (tempi != temp.end())
		{
			if ((int)(*rhsi) == 255)
			{
				tempchar[count] = *tempi;
			}
			else
			{
				tempchar[count] = (unsigned char) 0;
			}
			++count;
			++tempi;
			++rhsi;
		}

		temp.data = std::move(tempchar);

		return temp;
	}
	else
	{
		std::cout << "ERROR: Not same sizes";
		return *this;
	}
}

Image Image::operator * (int rhs)
{
	Image temp(*this);
	std::unique_ptr<unsigned char[]> tempchar (new unsigned char[height * width]);
	int j = 0;
	for (auto tempi = temp.begin(); tempi != temp.end(); ++tempi)
	{
		if ((int)(*tempi) > rhs)
		{
			tempchar[j] = (unsigned char)(255);
		}
		else
		{
			tempchar[j] = (unsigned char)(0);
		}
		++j;
	}

	temp.data = std::move(tempchar);
	return temp;
}

Image::Iterator Image::begin() const
{
	return Image::Iterator(data.get());
}

Image::Iterator Image::end() const
{
	Image::Iterator temp(data.get());
	temp.end(width * height);
	return temp;
}
