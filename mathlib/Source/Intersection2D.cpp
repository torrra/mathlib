#include "math/Intersection2D.h"


#ifndef  FLT_MAX
#include <cfloat>
#endif // ! FLT_MAX


namespace math
{


	AABBCollider2D::AABBCollider2D(const Vector2f& pos, const Vector2f& size)
		: m_position(pos), m_extents(size)
	{

	}


	Vector2f& AABBCollider2D::Position(void)
	{
		return m_position;
	}

	Vector2f& AABBCollider2D::Extents(void)
	{
		return m_extents;
	}

	Vector2f AABBCollider2D::GetPosition(void) const
	{
		return m_position;
	}

	Vector2f AABBCollider2D::GetExtents(void) const
	{
		return m_extents;
	}

	bool AABBCollider2D::CheckCollision(const AABBCollider2D& other) const
	{
		Vector2f		selfMin = GetMin(),
					selfMax = GetMax();

		Vector2f		otherMin = other.GetMin(),
					otherMax = other.GetMax();


		// Check min and max vertices on each axis to look for a gap

		if (selfMax[0] < otherMin[0] || selfMin[0] > otherMax[0])
			return false;

		if (selfMax[1] < otherMin[1] || selfMin[1] > otherMax[1])
			return false;

		return true;
	}

	bool AABBCollider2D::CheckCollision(const OBBCollider2D& other) const
	{
		// Turn this object and other into polygon colliders
		PolygonCollider2D    selfPoly, otherPoly;

		// Get AABB vertices
		Vector2f				 selfVertices[4] =
		{
			GetMax(),
			GetMin(),

			{
			  m_position.GetX() + m_extents.GetX(),
			  m_position.GetY() - m_extents.GetY()
			},

			{
				m_position.GetX() - m_extents.GetX(),
				m_position.GetY() + m_extents.GetY()
			},
		};

		Vector2f				otherRotated =
		Rotate(other.GetExtents(), other.GetRotation());

		// Get OBB rotated vertices
		Vector2f				otherVertices[4] =
		{
			other.GetPosition() + otherRotated,
			other.GetPosition() - otherRotated,

			other.GetPosition() + Rotate
			(
				{other.GetExtents().X(), -other.GetExtents().Y()},
				 other.GetRotation()
			),

			other.GetPosition() + Rotate
			(
				{-other.GetExtents().X(), other.GetExtents().Y()},
				 other.GetRotation()
			),
		};

		// Use stack array to avoid heap alloc/free
		selfPoly.m_vertices = selfVertices;
		otherPoly.m_vertices = otherVertices;

		selfPoly.m_vertexCount = otherPoly.m_vertexCount = 4;

		// Run SAT algorithm on nea
		bool		intersection = selfPoly.CheckCollision(otherPoly);

		// Avoid attempt to free stack (polygon destructor) by
		// setting pointers to nullptr
		selfPoly.m_vertices = otherPoly.m_vertices = nullptr;

		return intersection;

	}

	bool AABBCollider2D::CheckCollision(const CircleCollider2D& other) const
	{
		Vector2f		minVertex = GetMin(), maxVertex = GetMax();

		// Get closest point
		Vector2f		closestPoint
		{
			Max(minVertex.GetX(), Min(other.GetPosition().GetX(), maxVertex.GetX())),
			Max(minVertex.GetY(), Min(other.GetPosition().GetY(), maxVertex.GetY()))
		};

		Vector2f		distance = closestPoint - other.GetPosition();

		// Point closer than end of radius = intersection
		return distance.MagnitudeSquared() <= other.GetRadiusSquared();
	}

	bool AABBCollider2D::CheckCollision(const PolygonCollider2D& other) const
	{
		// Turn AABB into polygon collider
		PolygonCollider2D	selfPoly;

		// Get AABB vertices
		Vector2f				selfVertices[4] =
		{
			GetMax(),
			GetMin(),
			{ m_position.GetX() + m_extents.GetX(), m_position.GetY() - m_extents.GetY()},
			{ m_position.GetX() - m_extents.GetX(), m_position.GetY() + m_extents.GetY()},
		};

		selfPoly.m_vertices = selfVertices;

		selfPoly.m_vertexCount = 4;

		// Run SAT algorithm
		bool		intersection = selfPoly.CheckCollision(other);

		selfPoly.m_vertices = nullptr;

		return intersection;
	}

