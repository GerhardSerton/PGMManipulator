#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <memory>
#include <fstream>
#include <iostream>

class Image
{
private:
	int width, height;
	std::unique_ptr<unsigned char[]> data;
	std::string inputname;
public:
	Image();
	Image(std::string filename);
	Image(const Image & rhs);
	Image(Image && rhs);
	~Image();

	void load();
	void save();
	bool checkSizes(Image b);

	Image & operator = (const Image & rhs);
	Image & operator = (Image && rhs);
	Image operator + (Image rhs);
	Image operator ! ();
	Image operator / (Image rhs);
	Image operator * (int rhs);

	class Iterator
	{
	private:
		unsigned char * ptr;
		int size;

		Iterator(unsigned char * p): ptr(p)
		{}

	public:
		Iterator (const Iterator & rhs): ptr(rhs.ptr), size(rhs.size)
		{}
		~Iterator ()
		{}

		Iterator & operator = (const Iterator & rhs)
		{
			ptr = rhs.ptr;
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

		void setSize(int i)
		{
			size = i;
		}

		unsigned char * begin()
		{
			return ptr;
		}

		unsigned char * end()
		{
			return ptr + size;
		}




	};



};


#endif
