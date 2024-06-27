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
		ion::math::AABBCollider2D		controlAABB({ 4.f, 6.f }, { 1.f, 3.f });

		// Constructor / destructor
		{
			[[maybe_unused]]
			ion::math::AABBCollider2D		discard;
			ion::math::AABBCollider2D		copy = controlAABB;


			ion::math::Vector2<float>			position{ 4.f, 6.f }, extents{ 1.f, 3.f};

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

			ion::math::AABBCollider2D		noCollide({ 10.f, 8.f }, { 1.f, 2.f });
			ion::math::AABBCollider2D		collide({ 2.f, 7.f }, { 2.1f, 1.f });


			// Should not collide
			CHECK_FALSE(controlAABB.CheckCollision(noCollide));
			CHECK_FALSE(controlAABB.CheckCollision(ion::math::AABBCollider2D()));


			// Should collide with itself
			CHECK(controlAABB.CheckCollision(controlAABB));

			// Should collide
			CHECK(collide.CheckCollision(controlAABB));
		}

		SECTION("AABB / OBB")
		{
			ion::math::OBBCollider2D		noCollide({ 10.f, 8.f }, { 1.f, 2.f }, ion::math::Radian(0.f));
			ion::math::OBBCollider2D		collide({ 2.f, 7.f }, { 2.1f, 1.f }, ion::math::Radian(0.f));

			// Should not collide
			CHECK_FALSE(controlAABB.CheckCollision(noCollide));

			// Should collide
			CHECK(controlAABB.CheckCollision(collide));

			ion::math::OBBCollider2D		obbThree({5.f, 8.f }, {3.5f, 2.75f}, ion::math::Radian(100.f * DEG2RAD));


			CHECK(controlAABB.CheckCollision(obbThree));

			obbThree.Position() = { 0.f, 0.f };

			CHECK_FALSE(controlAABB.CheckCollision(obbThree));

		}

		SECTION("AABB / Circle")
		{
			ion::math::CircleCollider2D	noCollide({ 2.1f, 15.f }, 2.f);
			ion::math::CircleCollider2D	collide({ 4.2f, 1.f }, 10.f);


			CHECK_FALSE(controlAABB.CheckCollision(noCollide));
			CHECK_FALSE(controlAABB.CheckCollision(ion::math::CircleCollider2D()));

			CHECK(controlAABB.CheckCollision(collide));
		}

		SECTION("AABB / Polygon")
		{
			ion::math::Vector2<float> noColVertices[3] =
			{
				{0.f, 0.f},
				{4.5f, 4.f},
				{1.3f, 5.3f}
			};

			ion::math::Vector2<float>	collideVertices[3] =
			{
				{16.f, 8.f},
				{16.f, 4.f},
				{20.f, 6.f}
			};

			controlAABB.Position() = { 16.f, 4.f };
			controlAABB.Extents() = { 1.f, 1.f };

			ion::math::PolygonCollider2D		noCollide(noColVertices, 3);
			ion::math::PolygonCollider2D		collide(collideVertices, 3);


			CHECK_FALSE(controlAABB.CheckCollision(noCollide));

			CHECK(controlAABB.CheckCollision(collide));
		}

	}

	SECTION("OBB")
	{
		ion::math::OBBCollider2D		controlOBB
		(
			{ 4.f, 6.f }, { 1.f, 3.f }, ion::math::Radian(100.f * DEG2RAD)
		);

		SECTION("Instanciation and accessors")
		{

			ion::math::OBBCollider2D		discard;
			ion::math::OBBCollider2D		copy = controlOBB;

			ion::math::Vector2<float>			position{ 4.f, 6.f }, extents{ 1.f, 3.f};

			ion::math::Vector2<float>			rotated = ion::math::Rotate
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
			ion::math::OBBCollider2D 	noCollide
			(
				{0.f, 0.f}, {2.f, 1.f}, ion::math::Radian(0.f)
			);

			ion::math::OBBCollider2D 	collide
			(
				{3.f, 6.f}, {5.f, 4.f}, ion::math::Radian(0.f)
			);

			CHECK_FALSE(controlOBB.CheckCollision(noCollide));
			CHECK(controlOBB.CheckCollision(collide));
		}


		SECTION("OBB vs AABB")
		{
			ion::math::AABBCollider2D		noCollide({ 10.f, 8.f }, { 1.f, 2.f });
			ion::math::AABBCollider2D		collide({ 2.f, 7.f }, { 2.1f, 1.f });

			// Should not collide
			CHECK_FALSE(controlOBB.CheckCollision(noCollide));

			// Should collide
			CHECK(controlOBB.CheckCollision(collide));

			ion::math::AABBCollider2D		aabbThree({5.f, 8.f }, {3.5f, 2.75f});


			CHECK(controlOBB.CheckCollision(aabbThree));

			aabbThree.Position() = { 0.f, 0.f };

			CHECK_FALSE(controlOBB.CheckCollision(aabbThree));
		}

		SECTION("OBB vs Circle")
		{
			ion::math::CircleCollider2D	noCollide({ 2.1f, 15.f }, 2.f);
			ion::math::CircleCollider2D	collide({ 4.2f, 1.f }, 10.f);


			CHECK_FALSE(controlOBB.CheckCollision(noCollide));
			CHECK_FALSE(controlOBB.CheckCollision(ion::math::CircleCollider2D()));

			CHECK(controlOBB.CheckCollision(collide));
		}


		SECTION("OBB vs Polygon")
		{
			ion::math::Vector2<float> noColVertices[3] =
			{
				{0.f, 0.f},
				{4.5f, 4.f},
				{1.3f, 5.3f}
			};

			ion::math::Vector2<float>	collideVertices[3] =
			{
				{16.f, 8.f},
				{16.f, 4.f},
				{20.f, 6.f}
			};

			controlOBB.Position() = { 16.f, 4.f };
			controlOBB.Extents() = { 1.f, 1.f };

			ion::math::PolygonCollider2D		noCollide(noColVertices, 3);
			ion::math::PolygonCollider2D		collide(collideVertices, 3);


			CHECK_FALSE(controlOBB.CheckCollision(noCollide));

			CHECK(controlOBB.CheckCollision(collide));
		}

	}

	SECTION("CIRCLE")
	{
		ion::math::CircleCollider2D	controlCircle({ 4.f, 6.f }, 3.f );

		SECTION("Instanciation and accessors")
		{
			ion::math::CircleCollider2D		discard;
			ion::math::CircleCollider2D		copy = controlCircle;

			ion::math::Vector2<float>				position{ 4.f, 6.f };
			float						radius = 3.f;

			// Accessor
			CHECK(copy.GetPosition() == position);
			CHECK(copy.Position() == position);

			CHECK(copy.Radius() == radius);
			CHECK(copy.GetRadius() == radius);
		}

		SECTION("Circle vs AABB")
		{
			ion::math::AABBCollider2D		noCollide({ 10.f, 8.f }, { 1.f, 2.f });
			ion::math::AABBCollider2D		collide({ 2.f, 7.f }, { 2.1f, 1.f });

			// Should not collide
			CHECK_FALSE(controlCircle.CheckCollision(noCollide));

			// Should collide
			CHECK(controlCircle.CheckCollision(collide));

			ion::math::AABBCollider2D		aabbThree({ 5.f, 8.f }, { 3.5f, 2.75f });


			CHECK(controlCircle.CheckCollision(aabbThree));

			aabbThree.Position() = { 0.f, 0.f };

			CHECK_FALSE(controlCircle.CheckCollision(aabbThree));
		}


		SECTION("Circle vs Circle")
		{
			ion::math::CircleCollider2D	noCollide({ 2.1f, 15.f }, 2.f);
			ion::math::CircleCollider2D	collide({ 4.2f, 1.f }, 10.f);


			CHECK_FALSE(controlCircle.CheckCollision(noCollide));
			CHECK_FALSE(controlCircle.CheckCollision(ion::math::CircleCollider2D()));

			CHECK(controlCircle.CheckCollision(collide));
		}
	}

	SECTION("RAY")
	{
		ion::math::Ray2D	ray({4.f, 2.f}, {2.f, 3.f});

		SECTION("Instanciation and accessors")
		{
			ion::math::Ray2D	copy = ray;

			ion::math::Vector2<float>	origin{4.f, 2.f}, direction = ion::math::Normalize<float>({ 2.f, 3.f }),
							invDir{ 1.f / direction.X(), 1.f / direction.Y() };

			CHECK(copy.Direction() == direction);
			CHECK(copy.Origin() == origin);
			CHECK(copy.GetInverseDir() == (invDir));
		}

		SECTION("Ray vs AABB")
		{
			ion::math::AABBCollider2D		noCollision({ -4.f, -5.f }, { 1.f, 1.f });
			ion::math::AABBCollider2D		collision({ 6.f, 5.f }, { 3.f, 2.f });
			float					distance = FLT_MAX;

			CHECK_FALSE(ray.Intersect(noCollision, distance));

			CHECK(distance == FLT_MAX);


			CHECK(ray.Intersect(collision, distance));

			CHECK(distance != FLT_MAX);

		}
	}


	SECTION("LINE SEGMENT")
	{
		ion::math::Line2D		lineTrue({-3.f, 3.f}, {11.f, 2.f});
		ion::math::Line2D		lineFalse({-8.64f, 2.23f}, {-6.28f, -6.93f});

		SECTION("Line vs circle")
		{

			ion::math::CircleCollider2D	circle({ 4.2f, 1.f }, 10.f);

			CHECK(lineTrue.Intersect(circle));

			CHECK_FALSE(lineFalse.Intersect(circle));
		}

		SECTION("Line vs AABB")
		{
			ion::math::AABBCollider2D		aabb({ 4.2f, 1.f }, { 10.f, 10.f });

			CHECK(lineTrue.Intersect(aabb));

			CHECK_FALSE(lineFalse.Intersect(aabb));
		}
	}


	SECTION("Point 2D")
	{
		ion::math::Point2D	pointTrue{ 1.f, 1.5f };
		ion::math::Point2D	pointFalse{ -5.f, 7.5f };

		SECTION("Point vs AABB")
		{
			ion::math::AABBCollider2D		aabb({ 2.f, 2.f }, { 2.f, 2.f });

			CHECK(aabb.PointInBox(pointTrue));

			CHECK_FALSE(aabb.PointInBox(pointFalse));

		}

		SECTION("Point vs Circle")
		{
			ion::math::CircleCollider2D	circle{ { 2.f, 2.f }, 2.f };

			CHECK(circle.PointInCircle(pointTrue));

			CHECK_FALSE(circle.PointInCircle(pointFalse));
		}
	}

}