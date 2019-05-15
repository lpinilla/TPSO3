#include <utilities.h>
#include <syscall.h>

uint64_t main() {
	/*
	//All the following code may be removed
	*v = 'X';
	*(v+1) = 0x74;

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;
	*/
	return (uint64_t) (shell());
}
