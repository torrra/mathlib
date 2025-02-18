#pragma once

#include "Vector2.hpp"
#include "Arithmetic.hpp"

namespace math
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

						AABBCollider2D(const Vector2f& pos, const Vector2f& size);
						AABBCollider2D(const AABBCollider2D& other) = default;

						~AABBCollider2D(void) = default;

			// Collision checks

			bool		CheckCollision(const AABBCollider2D& other)	const;
			bool		CheckCollision(const OBBCollider2D& other)		const;
			bool		CheckCollision (const CircleCollider2D& other)	const;
			bool		CheckCollision(const PolygonCollider2D& other)	const;

			bool		PointInBox(const Vector2f& point)				const;

			// Accessors

			Vector2f&	Position(void);
			Vector2f&	Extents(void);

			Vector2f		GetPosition(void)								const;
			Vector2f		GetExtents(void)								const;

			// Calculate min and max vertices

			Vector2f		GetMin(void)									const;
			Vector2f		GetMax(void)									const;


	private:

		Vector2f		m_position;
		Vector2f		m_extents;

	};

	// 2D bounding circle
	class CircleCollider2D
	{
	public:

		// Constructors / destructors

					CircleCollider2D(void) = default;
					CircleCollider2D(const Vector2f& pos, float radius);

					CircleCollider2D
					(const CircleCollider2D& other) = default;

		// Collision checks

		bool		CheckCollision(const AABBCollider2D& other)	const;
		bool		CheckCollision(const OBBCollider2D& other)		const;
		bool		CheckCollision(const CircleCollider2D& other)	const;

		bool		PointInCircle(const Vector2f& point)			const;


		Vector2f&	Position(void);
		float&		Radius(void);

		Vector2f		GetPosition(void)								const;
		float		GetRadius(void)									const;
		float		GetRadiusSquared(void)							const;

	private:

		Vector2f		m_position;
		float		m_radius = 0.f;
	};

	class Ray2D
	{
	public:

		// Constructors / destructor

					Ray2D(void) = delete;
					Ray2D(const Vector2f& pos, const Vector2f& dir);
					Ray2D(const Ray2D& other) = default;

					~Ray2D(void) = default;

		// AABB intersection check

		bool		Intersect
		(const AABBCollider2D& box, float& distance)				 const;

		// Accessors

		Vector2f&	Origin(void);
		Vector2f&	Direction(void);

		Vector2f		GetOrigin(void)									 const;
		Vector2f		GetDirection(void)								 const;
		Vector2f		GetInverseDir(void)								 const;


	private:
		// Origin of ray
		Vector2f    m_origin;

		// Direction unit vector
		Vector2f    m_direction;

		// 1 / direction
		Vector2f    m_inverseDir;
	};

	class PolygonCollider2D
	{
	public:

		// Constructors / destructor

						PolygonCollider2D(void) = default;
						PolygonCollider2D(Vector2f vertices[], int count);
						PolygonCollider2D(const PolygonCollider2D& other);
						~PolygonCollider2D(void);

		// Collisions checks

		bool			CheckCollision
		(const PolygonCollider2D& other)									const;
		bool			CheckCollision
		(const AABBCollider2D& other)										const;

		bool			CheckCollision
		(const OBBCollider2D& other)										const;


		Vector2f&		operator[](int index);
		Vector2f			operator[](int index)								const;

	private:

		// Internal SAT functions

		bool			SeparatingAxisTheorem
		(const PolygonCollider2D& other)									const;


		void			MinMaxProjection
		(const Vector2f& normal, float& min, float& max)					const;


		bool			InternalSAT(const PolygonCollider2D& poly2)		const;

		Vector2f*		m_vertices = nullptr;
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
					(const Vector2f& pos, const Vector2f& extents, Radian<float> angle);

					OBBCollider2D(const OBBCollider2D& other) = default;
					~OBBCollider2D(void) = default;

		// Collision checks

		bool		CheckCollision(const AABBCollider2D& other)		const;
		bool		CheckCollision(const OBBCollider2D& other)			const;
		bool		CheckCollision(const CircleCollider2D& other)		const;
		bool		CheckCollision(const PolygonCollider2D& other)		const;


		// Accessors

		Vector2f&	Position(void);
		Vector2f&	Extents(void);

		Radian<float>&		Rotation(void);

		Vector2f		GetPosition(void)									const;
		Vector2f		GetExtents(void)									const;

		Radian<float>		GetRotation(void)									const;

		Vector2f		GetMin(void)										const;
		Vector2f		GetMax(void)										const;


	private:

		Vector2f		m_position;
		Vector2f		m_extents;
		Radian<float>		m_rotation;
	};


	// 2D line segment
	class Line2D
	{
	public:

		// Constructor / destructor

					Line2D(void) = default;
					Line2D(const Vector2f& start, const Vector2f& end);
					Line2D(const Line2D& other) = default;

					~Line2D(void) = default;


		// Accessors

		Vector2f&	Start(void);
		Vector2f&	End(void);

		Vector2f		GetStart(void)												const;
		Vector2f		GetEnd(void)												const;

		// Intersection checks

		bool		Intersect(const AABBCollider2D& box)						const;
		bool		Intersect(const CircleCollider2D& circle)					const;

		// Calculate segment length

		float		Length(void)												const;
		float		LengthSquared(void)											const;

	private:

		Vector2f		m_start;
		Vector2f		m_end;
	};

	using Rectangle				= AABBCollider2D;
	using OrientedRectangle		= OBBCollider2D;

	using Point2D				= Vector2f;
	using Circle				= CircleCollider2D;

}
