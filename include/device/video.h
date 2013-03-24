#ifndef __VIDEO_H__
#define __VIDEO_H__

#include "types.h"
#include "const.h"
#include "assert.h"

#define SCR_WIDTH  320
#define SCR_HEIGHT 200
#define WIDTH_BULLET ((SCR_WIDTH) - (bullet_size))
#define HEIGHT_BULLET ((SCR_HEIGHT) - (bullet_size))
#define WIDTH_PLANE ((SCR_WIDTH) - (plane_size))
#define HEIGHT_PLANE ((SCR_HEIGHT) - (plane_size))
#define SCR_SIZE ((SCR_WIDTH) * (SCR_HEIGHT))
#define VMEM_ADDR  ((uint8_t*)0xA0000)
#define bullet_size 2
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

void draw_bullets(const char*, int, int, int);
void draw_one_bullet(int, int, int);
void draw_plane(int, int ,int);

#endif
