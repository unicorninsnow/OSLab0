#ifndef __VIDEO_H__
#define __VIDEO_H__

#include "types.h"
#include "const.h"
#include "assert.h"

#define SCR_WIDTH  320
#define SCR_HEIGHT 200
#define WIDTH_BULLET ((SCR_WIDTH) - (bullet_size))      /* 表示子弹所在的横坐标的最大值 0<= y <= WIDTH_BULLET */ 
#define HEIGHT_BULLET ((SCR_HEIGHT) - (bullet_size))    /* 表示子弹所在的纵坐标的最大值 0<= x <= HEIGHT_BULLET */ 
#define WIDTH_PLANE ((SCR_WIDTH) - (plane_size))        /* 表示飞机所在的横坐标的最大值 0<= y <= WIDTH_PLANE */
#define HEIGHT_PLANE ((SCR_HEIGHT) - (plane_size))      /* 表示飞机所在的纵坐标的最大值 0<= x <= HEIGHT_PLANE */
#define SCR_SIZE ((SCR_WIDTH) * (SCR_HEIGHT))
#define VMEM_ADDR  ((uint8_t*)0xA0000)
#define bullet_size 2                                   /* 表示子弹的尺寸 */
//#define plane_size 8 

extern uint8_t *vmem;

static inline void
draw_pixel(int x, int y, int color) {
	assert(x >= 0 && y >= 0 && x < SCR_HEIGHT && y < SCR_WIDTH);
	vmem[(x << 8) + (x << 6) + y] = color;
}

void prepare_buffer(void);
void display_buffer(void);

void draw_string(const char*, int, int, int);

void draw_one_bullet(int, int, int);
void draw_plane(int, int ,int);

#endif
