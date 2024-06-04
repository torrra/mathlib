#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_FORCE_SILENT_WARNINGS
#define GLM_FORCE_XYZW_ONLY

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>


#include "libmath/Intersection3D.h"

#include <iostream>

TEST_CASE("Intersection3D", "[all][intersection]")
{
	SECTION("AABB")
	{
		mth::AABBCollider3D		controlAABB({ 4.f, 6.f, 1.f }, { 1.f, 3.f, 2.f });

		// Constructor / destructor
		{
			mth::AABBCollider3D		discard;
			mth::AABBCollider3D		copy = controlAABB;


			mth::Vector3			position{ 4.f, 6.f, 1.f }, extents{ 1.f, 3.f, 2.f };

			// Accessor
			CHECK(copy.GetMax() == controlAABB.GetPosition() + controlAABB.GetExtents());
			CHECK(copy.GetMin() == controlAABB.GetPosition() - controlAABB.GetExtents());

			CHECK(copy.GetPosition() == position);
			CHECK(copy.Position() == position);

			CHECK(copy.Extents() == extents);
			CHECK(copy.GetExtents() == extents);
		}

		SECTION("AABB / AABB")
		{

			mth::AABBCollider3D		noCollide({ 10.f, 8.f, 10.f }, { 1.f, 3.f, 1.f });
			mth::AABBCollider3D		collide({ 3.f, 7.f ,2.f }, { 3.1f, 1.f, 4.f });


			// Should not collide
			CHECK_FALSE(controlAABB.CheckCollision(noCollide));
			CHECK_FALSE(controlAABB.CheckCollision(mth::AABBCollider3D()));


			// Should collide with itself
			CHECK(controlAABB.CheckCollision(controlAABB));

			// Should collide
			CHECK(collide.CheckCollision(controlAABB));
		}

		SECTION("AABB / Sphere")
		{
			mth::SphereCollider3D	noCollide({ 3.1f, 15.f, 15.f }, 3.f);
			mth::SphereCollider3D	collide({ 4.3f, 1.f, 2.f }, 10.f);


			CHECK_FALSE(controlAABB.CheckCollision(noCollide));
			CHECK_FALSE(controlAABB.CheckCollision(mth::SphereCollider3D()));

			CHECK(controlAABB.CheckCollision(collide));
		}

	}


	SECTION("Sphere")
	{
		mth::SphereCollider3D	controlSphere({ 4.f, 6.f, 1.f }, 3.f);

		SECTION("Instanciation and accessors")
		{
			mth::SphereCollider3D		discard;
			mth::SphereCollider3D		copy = controlSphere;

			mth::Vector3				position{ 4.f, 6.f, 1.f };
			float						radius = 3.f;

			// Accessor
			CHECK(copy.GetPosition() == position);
			CHECK(copy.Position() == position);

			CHECK(copy.Radius() == radius);
			CHECK(copy.GetRadius() == radius);
		}

		SECTION("Sphere vs AABB")
		{
			mth::AABBCollider3D		noCollide({ 10.f, 8.f, 10.f }, { 1.f, 3.f, 1.f });
			mth::AABBCollider3D		collide({ 3.f, 7.f, 2.f }, { 3.1f, 2.f, 3.f });

			// Should not collide
			CHECK_FALSE(controlSphere.CheckCollision(noCollide));

			// Should collide
			CHECK(controlSphere.CheckCollision(collide));

			mth::AABBCollider3D		aabbThree({ 5.f, 8.f, 2.f }, { 3.5f, 3.75f, 1.f });


			CHECK(controlSphere.CheckCollision(aabbThree));

		}


		SECTION("Sphere vs Sphere")
		{
			mth::SphereCollider3D	noCollide({ 3.1f, 15.f, 10.f }, 3.f);
			mth::SphereCollider3D	collide({ 4.3f, 1.f, 2.f }, 10.f);


			CHECK_FALSE(controlSphere.CheckCollision(noCollide));
			CHECK_FALSE(controlSphere.CheckCollision(mth::SphereCollider3D()));

			CHECK(controlSphere.CheckCollision(collide));
		}
	}

	SECTION("RAY")
	{
		mth::Ray3D	ray({ 4.f, 3.f, 2.f }, { 2.f, 3.f, 2.f });

		SECTION("Instanciation and accessors")
		{
			mth::Ray3D	copy = ray;

			mth::Vector3	origin{ 4.f, 3.f, 2.f }, direction = mth::Normalize({ 2.f, 3.f, 2.f }),
				invDir{ 1.f / direction.X(), 1.f / direction.Y(), 1.f / direction.Z() };

			CHECK(copy.Direction() == direction);
			CHECK(copy.Origin() == origin);
			CHECK(copy.GetInverseDir() == (invDir));
		}

		SECTION("Ray vs AABB")
		{
			mth::AABBCollider3D		noCollision({ -4.f, -5.f, -15.f }, { 1.f, 1.f, 1.f });
			mth::AABBCollider3D		collision({ 6.f, 5.f, 4.f }, { 2.f, 3.f, 4.f });
			float					distance = FLT_MAX;

			CHECK_FALSE(ray.Intersect(noCollision, distance));

			CHECK(distance == FLT_MAX);


			CHECK(ray.Intersect(collision, distance));

			CHECK(distance != FLT_MAX);

		}
	}

}