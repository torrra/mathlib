#include "math/Intersection3D.h"
#include "math/Trigonometry.hpp"


#ifndef  FLT_MAX
#include <cfloat>
#endif // ! FLT_MAX


namespace math
{


	AABBCollider3D::AABBCollider3D(const Vector3f& pos, const Vector3f& size)
		: m_position(pos), m_extents(size)
	{

	}


	Vector3f& AABBCollider3D::Position(void)
	{
		return m_position;
	}

	Vector3f& AABBCollider3D::Extents(void)
	{
		return m_extents;
	}

	Vector3f AABBCollider3D::GetPosition(void) const
	{
		return m_position;
	}

	Vector3f AABBCollider3D::GetExtents(void) const
	{
		return m_extents;
	}

	bool AABBCollider3D::CheckCollision(const AABBCollider3D& other) const
	{
		Vector3f		selfMin = GetMin(),
					selfMax = GetMax();

		Vector3f		otherMin = other.GetMin(),
					otherMax = other.GetMax();

		// Check min and max vertices on each axis to look for a gap

		if (selfMax[0] < otherMin[0] || selfMin[0] > otherMax[0])
			return false;

		if (selfMax[1] < otherMin[1] || selfMin[1] > otherMax[1])
			return false;

		if (selfMax[2] < otherMin[2] || selfMin[2] > otherMax[2])
			return false;


		return true;
	}



	bool AABBCollider3D::CheckCollision(const SphereCollider3D& other) const
	{
		Vector3f minVertex = GetMin(), maxVertex = GetMax();

		// Get closest point
		Vector3f		closestPoint
		{
			Max(minVertex.GetX(), Min(other.GetPosition().GetX(), maxVertex.GetX())),
			Max(minVertex.GetY(), Min(other.GetPosition().GetY(), maxVertex.GetY())),
			Max(minVertex.GetZ(), Min(other.GetPosition().GetZ(), maxVertex.GetZ()))
		};

		Vector3f		distance = closestPoint - other.GetPosition();

		// Point closer than end of radius = intersection
		return distance.MagnitudeSquared() <= other.GetRadius() * other.GetRadius();
	}

	bool AABBCollider3D::PointInBox(const Vector3f& point) const
	{
		Vector3f		min = GetMin(), max = GetMax();

		// Check if point is within AABB bounds

		if (point.GetX() < min.GetX() || point.GetX() > max.GetX())
			return false;

		if (point.GetY() < min.GetY() || point.GetY() > max.GetY())
			return false;

		if (point.GetZ() < min.GetZ() || point.GetZ() > max.GetZ())
			return false;

		return true;
	}




	Ray3D::Ray3D(const Vector3f& pos, const Vector3f& dir)
		: m_origin(pos)
	{
		m_direction = Normalize(dir);

		// Pre compute direction divisor
		m_inverseDir.X() = (m_direction.GetX() != 0.f) ? 1.f / m_direction.GetX() : 0.f;
		m_inverseDir.Y() = (m_direction.GetY() != 0.f) ? 1.f / m_direction.GetY() : 0.f;
		m_inverseDir.Z() = (m_direction.GetZ() != 0.f) ? 1.f / m_direction.GetZ() : 0.f;
	}


	bool Ray3D::Intersect(const AABBCollider3D& box, float& distance) const
	{
		float   maxIntersect = FLT_MAX, minIntersect = -FLT_MAX;

		Vector3f minVertex = box.GetMin(), maxVertex = box.GetMax();

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
			distance = minIntersect;

		// Return intersection status
		return intersection;
	}

	bool Ray3D::Intersect(const SphereCollider3D& sphere, float& distance) const
	{
		Vector3f		sphereToOrigin = GetOrigin() - sphere.GetPosition();

		float		quadraticA = m_direction.MagnitudeSquared();

		float		quadraticB = 2.f * sphereToOrigin.Dot(m_direction);

		float		quadraticC = sphereToOrigin.MagnitudeSquared() -
								sphere.GetRadiusSquared();

		// delta = b^2 * 4ac
		float		quadraticDelta = quadraticB * quadraticB -
					4.f * quadraticA * quadraticC;

		if (quadraticDelta < 0.f)
			return false;

		distance = (-quadraticB * SquareRoot(quadraticDelta)) / (2.f * quadraticA);

		return true;

	}

    Vector3f &Ray3D::Origin(void)
    {
       return m_origin;
    }

    Vector3f &Ray3D::Direction(void)
    {
        return m_direction;
    }

    Vector3f Ray3D::GetOrigin(void) const
    {
        return m_origin;
    }

    Vector3f Ray3D::GetDirection(void) const
    {
        return m_direction;
    }

    Vector3f Ray3D::GetInverseDir(void) const
    {
        return m_inverseDir;
    }



	Vector3f AABBCollider3D::GetMin(void) const
	{
		return m_position - m_extents;
	}


	Vector3f AABBCollider3D::GetMax(void) const
	{
		return m_position + m_extents;
	}


	Vector3f OBBCollider3D::GetMin(void) const
	{
		// Rotate BEFORE translating
		Vector3f		rotated = Rotate
		(
			m_extents, m_rotation[0],
			m_rotation[1], m_rotation[2]
		);

		return m_position - rotated;
	}

