#pragma once

#include"GameObject.h"
#include"../Scene/Scene.h"

class Object : public GameObject
{
protected:
	class Scene* myscene;

	template<class OBJECT>
	OBJECT* CreateObjectP(const Vector2D& location, bool flip)
	{

	}

public:
	void SetMyScene(class Scene* scene)
	{
		myscene = scene;
	}

	
};