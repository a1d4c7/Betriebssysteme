#include "lib/tools.h"

void* memcpy(void* dest, const void* src, unsigned n){
	
	char* a= dest;
	const char* b= src;
	unsigned i= 0;

	for(i=0; i < n; i++){
		
		(*a) = (*b);
		a++;
		b++;
	}
	
	return dest;
}


