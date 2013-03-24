#ifndef __GAME_H__
#define __GAME_H__

#include "common.h"
#include "adt/linklist.h"

//static int bullet_num;

/* 中断时调用的函数 */
void timer_event(void);
void keyboard_event(int scan_code);

/* 按键相关 */
void press_key(int scan_code);
void release_key(int ch);
bool query_key(int ch);
int last_key_code(void);

/* 定义fly_t链表 */
/*LINKLIST_DEF(fly)
	float x, y;
	int text;
	float v;
LINKLIST_DEF_FI(fly)
*/
/* 定义bullet子弹链表 */    //为什么要_t
LINKLIST_DEF(bullet)
	float x, y; //用于生成每个子弹的初始位置 和 表示所在的当前位置
	int text;
    float x_p, y_p; //用于表示生成新子弹时飞机所在的位置，用于确定子弹的方向
	float v;
    float vx, vy;
LINKLIST_DEF_FI(bullet)

/* 定义plane结构 */
struct Plane_struct{
    float x, y;
    float v;
};
/*LINKLIST_DEF(Plane)
    float x, y; //用于生成每个子弹的初始位置 和 表示所在的当前位置
    float v;
LINKLIST_DEF_FI(Plane)
*/




/* 主循环 */
void main_loop(void);

/* 游戏逻辑相关 */
void create_plane();
//void create_new_letter(void);
void create_new_bullet(int x_p, int y_p);

//void update_letter_pos(void);
void update_bullet_pos(void);
bool update_keypress(void);
void update_plane_pos(void);

int get_hit(void);
int get_miss(void);
int get_bullet_num(void);
int get_fps(void);
void set_fps(int fps);
//fly_t characters(void);
bullet_t characters(void);
struct Plane_struct get_plane(void);
int get_plane_x(void);
int get_plane_y(void);


void redraw_screen(void);

/* 随机数 */
int rand(void);
void srand(int seed);

#endif
