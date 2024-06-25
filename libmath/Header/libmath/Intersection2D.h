#pragma once

#include "libmath/Vector2.h"
#include "libmath/Arithmetic.h"

namespace ion::math
{
	class OBBCollider2D;
	class CircleCollider2D;
	class PolygonCollider2D;


	// 2D Axis aligned bounding box
	class AABBCollider2D
	{

	public:

			// Constructors / destructor

						AABBCollider2D(void) = default;

						AABBCollider2D(const Vector2& _pos, const Vector2& _size);
						AABBCollider2D(const AABBCollider2D& _other) = default;

						~AABBCollider2D(void) = default;

			// Collision checks

			bool		CheckCollision(const AABBCollider2D& _other)	const;
			bool		CheckCollision(const OBBCollider2D& _other)		const;
			bool		CheckCollision (const CircleCollider2D& _other)	const;
			bool		CheckCollision(const PolygonCollider2D& _other)	const;

			bool		PointInBox(const Vector2& _point)				const;

			// Accessors

			Vector2&	Position(void);
			Vector2&	Extents(void);

			Vector2		GetPosition(void)								const;
			Vector2		GetExtents(void)								const;

			// Calculate min and max vertices

			Vector2		GetMin(void)									const;
			Vector2		GetMax(void)									const;


	private:

		Vector2		m_position;
		Vector2		m_extents;

	};

	// 2D bounding circle
	class CircleCollider2D
	{
	public:

		// Constructors / destructors

					CircleCollider2D(void) = default;
					CircleCollider2D(const Vector2& _pos, float _radius);

					CircleCollider2D
					(const CircleCollider2D& _other) = default;

		// Collision checks

		bool		CheckCollision(const AABBCollider2D& _other)	const;
		bool		CheckCollision(const OBBCollider2D& _other)		const;
		bool		CheckCollision(const CircleCollider2D& _other)	const;

		bool		PointInCircle(const Vector2& _point)			const;


		Vector2&	Position(void);
		float&		Radius(void);

		Vector2		GetPosition(void)								const;
		float		GetRadius(void)									const;
		float		GetRadiusSquared(void)							const;

	private:

		Vector2		m_position;
		float		m_radius = 0.f;
	};

	class Ray2D
	{
	public:

		// Constructors / destructor

					Ray2D(void) = delete;
					Ray2D(const Vector2& _pos, const Vector2& _dir);
					Ray2D(const Ray2D& _other) = default;

					~Ray2D(void) = default;

		// AABB intersection check

		bool		Intersect
		(const AABBCollider2D& _box, float& _distance)				 const;

		// Accessors

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

		// Constructors / destructor

						PolygonCollider2D(void) = default;
						PolygonCollider2D(Vector2 _vertices[], int _count);
						PolygonCollider2D(const PolygonCollider2D& _other);
						~PolygonCollider2D(void);

		// Collisions checks

		bool			CheckCollision
		(const PolygonCollider2D& _other)									const;
		bool			CheckCollision
		(const AABBCollider2D& _other)										const;

		bool			CheckCollision
		(const OBBCollider2D& _other)										const;


		Vector2&		operator[](int _index);
		Vector2			operator[](int _index)								const;

	private:

		// Internal SAT functions

		bool			SeparatingAxisTheorem
		(const PolygonCollider2D& _other)									const;


		void			MinMaxProjection
		(const Vector2& _normal, float& _min, float& _max)					const;


		bool			InternalSAT(const PolygonCollider2D& _poly2)		const;

		Vector2*		m_vertices = nullptr;
		unsigned int	m_vertexCount = 0;


		friend class	AABBCollider2D;
		friend class	OBBCollider2D;

	};

	// Oriented bounding box
	class OBBCollider2D
	{
	public:

		// Constructor / Destructor

					OBBCollider2D(void) = default;

					OBBCollider2D
					(const Vector2& _pos, const Vector2& _extents, Radian _angle);

					OBBCollider2D(const OBBCollider2D& _other) = default;
					~OBBCollider2D(void) = default;

		// Collision checks

		bool		CheckCollision(const AABBCollider2D& _other)		const;
		bool		CheckCollision(const OBBCollider2D& _other)			const;
		bool		CheckCollision(const CircleCollider2D& _other)		const;
		bool		CheckCollision(const PolygonCollider2D& _other)		const;


		// Accessors

		Vector2&	Position(void);
		Vector2&	Extents(void);

		Radian&		Rotation(void);

		Vector2		GetPosition(void)									const;
		Vector2		GetExtents(void)									const;

		Radian		GetRotation(void)									const;

		Vector2		GetMin(void)										const;
		Vector2		GetMax(void)										const;


	private:

		Vector2		m_position;
		Vector2		m_extents;
		Radian		m_rotation;
	};


	// 2D line segment
	class Line2D
	{
	public:

		// Constructor / destructor

					Line2D(void) = default;
					Line2D(const Vector2& _start, const Vector2& _end);
					Line2D(const Line2D& _other) = default;

					~Line2D(void) = default;


		// Accessors

		Vector2&	Start(void);
		Vector2&	End(void);

		Vector2		GetStart(void)												const;
		Vector2		GetEnd(void)												const;

		// Intersection checks

		bool		Intersect(const AABBCollider2D& _box)						const;
		bool		Intersect(const CircleCollider2D& _circle)					const;

		// Calculate segment length

		float		Length(void)												const;
		float		LengthSquared(void)											const;

	private:

		Vector2		m_start;
		Vector2		m_end;
	};

	using Rectangle				= AABBCollider2D;
	using OrientedRectangle		= OBBCollider2D;

	using Point2D				= Vector2;
	using Circle				= CircleCollider2D;

}
