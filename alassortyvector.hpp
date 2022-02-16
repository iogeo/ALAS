#ifndef ALASSORTY
#define ALASSORTY

namespace alas
{
	template <typename t> class sortyvector
	{
		t* array;
		int size;
		int maxsize;
		public:
		sortyvector()
		{
			size=0;
			maxsize=0;
		}
		~sortyvector()
		{
			delete[] array;
		}
		void push_back(t a)
		{
			if(size==maxsize)
			{
				if(size)
				{
					int* temparray=array;
					array=new t[size*2];
					for(int i=0; i<size; i++)
					{
						array[i]=temparray[i];
					}
					delete[] temparray;
					maxsize=size*2;
				}
				else
				{
					array=new t[1];
					maxsize=1;
				}
			}
			bool b=0;
			for(int i=0; i<size; i++)
			{
				if(!b)
				{
					if(array[i]>=a)
					{
						for(int j=size; j>=i; j--)
						{
							array[j]=array[j-1];
						}
						array[i]=a;
						b=1;
					}
				}
			}
			if(!b)
			{
				array[size]=a;
			}
			size++;
		}
		void resize(int a)
		{
			if(maxsize)
			{
				int* temparray=array;
				array=new t[a];
				for(int i=0; i<size; i++)
				{
					array[i]=temparray[i];
				}
				delete[] temparray;
				maxsize=a;
			}
			else
			{
				array=new t[a];
				maxsize=a;
			}
		}
		void erase(int a)
		{
			for(int j=a; j<size-1; j++)
			{
				array[j]=array[j+1];
			}
			size--;
		}
		void erase(int a, int c)
		{
			for(int j=a; j<size; j++)
			{
				array[j]=array[j+c];
			}
			size-=c;
		}
		void shrink_to_fit()
		{
			int* temparray=array;
			array=new t[size];
			for(int i=0; i<size; i++)
			{
				array[i]=temparray[i];
			}
			delete[] temparray;
			maxsize=size;
		}
		t get(int a)
		{
			return array[a];
		}
		int getsize()
		{
			return size;
		}
	};
}

#endif
