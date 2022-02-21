#ifndef ALASARRAYLISTS
#define ALASARRAYLISTS

namespace alas
{
	template <typename t> class arraylistelement
	{
		public:
		t* array;
		int size;
		bool original;
		arraylistelement<t>* prec;
		arraylistelement<t>* next;
		arraylistelement(t* arrayin, int sizein, arraylistelement<t>* precedentarrayin, arraylistelement<t>* nextarrayin)
		{
			size=sizein;
			array=arrayin;
			next=nextarrayin;
			prec=precedentarrayin;
			original=0;
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
			original=1;
		}
		arraylistelement()
		{
			
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
		void insert(t a, int p)
		{
			int b[1];
			*b=a;
			insert(b, 1, p);
		}
		void erase(int c, int p)
		{
			int tempsize=p;
			arraylistelement<t>* array=base;
			if(p)
			{
				while(tempsize>=array->size)
				{
					tempsize-=array->size;
					array=array->next;
				}
				if(!tempsize)
				{
					if(array->size>c)
					{
						array->size-=c;
					}
					else
					if(array->size==c)
					{
						array->next->prec=array->prec;
						array->prec->next=array->next;
						if(array->original)
						{
							delete[] array->array;
						}
						delete array;
						arraycount--;
					}
					else
					{
						int tempsize2=c;
						arraylistelement<t>* nprec=array->prec;
						while(tempsize2>=array->size)
						{
							tempsize2-=array->size;
							array=array->next;
							if(array->prec->original)
							{
								delete[] array->prec->array;
							}
							delete array->prec;
							arraycount--;
						}
						if(!tempsize2)
						{
							nprec->next=array;
							array->prec=nprec;
							if(array->prec->original)
							{
								delete[] array->prec->array;
							}
							delete array->prec;
							arraycount--;
						}
						else
						{
							array->array=&array->array[tempsize2];
							nprec->next=array;
							array->prec=nprec;
							array->size-=tempsize2;
						}
					}
				}
				else
				{
					int tempsize2=c;
					arraylistelement<t>* buffer=array;
					while(tempsize2>array->size)
					{
						tempsize2-=array->size;
						array=array->next;
						if(array->prec!=buffer)
						{
							if(array->prec->original)
							{
								delete[] array->prec->array;
							}
							delete array->prec;
							arraycount--;
						}
					}
					if(tempsize2==array->size)
					{
						buffer->size=p;
						buffer->next=array->next;
						array->next->prec=buffer;
						delete[] array->array;
						delete array;
						arraycount--;
					}
					else
					{
						arraylistelement<t>* nnext=new arraylistelement<t>(&array->array[tempsize2+tempsize], array->size-tempsize2-tempsize, buffer, array->next);
						buffer->size=tempsize;
						buffer->next=nnext;
						nnext->prec=buffer;
						arraycount++;
					}
				}
			}
			else
			{
				if(base->size>c)
				{
					base->array=&base->array[c];
					base->size-=c;
				}
				else
				{
					if(size>c)
					{
						int tempsize2=c;
						while(tempsize2>array->size)
						{
							tempsize2-=array->size;
							array=array->next;
							if(array->prec->original)
							{
								delete[] array->prec->array;
							}
							delete array->prec;
							arraycount--;
						}
						array->size=array->size-tempsize2;
						array->array=&array->array[tempsize2];
						base=array;
					}
					else
					{
						delete[] base->array;
						delete base;
					}
					arraycount--;
				}
			}
			size-=c;
		}
		void erase(int p)
		{
			if(p)
			{
				int tempsize=p;
				arraylistelement<t>* array=base;
				while(tempsize>=array->size)
				{
					tempsize-=array->size;
					array=array->next;
				}
				if(!tempsize)
				{
					if(array->size>1)
					{
						array->size-=1;
					}
					else
					if(array->size==1)
					{
						array->next->prec=array->prec;
						array->prec->next=array->next;
						if(array->original)
						{
							delete[] array->array;
						}
						delete array;
						arraycount--;
					}
				}
				else
				{
					arraylistelement<t>* nnext=new arraylistelement<t>(&array->array[1+tempsize], array->size+1-tempsize, array, array->next);
					array->next=nnext;
					array->size=tempsize;
					arraycount++;
				}
			}
			else
			{
				if(base->size>1)
				{
					base->array=&base->array[1];
					base->size-=1;
				}
				else
				{
					if(size>1)
					{
						base=base->next;
						delete[] base->prec->array;
						delete base->prec;
					}
					else
					{
						delete[] base->array;
						delete base;
					}
					arraycount--;
				}
			}
			size--;
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
				arraylistelement<t>* larray=array->next;
				delete array;
				array=larray;
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
