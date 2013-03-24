#include "game.h"
#include "common.h"
#include "string.h"
#include "adt/linklist.h"
#include "device/video.h"
#include "x86/x86.h"
#include "device/font.h"

//LINKLIST_IMPL(fly, 10000)
LINKLIST_IMPL(bullet, 10000)

//static fly_t head = NULL;
static bullet_t head = NULL;
static struct Plane_struct plane;
static int bullet_num = 0;
//bullet_num = 0;

static int hit = 0, miss = 0;

int
get_hit(void) {
	return hit;
}

int
get_miss(void) {
	return miss;
}

int
get_bullet_num(void) {
    return bullet_num;
}

/*fly_t
characters(void) {
	return head;
}*/

bullet_t
characters(void) {
    return head;
}

//Plane_struct *
struct Plane_struct
get_plane(void){
    return plane;
}

int get_plane_x(void){
    return plane.x;
}

int get_plane_y(void){
    return plane.y;
}

/* 创建飞机 */
void
create_plane(void){
    //Plane plane;
    //plane = new Plane_struct;
    plane.x = 100;
    plane.y = 100;
    plane.v = 0.5;
}


/* 在屏幕上创建一个新的字母 */
/*void
create_new_letter(void) {
	if (head == NULL) {
		head = fly_new(); // 当前没有任何字母，创建新链表 //
	} else {
		fly_t now = fly_new();
		fly_insert(NULL, head, now); // 插入到链表的头部 //
		head = now;
	}
	// 字母、初始位置、掉落速度均为随机设定 // 
	head->x = 0;
	head->y = rand() % (SCR_WIDTH / 8 - 2) * 8 + 8;
	head->v = (rand() % 1000 / 1000.0 + 1) / 2.0;
	head->text = rand() % 26;
	release_key(head->text); // 清除过往的按键 //
}*/

/*在屏幕上创建一个新的子弹*/
void
create_new_bullet(int x_p, int y_p) {
/*	if (head == NULL) {
		head = fly_new(); // 当前没有任何字母，创建新链表 //
	} else {
		fly_t now = fly_new();
		fly_insert(NULL, head, now); // 插入到链表的头部 //
		head = now;
        
	}
*/
	if (head == NULL) {
		head = bullet_new(); // 当前没有任何子弹，创建新链表 //
	    bullet_num = 1;
    } else {
		bullet_t now = bullet_new();
		bullet_insert(NULL, head, now); // 插入到链表的头部 //
		head = now;
        bullet_num++;
	}

	/* 字母、初始位置、掉落速度均为随机设定 */
/*	head->x = 0;
	head->y = rand() % (WIDTH_BULLET / 8 - 2) * 8 + 8;
	head->v = (rand() % 1000 / 1000.0 + 1) / 2.0;
	head->text = rand() % 26;
	release_key(head->text); // 清除过往的按键 // //为什么要清除？？？？？？
  */  

    head->x_p = x_p;
    head->y_p = y_p;
    
	float init_pos = rand() % (2 * (WIDTH_BULLET + HEIGHT_BULLET));
	float v = (rand() % 1000 / 1000.0 + 1) / 3.5;
    if(0 <= init_pos && init_pos < WIDTH_BULLET){
        head->x = 0; 
        head->y = init_pos;
        head->vx = v;
        head->vy = v * (head->y_p - head->y) / (head->x_p - head->x);
    }else if(WIDTH_BULLET <= init_pos && init_pos < (WIDTH_BULLET + HEIGHT_BULLET)){
        head->x = init_pos - WIDTH_BULLET + 1; 
        head->y = WIDTH_BULLET;
        head->vx = -v * (head->x_p - head->x) / (head->y_p - head->y);
        head->vy = -v;
   }else if((WIDTH_BULLET + HEIGHT_BULLET) <= init_pos && init_pos < (2 * WIDTH_BULLET + HEIGHT_BULLET)){
        head->x = HEIGHT_BULLET;
        head->y = 2 * WIDTH_BULLET + HEIGHT_BULLET - init_pos;
        head->vx = -v;
        head->vy = -v * (head->y_p - head->y) / (head->x_p - head->x);
    }else{
        head->x = 2 * (WIDTH_BULLET + HEIGHT_BULLET) - init_pos;
        head->y = 0;
        head->vx = v * (head->x_p - head->x) / (head->y_p - head->y);
        head->vy = v;
    }
    assert(0 <= head->x && head->x   <= HEIGHT_BULLET); //- bullet_size);
    assert(0 <= head->y && head->y   <= WIDTH_BULLET);// - bullet_size);
    
	//head->x = 0;
	//head->y = rand() % (WIDTH_BULLET / 8 - 2) * 8 + 8;
	head->v = (rand() % 1000 / 1000.0 + 1) / 2.0;
    head->text = 0;//rand() % 26;
	//release_key(head->text); // 清除过往的按键 // //为什么要清除？？？？？？

    
}

