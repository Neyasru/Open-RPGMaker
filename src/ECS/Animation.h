#ifndef _ANIMATION_H_
#define _ANIMATION_H_

struct Animation
{

	int index;
	int frames;
	int speed;
	int rowS;
	int columnS;

	Animation() {}
	Animation(int i, int r, int c, int f, int s)
	{
		index = i;
		rowS = r;
		columnS = c;
		frames = f;
		speed = s;
	}

};

#endif