	Vector3f OBBCollider3D::GetMax(void) const
	{
		// Rotate BEFORE translating
		Vector3f		rotated = Rotate
		(
			m_extents, m_rotation[0],
			m_rotation[1], m_rotation[2]
		);

		return rotated + m_position;
	}


	OBBCollider3D::OBBCollider3D
	(const Vector3f& pos, const Vector3f& extents,
	 Radian<float> angleX, Radian<float> angleY, Radian<float> angleZ)
		: m_position(pos), m_extents(extents)
	{
		m_rotation[0] = angleX;
		m_rotation[1] = angleY;
		m_rotation[2] = angleZ;
	}

	Radian<float>& OBBCollider3D::RotationX(void)
	{
		return m_rotation[0];
	}

	Radian<float>& OBBCollider3D::RotationY(void)
	{
		return m_rotation[1];
	}

	Radian<float>& OBBCollider3D::RotationZ(void)
	{
		return m_rotation[2];
	}

	Radian<float> OBBCollider3D::GetRotationX(void) const
	{
		return m_rotation[0];
	}

	Radian<float> OBBCollider3D::GetRotationY(void) const
	{
		return m_rotation[1];
	}

	Radian<float> OBBCollider3D::GetRotationZ(void) const
	{
		return m_rotation[2];
	}


	Vector3f& OBBCollider3D::Position(void)
	{
		return m_position;
	}

	Vector3f& OBBCollider3D::Extents(void)
	{
		return m_extents;
	}

	Matrix3f OBBCollider3D::RotationMatrix(void) const
	{
		// Store sines and cosines
		float		cosYaw = Cos(m_rotation[2]),
					sinYaw = Sin(m_rotation[2]);

		float		cosPitch = Cos(m_rotation[0]),
					sinPitch = Sin(m_rotation[0]);

		float		cosRoll = Cos(m_rotation[1]),
					sinRoll = Sin(m_rotation[1]);

		// Create rotation matrix
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

		return Matrix3f(rotation);
	}


	Vector3f OBBCollider3D::GetPosition(void) const
	{
		return m_position;
	}

	Vector3f OBBCollider3D::GetExtents(void) const
	{
		return m_extents;
	}


	Vector3f& SphereCollider3D::Position(void)
	{
		return m_position;
	}

	float& SphereCollider3D::Radius(void)
	{
		return m_radius;
	}

	Vector3f SphereCollider3D::GetPosition(void) const
	{
		return m_position;
	}

	float SphereCollider3D::GetRadius(void) const
	{
		return m_radius;
	}

	float SphereCollider3D::GetRadiusSquared(void) const
	{
		return m_radius * m_radius;
	}

	SphereCollider3D::SphereCollider3D(const Vector3f& pos, float radius)
		: m_position(pos), m_radius(radius)
	{
	}


	bool SphereCollider3D::CheckCollision(const AABBCollider3D& other) const
	{
		return other.CheckCollision(*this);
	}



	bool SphereCollider3D::CheckCollision(const SphereCollider3D& other) const
	{
		float		distance = DistanceSquared(m_position, other.m_position);

		return distance <= (m_radius * m_radius) + (other.m_radius * other.m_radius);
	}

	bool SphereCollider3D::PointInSphere(const Vector3f& point) const
	{
		Vector3f		distance = point - m_position;

		return distance.MagnitudeSquared() <= m_radius * m_radius;
	}

	Line3D::Line3D(const Vector3f& start, const Vector3f& end)
		: m_start(start), m_end(end)
	{
	}

	Vector3f& Line3D::Start(void)
	{
		return m_start;
	}

	Vector3f& Line3D::End(void)
	{
		return m_end;
	}

	Vector3f Line3D::GetStart(void) const
	{
		return m_start;
	}

	Vector3f Line3D::GetEnd(void) const
	{
		return m_end;
	}

	bool Line3D::Intersect(const AABBCollider3D& box) const
	{
		// Use huge value (likely smaller than line length)
		// that can be safely squared without causing
		// 32-bit overflow
		float 		distanceToBox = 1e10f;

		Vector3f		direction = m_end - m_start;

		// Turn segment into ray to use already defined raycast algorithm
		Ray3D		lineRay(m_start, direction);

		// If no intersection or intersection is further than line length,
		// no line intsersection occurs
		if (!lineRay.Intersect(box, distanceToBox) ||
			distanceToBox * distanceToBox > direction.MagnitudeSquared())
			return false;

		return true;
	}

	bool Line3D::Intersect(const SphereCollider3D& sphere) const
	{
		Vector3f		circleToLineStart = m_start - sphere.GetPosition();
		Vector3f		lineDirection = m_end - m_start;

		// Compute b^2
		float		quadraticDelta = (2.f * lineDirection.Dot(circleToLineStart));

		quadraticDelta *= quadraticDelta;

		// Find 4ac
		float		tmpQuadratic = 4.f * lineDirection.MagnitudeSquared() *
			(circleToLineStart.MagnitudeSquared() -
				sphere.GetRadiusSquared());

		// delta = b^2 - 4ac
		quadraticDelta -= tmpQuadratic;

		if (quadraticDelta < 0.f)
			return false;


		return true;
	}

	float Line3D::Length(void) const
	{
		// Distance from start to end
		return (m_end - m_start).Magnitude();
	}

	float Line3D::LengthSquared(void) const
	{
		// Distance from start to end squared
		return (m_end - m_start).MagnitudeSquared();
	}



}