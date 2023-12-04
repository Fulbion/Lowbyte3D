#pragma once

template<typename T>
struct Rect
{
	T left, top, width, height;

	Rect() {}
	Rect(T i_left, T i_top, T i_width, T i_height) :
		left(i_left), top(i_top), width(i_width), height(i_height)
	{
	}
};
