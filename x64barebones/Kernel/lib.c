#include "./include/lib.h"

void * memset(void * destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

void * memcpy(void * destination, const void * source, uint64_t length)
{
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}

int str_cpy(const char* from, char* destination){
  int i = 0;
	for (i = 0; from[i] != 0; ++i)
		destination[i] = from[i];
	destination[i] = 0;
	return i;
}

int str_len(char * msg){
	if(msg == (char *) 0x0) return 0;
	int aux = 1;
	while(*msg){
		aux++;
		msg++;
	}
	return aux;
}

int str_cmp(char * s1, char * s2){
	if((s1 != NULL && s2 == NULL) ||
		(s1 == NULL && s2 != NULL)) return -1;
	int i;
	if(s1==NULL || s2==NULL)
		return 1;
  	for (i = 0; s1[i] == s2[i]; i++){
	  	if (s1[i] == '\0'){
      		return 0;
		}
	}
	return s1[i] - s2[i];
}
