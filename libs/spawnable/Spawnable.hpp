#pragma once

class Spawnable
{
public:
	virtual int draw() {}
	virtual void setTextureAlphaMod() {}
	virtual void implementMovement() {}
};
