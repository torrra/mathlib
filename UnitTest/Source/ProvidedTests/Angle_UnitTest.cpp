#include <libmath/Angle.h>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

using namespace LibMath::Literal;

TEST_CASE("Degree", "[all][angle]")
{
	SECTION("Instantiation")
	{
		// destructor
		{
			LibMath::Degree temp;
		}

		// default constructor
		LibMath::Degree empty;
		CHECK(empty.Raw() == 0.f);

		// basic constructor
		float value = 60.f;
		LibMath::Degree angle{ value };
		CHECK(angle.Raw() == value);

		// copy constructor
		LibMath::Degree copy{ angle };
		CHECK(copy.Raw() == value);

		// assignment operator
		empty = angle;
		CHECK(empty.Raw() == value);

		LibMath::Degree literal = 60_deg;
		CHECK(literal.Raw() == value);
		literal = 22.5_deg;
		[[maybe_unused]] float f = literal.Raw();
		CHECK(literal.Raw() == 22.5f);


		CHECK(sizeof LibMath::Degree == sizeof(float));
	}

	SECTION("Accessor")
	{
		{
			// 0 value
			LibMath::Degree zeroDegree;
			CHECK(zeroDegree.Deg(true) == 0.f);
			CHECK(zeroDegree.Deg(false) == 0.f);
			CHECK(zeroDegree.Rad(true) == 0.f);
			CHECK(zeroDegree.Rad(false) == 0.f);
		}

		{
			// no change value
			LibMath::Degree sixtyDegree{ 60.f };
			CHECK(sixtyDegree.Deg(true) == 60.f);
			CHECK(sixtyDegree.Deg(false) == 60.f);
			CHECK(sixtyDegree.Rad(true) == Catch::Approx(glm::radians(60.f)));
			CHECK(sixtyDegree.Rad(false) == Catch::Approx(glm::radians(60.f)));
		}

		{
			// wrap when true value
			LibMath::Degree threeHundredDegree{ 300.f };
			CHECK(threeHundredDegree.Deg(true) == -60.f);
			CHECK(threeHundredDegree.Deg(false) == 300.f);
			CHECK(threeHundredDegree.Rad(true) == Catch::Approx(glm::radians(-60.f)));
			CHECK(threeHundredDegree.Rad(false) == Catch::Approx(glm::radians(300.f)));
		}

		{
			// wrap when false value
			LibMath::Degree minusSixtyDegree{ -60.f };
			CHECK(minusSixtyDegree.Deg(true) == -60.f);
			CHECK(minusSixtyDegree.Deg(false) == 300.f);
			CHECK(minusSixtyDegree.Rad(true) == Catch::Approx(glm::radians(-60.f)));
			CHECK(minusSixtyDegree.Rad(false) == Catch::Approx(glm::radians(300.f)));
		}

		{
			// positive wrap value
			LibMath::Degree oneThousandDegree{ 1000.f };
			CHECK(oneThousandDegree.Deg(true) == -80.f);
			CHECK(oneThousandDegree.Deg(false) == 280.f);
			CHECK(oneThousandDegree.Rad(true) == Catch::Approx(glm::radians(-80.f)));
			CHECK(oneThousandDegree.Rad(false) == Catch::Approx(glm::radians(280.f)));
		}

		{
			// negative wrap value
			LibMath::Degree minusOneThousandDegree{ -1000.f };
			CHECK(minusOneThousandDegree.Deg(true) == 80.f);
			CHECK(minusOneThousandDegree.Deg(false) == 80.f);
			CHECK(minusOneThousandDegree.Rad(true) == Catch::Approx(glm::radians(80.f)));
			CHECK(minusOneThousandDegree.Rad(false) == Catch::Approx(glm::radians(80.f)));
		}
	}

	SECTION("Comparator")
	{
		// compare with self
		LibMath::Degree self{ 60.f };
		CHECK(self == self);

		// compare with same
		CHECK(LibMath::Degree{ 60.f } == LibMath::Degree{ 60.f });

		// compare with wrapped value
		CHECK(LibMath::Degree{ 90.f } == LibMath::Degree(450.f));

		// compare with wrap edge value
		CHECK(LibMath::Degree{ 0.f } == LibMath::Degree{ 360.f });
		CHECK(LibMath::Degree{ -180.f } == LibMath::Degree{ 180.f });
	}

	SECTION("Arithmetic")
	{
		{
			// operator +
			LibMath::Degree sum = LibMath::Degree(45.f) + LibMath::Degree(30.f);
			CHECK(sum.Deg() == 75.f);
		}

		{
			// operator +=
			LibMath::Degree sum(45.f);
			sum += LibMath::Degree(30.f);
			CHECK(sum.Deg() == 75.f);
		}

		{
			// operator -
			LibMath::Degree opposite = -LibMath::Degree(45.f);
			CHECK(opposite.Deg() == 315.f);
		}

		{
			// operator -
			LibMath::Degree difference = LibMath::Degree(45.f) - LibMath::Degree(30.f);
			CHECK(difference.Deg() == 15.f);
		}

		{
			// operator -=
			LibMath::Degree difference(45.f);
			difference -= LibMath::Degree(30.f);
			CHECK(difference.Deg() == 15.f);
		}

		{
			// operator *
			LibMath::Degree product = LibMath::Degree(45.f) * 10.f;
			CHECK(product.Deg() == 90.f);
		}

		{
			// operator *=
			LibMath::Degree product(45.f);
			product *= 10.f;
			CHECK(product.Deg() == 90.f);
		}

		{
			// operator /
			LibMath::Degree quotient = LibMath::Degree(45.f) / 5.f;
			CHECK(quotient.Deg() == 9.f);
		}

		{
			// operator /=
			LibMath::Degree quotient(45.f);
			quotient /= 5.f;
			CHECK(quotient.Deg() == 9.f);
		}
	}

	SECTION("Functionality")
	{
		{
			// wrap value
			LibMath::Degree wrapAngle{ 900.f };
			wrapAngle.Wrap(false);
			CHECK(wrapAngle.Raw() == 180.f);
		}

		{
			// prefere lower edge value
			LibMath::Degree wrapEdge{ 360.f };
			wrapEdge.Wrap(false);
			CHECK(wrapEdge.Raw() == 0.f);

			wrapEdge = LibMath::Degree{ 900.f };
			wrapEdge.Wrap(true);
			CHECK(wrapEdge.Raw() == -180.f);
		}
	}
}

