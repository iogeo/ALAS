#ifndef ALASARRAYLISTS
#define ALASARRAYLISTS

namespace alas
{
	template <typename t> class arraylistelement
	{
		//ALAS
		public:
		t* array;
		int size;
		arraylistelement<t>* prec;
		arraylistelement<t>* next;
		arraylistelement(t* arrayin, int sizein, arraylistelement<t>* precedentarrayin, arraylistelement<t>* nextarrayin)
		{
			size=sizein;
			array=arrayin;
			next=nextarrayin;
			prec=precedentarrayin;
		}
		arraylistelement(t* arrayin, int sizein, arraylistelement<t>* precedentarrayin, arraylistelement<t>* nextarrayin, t** newarray)
		{
			size=sizein;
			array=new t[size];
			for(int i=0; i<sizein; i++)
			{
				array[i]=arrayin[i];
			}
			next=nextarrayin;
			prec=precedentarrayin;
			*newarray=array;
		}
		arraylistelement()
		{
			
		}
		~arraylistelement()
		{
			delete[] array;
		}
	};
	template <typename t> class arraylist
	{
		public:
		arraylistelement<t>* base;
		t** originalarrays;
		int arraycount;
		int originalarraycount;
		int originalarraymaxcount;
		int size;
		arraylist(t* a, int c)
		{
			originalarrays=new t*[1];
			base=new arraylistelement<t>(a, c, 0, 0, originalarrays);
			originalarraycount=1;
			originalarraymaxcount=1;
			arraycount=1;
			size=base->size;
		}
		arraylist(arraylistelement<t>* basein)
		{
			base=basein;
			arraycount=1;
			size=base->size;
		}
		void insert(t a, int p)
		{
			if(!p)
			{
				arraylistelement<t>* buffer=base;
				t* newarray[1];
				base=new arraylistelement<t>(&a, 1, 0, buffer, newarray);
				if(originalarraycount==originalarraymaxcount)
				{
					t** buffer2=originalarrays;
					originalarrays=new t*[originalarraycount*2];
					for(int i=0; i<originalarraycount; i++)
					{
						originalarrays[i]=buffer2[i];
					}
					originalarraymaxcount*=2;
				}
				originalarrays[originalarraycount]=*newarray;
				originalarraycount++;
				buffer->prec=base;
			}
			else
			if(p==size)
			{
				int tempsize=size;
				arraylistelement<t>* array=base;
				while(tempsize)
				{
					tempsize-=array->size;
					if(tempsize)
					array=array->next;
				}
				t* newarray[1];
				arraylistelement<t>* buffer=new arraylistelement<t>(&a, 1, array, 0, newarray);
				if(originalarraycount==originalarraymaxcount)
				{
					t** buffer2=originalarrays;
					originalarrays=new t*[originalarraycount*2];
					for(int i=0; i<originalarraycount; i++)
					{
						originalarrays[i]=buffer2[i];
					}
					originalarraymaxcount*=2;
				}
				originalarrays[originalarraycount]=*newarray;
				originalarraycount++;
				array->next=buffer;
			}
			else
			{
				int tempsize=p;
				arraylistelement<t>* array=base;
				t* newarray[1];
				while(tempsize>array->size)
				{
					tempsize-=array->size;
					array=array->next;
				}
				if(tempsize==array->size)
				{
					arraylistelement<t>* buffer=new arraylistelement<t>(&a, 1, array, array->next, newarray);
					array->next->prec=buffer;
					array->next=buffer;
				}
				else
				{
					arraylistelement<t>* buffer=new arraylistelement<t>(&a, 1, array, 0, newarray);
					arraylistelement<t>* nnext=new arraylistelement<t>(&array->array[tempsize], array->size-tempsize, buffer, array->next);
					array->next=buffer;
					array->size=tempsize;
					buffer->next=nnext;
					arraycount++;
				}
				if(originalarraycount==originalarraymaxcount)
				{
					t** buffer2=originalarrays;
					originalarrays=new t*[originalarraycount*2];
					for(int i=0; i<originalarraycount; i++)
					{
						originalarrays[i]=buffer2[i];
					}
					originalarraymaxcount*=2;
				}
				originalarrays[originalarraycount]=*newarray;
				originalarraycount++;
			}
			size++;
			arraycount++;
		}
		void insert(t* a, int c, int p)
		{
			if(!p)
			{
				arraylistelement<t>* buffer=base;
				t* newarray[1];
				base=new arraylistelement<t>(a, c, 0, buffer, newarray);
				if(originalarraycount==originalarraymaxcount)
				{
					t** buffer2=originalarrays;
					originalarrays=new t*[originalarraycount*2];
					for(int i=0; i<originalarraycount; i++)
					{
						originalarrays[i]=buffer2[i];
					}
					originalarraymaxcount*=2;
				}
				originalarrays[originalarraycount]=*newarray;
				originalarraycount++;
				buffer->prec=base;
			}
			else
			if(p==size)
			{
				int tempsize=size;
				arraylistelement<t>* array=base;
				while(tempsize)
				{
					tempsize-=array->size;
					if(tempsize)
					array=array->next;
				}
				t* newarray[1];
				arraylistelement<t>* buffer=new arraylistelement<t>(a, c, array, 0, newarray);
				if(originalarraycount==originalarraymaxcount)
				{
					t** buffer2=originalarrays;
					originalarrays=new t*[originalarraycount*2];
					for(int i=0; i<originalarraycount; i++)
					{
						originalarrays[i]=buffer2[i];
					}
					originalarraymaxcount*=2;
				}
				originalarrays[originalarraycount]=*newarray;
				originalarraycount++;
				array->next=buffer;
			}
			else
			{
				int tempsize=p;
				arraylistelement<t>* array=base;
				t* newarray[1];
				while(tempsize>array->size)
				{
					tempsize-=array->size;
					array=array->next;
				}
				if(tempsize==array->size)
				{
					arraylistelement<t>* buffer=new arraylistelement<t>(a, c, array, array->next, newarray);
					array->next->prec=buffer;
					array->next=buffer;
				}
				else
				{
					arraylistelement<t>* buffer=new arraylistelement<t>(a, c, array, 0, newarray);
					arraylistelement<t>* nnext=new arraylistelement<t>(&array->array[tempsize], array->size-tempsize, buffer, array->next);
					array->next=buffer;
					array->size=tempsize;
					buffer->next=nnext;
					arraycount++;
				}
				if(originalarraycount==originalarraymaxcount)
				{
					t** buffer2=originalarrays;
					originalarrays=new t*[originalarraycount*2];
					for(int i=0; i<originalarraycount; i++)
					{
						originalarrays[i]=buffer2[i];
					}
					originalarraymaxcount*=2;
				}
				originalarrays[originalarraycount]=*newarray;
				originalarraycount++;
			}
			size+=c;
			arraycount++;
		}
		t get(int p)
		{
			int tempsize=p;
			arraylistelement<t>* array=base;
			while(tempsize>=array->size)
			{
				tempsize-=array->size;
				array=array->next;
			}
			return array->array[tempsize];
		}
		void makeMasterArray()
		{
			t* newarray[1];
			arraylistelement<t>* buffer=new arraylistelement<t>(base->array, size, 0, 0, newarray);
			arraylistelement<t>* array=base;
			int p=0;
			while(array->next)
			{
				for(int i=0; i<array->size; i++)
				{
					buffer->array[p]=array->array[i];
					p++;
				}
				array=array->next;
			}
			for(int i=0; i<array->size; i++)
			{
				buffer->array[p]=array->array[i];
				p++;
			}
			for(int i=0; i<originalarraycount; i++)
			{
				delete[] originalarrays[i];
			}
			delete[] originalarrays;
			originalarrays=new t*[1];
			originalarrays[0]=*newarray;
			originalarraycount=1;
			originalarraymaxcount=1;	
			base=buffer;
			arraycount=1;
		}
	};
}

#endif
