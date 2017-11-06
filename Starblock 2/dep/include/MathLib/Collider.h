#pragma once


#include "shapes.h"
#include "Transform.h"
#include "Collision.h"




class Collider
{
public:
	Collider();
	~Collider();

	AABB box;

	AABB getGlobalBox (const Transform& T) const;
};


Collision collides(	const Transform& at, const Collider&ac,
					const Transform& bt, const Collider& bc);
