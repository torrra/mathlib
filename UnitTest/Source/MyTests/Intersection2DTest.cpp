#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_FORCE_SILENT_WARNINGS
#define GLM_FORCE_XYZW_ONLY

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>


#include "libmath/Intersection2D.h"

#include <iostream>

TEST_CASE("Intersection2D", "[all][intersection]")
{
	SECTION("AABB")
	{
		mth::AABBCollider2D		controlAABB({ 4.f, 6.f }, { 1.f, 3.f });

		// Constructor / destructor
		{
			mth::AABBCollider2D		discard;
			mth::AABBCollider2D		copy = controlAABB;


			mth::Vector2			position{ 4.f, 6.f }, extents{ 1.f, 3.f};

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

			mth::AABBCollider2D		noCollide({ 10.f, 8.f }, { 1.f, 2.f });
			mth::AABBCollider2D		collide({ 2.f, 7.f }, { 2.1f, 1.f });


			// Should not collide
			CHECK_FALSE(controlAABB.CheckCollision(noCollide));
			CHECK_FALSE(controlAABB.CheckCollision(mth::AABBCollider2D()));


			// Should collide with itself
			CHECK(controlAABB.CheckCollision(controlAABB));

			// Should collide
			CHECK(collide.CheckCollision(controlAABB));
		}

		SECTION("AABB / OBB")
		{
			mth::OBBCollider2D		noCollide({ 10.f, 8.f }, { 1.f, 2.f }, mth::Radian(0.f));
			mth::OBBCollider2D		collide({ 2.f, 7.f }, { 2.1f, 1.f }, mth::Radian(0.f));

			// Should not collide
			CHECK_FALSE(controlAABB.CheckCollision(noCollide));

			// Should collide
			CHECK(controlAABB.CheckCollision(collide));

			mth::OBBCollider2D		obbThree({5.f, 8.f }, {3.5f, 2.75f}, mth::Radian(100.f * DEG2RAD));


			CHECK(controlAABB.CheckCollision(obbThree));

			obbThree.Position() = { 0.f, 0.f };

			CHECK_FALSE(controlAABB.CheckCollision(obbThree));

		}

		SECTION("AABB / Circle")
		{
			mth::CircleCollider2D	noCollide({ 2.1f, 15.f }, 2.f);
			mth::CircleCollider2D	collide({ 4.2f, 1.f }, 10.f);


			CHECK_FALSE(controlAABB.CheckCollision(noCollide));
			CHECK_FALSE(controlAABB.CheckCollision(mth::CircleCollider2D()));

			CHECK(controlAABB.CheckCollision(collide));
		}

		SECTION("AABB / Polygon")
		{
			mth::Vector2 noColVertices[3] =
			{
				{0.f, 0.f},
				{4.5f, 4.f},
				{1.3f, 5.3f}
			};

			mth::Vector2	collideVertices[3] =
			{
				{16.f, 8.f},
				{16.f, 4.f},
				{20.f, 6.f}
			};

			controlAABB.Position() = { 16.f, 4.f };
			controlAABB.Extents() = { 1.f, 1.f };

			mth::PolygonCollider2D		noCollide(noColVertices, 3);
			mth::PolygonCollider2D		collide(collideVertices, 3);


			CHECK_FALSE(controlAABB.CheckCollision(noCollide));

			CHECK(controlAABB.CheckCollision(collide));
		}

	}

	SECTION("OBB")
	{
		mth::OBBCollider2D		controlOBB
		(
			{ 4.f, 6.f }, { 1.f, 3.f }, mth::Radian(100.f * DEG2RAD)
		);

		SECTION("Instanciation and accessors")
		{

			mth::OBBCollider2D		discard;
			mth::OBBCollider2D		copy = controlOBB;

			mth::Vector2			position{ 4.f, 6.f }, extents{ 1.f, 3.f};

			mth::Vector2			rotated = mth::Rotate
			(
				controlOBB.GetExtents(),
				controlOBB.GetRotation()
			);

			// Accessor
			CHECK(copy.GetMax() == controlOBB.GetPosition() + rotated);
			CHECK(copy.GetMin() == controlOBB.GetPosition() - rotated);

			CHECK(copy.GetPosition() == position);
			CHECK(copy.Position() == position);

			CHECK(copy.Extents() == extents);
			CHECK(copy.GetExtents() == extents);
		}

		SECTION("OBB / OBB")
		{
			mth::OBBCollider2D 	noCollide
			(
				{0.f, 0.f}, {2.f, 1.f}, mth::Radian(0.f)
			);

			mth::OBBCollider2D 	collide
			(
				{3.f, 6.f}, {5.f, 4.f}, mth::Radian(0.f)
			);

			CHECK_FALSE(controlOBB.CheckCollision(noCollide));
			CHECK(controlOBB.CheckCollision(collide));
		}


		SECTION("OBB vs AABB")
		{
			mth::AABBCollider2D		noCollide({ 10.f, 8.f }, { 1.f, 2.f });
			mth::AABBCollider2D		collide({ 2.f, 7.f }, { 2.1f, 1.f });

			// Should not collide
			CHECK_FALSE(controlOBB.CheckCollision(noCollide));

			// Should collide
			CHECK(controlOBB.CheckCollision(collide));

			mth::AABBCollider2D		aabbThree({5.f, 8.f }, {3.5f, 2.75f});


			CHECK(controlOBB.CheckCollision(aabbThree));

			aabbThree.Position() = { 0.f, 0.f };

			CHECK_FALSE(controlOBB.CheckCollision(aabbThree));
		}

		SECTION("OBB vs Circle")
		{
			mth::CircleCollider2D	noCollide({ 2.1f, 15.f }, 2.f);
			mth::CircleCollider2D	collide({ 4.2f, 1.f }, 10.f);


			CHECK_FALSE(controlOBB.CheckCollision(noCollide));
			CHECK_FALSE(controlOBB.CheckCollision(mth::CircleCollider2D()));

			CHECK(controlOBB.CheckCollision(collide));
		}


		SECTION("OBB vs Polygon")
		{
			mth::Vector2 noColVertices[3] =
			{
				{0.f, 0.f},
				{4.5f, 4.f},
				{1.3f, 5.3f}
			};

			mth::Vector2	collideVertices[3] =
			{
				{16.f, 8.f},
				{16.f, 4.f},
				{20.f, 6.f}
			};

			controlOBB.Position() = { 16.f, 4.f };
			controlOBB.Extents() = { 1.f, 1.f };

			mth::PolygonCollider2D		noCollide(noColVertices, 3);
			mth::PolygonCollider2D		collide(collideVertices, 3);


			CHECK_FALSE(controlOBB.CheckCollision(noCollide));

			CHECK(controlOBB.CheckCollision(collide));
		}

	}

	SECTION("CIRCLE")
	{
		mth::CircleCollider2D	controlCircle({ 4.f, 6.f }, 3.f );

		SECTION("Instanciation and accessors")
		{
			mth::CircleCollider2D		discard;
			mth::CircleCollider2D		copy = controlCircle;

			mth::Vector2				position{ 4.f, 6.f };
			float						radius = 3.f;

			// Accessor
			CHECK(copy.GetPosition() == position);
			CHECK(copy.Position() == position);

			CHECK(copy.Radius() == radius);
			CHECK(copy.GetRadius() == radius);
		}

		SECTION("Circle vs AABB")
		{
			mth::AABBCollider2D		noCollide({ 10.f, 8.f }, { 1.f, 2.f });
			mth::AABBCollider2D		collide({ 2.f, 7.f }, { 2.1f, 1.f });

			// Should not collide
			CHECK_FALSE(controlCircle.CheckCollision(noCollide));

			// Should collide
			CHECK(controlCircle.CheckCollision(collide));

			mth::AABBCollider2D		aabbThree({ 5.f, 8.f }, { 3.5f, 2.75f });


			CHECK(controlCircle.CheckCollision(aabbThree));

			aabbThree.Position() = { 0.f, 0.f };

			CHECK_FALSE(controlCircle.CheckCollision(aabbThree));
		}


		SECTION("Circle vs Circle")
		{
			mth::CircleCollider2D	noCollide({ 2.1f, 15.f }, 2.f);
			mth::CircleCollider2D	collide({ 4.2f, 1.f }, 10.f);


			CHECK_FALSE(controlCircle.CheckCollision(noCollide));
			CHECK_FALSE(controlCircle.CheckCollision(mth::CircleCollider2D()));

			CHECK(controlCircle.CheckCollision(collide));
		}
	}

	SECTION("RAY")
	{
		mth::Ray2D	ray({4.f, 2.f}, {2.f, 3.f});

		SECTION("Instanciation and accessors")
		{
			mth::Ray2D	copy = ray;

			mth::Vector2	origin{4.f, 2.f}, direction = mth::Normalize({ 2.f, 3.f }),
							invDir{ 1.f / direction.X(), 1.f / direction.Y() };

			CHECK(copy.Direction() == direction);
			CHECK(copy.Origin() == origin);
			CHECK(copy.GetInverseDir() == (invDir));
		}

		SECTION("Ray vs AABB")
		{
			mth::AABBCollider2D		noCollision({ -4.f, -5.f }, { 1.f, 1.f });
			mth::AABBCollider2D		collision({ 6.f, 5.f }, { 3.f, 2.f });
			float					distance = FLT_MAX;

			CHECK_FALSE(ray.Intersect(noCollision, distance));

			CHECK(distance == FLT_MAX);


			CHECK(ray.Intersect(collision, distance));

			CHECK(distance != FLT_MAX);

		}
	}

}