/* 逻辑时钟前进1单位 */
/*void
update_letter_pos(void) {
	fly_t it;
	for (it = head; it != NULL; ) {
		fly_t next = it->_next;
		it->x += it->v; // 根据速度更新位置 //
		if (it->x < 0 || it->x + 7.9 > SCR_HEIGHT) {
			if (it->x < 0) hit ++; // 从上部飞出屏幕 //
			else miss ++; // 从下部飞出屏幕 //
			fly_remove(it);
			fly_free(it);
			if (it == head) head = next; // 更新链表 //
		}
		it = next;
	}
}
*/
void
update_bullet_pos(void) {
	bullet_t it;
	for (it = head; it != NULL; ) {
		bullet_t next = it->_next;
		//it->x += it->v; // 根据速度更新位置 //
//        bool is_bullet_in_area = (0 <= (it->x + it->vx)) && ((it->x + it->vy) <= WIDT)
        it->x += it->vx;
        it->y += it->vy;
		if (it->x < 0 || it->x > HEIGHT_BULLET || it->y < 0 || it->y > WIDTH_BULLET) {
        
	//		if (it->x < 0) hit ++; // 从上部飞出屏幕 //
	//		else miss ++; // 从下部飞出屏幕 //
			bullet_remove(it);
			bullet_free(it);
            if(bullet_num > 0) --bullet_num;
			if (it == head) head = next; // 更新链表 //
		}
		it = next;
	}
}

/* 更新按键 */
/*bool
update_keypress(void) {
	fly_t it, target = NULL;
	float min = -100;

	disable_interrupt();
	// 寻找相应键已被按下、最底部且未被击中的字符 //
	for (it = head; it != NULL; it = it->_next) {
		assert(it->text >= 0 && it->text < 26);
		if (it->v > 0 && it->x > min && query_key(it->text)) {
			min = it->x;
			target = it;
		}
	}
	// 如果找到则更新相应数据 //
	if (target != NULL) {
		release_key(target->text);
		target->v = -3; // 速度改为向上 //
		return TRUE;
	}
	enable_interrupt();

	return FALSE;
}*/
/*
bool
update_keypress(void) {
	bullet_t it, target = NULL;
	float min = -100;

	disable_interrupt();
	// 寻找相应键已被按下、最底部且未被击中的字符 //
	for (it = head; it != NULL; it = it->_next) {
		assert(it->text >= 0 && it->text < 26);
		if (it->v > 0 && it->x > min && query_key(it->text)) {
			min = it->x;
			target = it;
		}
	}
	// 如果找到则更新相应数据 //
	if (target != NULL) {
		release_key(target->text);
		target->v = -3; // 速度改为向上 //
        target->vx = -3;
        target->vy = 0;
		return TRUE;
	}
	enable_interrupt();

	return FALSE;
}
*/
void
update_plane_pos(void) {
	disable_interrupt();
	// 根据键盘的上下左右键控制飞机移动 //
    bool is_in_area_up      = (0 <= plane.x);
    bool is_in_area_down    = (plane.x < HEIGHT_PLANE - 1);
    bool is_in_area_left    = (0 <= plane.y);
    bool is_in_area_right   = (plane.y < WIDTH_PLANE - 1);
    
        if((is_in_area_up) && query_key(0))    plane.x -= plane.v; //up
        if((is_in_area_down) && query_key(1))    plane.x += plane.v; //down
        if((is_in_area_left) && query_key(2))    plane.y -= plane.v; //left
        if((is_in_area_right) && query_key(3))    plane.y += plane.v; //right

/*
	// 如果找到则更新相应数据 //
	if (target != NULL) {
		release_key(target->text);
		target->v = -3; // 速度改为向上 //
        target->vx = -3;
        target->vy = 0;
		return TRUE;
	}*/
	enable_interrupt();

	return;
}
