#ifndef ALASUNSORT
#define ALASUNSORT

#include <random>

namespace alas
{
	template <typename t>* void unsortarray(t* arr, int c)
	{
		int buffer, temp;
		for(int ac=0; ac<c; ac++)
		{
			buffer=arr[ac];
			temp=std::rand()%(c-ac);
			arr[ac]=arr[ac+temp];
			arr[ac+temp]=buffer;
		}
	}
}

#endif