	bool AABBCollider2D::PointInBox(const Vector2f& point) const
	{
		Vector2f		min = GetMin(), max = GetMax();

		// Check if point is within AABB bounds

		if (point.GetX() < min.GetX() || point.GetX() > max.GetX())
			return false;

		if (point.GetY() < min.GetY() || point.GetY() > max.GetY())
			return false;

		return true;
	}


	Ray2D::Ray2D(const Vector2f& pos, const Vector2f& dir)
		: m_origin(pos)
	{
		m_direction = Normalize(dir);

		// Pre compute direction divisor
		m_inverseDir.X() = (m_direction.GetX() != 0.f) ?
		1.f / m_direction.GetX() : 0.f;


		m_inverseDir.Y() = (m_direction.GetY() != 0.f) ?
		1.f / m_direction.GetY() : 0.f;
	}


	bool Ray2D::Intersect(const AABBCollider2D& box, float& distance) const
	{
		float   maxIntersect = FLT_MAX, minIntersect = -FLT_MAX;

		Vector2f minVertex = box.GetMin(), maxVertex = box.GetMax();

		// x plane = 0, y plane = 1, z plane = 2
		for (int axis = 0; axis < 2; ++axis)
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
			distance = minIntersect;

		// Return intersection status
		return intersection;
	}

    Vector2f &Ray2D::Origin(void)
    {
       return m_origin;
    }

    Vector2f &Ray2D::Direction(void)
    {
        return m_direction;
    }

    Vector2f Ray2D::GetOrigin(void) const
    {
        return m_origin;
    }

    Vector2f Ray2D::GetDirection(void) const
    {
        return m_direction;
    }

    Vector2f Ray2D::GetInverseDir(void) const
    {
        return m_inverseDir;
    }

    PolygonCollider2D::PolygonCollider2D(Vector2f vertices[], int count)
        : m_vertexCount(count)
    {
		// Allocate space for vertices
		if (!m_vertices)
			m_vertices = new Vector2f[count];


		for (int vertex = 0; vertex < count; ++vertex)
		{
			// Copy vertices into heap array
			m_vertices[vertex] = vertices[vertex];
		}
	}

	PolygonCollider2D::PolygonCollider2D(const PolygonCollider2D& other)
		: m_vertexCount(other.m_vertexCount)
	{
		// Allocate vertices for deep copy
		if (other.m_vertexCount)
			m_vertices = new Vector2f[other.m_vertexCount];

		// Copy vertices into new array
		for (unsigned int vert = 0; vert < other.m_vertexCount; ++vert)
			m_vertices[vert] = other.m_vertices[vert];

	}


	PolygonCollider2D::~PolygonCollider2D(void)
	{
		if (m_vertices)
			delete[] m_vertices;
	}


	Vector2f& PolygonCollider2D::operator[](int index)
	{
		return m_vertices[index];
	}


	Vector2f PolygonCollider2D::operator[](int index) const
	{
		return m_vertices[index];
	}



	bool PolygonCollider2D::CheckCollision(const PolygonCollider2D& other) const
	{
		return SeparatingAxisTheorem(other);
	}

	void PolygonCollider2D::MinMaxProjection
	(const Vector2f& normal, float& min, float& max) const
	{
		// Find min and max projections by testing each vertex against normal
		for (unsigned int vertex = 0; vertex < m_vertexCount; ++vertex)
		{
			float	projection = Round(normal.Dot(m_vertices[vertex]));

			if (projection < min)
				min = projection;

			else if (projection > max)
				max = projection;
		}
	}

	bool PolygonCollider2D::
		SeparatingAxisTheorem(const PolygonCollider2D& other) const
	{
		// Check all of this polygon's axes for a gap
		if (!InternalSAT(other))
			return false;

		// Check all the other polygon's axes if no gap was previously found
		if (!other.InternalSAT(*this))
			return false;

		return true;
	}


	bool PolygonCollider2D::InternalSAT(const PolygonCollider2D& other) const
	{
		float	min1, max1;
		float   min2, max2;

		// Get every normal
		for (unsigned int side = 0; side < m_vertexCount; ++side)
		{
			min1 = FLT_MAX, max1 = -FLT_MAX;
			min2 = FLT_MAX, max2 = -FLT_MAX;

			Vector2f		normal;

			if (0 == side)
				normal = (m_vertices[side] - m_vertices[m_vertexCount - 1])
						  .Normal();

			else
				normal = (m_vertices[side] - m_vertices[side - 1]).Normal();

			// Find min and max projections onot normal for both polygons
			MinMaxProjection(normal, min1, max1);
			other.MinMaxProjection(normal, min2, max2);

			if (min2 > max1 || min1 > max2)
				return false;
		}

		return true;
	}

