#include "game.h"
static int seed = 0;
//seed = last_key_code();

void
srand(int s) {
	seed = s;
}

/* 生成下一个随机数 */
int
rand(void) {
	seed = 0x015A4E35 * seed + 1 + last_key_code();
	return (seed >> 16) & 0x7FFF;
}

