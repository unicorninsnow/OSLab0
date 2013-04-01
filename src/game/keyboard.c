#include "common.h"
#include "string.h"

///* a-z对应的键盘扫描码 */
/*static int letter_code[] = {
	30, 48, 46, 32, 18, 33, 34, 35, 23, 36,
	37, 38, 50, 49, 24, 25, 16, 19, 31, 20,
	22, 47, 17, 45, 21, 44
};*/


/* 上下左右 W S A D 对应的键盘扫描码 */
static int direct_key_code[] = {
    72,80,75,77,        //up down left right 按下
    200,208,203,205,    //up down left right 松开
    17,31,30,32,        //w s a d 按下
    145,159,158,160     //w s a d 松开
};


/* 对应键按下的标志位 */
static bool direct_key_pressed[4];

void
press_key(int scan_code) {
	int i;
	for (i = 0; i < 4; i ++) {                      //处理up down left right 按下
		if (direct_key_code[i] == scan_code) {
			direct_key_pressed[i] = TRUE;
		}
	}
    for (i = 4; i < 8; i++){                        //处理up down left right 松开
        if (direct_key_code[i] == scan_code) {
			direct_key_pressed[i - 4] = FALSE;
		}
    }
    for (i = 8; i < 12; i++){                       //处理w s a d 按下
        if (direct_key_code[i] == scan_code) {
			direct_key_pressed[i - 8] = TRUE;
		}
    }
    for (i = 12; i < 16; i++){                      //处理w s a d 松开
        if (direct_key_code[i] == scan_code) {
			direct_key_pressed[i - 12] = FALSE;
		}
    }


}


void
release_key(int index) {
	assert(0 <= index && index < 4);
	direct_key_pressed[index] = FALSE;
}

bool
query_key(int index) {
	assert(0 <= index && index < 4);
	return direct_key_pressed[index];
}


/* key_code保存了上一次键盘事件中的扫描码 */
static volatile int key_code = 0;

int last_key_code(void) {
	return key_code;
}

/*对某个键盘扫描码的键盘活动：先保存该扫描码，然后记录按键是什么*/
void
keyboard_event(int code) {  
	key_code = code;
	press_key(code);
}

