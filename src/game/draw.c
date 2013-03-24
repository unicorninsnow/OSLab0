#include "game.h"
#include "string.h"
#include "device/video.h"

/* 绘制屏幕上的内容。
 * 注意程序在绘图之前调用了prepare_buffer，结束前调用了display_buffer。
 * prepare_buffer会准备一个空白的绘图缓冲区，display_buffer则会将缓冲区绘制到屏幕上，
 * draw_pixel或draw_string绘制的内容将保存在缓冲区内(暂时不会显示在屏幕上)，调用
 * display_buffer后才会显示。
*/
void
redraw_screen() {
	//fly_t it;
    bullet_t it;
	const char *hit;
//  const char *bullet_num;
    const char *sec_int;
    const char *sec_fra;
	
	prepare_buffer(); /* 准备缓冲区 */


    /* 绘制飞机 */
    struct Plane_struct plane_now = get_plane();
    draw_plane(plane_now.x,plane_now.y,14);


	/* 绘制每个字符 */
	/*for (it = characters(); it != NULL; it = it->_next) {
		static char buf[2];
		buf[0] = it->text + 'A'; buf[1] = 0;
		draw_string(buf, it->x, it->y, 12);
	}*/
    
	/* 绘制每个子弹 */
	for (it = characters(); it != NULL; it = it->_next) {
        draw_one_bullet( it->x, it->y, 12);
	}
       

	/* 绘制被击中数、坚持的时间、最后一次按键扫描码和fps */
	draw_string(itoa(last_key_code()), SCR_HEIGHT - 8, 0, 48);
	hit = itoa(get_hit());
	draw_string(hit, 0, SCR_WIDTH - strlen(hit) * 8, 10);

    //bullet_num = itoa(get_bullet_num()); 
    //draw_string(bullet_num, SCR_HEIGHT - 8, SCR_WIDTH - strlen(bullet_num) * 8, 10);

    sec_fra = itoa(get_tick() % 1000);
    draw_string(sec_fra, SCR_HEIGHT - 8, SCR_WIDTH - strlen(sec_fra) * 8, 10);
    sec_int = itoa(get_tick()/1000); 
    draw_string(".", SCR_HEIGHT - 8, SCR_WIDTH - strlen(sec_fra) * 8 - 8, 10);
    draw_string(sec_int, SCR_HEIGHT - 8, SCR_WIDTH - strlen(sec_fra) * 8 - strlen(sec_int) * 8 - 8, 10);
	
    draw_string(itoa(get_fps()), 0, 0, 14);
	draw_string("FPS", 0, strlen(itoa(get_fps())) * 8, 14);

	display_buffer(); /* 绘制缓冲区 */
}

