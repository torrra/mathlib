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

	class CircleCollider2D
	{
	public:

					CircleCollider2D(void) = default;
					CircleCollider2D(const Vector2& _pos, float _radius);

					CircleCollider2D
					(const CircleCollider2D& _other) = default;

		bool		CheckCollision(const AABBCollider2D& _other)	const;

		bool		CheckCollision(const OBBCollider2D& _other)		const;

		bool		CheckCollision(const CircleCollider2D& _other)	const;


		Vector2&	Position(void);
		float&		Radius(void);

		Vector2		GetPosition(void)								const;
		float		GetRadius(void)									const;

	private:

		Vector2 m_position;
		float	m_radius = 0.f;
	};

	class Ray2D
	{
	public:

		Ray2D(void) = delete;
		Ray2D(const Vector2& _pos, const Vector2& _dir);
		Ray2D(const Ray2D& _other) = default;

		~Ray2D(void) = default;

		bool Intersect
		(const AABBCollider2D& _box, float& _distance)				const;


		Vector2&	Origin(void);
		Vector2&	Direction(void);

		Vector2		GetOrigin(void)									 const;
		Vector2		GetDirection(void)								 const;
		Vector2		GetInverseDir(void)								 const;


	private:
		// Origin of ray
		Vector2    m_origin;

		// Direction unit vector
		Vector2    m_direction;

		// 1 / direction
		Vector2    m_inverseDir;
	};

	class PolygonCollider2D
	{
	public:

		PolygonCollider2D(void) = default;
		PolygonCollider2D(Vector2 _vertices[], int _count);
		PolygonCollider2D(const PolygonCollider2D& _other);
		~PolygonCollider2D(void);


		bool			CheckCollision
		(const PolygonCollider2D& _other)							const;
		bool			CheckCollision
		(const AABBCollider2D& _other)								const;

		bool			CheckCollision
		(const OBBCollider2D& _other)								const;


		Vector2&		operator[](int _index);
		Vector2			operator[](int _index)						const;

	private:

		bool SeparatingAxisTheorem
		(const PolygonCollider2D& _other)							const;


		void MinMaxProjection
		(const Vector2& _normal, float& _min, float& _max)					const;


		bool InternalSAT(const PolygonCollider2D& _poly2)					const;

		Vector2*		m_vertices = nullptr;
		unsigned int	m_vertexCount = 0;


		friend class AABBCollider2D;
		friend class OBBCollider2D;

	};

	class OBBCollider2D
	{
	public:

					OBBCollider2D(void) = default;

					OBBCollider2D
					(const Vector2& _pos, const Vector2& _extents, Radian _angle);

					OBBCollider2D(const OBBCollider2D& _other) = default;
					~OBBCollider2D(void) = default;


		bool		CheckCollision(const AABBCollider2D& _other)	const;

		bool		CheckCollision(const OBBCollider2D& _other)		const;

		bool		CheckCollision(const CircleCollider2D& _other)	const;

		bool		CheckCollision(const PolygonCollider2D& _other)	const;

		Vector2&	Position(void);
		Vector2&	Extents(void);

		Radian&		Rotation(void);

		Vector2		GetPosition(void)								const;
		Vector2		GetExtents(void)								const;

		Radian		GetRotation(void)								const;

		Vector2		GetMin(void)									const;
		Vector2		GetMax(void)									const;


	private:

		Vector2		m_position;
		Vector2		m_extents;
		Radian		m_rotation;
	};

}
