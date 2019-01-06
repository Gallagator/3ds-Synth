#ifndef MAIN_H
#define MAIN_H

#include <math.h>
#include <string.h>
#include <string>
#include <3ds.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>


#define SAMPLERATE 22050
#define SAMPLESPERBUF (SAMPLERATE / 30)
#define BYTESPERSAMPLE 4

#define TOPSCREEN_HEIGHT 240
#define TOPSCREEN_WIDTH 400
#define SCREENPROPORTION 0.5f

#define BOTTOMSCREEN_HEIGHT 240
#define BOTTOMSCREEN_WIDTH 320

#define SINE		0
#define TRIANGLE	1
#define SAWTOOTH	2
#define	SQUARE		3
#define NOISE		4

#define NFREQUENCIES 3

#define SCREEN_BPP 24



#endif
