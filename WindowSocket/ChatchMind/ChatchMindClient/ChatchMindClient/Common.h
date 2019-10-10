#pragma once

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960

#define BUFSIZE 512
#define SHORT_BUFSIZE 20
#define LONG_BUFSIZE 200

#define FPS 60

struct DRAWLINE
{
	int color;
	int x0, y0;
	int x1, y1;
};

enum INPUT_KEY
{
	INPUT_KEY_ENTER,
};