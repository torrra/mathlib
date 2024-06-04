#pragma once

#include "libmath/Vector3.h"
#include "libmath/Matrix3.h"
#include "libmath/Arithmetic.h"

namespace mth
{
	class OBBCollider3D;
	class SphereCollider3D;

	class AABBCollider3D
	{

	public:
						AABBCollider3D(void) = default;

						AABBCollider3D(const Vector3& _pos, const Vector3& _size);
						AABBCollider3D(const AABBCollider3D& _other) = default;

						~AABBCollider3D(void) = default;

			bool		CheckCollision(const AABBCollider3D& _other)	const;


			bool		CheckCollision (const SphereCollider3D& _other)	const;

			bool		PointInBox(const Vector3& _point)				const;

			Vector3&	Position(void);
			Vector3&	Extents(void);

			Vector3		GetPosition(void)								const;
			Vector3		GetExtents(void)								const;

			Vector3		GetMin(void)									const;
			Vector3		GetMax(void)									const;


	private:

		Vector3		m_position;
		Vector3		m_extents;

	};

	class SphereCollider3D
	{
	public:

					SphereCollider3D(void) = default;
					SphereCollider3D(const Vector3& _pos, float _radius);

					SphereCollider3D
					(const SphereCollider3D& _other) = default;

		bool		CheckCollision(const AABBCollider3D& _other)	const;
		bool		CheckCollision(const SphereCollider3D& _other)	const;

		bool		PointInSphere(const Vector3& _point)			const;

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

		Ray3D(void) = delete;
		Ray3D(const Vector3& _pos, const Vector3& _dir);
		Ray3D(const Ray3D& _other) = default;

		~Ray3D(void) = default;

		bool Intersect
		(const AABBCollider3D& _box, float& _distance)				const;

		bool Intersect
		(const SphereCollider3D& _sphere, float& _distance)			const;


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



	class OBBCollider3D
	{
	public:

					OBBCollider3D(void) = default;

					OBBCollider3D
					(const Vector3& _pos, const Vector3& _extents,
					 Radian _angleX, Radian _angleY, Radian _angleZ);

					OBBCollider3D(const OBBCollider3D& _other) = default;
					~OBBCollider3D(void) = default;

		Radian&		RotationX(void);
		Radian&		RotationY(void);
		Radian&		RotationZ(void);

		Radian		GetRotationX(void);
		Radian		GetRotationY(void);
		Radian		GetRotationZ(void);

		Vector3&	Position(void);
		Vector3&	Extents(void);

		Matrix3 	RotationMatrix(void)							const;

		Vector3		GetPosition(void)								const;
		Vector3		GetExtents(void)								const;


		Vector3		GetMin(void)									const;
		Vector3		GetMax(void)									const;


	private:

		Vector3		m_position;
		Vector3		m_extents;
		Radian		m_rotation[3];
	};


	class Line3D
	{
	public:

					Line3D(void) = default;
					Line3D(const Vector3& _start, const Vector3& _end);
					Line3D(const Line3D& _other) = default;

		Vector3&	Start(void);
		Vector3&	End(void);

		Vector3		GetStart(void)												const;
		Vector3		GetEnd(void)												const;

		bool		Intersect(const AABBCollider3D& _box)						const;
		bool		Intersect(const SphereCollider3D& _circle)					const;

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
