#pragma once

#include "libmath/Vector2.h"
#include "libmath/Arithmetic.h"

namespace mth
{
	class OBBCollider2D;
	class CircleCollider2D;
	class PolygonCollider2D;

	class AABBCollider2D
	{

	public:
						AABBCollider2D(void) = default;

						AABBCollider2D(const Vector2& _pos, const Vector2& _size);
						AABBCollider2D(const AABBCollider2D& _other) = default;

						~AABBCollider2D(void) = default;

			bool		CheckCollision(const AABBCollider2D& _other)	const;

			bool		CheckCollision(const OBBCollider2D& _other)		const;

			bool		CheckCollision (const CircleCollider2D& _other)	const;

			bool		CheckCollision(const PolygonCollider2D& _other)	const;

			Vector2&	Position(void);
			Vector2&	Extents(void);

			Vector2		GetPosition(void)								const;
			Vector2		GetExtents(void)								const;

			Vector2		GetMin(void)									const;
			Vector2		GetMax(void)									const;


	private:

		Vector2		m_position;
		Vector2		m_extents;

	};
}
