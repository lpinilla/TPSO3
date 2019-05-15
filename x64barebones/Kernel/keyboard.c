
#include <keyboard.h>
extern uint8_t io_read(uint16_t port);

static char buffer[BUFFER_SIZE];
static int head; //variable global
static int tail;
static int full=FALSE;
static int caps_lock_pressed = FALSE;
static int shift= FALSE;

int is_alpha(unsigned char c);
int is_cntrl(unsigned char c);
void add_buffer(char);
int buffer_empty();

#define CHECKBYTE(binary, index) (binary & 1<<(index)) // macro que checkea si el byte en la posicion index esta prendido

unsigned char keycode_map[128] = {
    27,  '`', '1', '2', '3', '4', '5', '6', '7', '8', /* INDEX: 0 - 9 */
    '9','0', '-', '=','\b', '\t' /* Tab */,'q', 'w', 'e', 'r',	/* INDEX: 10 - 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0 /* Control */, /* INDEX: 20 - 29 */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* INDEX: 30 - 39 */
 '\'', '`',  LEFT_SHIFT,'\\', 'z', 'x', 'c', 'v', 'b', 'n', /* INDEX: 40 - 49 */
  'm', ',', '.', '/', RIGHT_SHIFT,'*',0/* Alt */,' '/* Space bar */, CAPS_LOCK, 0 /* F1 */, /* INDEX: 50 - 59 */
    0/* F2 */,   0/* F3 */,   0/* F4 */,   0/* F5 */,   0/* F6 */,   0/* F7 */,   0/* F8 */,   0/* F9 */, 0 /*F10 */, 0/*Num lock*/, /* INDEX: 60 - 69 */
    0 /* Scroll Lock */,0 /* Home key */, UP_ARROW /* Up Arrow */, 0 /* Page Up */, '-', LEFT_ARROW/* Left Arrow */, 0, RIGHT_ARROW/* Right Arrow */,'+', 0/*End key*/, /* INDEX: 70 - 79 */
    DOWN_ARROW/* Down Arrow */,0/* Page Down */, 0/* Insert Key */, 0/* Delete Key */, 0,   0,   0,  0/* F11 Key */, 0/* F12 Key */,
    0,	/* All other keys are undefined */
};
unsigned char alternative_keycode_map[128] = {
  0,'~','!','@','#','$','%',94, '&', '*', '(', ')', 95,'+', '\b', '\t', /* shift + tab not defined in normal aasci*/
  'Q','W','E','R','T','Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0,
  'A', 'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
  '~', LEFT_SHIFT, '|', 'Z', 'X', 'C', 'V', 'B', 'N',
  'M', '<', '>', '?', RIGHT_SHIFT, '*', 0, ' ', CAPS_LOCK, 0,
  0,0,0,0,0,0,0,0,0,
  DOWN_ARROW,0,0,0,0,0,0,0,0,
  0,};

void keyboard_handler(){
	int key;
	if(CHECKBYTE(io_read(KEYBOARD_STATUS_PORT),0)) // verificamos que se pueda leer del port
		key = io_read(KEYBOARD_DATA_PORT);
	else
		return;
  if(CHECKBYTE(key,7)){ // si esta el bit 7 prendido es que es un codigo de tecla break
    	if(keycode_map[key-BREAK_CODE_DIF] == LEFT_SHIFT || keycode_map[key-BREAK_CODE_DIF] == RIGHT_SHIFT)// nos fijamos si es una tecla soltada y por ahora solo tenemos en cuenta que los caracteres combinacion son los shift
  		shift=FALSE;
  	return;
  }
	if(keycode_map[key]==CAPS_LOCK){
		caps_lock_pressed=(caps_lock_pressed?FALSE:TRUE);
		return;
	}
  if(keycode_map[key]==LEFT_SHIFT || keycode_map[key]==RIGHT_SHIFT){
    shift=TRUE;
    return;
  }
	unsigned char c=keycode_map[key];
  if(is_alpha(c) /*|| is_cntrl(c)*/){
  	if(caps_lock_pressed==TRUE && shift==FALSE){
  				c-=32;
  	}
    else if(caps_lock_pressed==FALSE && shift==TRUE)
          c-=32;
  }
  else{
    if(shift==TRUE)
      c = alternative_keycode_map[key];
  }
  add_buffer(c);
  return;
}

void add_buffer(char c){
  buffer[head]=c;
  if(full==TRUE){
    tail = (tail+1) % BUFFER_SIZE;
  }
  head = (head+1) % BUFFER_SIZE;
  if(head==tail){
    full=TRUE;
  }
}

void erase_buffer(){ // vacia el buffer
	tail=head;
  full=FALSE;
}

char get_char(){
  int aux = EOF;
  if(!buffer_empty()){
    aux=buffer[tail];
    full=FALSE;
    tail=(tail+1) % BUFFER_SIZE;
  }
  return aux;
}
int is_alpha(unsigned char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
int is_digit(unsigned char c) {
    return (c >= '0' && c <= '9');
}
int is_cntrl(unsigned char c){
  return ((c == '\n' || c == '\t'));
}
int is_space(unsigned char c){
  return (c=='\t' || c == ' ');
}

int buffer_empty(){
  return head==tail;
}
