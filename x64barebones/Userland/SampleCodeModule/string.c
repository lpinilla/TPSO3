#include <string.h>

int str_cmp(const char string1[],const char string2[]){
    for (int i = 0; ; i++){
        if (string1[i] != string2[i]){
            if(string1[i]<string2[i])
              return 1;
            return -1;
          }
        if (string1[i] == '\0')
            return 0;
    }
}

int str_cpy(const char* from, char* destination){
  int i = 0;
	for (i = 0; from[i] != 0; ++i)
		destination[i] = from[i];
	destination[i] = 0;
	return i;
}
