#include "libmath/Intersection2D.h"

#include <iostream>

namespace mth
{


	AABBCollider2D::AABBCollider2D(const Vector2& _pos, const Vector2& _size)
		: m_position(_pos), m_extents(_size)
	{

	}


	Vector2& AABBCollider2D::Position(void)
	{
		return m_position;
	}

	Vector2& AABBCollider2D::Extents(void)
	{
		return m_extents;
	}

	Vector2 AABBCollider2D::GetPosition(void) const
	{
		return m_position;
	}

	Vector2 AABBCollider2D::GetExtents(void) const
	{
		return m_extents;
	}

}