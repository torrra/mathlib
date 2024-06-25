#pragma once

#include "libmath/Vector3.h"
#include "libmath/Matrix3.h"
#include "libmath/Arithmetic.h"

namespace ion::math
{
	class OBBCollider3D;
	class SphereCollider3D;

	// Axis aligned bounding box
	class AABBCollider3D
	{

	public:

			// Constructors

						AABBCollider3D(void) = default;

						AABBCollider3D(const Vector3& _pos, const Vector3& _size);
						AABBCollider3D(const AABBCollider3D& _other) = default;

						~AABBCollider3D(void) = default;


			// AABB collision checks

			bool		CheckCollision(const AABBCollider3D& _other)	const;
			bool		CheckCollision (const SphereCollider3D& _other)	const;

			bool		PointInBox(const Vector3& _point)				const;

			// Accessors

			Vector3&	Position(void);
			Vector3&	Extents(void);

			Vector3		GetPosition(void)								const;
			Vector3		GetExtents(void)								const;

			// Calculate min and max vertex coords.

			Vector3		GetMin(void)									const;
			Vector3		GetMax(void)									const;


	private:

		Vector3		m_position;
		Vector3		m_extents;

	};

	// Bounding sphere
	class SphereCollider3D
	{
	public:

		// Constructors / destructor

					SphereCollider3D(void) = default;
					SphereCollider3D(const Vector3& _pos, float _radius);

					SphereCollider3D
					(const SphereCollider3D& _other) = default;

					~SphereCollider3D(void) = default;

		// Collision checks

		bool		CheckCollision(const AABBCollider3D& _other)	const;
		bool		CheckCollision(const SphereCollider3D& _other)	const;

		// Point vs sphere
		bool		PointInSphere(const Vector3& _point)			const;


		// Accessors

		Vector3&	Position(void);
		float&		Radius(void);

		Vector3		GetPosition(void)								const;
		float		GetRadius(void)									const;
		float		GetRadiusSquared(void)							const;

	private:

		Vector3 m_position;
		float	m_radius = 0.f;
	};

	class Ray3D
	{
	public:

		// Constructors / destructor

					Ray3D(void) = delete;
					Ray3D(const Vector3& _pos, const Vector3& _dir);
					Ray3D(const Ray3D& _other) = default;

					~Ray3D(void) = default;

		// Intersection with 3D vounding volumes

		bool		Intersect
		(const AABBCollider3D& _box, float& _distance)				const;

		bool		Intersect
		(const SphereCollider3D& _sphere, float& _distance)			const;

		// Accessors

		Vector3&	Origin(void);
		Vector3&	Direction(void);

		Vector3		GetOrigin(void)									 const;
		Vector3		GetDirection(void)								 const;
		Vector3		GetInverseDir(void)								 const;


	private:
		// Origin of ray
		Vector3    m_origin;

		// Direction unit vector
		Vector3    m_direction;

		// 1 / direction
		Vector3    m_inverseDir;
	};


	// Oriented bounding box
	class OBBCollider3D
	{
	public:

		// Constructors / destructor

					OBBCollider3D(void) = default;

					OBBCollider3D
					(const Vector3& _pos, const Vector3& _extents,
					 Radian _angleX, Radian _angleY, Radian _angleZ);

					OBBCollider3D(const OBBCollider3D& _other) = default;
					~OBBCollider3D(void) = default;

		// Accessors

		Radian&		RotationX(void);
		Radian&		RotationY(void);
		Radian&		RotationZ(void);

		Radian		GetRotationX(void);
		Radian		GetRotationY(void);
		Radian		GetRotationZ(void);

		Vector3&	Position(void);
		Vector3&	Extents(void);

		// Calculate rotation matrix from 3 object's 3 angles
		Matrix3 	RotationMatrix(void)							const;

		Vector3		GetPosition(void)								const;
		Vector3		GetExtents(void)								const;

		// Calculate rotated min and max vertices

		Vector3		GetMin(void)									const;
		Vector3		GetMax(void)									const;


	private:

		Vector3		m_position;
		Vector3		m_extents;
		Radian		m_rotation[3];
	};

	// 3D line segment
	class Line3D
	{
	public:
		// Constructors / destructor

					Line3D(void) = default;
					Line3D(const Vector3& _start, const Vector3& _end);
					Line3D(const Line3D& _other) = default;

		// Accessors

		Vector3&	Start(void);
		Vector3&	End(void);

		Vector3		GetStart(void)												const;
		Vector3		GetEnd(void)												const;

		// Intersection checks

		bool		Intersect(const AABBCollider3D& _box)						const;
		bool		Intersect(const SphereCollider3D& _circle)					const;

		// Calculate segment length

		float		Length(void)												const;
		float		LengthSquared(void)											const;

	private:

		Vector3		m_start;
		Vector3		m_end;
	};


	using Box = AABBCollider3D;
	using OrientedBox = OBBCollider3D;

	using Point3D = Vector3;
	using Sphere = SphereCollider3D;

}
