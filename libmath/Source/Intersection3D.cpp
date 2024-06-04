#include "libmath/Intersection3D.h"
#include "libmath/Trigonometry.h"

namespace mth
{


	AABBCollider3D::AABBCollider3D(const Vector3& _pos, const Vector3& _size)
		: m_position(_pos), m_extents(_size)
	{

	}


	Vector3& AABBCollider3D::Position(void)
	{
		return m_position;
	}

	Vector3& AABBCollider3D::Extents(void)
	{
		return m_extents;
	}

	Vector3 AABBCollider3D::GetPosition(void) const
	{
		return m_position;
	}

	Vector3 AABBCollider3D::GetExtents(void) const
	{
		return m_extents;
	}

	bool AABBCollider3D::CheckCollision(const AABBCollider3D& _other) const
	{
		Vector3		selfMin = GetMin(),
					selfMax = GetMax();

		Vector3		otherMin = _other.GetMin(),
					otherMax = _other.GetMax();


		if (selfMax[0] < otherMin[0] || selfMin[0] > otherMax[0])
			return false;

		if (selfMax[1] < otherMin[1] || selfMin[1] > otherMax[1])
			return false;

		if (selfMax[2] < otherMin[2] || selfMin[2] > otherMax[2])
			return false;


		return true;
	}



	bool AABBCollider3D::CheckCollision(const SphereCollider3D& _other) const
	{
		Vector3 minVertex = GetMin(), maxVertex = GetMax();


		Vector3		closestPoint
		{
			Max(minVertex.GetX(), Min(_other.GetPosition().GetX(), maxVertex.GetX())),
			Max(minVertex.GetY(), Min(_other.GetPosition().GetY(), maxVertex.GetY())),
			Max(minVertex.GetZ(), Min(_other.GetPosition().GetZ(), maxVertex.GetZ()))
		};

		Vector3		distance = closestPoint - _other.GetPosition();


		return distance.MagnitudeSquared() <= _other.GetRadius() * _other.GetRadius();
	}




	Ray3D::Ray3D(const Vector3& _pos, const Vector3& _dir)
		: m_origin(_pos)
	{
		m_direction = Normalize(_dir);

		// Pre compute direction divisor
		m_inverseDir.X() = (m_direction.GetX() != 0.f) ? 1.f / m_direction.GetX() : 0.f;
		m_inverseDir.Y() = (m_direction.GetY() != 0.f) ? 1.f / m_direction.GetY() : 0.f;
		m_inverseDir.Z() = (m_direction.GetZ() != 0.f) ? 1.f / m_direction.GetZ() : 0.f;
	}


	bool Ray3D::Intersect(const AABBCollider3D& _box, float& _distance) const
	{
		float   maxIntersect = FLT_MAX, minIntersect = -FLT_MAX;

		Vector3 minVertex = _box.GetMin(), maxVertex = _box.GetMax();

		// x plane = 0, y plane = 1, z plane = 3
		for (int axis = 0; axis < 3; ++axis)
		{
			// t1 for x, t3 for y, t5 for z
			float lowIntersect = (minVertex[axis] - m_origin[axis]) * m_inverseDir[axis];

			// t3 for x, t8 for y, t6 for z
			float highIntersect = (maxVertex[axis] - m_origin[axis]) * m_inverseDir[axis];

			maxIntersect = Min(Max(lowIntersect, highIntersect), maxIntersect);
			minIntersect = Max(Min(lowIntersect, highIntersect), minIntersect);
		}

		// Check if an intersection occurred
		bool	intersection = maxIntersect > Max(minIntersect, 0.f);

		// Write distance into reference argument if intersection is successful
		if (intersection)
			_distance = minIntersect;

		// Return intersection status
		return intersection;
	}

    Vector3 &Ray3D::Origin(void)
    {
       return m_origin;
    }

    Vector3 &Ray3D::Direction(void)
    {
        return m_direction;
    }

    Vector3 Ray3D::GetOrigin(void) const
    {
        return m_origin;
    }

    Vector3 Ray3D::GetDirection(void) const
    {
        return m_direction;
    }