	bool PolygonCollider2D::CheckCollision(const AABBCollider2D& other) const
	{
		// Use already defined AABB vs polygon check
		return other.CheckCollision(*this);
	}

	bool PolygonCollider2D::CheckCollision(const OBBCollider2D& other) const
	{
		// Use already define OBB vs polygon check
		return other.CheckCollision(*this);
	}



	Vector2f AABBCollider2D::GetMin(void) const
	{
		return m_position - m_extents;
	}


	Vector2f AABBCollider2D::GetMax(void) const
	{
		return m_position + m_extents;
	}


	Vector2f OBBCollider2D::GetMin(void) const
	{
		// Rotate BEFORE translating
		Vector2f		rotated = Rotate(m_extents, m_rotation);

		return m_position - rotated;
	}

	Vector2f OBBCollider2D::GetMax(void) const
	{
		// Rotate BEFORE translating
		Vector2f		rotated = Rotate(m_extents, m_rotation);

		return rotated + m_position;
	}


	OBBCollider2D::OBBCollider2D
	(const Vector2f& pos, const Vector2f& extents, Radian<float> angle)
		: m_position(pos), m_extents(extents), m_rotation(angle)
	{
	}

	bool OBBCollider2D::CheckCollision(const AABBCollider2D& other) const
	{
		// Use already defined AABB vs OBB check
		return other.CheckCollision(*this);
	}


	Vector2f& OBBCollider2D::Position(void)
	{
		return m_position;
	}

	Vector2f& OBBCollider2D::Extents(void)
	{
		return m_extents;
	}

	Radian<float>& OBBCollider2D::Rotation(void)
	{
		return m_rotation;
	}

	Vector2f OBBCollider2D::GetPosition(void) const
	{
		return m_position;
	}

	Vector2f OBBCollider2D::GetExtents(void) const
	{
		return m_extents;
	}

	Radian<float> OBBCollider2D::GetRotation(void) const
	{
		return m_rotation;
	}


	bool OBBCollider2D::CheckCollision(const OBBCollider2D& other) const
	{
		// Turn both OBBs into polygons
		PolygonCollider2D	selfPoly, otherPoly;

		Vector2f				selfRotated = Rotate(m_extents, m_rotation);
		Vector2f				otherRotated = Rotate(other.m_extents,
												  other.m_rotation);

		// Rotate vertices
		Vector2f				selfVertices[4] =
		{
			m_position + selfRotated,
			m_position - selfRotated,
			m_position + Rotate
			(
				{ m_extents.GetX(), -m_extents.GetY() },
				  m_rotation
			),
			m_position + Rotate
			(
				{ -m_extents.GetX(), m_extents.GetY() },
				  m_rotation
			),
		};

		// Rotate vertices
		Vector2f				otherVertices[4] =
		{
			other.GetPosition() + otherRotated,
			other.GetPosition() - otherRotated,

			other.GetPosition() + Rotate
			(
				{other.GetExtents().X(), -other.GetExtents().Y()},
				 other.GetRotation()
			),

			other.GetPosition() + Rotate
			(
				{-other.GetExtents().X(), other.GetExtents().Y()},
				 other.GetRotation()
			),
		};

		// Use stack instead of heap
		selfPoly.m_vertices = selfVertices;
		otherPoly.m_vertices = otherVertices;

		selfPoly.m_vertexCount = otherPoly.m_vertexCount = 4;

		// Run SAT
		bool		intersection = selfPoly.CheckCollision(otherPoly);

		// Avoid attempt to free stack
		selfPoly.m_vertices = otherPoly.m_vertices = nullptr;

		return intersection;
	}

	bool OBBCollider2D::CheckCollision(const CircleCollider2D& other) const
	{
		Vector2f		 minVertex = GetMin(), maxVertex = GetMax();

		Vector2f		closestPoint
		{
			Max(minVertex.GetX(), Min(other.GetPosition().GetX(), maxVertex.GetX())),
			Max(minVertex.GetY(), Min(other.GetPosition().GetY(), maxVertex.GetY()))
		};

		// Check if closest point is within the circle's range

		Vector2f		distance = closestPoint - other.GetPosition();


		return distance.MagnitudeSquared() <= other.GetRadiusSquared();
	}

