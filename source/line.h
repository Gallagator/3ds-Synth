#ifndef LINE_H
#define LINE_H

#include "main.h"

u16 abs(s16 num)
{
	if(num < 0)
		return -num;
	return num;
}

void drawPoint(u8* fb, u16 x, u16 y)
{
	
	fb[ 3 * (240 * (x + 1) - y) + 0] = 255;
	fb[ 3 * (240 * (x + 1) - y) + 1] = 255;
	fb[ 3 * (240 * (x + 1) - y) + 2] = 255;
}


void drawLine(u8* fb, s16 x0, s16 y0, s16 x1, s16 y1)
{
  s16 dx =  abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  s16 dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1; 
  s16 err = dx + dy, e2; /* error value e_xy */
 
  for (;;){  /* loop */
    drawPoint(fb, x0, y0);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}

#endif