TEST_CASE("Radian", "[all][angle]")
{
	constexpr float halfRadianCircle = glm::pi<float>();
	constexpr float radianCircle = glm::two_pi<float>();

	SECTION("Instantiation")
	{
		// destructor
		{
			LibMath::Radian temp;
		}

		// default constructor
		LibMath::Radian empty;
		CHECK(empty.Raw() == 0.f);

		// basic constructor
		float value = 1.2f;
		LibMath::Radian angle{ value };
		CHECK(angle.Raw() == value);

		// copy constructor
		LibMath::Radian copy{ angle };
		CHECK(copy.Raw() == value);

		// assignment operator
		empty = angle;
		CHECK(empty.Raw() == value);

		LibMath::Radian literal = 1.2_rad;
		CHECK(literal.Raw() == value);
		literal = 1_rad;
		CHECK(literal.Raw() == 1.f);

		CHECK(sizeof LibMath::Radian == sizeof(float));
	}

	SECTION("Accessor")
	{
		{
			// 0 value
			LibMath::Radian zeroRadian;
			CHECK(zeroRadian.Deg(true) == 0.f);
			CHECK(zeroRadian.Deg(false) == 0.f);
			CHECK(zeroRadian.Rad(true) == 0.f);
			CHECK(zeroRadian.Rad(false) == 0.f);
		}

		{
			// no change value
			LibMath::Radian oneRadian{ 1.2f };
			CHECK(oneRadian.Deg(true) == Catch::Approx(glm::degrees(1.2f)));
			CHECK(oneRadian.Deg(false) == Catch::Approx(glm::degrees(1.2f)));
			CHECK(oneRadian.Rad(true) == 1.2f);
			CHECK(oneRadian.Rad(false) == 1.2f);
		}

		{
			// wrap when true value
			const/*expr*/ float wrapRadian = 5.8f - radianCircle;

			LibMath::Radian sixRadian{ 5.8f };
			CHECK(sixRadian.Deg(true) == Catch::Approx(glm::degrees(wrapRadian)));
			CHECK(sixRadian.Deg(false) == Catch::Approx(glm::degrees(5.8f)));
			CHECK(sixRadian.Rad(true) == Catch::Approx(wrapRadian));
			CHECK(sixRadian.Rad(false) == 5.8f);
		}

		{
			// wrap when false value
			const/*expr*/ float wrapRadian = radianCircle - 1.2f;

			LibMath::Radian minusOneRadian{ -1.2f };
			CHECK(minusOneRadian.Deg(true) == Catch::Approx(glm::degrees(-1.2f)));
			CHECK(minusOneRadian.Deg(false) == Catch::Approx(glm::degrees(wrapRadian)));
			CHECK(minusOneRadian.Rad(true) == -1.2f);
			CHECK(minusOneRadian.Rad(false) == Catch::Approx(wrapRadian));
		}

		{
			// positive wrap value
			const/*expr*/ float radian = 15.f - 2.f * radianCircle;

			LibMath::Radian fifteenRadian{ 15.f };
			CHECK(fifteenRadian.Deg(true) == Catch::Approx(glm::degrees(radian)));
			CHECK(fifteenRadian.Deg(false) == Catch::Approx(glm::degrees(radian)));
			CHECK(fifteenRadian.Rad(true) == Catch::Approx(radian));
			CHECK(fifteenRadian.Rad(false) == Catch::Approx(radian));
		}

		{
			// negative wrap value
			const/*expr*/ float radian = -15.f + 3.f * radianCircle;
			const/*expr*/ float wrapRadian = -15.f + 2.f * radianCircle;

			LibMath::Radian minusFifteenRadian{ -15.f };
			CHECK(minusFifteenRadian.Deg(true) == Catch::Approx(glm::degrees(wrapRadian)));
			CHECK(minusFifteenRadian.Deg(false) == Catch::Approx(glm::degrees(radian)));
			CHECK(minusFifteenRadian.Rad(true) == Catch::Approx(wrapRadian));
			CHECK(minusFifteenRadian.Rad(false) == Catch::Approx(radian));
		}
	}

	SECTION("Comparator")
	{
		// compare with self
		LibMath::Radian self{ 1.2f };
		CHECK(self == self);

		// compare with same
		CHECK(LibMath::Radian{ 1.2f } == LibMath::Radian{ 1.2f });

		// compare with wrapped value
		CHECK(LibMath::Radian{ 1.2f } == LibMath::Radian(1.2f + radianCircle));

		// compare with wrap edge value
		CHECK(LibMath::Radian{ 0.f } == LibMath::Radian{ radianCircle });

		CHECK(LibMath::Radian{ -halfRadianCircle } == LibMath::Radian{ halfRadianCircle });
	}

	SECTION("Arithmetic")
	{
		{
			// operator +
			LibMath::Radian sum = LibMath::Radian(0.75f) + LibMath::Radian(0.5f);
			CHECK(sum.Rad() == 1.25f);
		}

		{
			// operator +=
			LibMath::Radian sum(0.75f);
			sum += LibMath::Radian(0.5f);
			CHECK(sum.Rad() == 1.25f);
		}

		{
			// operator -
			LibMath::Radian opposite = -LibMath::Radian(0.75f);
			CHECK(opposite.Rad() == -0.75f);
		}

		{
			// operator -
			LibMath::Radian difference = LibMath::Radian(0.75f) - LibMath::Radian(0.5f);
			CHECK(difference.Rad() == 0.25f);
		}

		{
			// operator -=
			LibMath::Radian difference(0.75f);
			difference -= LibMath::Radian(0.5f);
			CHECK(difference.Rad() == 0.25f);
		}

		{
			// operator *
			LibMath::Radian product = LibMath::Radian(0.75f) * 10.f;
			CHECK(product.Rad() == 7.5f - radianCircle);
		}

		{
			// operator *=
			LibMath::Radian product(0.75f);
			product *= 10.f;
			CHECK(product.Rad() == 7.5f - radianCircle);
		}

		{
			// operator /
			LibMath::Radian quotient = LibMath::Radian(0.75f) / 4.f;
			CHECK(quotient.Rad() == 0.1875f);
		}

		{
			// operator /=
			LibMath::Radian quotient(0.75f);
			quotient /= 4.f;
			CHECK(quotient.Rad() == 0.1875f);
		}
	}

	SECTION("Functionality")
	{
		{
			// wrap value
			LibMath::Radian wrapAngle{ halfRadianCircle * 5.f };
			wrapAngle.Wrap(false);
			CHECK(wrapAngle.Raw() == Catch::Approx(halfRadianCircle));
		}

		{
			// prefer lower edge value
			LibMath::Radian wrapEdge{ radianCircle };
			wrapEdge.Wrap(false);
			CHECK(wrapEdge.Raw() == 0.f);

			wrapEdge = LibMath::Radian{ halfRadianCircle };
			wrapEdge.Wrap(true);
			CHECK(wrapEdge.Raw() == Catch::Approx(-halfRadianCircle));
		}
	}

	SECTION("Conversion")
	{
		LibMath::Radian radian{ LibMath::Degree{ 60.f } };
		CHECK(radian.Raw() == Catch::Approx(glm::radians(60.f)));

		LibMath::Degree degree{ LibMath::Radian{ 1.2f } };
		CHECK(degree.Raw() == Catch::Approx(glm::degrees(1.2f)));
	}
}
