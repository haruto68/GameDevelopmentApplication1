#pragma once

#include"GameObject.h"
#include"../Scene/Scene.h"

class Object : public GameObject
{
protected:
	template<class OBJECT>
	OBJECT* CreateObject(const Vector2D& location, bool flip)
	{
		this->MyScene->CreateObject<OBJECT>(location, flip);
	}

	//ƒeƒL’e—p
	void GenerateObject(Vector2D generate)
	{
		this->MyScene->InsertFactory(generate);
	}
	
	//”jŠü
	void DiscardObject(GameObject* discard)
	{
		this->MyScene->InsertTrash(discard);
	}

	//Šl“¾ƒXƒRƒA
	void Score(int value)
	{
		this->MyScene->GetScore(value / 2);
	}
};