	bool OBBCollider2D::CheckCollision(const PolygonCollider2D& other) const
	{
		// Turn OBB into polygon collider
		PolygonCollider2D	selfPoly;

		Vector2f				selfRotated = Rotate(m_extents, m_rotation);

		Vector2f				selfVertices[4] =
		{
			m_position + selfRotated,
			m_position - selfRotated,
			m_position + Rotate
			(
				{ m_extents.GetX(), -m_extents.GetY() },
				  m_rotation
			),
			m_position + Rotate
			(
				{ -m_extents.GetX(), m_extents.GetY() },
				  m_rotation
			),
		};

		// Use stack array instead of heap
		selfPoly.m_vertices = selfVertices;

		selfPoly.m_vertexCount = 4;

		// Run SAT
		bool	intersection = selfPoly.CheckCollision(other);

		// Avoid attempt to free stack in destructor
		selfPoly.m_vertices = nullptr;

		return intersection;
	}

	Vector2f& CircleCollider2D::Position(void)
	{
		return m_position;
	}

	float& CircleCollider2D::Radius(void)
	{
		return m_radius;
	}

	Vector2f CircleCollider2D::GetPosition(void) const
	{
		return m_position;
	}

	float CircleCollider2D::GetRadius(void) const
	{
		return m_radius;
	}

	float CircleCollider2D::GetRadiusSquared(void) const
	{
		return m_radius * m_radius;
	}

	CircleCollider2D::CircleCollider2D(const Vector2f& pos, float radius)
		: m_position(pos), m_radius(radius)
	{
	}


	bool CircleCollider2D::CheckCollision(const AABBCollider2D& other) const
	{
		// Use already defined AABB vs circle check
		return other.CheckCollision(*this);
	}

	bool CircleCollider2D::CheckCollision(const OBBCollider2D& other) const
	{
		// Use already defined OBB vs circle cleck
		return other.CheckCollision(*this);
	}

	bool CircleCollider2D::CheckCollision(const CircleCollider2D& other) const
	{
		// Check if distance between two circles is shorter than their radii
		float		distance = DistanceSquared(m_position, other.m_position);

		// Use square instead of square root for speed
		return distance <= GetRadiusSquared() + other.GetRadiusSquared();
	}

	bool CircleCollider2D::PointInCircle(const Vector2f& point) const
	{
		Vector2f		distance = point - m_position;

		// Check if distance is shorter than circle radius
		return distance.MagnitudeSquared() <= m_radius * m_radius;
	}

	Line2D::Line2D(const Vector2f& start, const Vector2f& end)
		: m_start(start), m_end(end)
	{
	}

    Vector2f &Line2D::Start(void)
    {
       return m_start;
    }

    Vector2f &Line2D::End(void)
    {
        return m_end;
    }

    Vector2f Line2D::GetStart(void) const
    {
        return m_start;
    }

    Vector2f Line2D::GetEnd(void) const
    {
        return m_end;
    }

    bool Line2D::Intersect(const AABBCollider2D& box) const
    {
		// Use huge value (likely smaller than line length)
		// that can be safely squared without causing
		// 32-bit overflow
		float 		distanceToBox = 1e10f;


		Vector2f		direction = m_end - m_start;

		// Turn segment into ray to use already defined raycast algorithm
		Ray2D		lineRay(m_start, direction);

		// If no intersection or intersection is further than line length,
		// no line intsersection occurs
		if(!lineRay.Intersect(box, distanceToBox) ||
			distanceToBox * distanceToBox > direction.MagnitudeSquared())
		{
			return false;
		}

		return true;
    }

    bool Line2D::Intersect(const CircleCollider2D& circle) const
    {
		// Apply quadratic formula to find whether there is an intersection

		Vector2f		circleToLineStart = m_start - circle.GetPosition();
		Vector2f		lineDirection = m_end - m_start;

		// Compute b^2
		float		quadraticDelta =
		(2.f * lineDirection.Dot(circleToLineStart));

		quadraticDelta *= quadraticDelta;

		// Find 4ac
		float		tmpQuadratic = 4.f * lineDirection.MagnitudeSquared() *
					(circleToLineStart.MagnitudeSquared() -
					circle.GetRadiusSquared());

		// delta = b^2 - 4ac
		quadraticDelta -= tmpQuadratic;

		// No intersection if unable to compute square root of delta
		// (delta is negative)
		if (quadraticDelta < 0.f)
			return false;


        return true;
    }

    float Line2D::Length(void) const
    {
		// Distance from start to end
        return (m_end - m_start).Magnitude();
    }

    float Line2D::LengthSquared(void) const
    {
		// Distance from start to end squared
       return (m_end - m_start).MagnitudeSquared();
    }
}