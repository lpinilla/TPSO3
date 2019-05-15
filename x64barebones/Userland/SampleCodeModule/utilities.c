#include <utilities.h>

void put_char(char c){
  sys_write(&c,1);
}

void print_string(char *s){
  int i=0;
  while(s[i]!='\0'){
    sys_write(s+i,1);
    i++;
  }
}
char get_char(){
  char c=EOF;
  while(c==EOF)
    sys_read(&c,1);
  return c;
}


void print_number(int number){
  if (number == 0){
   put_char('0');
   return;
  }
  int n = get_digits(number);
  char array[n];
  for(int i = 0; i < n; i++){
    array[n-1-i] = number % 10;
    number /= 10;
  }
  for(int i = 0; i < n; i++){
    put_char(array[i] + '0');
  }
}

int print_f(const char * format, ...){
  if(format==NULL)
    return 0;
  int i=0;
  int flag=FALSE;
  va_list va;
  va_start(va, format);
  while(format[i]!=0){
    switch(format[i]){
      case '%':
        if(flag){
          put_char('%');
          flag=FALSE;
        }
        else
          flag=TRUE;
        break;
      case 'd':
          if(flag){
            print_number(va_arg(va,int));
            flag=FALSE;
          }
          else
            put_char('d');
          break;
      case 's':
        if(flag){
          print_string(va_arg(va, char *));
          flag=FALSE;
        }
        else
          put_char('s');
        break;
      case 'c':
        if(flag){
          put_char(va_arg(va,int));
          flag=FALSE;
        }
        else
          put_char('c');
        break;

      default:
          put_char(format[i]);
    }
    i++;
  }
  va_end(va);
  return i;
}


int get_digits(int number){
  if(number/10 == 0)
    return 1;
  return 1 + get_digits(number/10);
}


void clear_console(){
  sys_clear_console();
}

int scan_f(const char* format, ...){
	va_list va;
	va_start(va,format);
	int ret = 0; // valor de retorno, numero de variables que escribio
	int flag = FALSE; // flag para saber si estamos en un %
	int i = 0;
	char buffer[MAX_BUFFER];  // buffer donde guardamos el comando
	int j = 0;
	char c;

	while((c = get_char()) != '\n'){ // Este while hace la logica de guardar en buffer el comando e imprimirlo en STDOUT
		if(c == '\b'){
			if(i>0){
				buffer[--i] = 0;
				print_f("\b");
			}
		}else{
			if(i < MAX_BUFFER){
				buffer[i++]	= c;
				put_char(c);
			}
		}
	}
	buffer[i] = 0;
	i = 0;
	while(format[i]!=0&&ret>=0){  //loop para comparar el comando que tenemos con el formato, ret se usa como flag para salir si hay algo no igual
		switch(format[i]) {
			case '%':  //caso del %
				if(flag) {  // aca entra si el % anterior es un %, por lo tanto hubo un error de formato si el comando no viene con un %
					if(buffer[j]!='%')
						ret = -1;
					else  //  //si viene con un % sumamos al indice del comando ya que el acual matchea
						j++;
				} else {  // si es el primer % que encontramos activamos el flag
					flag = TRUE;
				}
				break;
			case 'd':      // caso de una d
				if(flag){  // si ya estaba el flag significa que estamos en un %d por lo tanto vamos a consumir todo el numero que haya
					if(get_number(buffer, va_arg(va, int *), &j))
            ret++;
				  else
            ret = -1;
          flag = FALSE;
        }
        else{  // si no esta el flag activado significa que es una d sola, chequeamos que el comando venga una d y si no activamos el flag para romper
					       if(buffer[j]!='d')
						           ret = -1;
					       else
						     j++;
				  }
				  break;
          case 's':
                if(flag){
                    j += str_cpy(buffer+j,va_arg(va,char*));
                    ret++;
                    flag = FALSE;
                  } else {
                    if(buffer[j]!='s')
                      ret = -1;
                    else
                      j++;
                  }
                  break;
        default: // caso default comparamos el comando con el buffer
            if(buffer[j]!=format[i])
              ret = -1;
            else
              j++;
		}
		i++;
	}
  put_char('\n');
	va_end(va);
	return ret;
}
int get_number(char * array, int * pointer, int * index){
  *pointer = 0; // limpio el puntero
	int ret = 0; // auxiliar de retorno
	char c; // auxiliar de char
	int flag = TRUE;
	do{
		c = array[*index];  //asigno el auxiliar al indice del array
		if(is_digit(c)){  // si lo que asigne es un numero
			*pointer = (*pointer)*10; // multiplico al puntero por 10 para agregar un 0
			*pointer += c - '0';  // le sumo el ascii del numero
			ret = TRUE; //ponemos en true ya que pudimos leer al menos un numero
			*index = (*index)+1; //sumamos el indice
		}
    else {
			flag = FALSE;
		}
	} while(flag);
	return ret;
}

int is_alpha(unsigned char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
int is_digit(unsigned char c) {
    return (c >= '0' && c <= '9');
}
int is_symbol(unsigned char c){
	return ((c >= '!' && c <= '/') || (c >= ':' && c <= '@') || (c>='[' && c <= 96) || (c>='{' && c <='~'));
}
int is_space(unsigned char c){
	return (c==' ');
}
