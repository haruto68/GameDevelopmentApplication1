#pragma once

#include"../EnemyBase.h"

class Pinky : public EnemyBase
{
public:
	Pinky();
	virtual ~Pinky();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

private:
	void AnimationControl();
	void DecisionDirection();
};