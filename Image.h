#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <memory>

class Image
{
private:
	int width, height;
	std::unique_ptr<unsigned char[]> data;
public:
	Image();
	Image(int w, int h, string filename);
	Image(const Image & rhs);
	Image(Image && rhs);
	~Image();

	Image & operator = (const Image & rhs);
	Image & operator = (Image && rhs);
	Image operator + (Image rhs);
	Image operator ! ();
	Image operator / (Image rhs);
	Image operator * (int rhs);

	class Interator
	{
	private:
		unsigned char * ptr;
		
		Iterator(u_char * p): ptr(p)
		{}

	public:
		Iterator (const Iterator & rhs)
		{}
		~Iterator ()
		{}

		Iterator & operator = (const Interator & rhs)
		{}

		Iterator operator ++()
		{}

		Iterator operator ++ (int)
		{}

		Iterator operator --()
		{}

		Iterator operator -- (int)
		{}

		Iterator operator * (int rhs)
		{}


	}

		

}


#endif
