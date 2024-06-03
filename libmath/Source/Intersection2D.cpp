#include "libmath/Intersection2D.h"

#include <iostream>

namespace mth
{


	AABBCollider2D::AABBCollider2D(const Vector2& _pos, const Vector2& _size)
		: m_position(_pos), m_extents(_size)
	{

	}


	Vector2& AABBCollider2D::Position(void)
	{
		return m_position;
	}

	Vector2& AABBCollider2D::Extents(void)
	{
		return m_extents;
	}

	Vector2 AABBCollider2D::GetPosition(void) const
	{
		return m_position;
	}

	Vector2 AABBCollider2D::GetExtents(void) const
	{
		return m_extents;
	}

	bool AABBCollider2D::CheckCollision(const AABBCollider2D& _other) const
	{
		Vector2		selfMin = GetMin(),
					selfMax = GetMax();

		Vector2		otherMin = _other.GetMin(),
					otherMax = _other.GetMax();


		if (selfMax[0] < otherMin[0] || selfMin[0] > otherMax[0])
			return false;

		if (selfMax[1] < otherMin[1] || selfMin[1] > otherMax[1])
			return false;

		return true;
	}

	bool AABBCollider2D::CheckCollision(const OBBCollider2D& _other) const
	{
		PolygonCollider2D    selfPoly, otherPoly;

		Vector2        selfVertices[4] =
		{
			GetMax(),
			GetMin(),
			{ m_position.GetX() + m_extents.GetX(), m_position.GetY() - m_extents.GetY()},
			{ m_position.GetX() - m_extents.GetX(), m_position.GetY() + m_extents.GetY()},
		};

		Vector2				otherRotated = Rotate(_other.GetExtents(), _other.GetRotation());


		Vector2		otherVertices[4] =
		{
			_other.GetPosition() + otherRotated,
			_other.GetPosition() - otherRotated,
			{
				_other.GetPosition().GetX() + otherRotated.GetX(),
				_other.GetPosition().GetY() - otherRotated.GetY()
			},
			{
				_other.GetPosition().GetX() - otherRotated.GetX(),
				_other.GetPosition().GetY() + otherRotated.GetY()
			},
		};

		selfPoly.m_vertices = selfVertices;
		otherPoly.m_vertices = otherVertices;

		selfPoly.m_vertexCount = otherPoly.m_vertexCount = 4;


		bool		intersection = selfPoly.CheckCollision(otherPoly);

		selfPoly.m_vertices = otherPoly.m_vertices = nullptr;

		return intersection;

	}

	bool AABBCollider2D::CheckCollision(const CircleCollider2D& _other) const
	{
		Vector2 minVertex = GetMin(), maxVertex = GetMax();


		Vector2		closestPoint
		{
			Max(minVertex.GetX(), Min(_other.GetPosition().GetX(), maxVertex.GetX())),
			Max(minVertex.GetY(), Min(_other.GetPosition().GetY(), maxVertex.GetY()))
		};

		Vector2		distance = closestPoint - _other.GetPosition();


		return distance.MagnitudeSquared() <= _other.GetRadius() * _other.GetRadius();
	}

	bool AABBCollider2D::CheckCollision(const PolygonCollider2D& _other) const
	{
		PolygonCollider2D	selfPoly;

		Vector2		selfVertices[4] =
		{
			GetMax(),
			GetMin(),
			{ m_position.GetX() + m_extents.GetX(), m_position.GetY() - m_extents.GetY()},
			{ m_position.GetX() - m_extents.GetX(), m_position.GetY() + m_extents.GetY()},
		};

		selfPoly.m_vertices = selfVertices;

		selfPoly.m_vertexCount = 4;


		bool		intersection = selfPoly.CheckCollision(_other);

		selfPoly.m_vertices = nullptr;

		return intersection;
	}


	Ray2D::Ray2D(const Vector2& _pos, const Vector2& _dir)
		: m_origin(_pos)
	{
		m_direction = Normalize(_dir);

		// Pre compute direction divisor
		m_inverseDir.X() = (m_direction.GetX() != 0.f) ? 1.f / m_direction.GetX() : 0.f;
		m_inverseDir.Y() = (m_direction.GetY() != 0.f) ? 1.f / m_direction.GetY() : 0.f;
	}


	bool Ray2D::Intersect(const AABBCollider2D& _box, float& _distance) const
	{
		float   maxIntersect = FLT_MAX, minIntersect = -FLT_MAX;

		Vector2 minVertex = _box.GetMin(), maxVertex = _box.GetMax();

		// x plane = 0, y plane = 1, z plane = 2
		for (int axis = 0; axis < 3; ++axis)
		{
			// t1 for x, t3 for y, t5 for z
			float lowIntersect = (minVertex[axis] - m_origin[axis]) * m_inverseDir[axis];

			// t2 for x, t4 for y, t6 for z
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

	PolygonCollider2D::PolygonCollider2D(Vector2 _vertices[], int _count)
		: m_vertexCount(_count)
	{
		if (!m_vertices)
			m_vertices = new Vector2[_count];


		for (int vertex = 0; vertex < _count; ++vertex)
		{
			m_vertices[vertex] = _vertices[vertex];
		}
	}

	PolygonCollider2D::PolygonCollider2D(const PolygonCollider2D& _other)
		: m_vertexCount(_other.m_vertexCount)
	{
		if (_other.m_vertexCount)
			m_vertices = new Vector2[_other.m_vertexCount];

		for (unsigned int vert = 0; vert < _other.m_vertexCount; ++vert)
			m_vertices[vert] = _other.m_vertices[vert];

	}


	PolygonCollider2D::~PolygonCollider2D(void)
	{
		if (m_vertices)
			delete[] m_vertices;
	}


	Vector2& PolygonCollider2D::operator[](int _index)
	{
		return m_vertices[_index];
	}


	Vector2 PolygonCollider2D::operator[](int _index) const
	{
		return m_vertices[_index];
	}



	bool PolygonCollider2D::CheckCollision(const PolygonCollider2D& _other) const
	{
		return SeparatingAxisTheorem(_other);
	}

	void PolygonCollider2D::MinMaxProjection
	(const Vector2& _normal, float& _min, float& _max) const
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

	bool PolygonCollider2D::
		SeparatingAxisTheorem(const PolygonCollider2D& _other) const
	{

		if (!InternalSAT(_other))
			return false;

		if (!_other.InternalSAT(*this))
			return false;

		return true;
	}


	bool PolygonCollider2D::InternalSAT(const PolygonCollider2D& _other) const
	{
		float	min1, max1;
		float   min2, max2;


		for (unsigned int side = 0; side < m_vertexCount; ++side)
		{
			min1 = FLT_MAX, max1 = -FLT_MAX;
			min2 = FLT_MAX, max2 = -FLT_MAX;

			Vector2		normal;

			if (0 == side)
				normal = (m_vertices[side] - m_vertices[m_vertexCount - 1]).Normal();

			else
				normal = (m_vertices[side] - m_vertices[side - 1]).Normal();

			MinMaxProjection(normal, min1, max1);
			_other.MinMaxProjection(normal, min2, max2);

			if (min2 > max1 || min1 > max2)
				return false;
		}

		return true;
	}
}