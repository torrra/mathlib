#pragma once

#include "Vector3.hpp"
#include "Matrix3.hpp"
#include "Arithmetic.hpp"

namespace math
{
	class OBBCollider3D;
	class SphereCollider3D;

	// Axis aligned bounding box
	class AABBCollider3D
	{

	public:

			// Constructors

						AABBCollider3D(void) = default;

						AABBCollider3D(const Vector3f& pos, const Vector3f& size);
						AABBCollider3D(const AABBCollider3D& other) = default;

						~AABBCollider3D(void) = default;


			// AABB collision checks

			bool		CheckCollision(const AABBCollider3D& other)	const;
			bool		CheckCollision (const SphereCollider3D& other)	const;

			bool		PointInBox(const Vector3f& point)				const;

			// Accessors

			Vector3f&	Position(void);
			Vector3f&	Extents(void);

			Vector3f		GetPosition(void)								const;
			Vector3f		GetExtents(void)								const;

			// Calculate min and max vertex coords.

			Vector3f		GetMin(void)									const;
			Vector3f		GetMax(void)									const;


	private:

		Vector3f		m_position;
		Vector3f		m_extents;

	};

	// Bounding sphere
	class SphereCollider3D
	{
	public:

		// Constructors / destructor

					SphereCollider3D(void) = default;
					SphereCollider3D(const Vector3f& pos, float radius);

					SphereCollider3D
					(const SphereCollider3D& other) = default;

					~SphereCollider3D(void) = default;

		// Collision checks

		bool		CheckCollision(const AABBCollider3D& other)	const;
		bool		CheckCollision(const SphereCollider3D& other)	const;

		// Point vs sphere
		bool		PointInSphere(const Vector3f& point)			const;


		// Accessors

		Vector3f&	Position(void);
		float&		Radius(void);

		Vector3f		GetPosition(void)								const;
		float		GetRadius(void)									const;
		float		GetRadiusSquared(void)							const;

	private:

		Vector3f m_position{};
		float	m_radius = 0.f;
	};

	class Ray3D
	{
	public:

		// Constructors / destructor

					Ray3D(void) = delete;
					Ray3D(const Vector3f& pos, const Vector3f& dir);
					Ray3D(const Ray3D& other) = default;

					~Ray3D(void) = default;

		// Intersection with 3D vounding volumes

		bool		Intersect
		(const AABBCollider3D& box, float& distance)				const;

		bool		Intersect
		(const SphereCollider3D& sphere, float& distance)			const;

		// Accessors

		Vector3f&	Origin(void);
		Vector3f&	Direction(void);

		Vector3f		GetOrigin(void)									 const;
		Vector3f		GetDirection(void)								 const;
		Vector3f		GetInverseDir(void)								 const;


	private:
		// Origin of ray
		Vector3f    m_origin;

		// Direction unit vector
		Vector3f    m_direction;

		// 1 / direction
		Vector3f    m_inverseDir;
	};


	// Oriented bounding box
	class OBBCollider3D
	{
	public:

		// Constructors / destructor

					OBBCollider3D(void) = default;

					OBBCollider3D
					(const Vector3f& pos, const Vector3f& extents,
					 Radian<float> angleX, Radian<float> angleY, Radian<float> angleZ);

					OBBCollider3D(const OBBCollider3D& other) = default;
					~OBBCollider3D(void) = default;

		// Accessors

		Radian<float>&		RotationX(void);
		Radian<float>&		RotationY(void);
		Radian<float>&		RotationZ(void);

		Radian<float>		GetRotationX(void) const;
		Radian<float>		GetRotationY(void) const;
		Radian<float>		GetRotationZ(void) const;

		Vector3f&	Position(void);
		Vector3f&	Extents(void);

		// Calculate rotation matrix from 3 object's 3 angles
		Matrix3f 	RotationMatrix(void)							const;

		Vector3f		GetPosition(void)								const;
		Vector3f		GetExtents(void)								const;

		// Calculate rotated min and max vertices

		Vector3f		GetMin(void)									const;
		Vector3f		GetMax(void)									const;


	private:

		Vector3f		m_position;
		Vector3f		m_extents;
		Radian<float>		m_rotation[3];
	};

	// 3D line segment
	class Line3D
	{
	public:
		// Constructors / destructor

					Line3D(void) = default;
					Line3D(const Vector3f& start, const Vector3f& end);
					Line3D(const Line3D& other) = default;

		// Accessors

		Vector3f&	Start(void);
		Vector3f&	End(void);

		Vector3f		GetStart(void)												const;
		Vector3f		GetEnd(void)												const;

		// Intersection checks

		bool		Intersect(const AABBCollider3D& box)						const;
		bool		Intersect(const SphereCollider3D& circle)					const;

		// Calculate segment length

		float		Length(void)												const;
		float		LengthSquared(void)											const;

	private:

		Vector3f		m_start;
		Vector3f		m_end;
	};


	using Box = AABBCollider3D;
	using OrientedBox = OBBCollider3D;

	using Point3D = Vector3f;
	using Sphere = SphereCollider3D;

}
