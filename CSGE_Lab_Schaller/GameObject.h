#pragma once

#include "texture2d.h"

class GameObject 
{
public:

	GameObject(Texture2d texture);

	void Generate();

	void Draw();

private:
};