    Vector3 Ray3D::GetInverseDir(void) const
    {
        return m_inverseDir;
    }



	Vector3 AABBCollider3D::GetMin(void) const
	{
		return m_position - m_extents;
	}


	Vector3 AABBCollider3D::GetMax(void) const
	{
		return m_position + m_extents;
	}


	Vector3 OBBCollider3D::GetMin(void) const
	{
		Vector3		rotated = Rotate
		(
			m_extents, m_rotation[0], m_rotation[1], m_rotation[2]
		);

		return m_position - rotated;
	}

	Vector3 OBBCollider3D::GetMax(void) const
	{
		Vector3		rotated = Rotate
		(
			m_extents, m_rotation[0], m_rotation[1], m_rotation[2]
		);

		return rotated + m_position;
	}


	OBBCollider3D::OBBCollider3D
	(const Vector3& _pos, const Vector3& _extents,
	 Radian _angleX, Radian _angleY, Radian _angleZ)
		: m_position(_pos), m_extents(_extents)
	{
		m_rotation[0] = _angleX;
		m_rotation[1] = _angleY;
		m_rotation[2] = _angleZ;
	}

	Radian& OBBCollider3D::RotationX(void)
	{
		return m_rotation[0];
	}

	Radian& OBBCollider3D::RotationY(void)
	{
		return m_rotation[1];
	}

	Radian& OBBCollider3D::RotationZ(void)
	{
		return m_rotation[2];
	}

	Radian OBBCollider3D::GetRotationX(void)
	{
		return m_rotation[0];
	}

	Radian OBBCollider3D::GetRotationY(void)
	{
		return m_rotation[1];
	}

	Radian OBBCollider3D::GetRotationZ(void)
	{
		return m_rotation[2];
	}


	Vector3& OBBCollider3D::Position(void)
	{
		return m_position;
	}

	Vector3& OBBCollider3D::Extents(void)
	{
		return m_extents;
	}

	Matrix3 OBBCollider3D::RotationMatrix(void) const
	{
		float		cosYaw = Cos(m_rotation[2]), sinYaw = Sin(m_rotation[2]);
		float		cosPitch = Cos(m_rotation[0]), sinPitch = Sin(m_rotation[0]);
		float		cosRoll = Cos(m_rotation[1]), sinRoll = Sin(m_rotation[1]);


		float		rotation[][3] =
		{
			{
				cosYaw * cosRoll + sinYaw * sinPitch * sinRoll,
				-cosYaw * sinRoll + sinYaw * sinPitch * cosRoll,
				sinYaw * cosPitch
			},


			{
				sinRoll * cosPitch,
				cosRoll * cosPitch,
				-sinPitch
			},


			{
				-sinYaw * cosRoll + cosYaw * sinPitch * sinRoll,
				sinRoll * sinYaw + cosYaw * sinPitch * cosRoll,
				cosYaw * cosPitch
			}
		};

		return Matrix3(rotation);
	}


	Vector3 OBBCollider3D::GetPosition(void) const
	{
		return m_position;
	}

	Vector3 OBBCollider3D::GetExtents(void) const
	{
		return m_extents;
	}


	Vector3& SphereCollider3D::Position(void)
	{
		return m_position;
	}

	float& SphereCollider3D::Radius(void)
	{
		return m_radius;
	}

	Vector3 SphereCollider3D::GetPosition(void) const
	{
		return m_position;
	}

	float SphereCollider3D::GetRadius(void) const
	{
		return m_radius;
	}

	SphereCollider3D::SphereCollider3D(const Vector3& _pos, float _radius)
		: m_position(_pos), m_radius(_radius)
	{
	}


	bool SphereCollider3D::CheckCollision(const AABBCollider3D& _other) const
	{
		return _other.CheckCollision(*this);
	}



	bool SphereCollider3D::CheckCollision(const SphereCollider3D& _other) const
	{
		float		distance = DistanceSquared(m_position, _other.m_position);

		return distance <= (m_radius * m_radius) + (_other.m_radius * _other.m_radius);
	}

}