#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_FORCE_SILENT_WARNINGS
#define GLM_FORCE_XYZW_ONLY

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>


#include "math/Intersection2D.h"

#include <iostream>

TEST_CASE("Intersection2D", "[all][intersection]")
{
	SECTION("AABB")
	{
		math::AABBCollider2D		controlAABB({ 4.f, 6.f }, { 1.f, 3.f });

		// Constructor / destructor
		{
			[[maybe_unused]]
			math::AABBCollider2D		discard;
			math::AABBCollider2D		copy = controlAABB;


			math::Vector2<float>			position{ 4.f, 6.f }, extents{ 1.f, 3.f};

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

			math::AABBCollider2D		noCollide({ 10.f, 8.f }, { 1.f, 2.f });
			math::AABBCollider2D		collide({ 2.f, 7.f }, { 2.1f, 1.f });


			// Should not collide
			CHECK_FALSE(controlAABB.CheckCollision(noCollide));
			CHECK_FALSE(controlAABB.CheckCollision(math::AABBCollider2D()));


			// Should collide with itself
			CHECK(controlAABB.CheckCollision(controlAABB));

			// Should collide
			CHECK(collide.CheckCollision(controlAABB));
		}

		SECTION("AABB / OBB")
		{
			math::OBBCollider2D		noCollide({ 10.f, 8.f }, { 1.f, 2.f }, math::Radian(0.f));
			math::OBBCollider2D		collide({ 2.f, 7.f }, { 2.1f, 1.f }, math::Radian(0.f));

			// Should not collide
			CHECK_FALSE(controlAABB.CheckCollision(noCollide));

			// Should collide
			CHECK(controlAABB.CheckCollision(collide));

			math::OBBCollider2D		obbThree({5.f, 8.f }, {3.5f, 2.75f}, math::Radian(100.f * DEG2RAD));


			CHECK(controlAABB.CheckCollision(obbThree));

			obbThree.Position() = { 0.f, 0.f };

			CHECK_FALSE(controlAABB.CheckCollision(obbThree));

		}

		SECTION("AABB / Circle")
		{
			math::CircleCollider2D	noCollide({ 2.1f, 15.f }, 2.f);
			math::CircleCollider2D	collide({ 4.2f, 1.f }, 10.f);


			CHECK_FALSE(controlAABB.CheckCollision(noCollide));
			CHECK_FALSE(controlAABB.CheckCollision(math::CircleCollider2D()));

			CHECK(controlAABB.CheckCollision(collide));
		}

		SECTION("AABB / Polygon")
		{
			math::Vector2<float> noColVertices[3] =
			{
				{0.f, 0.f},
				{4.5f, 4.f},
				{1.3f, 5.3f}
			};

			math::Vector2<float>	collideVertices[3] =
			{
				{16.f, 8.f},
				{16.f, 4.f},
				{20.f, 6.f}
			};

			controlAABB.Position() = { 16.f, 4.f };
			controlAABB.Extents() = { 1.f, 1.f };

			math::PolygonCollider2D		noCollide(noColVertices, 3);
			math::PolygonCollider2D		collide(collideVertices, 3);


			CHECK_FALSE(controlAABB.CheckCollision(noCollide));

			CHECK(controlAABB.CheckCollision(collide));
		}

	}

	SECTION("OBB")
	{
		math::OBBCollider2D		controlOBB
		(
			{ 4.f, 6.f }, { 1.f, 3.f }, math::Radian(100.f * DEG2RAD)
		);

		SECTION("Instanciation and accessors")
		{

			math::OBBCollider2D		discard;
			math::OBBCollider2D		copy = controlOBB;

			math::Vector2<float>			position{ 4.f, 6.f }, extents{ 1.f, 3.f};

			math::Vector2<float>			rotated = math::Rotate
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
			math::OBBCollider2D 	noCollide
			(
				{0.f, 0.f}, {2.f, 1.f}, math::Radian(0.f)
			);

			math::OBBCollider2D 	collide
			(
				{3.f, 6.f}, {5.f, 4.f}, math::Radian(0.f)
			);

			CHECK_FALSE(controlOBB.CheckCollision(noCollide));
			CHECK(controlOBB.CheckCollision(collide));
		}


		SECTION("OBB vs AABB")
		{
			math::AABBCollider2D		noCollide({ 10.f, 8.f }, { 1.f, 2.f });
			math::AABBCollider2D		collide({ 2.f, 7.f }, { 2.1f, 1.f });

			// Should not collide
			CHECK_FALSE(controlOBB.CheckCollision(noCollide));

			// Should collide
			CHECK(controlOBB.CheckCollision(collide));

			math::AABBCollider2D		aabbThree({5.f, 8.f }, {3.5f, 2.75f});


			CHECK(controlOBB.CheckCollision(aabbThree));

			aabbThree.Position() = { 0.f, 0.f };

			CHECK_FALSE(controlOBB.CheckCollision(aabbThree));
		}

		SECTION("OBB vs Circle")
		{
			math::CircleCollider2D	noCollide({ 2.1f, 15.f }, 2.f);
			math::CircleCollider2D	collide({ 4.2f, 1.f }, 10.f);


			CHECK_FALSE(controlOBB.CheckCollision(noCollide));
			CHECK_FALSE(controlOBB.CheckCollision(math::CircleCollider2D()));

			CHECK(controlOBB.CheckCollision(collide));
		}


		SECTION("OBB vs Polygon")
		{
			math::Vector2<float> noColVertices[3] =
			{
				{0.f, 0.f},
				{4.5f, 4.f},
				{1.3f, 5.3f}
			};

			math::Vector2<float>	collideVertices[3] =
			{
				{16.f, 8.f},
				{16.f, 4.f},
				{20.f, 6.f}
			};

			controlOBB.Position() = { 16.f, 4.f };
			controlOBB.Extents() = { 1.f, 1.f };

			math::PolygonCollider2D		noCollide(noColVertices, 3);
			math::PolygonCollider2D		collide(collideVertices, 3);


			CHECK_FALSE(controlOBB.CheckCollision(noCollide));

			CHECK(controlOBB.CheckCollision(collide));
		}

	}

	SECTION("CIRCLE")
	{
		math::CircleCollider2D	controlCircle({ 4.f, 6.f }, 3.f );

		SECTION("Instanciation and accessors")
		{
			math::CircleCollider2D		discard;
			math::CircleCollider2D		copy = controlCircle;

			math::Vector2<float>				position{ 4.f, 6.f };
			float						radius = 3.f;

			// Accessor
			CHECK(copy.GetPosition() == position);
			CHECK(copy.Position() == position);

			CHECK(copy.Radius() == radius);
			CHECK(copy.GetRadius() == radius);
		}

		SECTION("Circle vs AABB")
		{
			math::AABBCollider2D		noCollide({ 10.f, 8.f }, { 1.f, 2.f });
			math::AABBCollider2D		collide({ 2.f, 7.f }, { 2.1f, 1.f });

			// Should not collide
			CHECK_FALSE(controlCircle.CheckCollision(noCollide));

			// Should collide
			CHECK(controlCircle.CheckCollision(collide));

			math::AABBCollider2D		aabbThree({ 5.f, 8.f }, { 3.5f, 2.75f });


			CHECK(controlCircle.CheckCollision(aabbThree));

			aabbThree.Position() = { 0.f, 0.f };

			CHECK_FALSE(controlCircle.CheckCollision(aabbThree));
		}


		SECTION("Circle vs Circle")
		{
			math::CircleCollider2D	noCollide({ 2.1f, 15.f }, 2.f);
			math::CircleCollider2D	collide({ 4.2f, 1.f }, 10.f);


			CHECK_FALSE(controlCircle.CheckCollision(noCollide));
			CHECK_FALSE(controlCircle.CheckCollision(math::CircleCollider2D()));

			CHECK(controlCircle.CheckCollision(collide));
		}
	}

	SECTION("RAY")
	{
		math::Ray2D	ray({4.f, 2.f}, {2.f, 3.f});

		SECTION("Instanciation and accessors")
		{
			math::Ray2D	copy = ray;

			math::Vector2<float>	origin{4.f, 2.f}, direction = math::Normalize<float>({ 2.f, 3.f }),
							invDir{ 1.f / direction.X(), 1.f / direction.Y() };

			CHECK(copy.Direction() == direction);
			CHECK(copy.Origin() == origin);
			CHECK(copy.GetInverseDir() == (invDir));
		}

		SECTION("Ray vs AABB")
		{
			math::AABBCollider2D		noCollision({ -4.f, -5.f }, { 1.f, 1.f });
			math::AABBCollider2D		collision({ 6.f, 5.f }, { 3.f, 2.f });
			float					distance = FLT_MAX;

			CHECK_FALSE(ray.Intersect(noCollision, distance));

			CHECK(distance == FLT_MAX);


			CHECK(ray.Intersect(collision, distance));

			CHECK(distance != FLT_MAX);

		}
	}


	SECTION("LINE SEGMENT")
	{
		math::Line2D		lineTrue({-3.f, 3.f}, {11.f, 2.f});
		math::Line2D		lineFalse({-8.64f, 2.23f}, {-6.28f, -6.93f});

		SECTION("Line vs circle")
		{

			math::CircleCollider2D	circle({ 4.2f, 1.f }, 10.f);

			CHECK(lineTrue.Intersect(circle));

			CHECK_FALSE(lineFalse.Intersect(circle));
		}

		SECTION("Line vs AABB")
		{
			math::AABBCollider2D		aabb({ 4.2f, 1.f }, { 10.f, 10.f });

			CHECK(lineTrue.Intersect(aabb));

			CHECK_FALSE(lineFalse.Intersect(aabb));
		}
	}


	SECTION("Point 2D")
	{
		math::Point2D	pointTrue{ 1.f, 1.5f };
		math::Point2D	pointFalse{ -5.f, 7.5f };

		SECTION("Point vs AABB")
		{
			math::AABBCollider2D		aabb({ 2.f, 2.f }, { 2.f, 2.f });

			CHECK(aabb.PointInBox(pointTrue));

			CHECK_FALSE(aabb.PointInBox(pointFalse));

		}

		SECTION("Point vs Circle")
		{
			math::CircleCollider2D	circle{ { 2.f, 2.f }, 2.f };

			CHECK(circle.PointInCircle(pointTrue));

			CHECK_FALSE(circle.PointInCircle(pointFalse));
		}
	}

}