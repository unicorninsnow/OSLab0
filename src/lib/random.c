#include "game.h"
static int seed = 0;

void
srand(int s) {
	seed = s;
}

/* 生成下一个随机数 */
int
rand(void) {
    /* 此处通过在生成随机数的方法中加上了一个随机元素：
     * 最后一次键盘扫描码 
     * 可以在一定程度上提高游戏中子弹出现位置和速度等需要随机数地方的随机性
     * 只少不会每次出现的子弹必然都一样了*/
	seed = 0x015A4E35 * seed + 1 + last_key_code();
	return (seed >> 16) & 0x7FFF;
}

