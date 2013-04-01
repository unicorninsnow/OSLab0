#include "game.h"
#include "common.h"
#include "string.h"
#include "adt/linklist.h"
#include "device/video.h"
#include "x86/x86.h"
#include "device/font.h"

LINKLIST_IMPL(bullet, 10000)

static bullet_t head = NULL;
static struct Plane_struct plane;
static int bullet_num = 0;

static int  miss = 0;
static int  life = 3;

int
get_life(void) {
	return life;
}

int
get_miss(void) {
	return miss;
}

int
get_bullet_num(void) {
    return bullet_num;
}

bullet_t
characters(void) {
    return head;
}

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
    plane.x = HEIGHT_PLANE / 2;
    plane.y = WIDTH_PLANE / 2;
    plane.v = 0.5;
}


/*在屏幕上创建一个新的子弹*/
void
create_new_bullet(int x_p, int y_p) {
	if (head == NULL) {
		head = bullet_new(); // 当前没有任何子弹，创建新链表 //
	    bullet_num = 1;      // 当前子弹数初始化为1
    } else {
		bullet_t now = bullet_new();
		bullet_insert(NULL, head, now); // 插入到链表的头部 //
		head = now;
        bullet_num++;        // 当前子弹数自增
	}

    head->x_p = x_p;
    head->y_p = y_p;
    

	/* 以子弹左上角可以出现的屏幕边界范围为准生成随机数，代表初始化的子弹位置 */
	float init_pos = rand() % (2 * (WIDTH_BULLET + HEIGHT_BULLET));    
    /* 生成子弹的速度 */
	float v = (rand() % 1000 / 1000.0 + 1) / 3.5;
    if(0 <= init_pos && init_pos < WIDTH_BULLET){   //处理上边缘的情况
        head->x = 0; 
        head->y = init_pos;
        head->vx = v;
        head->vy = v * (head->y_p - head->y) / (head->x_p - head->x);
    }else if(WIDTH_BULLET <= init_pos && init_pos < (WIDTH_BULLET + HEIGHT_BULLET)){    //处理右边缘的情况
        head->x = init_pos - WIDTH_BULLET + 1; 
        head->y = WIDTH_BULLET;
        head->vx = -v * (head->x_p - head->x) / (head->y_p - head->y);
        head->vy = -v;
   }else if((WIDTH_BULLET + HEIGHT_BULLET) <= init_pos && init_pos < (2 * WIDTH_BULLET + HEIGHT_BULLET)){   //处理下边缘的情况
        head->x = HEIGHT_BULLET;
        head->y = 2 * WIDTH_BULLET + HEIGHT_BULLET - init_pos;
        head->vx = -v;
        head->vy = -v * (head->y_p - head->y) / (head->x_p - head->x);
    }else{  //处理左边缘的情况
        head->x = 2 * (WIDTH_BULLET + HEIGHT_BULLET) - init_pos;
        head->y = 0;
        head->vx = v * (head->x_p - head->x) / (head->y_p - head->y);
        head->vy = v;
    }
    assert(0 <= head->x && head->x   <= HEIGHT_BULLET); 
    assert(0 <= head->y && head->y   <= WIDTH_BULLET);
    
	head->v = (rand() % 1000 / 1000.0 + 1) / 2.0;
}

/* 逻辑时钟前进1单位 */
void
update_bullet_pos(void) {
	bullet_t it;
	for (it = head; it != NULL; ) {
		bullet_t next = it->_next;
        it->x += it->vx;
        it->y += it->vy;
		if (it->x < 0 || it->x > HEIGHT_BULLET || it->y < 0 || it->y > WIDTH_BULLET) {
			bullet_remove(it);
			bullet_free(it);
            if(bullet_num > 0) --bullet_num;
			if (it == head) head = next; // 更新链表 //
		}
		it = next;
	}
}


//void
int 
Is_hit(void) {
	bullet_t it;
	// 逐个子弹进行查看，比较判断其有没有击中飞机 //
	for (it = head; it != NULL; it = it->_next) {
        /* 此处以子弹和飞机所在的8*8像素区 有像素点重合为击中条件 */
		if (((it->x + bullet_size) > get_plane_x()) && (it->x < get_plane_x() + plane_size)
                && ((it->y + bullet_size) > get_plane_y()) && (it->y < get_plane_y() + plane_size)) {
			--life;
		    bullet_t next = it->_next;
            bullet_remove(it);
			bullet_free(it);
            if(bullet_num > 0) --bullet_num;
			if (it == head) head = next; // 更新链表 //
            // assert(life >= 0);
            if (life <= 0) return 0;
		}
	}
	return life;
}

void
update_plane_pos(void) {
	disable_interrupt();
	// 根据键盘的上下左右键控制飞机移动 //
    bool is_in_area_up      = (0 <= plane.x);
    bool is_in_area_down    = (plane.x < HEIGHT_PLANE - 1);
    bool is_in_area_left    = (0 <= plane.y);
    bool is_in_area_right   = (plane.y < WIDTH_PLANE - 1);
    
        if((is_in_area_up) && query_key(0))     plane.x -= plane.v; //up
        if((is_in_area_down) && query_key(1))   plane.x += plane.v; //down
        if((is_in_area_left) && query_key(2))   plane.y -= plane.v; //left
        if((is_in_area_right) && query_key(3))  plane.y += plane.v; //right

	enable_interrupt();

	return;
}
