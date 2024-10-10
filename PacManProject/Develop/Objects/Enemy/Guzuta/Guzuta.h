#pragma once

#include"../EnemyBase.h"

class Guzuta : public EnemyBase
{
public:
	Guzuta();
	virtual ~Guzuta();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

private:
	void AnimationControl();
	void DecisionDirection();
};