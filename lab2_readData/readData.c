#include "endian.h" 

// read chars (1 byte), no swaps needed
void readChar(FILE *f, int swap, char *c){
	fread(c, 1, 1, f); 
}

// read string (1 byte for each character in string), no swaps needed
void readString(FILE *f, int swap, char *c){
	
	char str; 
	int i=0; 
	
	do{
		fread(&str,1,1,f); //read from address of string (one byte for
				//chars)
		*(c+i)=str; //takes in the current element of the string to 
				// check to see if it's null character
		i++; //increment the pointer
	}while(str!='\0');
}

void readInt(FILE *f, int swap, int *c){
	
	
	fread(c, 4, 1, f); // read int (4 bytes)
	
	//check swap, if 1 swap the content of c, otherwise don't swap
	if(swap==1){
		*c = swapInt(*c);
	}
	
}

void readLong(FILE *f, int swap, long *c){
	
	
	fread(c, 8, 1, f); //read long (8 bytes)
	
	//check swap, if 1 then swap contents of c, otherwise leave c as is
	if(swap==1){
		*c = swapLong(*c);
	}
	
}

void readPtr(FILE *f, int swap, void **c){
	
	
	
	fread(c,8,1,f); // read pointer (8 bytes to be safe, since we're
			// dealing with int-4bytes,char-1byte,and long-8byte, 				// and max is long-8bytes)
	if(swap==1){
		*(long*)c = swapLong(*(long*)c); //since we assumed long-8byte
						//earlier, we might as well 
						//use long
		
	}
}


