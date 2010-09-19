#include <ctype.h>

int isprint (int ch) {
	ch &= 0x7f;
	return (ch>=32 && ch<127);
}
