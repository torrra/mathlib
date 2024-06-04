#include "libmath/Intersection3D.h"

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

	bool AABBCollider3D::CheckCollision(const OBBCollider3D& _other) const
	{
		MeshCollider3D    selfPoly, otherPoly;

		Vector3        selfVertices[8] =
		{
			GetMax(),
			{ m_position.GetX() - m_extents.GetX(), m_position.GetY() + m_extents.GetY(), m_position.GetZ() + m_extents.GetZ()},

			{ m_position.GetX() + m_extents.GetX(), m_position.GetY() - m_extents.GetY(), m_position.GetZ() + m_extents.GetZ()},
			{ m_position.GetX() - m_extents.GetX(), m_position.GetY() - m_extents.GetY(), m_position.GetZ() + m_extents.GetZ()},


			GetMin(),
			{ m_position.GetX() - m_extents.GetX(), m_position.GetY() + m_extents.GetY(), m_position.GetZ() - m_extents.GetZ()},

			{ m_position.GetX() + m_extents.GetX(), m_position.GetY() - m_extents.GetY(), m_position.GetZ() - m_extents.GetZ()},
			{ m_position.GetX() - m_extents.GetX(), m_position.GetY() - m_extents.GetY(), m_position.GetZ() - m_extents.GetZ()},
		};

		Vector3				otherRotated = Rotate(_other.GetExtents(), _other.GetRotation()[0], _other.GetRotation()[1], _other.GetRotation()[2]);


		Vector3		otherVertices[8] =
		{
			_other.GetPosition() + otherRotated,

			_other.GetPosition() + Rotate
			(
				{_other.GetExtents().X(), -_other.GetExtents().Y(), _other.GetExtents().Z()},
				 _other.GetRotation()[0], _other.GetRotation()[1], _other.GetRotation()[2]
			),

			_other.GetPosition() + Rotate
			(
				{-_other.GetExtents().X(), -_other.GetExtents().Y(), _other.GetExtents().Z()},
				 _other.GetRotation()[0], _other.GetRotation()[1], _other.GetRotation()[2]
			),

			_other.GetPosition() + Rotate
			(
				{-_other.GetExtents().X(), _other.GetExtents().Y(), _other.GetExtents().Z()},
				 _other.GetRotation()[0], _other.GetRotation()[1], _other.GetRotation()[2]
			),


			_other.GetPosition() - otherRotated,

			_other.GetPosition() + Rotate
			(
				{_other.GetExtents().X(), -_other.GetExtents().Y(), -_other.GetExtents().Z()},
				 _other.GetRotation()[0], _other.GetRotation()[1], _other.GetRotation()[2]
			),

			_other.GetPosition() + Rotate
			(
				{-_other.GetExtents().X(), -_other.GetExtents().Y(), -_other.GetExtents().Z()},
				 _other.GetRotation()[0], _other.GetRotation()[1], _other.GetRotation()[2]
			),

			_other.GetPosition() + Rotate
			(
				{-_other.GetExtents().X(), _other.GetExtents().Y(), -_other.GetExtents().Z()},
				 _other.GetRotation()[0], _other.GetRotation()[1], _other.GetRotation()[2]
			),
		};

		selfPoly.m_vertices = selfVertices;
		otherPoly.m_vertices = otherVertices;

		selfPoly.m_vertexCount = otherPoly.m_vertexCount = 8;


		bool		intersection = selfPoly.CheckCollision(otherPoly);

		selfPoly.m_vertices = otherPoly.m_vertices = nullptr;

		return intersection;

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

	bool AABBCollider3D::CheckCollision(const MeshCollider3D& _other) const
	{
		MeshCollider3D	selfPoly;

		Vector3        selfVertices[8] =
		{
			GetMax(),
			{ m_position.GetX() - m_extents.GetX(), m_position.GetY() + m_extents.GetY(), m_position.GetZ() + m_extents.GetZ()},

			{ m_position.GetX() + m_extents.GetX(), m_position.GetY() - m_extents.GetY(), m_position.GetZ() + m_extents.GetZ()},
			{ m_position.GetX() - m_extents.GetX(), m_position.GetY() - m_extents.GetY(), m_position.GetZ() + m_extents.GetZ()},


			GetMin(),
			{ m_position.GetX() - m_extents.GetX(), m_position.GetY() + m_extents.GetY(), m_position.GetZ() - m_extents.GetZ()},

			{ m_position.GetX() + m_extents.GetX(), m_position.GetY() - m_extents.GetY(), m_position.GetZ() - m_extents.GetZ()},
			{ m_position.GetX() - m_extents.GetX(), m_position.GetY() - m_extents.GetY(), m_position.GetZ() - m_extents.GetZ()},
		};

		selfPoly.m_vertices = selfVertices;

		selfPoly.m_vertexCount = 8;


		bool		intersection = selfPoly.CheckCollision(_other);

		selfPoly.m_vertices = nullptr;

		return intersection;
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

    MeshCollider3D::MeshCollider3D(Vector3 _vertices[], int _count)
        : m_vertexCount(_count)
    {
		if (!m_vertices)
			m_vertices = new Vector3[_count];


		for (int vertex = 0; vertex < _count; ++vertex)
		{
			m_vertices[vertex] = _vertices[vertex];
		}
	}

	MeshCollider3D::MeshCollider3D(const MeshCollider3D& _other)
		: m_vertexCount(_other.m_vertexCount)
	{
		if (_other.m_vertexCount)
			m_vertices = new Vector3[_other.m_vertexCount];

		for (unsigned int vert = 0; vert < _other.m_vertexCount; ++vert)
			m_vertices[vert] = _other.m_vertices[vert];

	}


	MeshCollider3D::~MeshCollider3D(void)
	{
		if (m_vertices)
			delete[] m_vertices;
	}


	Vector3& MeshCollider3D::operator[](int _index)
	{
		return m_vertices[_index];
	}


	Vector3 MeshCollider3D::operator[](int _index) const
	{
		return m_vertices[_index];
	}



	bool MeshCollider3D::CheckCollision(const MeshCollider3D& _other) const
	{
		return SeparatingAxisTheorem(_other);
	}

	void MeshCollider3D::MinMaxProjection
	(const Vector3& _normal, float& _min, float& _max) const
	{
		for (unsigned int vertex = 0; vertex < m_vertexCount; ++vertex)
		{
			float	projection = Round(_normal.Dot(m_vertices[vertex]));

			if (projection < _min)
				_min = projection;

			else if (projection > _max)
				_max = projection;
		}
	}

	bool MeshCollider3D::
		SeparatingAxisTheorem(const MeshCollider3D& _other) const
	{

		if (!InternalSAT(_other))
			return false;

		if (!_other.InternalSAT(*this))
			return false;

		return true;
	}


	bool MeshCollider3D::InternalSAT(const MeshCollider3D& _other) const
	{
		/*float	min1, max1;
		float   min3, max3;


		for (unsigned int side = 0; side < m_vertexCount; ++side)
		{
			min1 = FLT_MAX, max1 = -FLT_MAX;
			min3 = FLT_MAX, max3 = -FLT_MAX;

			Vector3		normal;

			if (0 == side)
				normal = (m_vertices[side] - m_vertices[m_vertexCount - 1]).Normal();

			else
				normal = (m_vertices[side] - m_vertices[side - 1]).Normal();

			MinMaxProjection(normal, min1, max1);
			_other.MinMaxProjection(normal, min3, max3);

			if (min3 > max1 || min1 > max3)
				return false;
		}*/

		return true;
	}

	bool MeshCollider3D::PlanesSAT(const MeshCollider3D& _other) const
	{
		return false;
	}

	bool MeshCollider3D::CheckCollision(const AABBCollider3D& _other) const
	{
		return _other.CheckCollision(*this);
	}

	bool MeshCollider3D::CheckCollision(const OBBCollider3D& _other) const
	{
		return _other.CheckCollision(*this);
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

	bool OBBCollider3D::CheckCollision(const AABBCollider3D& _other) const
	{
		return _other.CheckCollision(*this);
	}


	Vector3& OBBCollider3D::Position(void)
	{
		return m_position;
	}

	Vector3& OBBCollider3D::Extents(void)
	{
		return m_extents;
	}

	Radian* OBBCollider3D::Rotation(void)
	{
		return m_rotation;
	}

	Vector3 OBBCollider3D::GetPosition(void) const
	{
		return m_position;
	}

	Vector3 OBBCollider3D::GetExtents(void) const
	{
		return m_extents;
	}

	Radian const* OBBCollider3D::GetRotation(void) const
	{
		return m_rotation;
	}


	bool OBBCollider3D::CheckCollision(const OBBCollider3D& _other) const
	{
		MeshCollider3D	selfPoly, otherPoly;

		Vector3				selfRotated = Rotate(m_extents, m_rotation[0], m_rotation[1], m_rotation[2]);
		Vector3				otherRotated = Rotate(_other.m_extents, _other.m_rotation[0], _other.m_rotation[1], _other.m_rotation[2]);


		Vector3		selfVertices[8] =
		{
			GetPosition() + selfRotated,

			GetPosition() + Rotate
			(
				{GetExtents().X(), -GetExtents().Y(), GetExtents().Z()},
				 GetRotation()[0], GetRotation()[1], GetRotation()[2]
			),

			GetPosition() + Rotate
			(
				{-GetExtents().X(), -GetExtents().Y(), GetExtents().Z()},
				 GetRotation()[0], GetRotation()[1], GetRotation()[2]
			),

			GetPosition() + Rotate
			(
				{-GetExtents().X(), GetExtents().Y(), GetExtents().Z()},
				 GetRotation()[0], GetRotation()[1], GetRotation()[2]
			),


			GetPosition() - selfRotated,

			GetPosition() + Rotate
			(
				{GetExtents().X(), -GetExtents().Y(), -GetExtents().Z()},
				 GetRotation()[0], GetRotation()[1], GetRotation()[2]
			),

			GetPosition() + Rotate
			(
				{-GetExtents().X(), -GetExtents().Y(), -GetExtents().Z()},
				 GetRotation()[0], GetRotation()[1], GetRotation()[2]
			),

			GetPosition() + Rotate
			(
				{-GetExtents().X(), GetExtents().Y(), -GetExtents().Z()},
				 GetRotation()[0], GetRotation()[1], GetRotation()[2]
			),
		};

		Vector3		otherVertices[8] =
		{
			_other.GetPosition() + otherRotated,

			_other.GetPosition() + Rotate
			(
				{_other.GetExtents().X(), -_other.GetExtents().Y(), _other.GetExtents().Z()},
				 _other.GetRotation()[0], _other.GetRotation()[1], _other.GetRotation()[2]
			),

			_other.GetPosition() + Rotate
			(
				{-_other.GetExtents().X(), -_other.GetExtents().Y(), _other.GetExtents().Z()},
				 _other.GetRotation()[0], _other.GetRotation()[1], _other.GetRotation()[2]
			),

			_other.GetPosition() + Rotate
			(
				{-_other.GetExtents().X(), _other.GetExtents().Y(), _other.GetExtents().Z()},
				 _other.GetRotation()[0], _other.GetRotation()[1], _other.GetRotation()[2]
			),


			_other.GetPosition() - otherRotated,

			_other.GetPosition() + Rotate
			(
				{_other.GetExtents().X(), -_other.GetExtents().Y(), -_other.GetExtents().Z()},
				 _other.GetRotation()[0], _other.GetRotation()[1], _other.GetRotation()[2]
			),

			_other.GetPosition() + Rotate
			(
				{-_other.GetExtents().X(), -_other.GetExtents().Y(), -_other.GetExtents().Z()},
				 _other.GetRotation()[0], _other.GetRotation()[1], _other.GetRotation()[2]
			),

			_other.GetPosition() + Rotate
			(
				{-_other.GetExtents().X(), _other.GetExtents().Y(), -_other.GetExtents().Z()},
				 _other.GetRotation()[0], _other.GetRotation()[1], _other.GetRotation()[2]
			),
		};

		selfPoly.m_vertices = selfVertices;
		otherPoly.m_vertices = otherVertices;

		selfPoly.m_vertexCount = otherPoly.m_vertexCount = 8;


		bool		intersection = selfPoly.CheckCollision(otherPoly);

		selfPoly.m_vertices = otherPoly.m_vertices = nullptr;

		return intersection;
	}

	bool OBBCollider3D::CheckCollision(const SphereCollider3D& _other) const
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

	bool OBBCollider3D::CheckCollision(const MeshCollider3D& _other) const
	{
		MeshCollider3D	selfPoly;

		Vector3				selfRotated = Rotate(m_extents, m_rotation[0], m_rotation[1], m_rotation[2]);


		Vector3		selfVertices[8] =
		{
			GetPosition() + selfRotated,

			GetPosition() + Rotate
			(
				{GetExtents().X(), -GetExtents().Y(), GetExtents().Z()},
				 GetRotation()[0], GetRotation()[1], GetRotation()[2]
			),

			GetPosition() + Rotate
			(
				{-GetExtents().X(), -GetExtents().Y(), GetExtents().Z()},
				 GetRotation()[0], GetRotation()[1], GetRotation()[2]
			),

			GetPosition() + Rotate
			(
				{-GetExtents().X(), GetExtents().Y(), GetExtents().Z()},
				 GetRotation()[0], GetRotation()[1], GetRotation()[2]
			),


			GetPosition() - selfRotated,

			GetPosition() + Rotate
			(
				{GetExtents().X(), -GetExtents().Y(), -GetExtents().Z()},
				 GetRotation()[0], GetRotation()[1], GetRotation()[2]
			),

			GetPosition() + Rotate
			(
				{-GetExtents().X(), -GetExtents().Y(), -GetExtents().Z()},
				 GetRotation()[0], GetRotation()[1], GetRotation()[2]
			),

			GetPosition() + Rotate
			(
				{-GetExtents().X(), GetExtents().Y(), -GetExtents().Z()},
				 GetRotation()[0], GetRotation()[1], GetRotation()[2]
			),
		};

		selfPoly.m_vertices = selfVertices;

		selfPoly.m_vertexCount = 8;


		bool	intersection = selfPoly.CheckCollision(_other);

		selfPoly.m_vertices = nullptr;

		return intersection;
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

	bool SphereCollider3D::CheckCollision(const OBBCollider3D& _other) const
	{
		return _other.CheckCollision(*this);
	}

	bool SphereCollider3D::CheckCollision(const SphereCollider3D& _other) const
	{
		float		distance = DistanceSquared(m_position, _other.m_position);

		return distance <= (m_radius * m_radius) + (_other.m_radius * _other.m_radius);
	}

}