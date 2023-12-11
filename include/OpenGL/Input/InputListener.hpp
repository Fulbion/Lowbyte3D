#pragma once

class InputListener
{
public:
	InputListener()
	{

	}

	~InputListener()
	{

	}

	virtual void onKeyPressed(int i_key) = 0;
	virtual void onKeyReleased(int i_key) = 0;

private:

};