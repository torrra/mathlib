#pragma once

#include "libmath/Vector3.h"
#include "libmath/Arithmetic.h"

namespace mth
{
	class OBBCollider3D;
	class SphereCollider3D;
	class MeshCollider3D;

	class AABBCollider3D
	{

	public:
						AABBCollider3D(void) = default;

						AABBCollider3D(const Vector3& _pos, const Vector3& _size);
						AABBCollider3D(const AABBCollider3D& _other) = default;

						~AABBCollider3D(void) = default;

			bool		CheckCollision(const AABBCollider3D& _other)	const;

			bool		CheckCollision(const OBBCollider3D& _other)		const;

			bool		CheckCollision (const SphereCollider3D& _other)	const;

			bool		CheckCollision(const MeshCollider3D& _other)	const;

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


		Vector3&	Position(void);
		float&		Radius(void);

		Vector3		GetPosition(void)								const;
		float		GetRadius(void)									const;

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

	class MeshCollider3D
	{
	public:

		MeshCollider3D(void) = default;
		MeshCollider3D(Vector3 _vertices[], int _count);
		MeshCollider3D(const MeshCollider3D& _other);
		~MeshCollider3D(void);


		bool			CheckCollision
		(const MeshCollider3D& _other)							const;
		bool			CheckCollision
		(const AABBCollider3D& _other)								const;

		bool			CheckCollision
		(const OBBCollider3D& _other)								const;


		Vector3&		operator[](int _index);
		Vector3			operator[](int _index)						const;

	private:

		bool SeparatingAxisTheorem
		(const MeshCollider3D& _other)							const;


		void MinMaxProjection
		(const Vector3& _normal, float& _min, float& _max)		const;


		bool InternalSAT(const MeshCollider3D& _poly3)					const;

		bool PlanesSAT(const MeshCollider3D& _other)			const;

		Vector3*		m_vertices = nullptr;
		unsigned int	m_vertexCount = 0;


		friend class AABBCollider3D;
		friend class OBBCollider3D;

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


		bool		CheckCollision(const AABBCollider3D& _other)	const;

		bool		CheckCollision(const OBBCollider3D& _other)		const;

		bool		CheckCollision(const SphereCollider3D& _other)	const;

		bool		CheckCollision(const MeshCollider3D& _other)	const;

		Vector3&	Position(void);
		Vector3&	Extents(void);

		Radian* 	Rotation(void);

		Vector3		GetPosition(void)								const;
		Vector3		GetExtents(void)								const;

		Radian const*	GetRotation(void)							const;

		Vector3		GetMin(void)									const;
		Vector3		GetMax(void)									const;


	private:

		Vector3		m_position;
		Vector3		m_extents;
		Radian		m_rotation[3];
	};


	using Box = AABBCollider3D;
	using OrientedBox = OBBCollider3D;

	using Point3D = Vector3;
	using Sphere = SphereCollider3D;

}
