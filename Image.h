#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <memory>
#include <fstream>
#include <iostream>

class Image
{
friend class Iterator;
private:
	int width, height;
	std::unique_ptr<unsigned char[]> data;
	std::string inputname;
	std::string outputname;
	std::string topl;

public:
	Image();
	Image(std::string filename, std::string outputname);
	Image(const Image & rhs);
	Image(Image && rhs);
	~Image();

	void load();
	void save();
	bool checkSizes(Image b);
	unsigned char * getContents();

	Image & operator = (const Image & rhs);
	Image & operator = (Image && rhs);
	Image operator + (Image rhs);
	Image operator ! ();
	Image operator / (Image rhs);
	Image operator * (int rhs);

	class Iterator
	{
	friend class Image;
	private:
		unsigned char * ptr;

		Iterator(unsigned char * p): ptr(p)
		{}


	public:
		Iterator (const Iterator & rhs): ptr(rhs.ptr)
		{}
		~Iterator ()
		{}

		Iterator & operator = (const Iterator & rhs)
		{
			ptr = rhs.ptr;
			return *this;
		}

		Iterator(Iterator && rhs): ptr(std::move(rhs.ptr))
		{}

		Iterator & operator = (Iterator && rhs)
		{
			ptr = std::move(rhs.ptr);
			return *this;
		}

		Iterator operator ++ ()
		{
			++ptr;
			return *this;
		}

		Iterator operator ++ (int)
		{
			Iterator temp = Iterator(*this);
			operator++();
			return temp;
		}

		Iterator operator --()
		{
			--ptr;
			return *this;
		}

		Iterator operator -- (int)
		{
			Iterator temp = *this;
			operator--();
			return temp;
		}
		unsigned char operator * ()
		{
			return *ptr;
		}

		bool operator != (Iterator rhs)
		{
			if (ptr == rhs.ptr)
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		unsigned char * begin()
		{
			return ptr;
		}

		unsigned char * end(int size)
		{
			ptr = ptr + size;
			return ptr;
		}
	};

	Iterator begin();
	Iterator end();

};




#endif
