#include <iostream>
#include <random>

int main()
{
	int* a=new int[22222222];
	alas::arraylist<int> al(a, 22222222);
	delete a;
	for(int i=0; i<2222; i++)
	{
		std::cout<<al.get(i);
	}
	for(int i=0; i<8; i++)
	{
		a=new int[22222222];
		al.insert(a, 22222222, al.size);
		delete a;
	}
	int t=al.size;
	a=new int[222222];
	for(int i=0; i<222222; i++)
	{
		a[i]=rand()*rand();
	}
	al.insert(a, 222222, al.size);
	delete a;
	for(int i=0; i<2222; i++)
	{
		al.erase(rand()*i);
	}
	for(int i=t; i<al.size; i++)
	{
		std::cout<<al.get(i);
	}
	al.makeMasterArray();
	for(int i=0; i<al.size; i++)
	{
		std::cout<<al.get(i);
	}
}
