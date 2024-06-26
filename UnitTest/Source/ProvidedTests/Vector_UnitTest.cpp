#include <iostream>
#include <sstream>

#include <libmath/Vector3.h>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_FORCE_SILENT_WARNINGS
#define GLM_FORCE_XYZW_ONLY

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/projection.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>

using namespace LibMath::Literal;

#define CHECK_VECTOR3(vector, vectorGlm)\
CHECK(vector[0] == Catch::Approx(vectorGlm[0]));\
CHECK(vector[1] == Catch::Approx(vectorGlm[1]));\
CHECK(vector[2] == Catch::Approx(vectorGlm[2]))

TEST_CASE("Vector3", "[all][vector][Vector3]")
{
	SECTION("Instantiation")
	{
		// destructor
		{
			[[maybe_unused]]
			LibMath::Vector3 temp;
		}

		// default constructor
		LibMath::Vector3 empty{};
		glm::vec3 emptyGlm{};
		CHECK_VECTOR3(empty, emptyGlm);

		// basic constructor
		LibMath::Vector3 oneParam{ 2.5f };
		glm::vec3 oneParamGlm{ 2.5f };
		CHECK_VECTOR3(oneParam, oneParamGlm);

		LibMath::Vector3 allParam{ 2.5f, .5f, 2.f };
		glm::vec3 allParamGlm{ 2.5f, .5f, 2.f };
		CHECK_VECTOR3(allParam, allParamGlm);

		// copy constructor
		LibMath::Vector3 copy{ allParam };
		glm::vec3 copyGlm{ allParamGlm };
		CHECK_VECTOR3(copy, copyGlm);

		// assignment operator
		empty = allParam;
		emptyGlm = allParamGlm;
		CHECK_VECTOR3(empty, emptyGlm);

		// OpenGL compatibility
		CHECK(sizeof(LibMath::Vector3<float>) == sizeof(glm::vec3));
		CHECK(memcmp(&allParam, &allParamGlm, sizeof(LibMath::Vector3<float>)) == 0);
	}

	SECTION("Accessor")
	{
		float const x = 2.5f;
		float const y = .5f;
		float const z = 2.f;
		LibMath::Vector3 vector{ x, y, z };

		{
			LibMath::Vector3<float> const& vectorConst = vector;
			CHECK(vectorConst[0] == x);
			CHECK(vectorConst[1] == y);
			CHECK(vectorConst[2] == z);
		}

		{
			vector[0] += 1.f;
			vector[1] += 1.f;
			vector[2] += 1.f;
			CHECK(vector[0] == x + 1.f);
			CHECK(vector[1] == y + 1.f);
			CHECK(vector[2] == z + 1.f);
		}
	}

	SECTION("Comparator")
	{
		// compare with self
		LibMath::Vector3 self{ 2.5f, .5f, 2.f };
		CHECK(self == self);
		CHECK_FALSE(self != self);

		// compare with same
		CHECK(LibMath::Vector3{ 2.5f, .5f, 2.f } == LibMath::Vector3{ 2.5f, .5f, 2.f });
		CHECK(LibMath::Vector3{ 2.5f, .5f, 2.f } != LibMath::Vector3{ 6.f, .25f, -2.f });

		// trying to find copy/paste mistake
		LibMath::Vector3 twos{ 2.f, 2.f, 2.f };
		CHECK_FALSE(LibMath::Vector3{ .5f, 2.f, 2.f } == twos);
		CHECK_FALSE(LibMath::Vector3{ 2.f, .5f, 2.f } == twos);
		CHECK_FALSE(LibMath::Vector3{ 2.f, 2.f, .5f } == twos);
		CHECK(LibMath::Vector3{ .5f, 2.f, 2.f } != twos);
		CHECK(LibMath::Vector3{ 2.f, .5f, 2.f } != twos);
		CHECK(LibMath::Vector3{ 2.f, 2.f, .5f } != twos);
		CHECK_FALSE(twos == LibMath::Vector3{ .5f, 2.f, 2.f });
		CHECK_FALSE(twos == LibMath::Vector3{ 2.f, .5f, 2.f });
		CHECK_FALSE(twos == LibMath::Vector3{ 2.f, 2.f, .5f });
		CHECK(twos != LibMath::Vector3{ .5f, 2.f, 2.f });
		CHECK(twos != LibMath::Vector3{ 2.f, .5f, 2.f });
		CHECK(twos != LibMath::Vector3{ 2.f, 2.f, .5f });

		// testing comparaision fonctionnality
		LibMath::Vector3 small{ 2.5f, .5f, 2.f };
		LibMath::Vector3 big{ 3.75f, 3.f, .75f };

		CHECK(big.IsLongerThan(small));
		CHECK_FALSE(small.IsLongerThan(big));

		CHECK(small.IsShorterThan(big));
		CHECK_FALSE(big.IsShorterThan(small));

		CHECK_FALSE(big.IsLongerThan(big));
		CHECK_FALSE(big.IsShorterThan(big));

		CHECK_FALSE(self.IsUnitVector());
		CHECK(LibMath::Vector3{ 0.771516740f, 0.154303357f, 0.617213428f }.IsUnitVector());
	}

	SECTION("Constant")
	{
		CHECK_VECTOR3(LibMath::Vector3<float>::Back(), glm::vec3(0.f, 0.f, -1.f));

		CHECK_VECTOR3(LibMath::Vector3<float>::Down(), glm::vec3(0.f, -1.f, 0.f));

		CHECK_VECTOR3(LibMath::Vector3<float>::Front(), glm::vec3(0.f, 0.f, 1.f));

		CHECK_VECTOR3(LibMath::Vector3<float>::Left(), glm::vec3(-1.f, 0.f, 0.f));

		CHECK_VECTOR3(LibMath::Vector3<float>::One(), glm::vec3(1.f, 1.f, 1.f));

		CHECK_VECTOR3(LibMath::Vector3<float>::Right(), glm::vec3(1.f, 0.f, 0.f));

		CHECK_VECTOR3(LibMath::Vector3<float>::Up(), glm::vec3(0.f, 1.f, 0.f));

		CHECK_VECTOR3(LibMath::Vector3<float>::Zero(), glm::vec3(0.f, 0.f, 0.f));
	}

	SECTION("Arithmetic")
	{
		LibMath::Vector3 const small{ 2.5f, .5f, 2.f };
		LibMath::Vector3 const big{ 3.75f, 3.f, .75f };

		glm::vec3 const smallGlm{ 2.5f, .5f, 2.f };
		glm::vec3 const bigGlm{ 3.75f, 3.f, .75f };

		SECTION("Addition")
		{
			{
				LibMath::Vector3 sumAssignment = big;
				sumAssignment += small;

				glm::vec3 sumAssignmentGlm = bigGlm;
				sumAssignmentGlm += smallGlm;

				CHECK_VECTOR3(sumAssignment, sumAssignmentGlm);
			}

			{
				LibMath::Vector3 sum = big + small;

				glm::vec3 sumGlm = bigGlm + smallGlm;

				CHECK_VECTOR3(sum, sumGlm);
			}
		}

		SECTION("Opposite")
		{
			LibMath::Vector3 opposite = -LibMath::Vector3{ 3.7f, 3.f, .7f };

			glm::vec3 oppositeGlm = -glm::vec3{ 3.7f, 3.f, .7f };

			CHECK_VECTOR3(opposite, oppositeGlm);
		}

		SECTION("Substraction")
		{
			{
				LibMath::Vector3 differenceAssignment = big;
				differenceAssignment -= small;

				glm::vec3 differenceAssignmentGlm = bigGlm;
				differenceAssignmentGlm -= smallGlm;

				CHECK_VECTOR3(differenceAssignment, differenceAssignmentGlm);
			}

			{
				LibMath::Vector3 difference = big - small;

				glm::vec3 differenceGlm = bigGlm - smallGlm;

				CHECK_VECTOR3(difference, differenceGlm);
			}
		}

		SECTION("Multiplication")
		{
			{
				LibMath::Vector3 productAssignment = big;
				productAssignment *= small;

				glm::vec3 productAssignmentGlm = bigGlm;
				productAssignmentGlm *= smallGlm;

				CHECK_VECTOR3(productAssignment, productAssignmentGlm);
			}

			{
				LibMath::Vector3 product = big * small;

				glm::vec3 productGlm = bigGlm * smallGlm;

				CHECK_VECTOR3(product, productGlm);
			}
		}

		SECTION("Division")
		{
			{
				LibMath::Vector3 quotientAssignment = big;
				quotientAssignment /= small;

				glm::vec3 quotientAssignmentGlm = bigGlm;
				quotientAssignmentGlm /= smallGlm;

				CHECK_VECTOR3(quotientAssignment, quotientAssignmentGlm);
			}

			{
				LibMath::Vector3 quotient = big / small;

				glm::vec3 quotientGlm = bigGlm / smallGlm;

				CHECK_VECTOR3(quotient, quotientGlm);
			}
		}
	}

	SECTION("Transformation")
	{
		LibMath::Vector3 const origin{ 2.5f, .5f, 2.f };
		LibMath::Vector3 const transformation{ -2.f, 0.f, 1.25f };

		glm::vec4 const originGlm{ 2.5f, .5f, 2.f, 1.f };
		glm::vec3 const transformationGlm{ -2.f, 0.f, 1.25f };

		SECTION("Translation")
		{
			LibMath::Vector3 translate = origin;
			translate.Translate(transformation);

			glm::vec4 translateGlm = glm::translate(transformationGlm) * originGlm;

			CHECK_VECTOR3(translate, translateGlm);
		}

		SECTION("Scale")
		{
			LibMath::Vector3 scale = origin;
			scale.Scale(transformation);

			glm::vec4 scaleGlm = glm::scale(transformationGlm) * originGlm;

			CHECK_VECTOR3(scale, scaleGlm);
		}

		SECTION("Rotation")
		{
			SECTION("Euler Angle")
			{
				LibMath::Vector3 rotate = origin;

				LibMath::Vector3 rotateCpy = rotate;
				const glm::vec3 rotationX{ -2.f, 0.f, 0.f };

				rotateCpy.Rotate(LibMath::Radian{ -2.f }, LibMath::Radian{ 0.f }, LibMath::Radian{ 0.f });
				glm::vec4 rotatedX = glm::orientate4(rotationX) * originGlm;


				CHECK_VECTOR3(rotateCpy, rotatedX);


				LibMath::Vector3 rotateCpy2 = rotate;
				const glm::vec3 rotationY{ 0.f, -2.f, 0.f };

				rotateCpy2.Rotate(LibMath::Radian{ 0.f }, LibMath::Radian{ -2.f }, LibMath::Radian{ 0.f });
				glm::vec3 rotatedY = glm::orientate3(rotationY) * originGlm;

				CHECK_VECTOR3(rotateCpy2, rotatedY);

				rotate.Rotate(LibMath::Radian{ transformation.GetX() }, LibMath::Radian{ transformation.GetY() }, LibMath::Radian{ transformation.GetZ() });

				glm::vec4 rotateGlm = glm::orientate4(transformationGlm) * originGlm;

				CHECK_VECTOR3(rotate, rotateGlm);
			}

			SECTION("Axis")
			{
				LibMath::Vector3 rotate = origin;
				rotate.Rotate(-3_rad, transformation);

				glm::vec4 rotateGlm = glm::rotate(-3.f, transformationGlm) * originGlm;

				CHECK_VECTOR3(rotate, rotateGlm);
			}

			SECTION("Quaternion")
			{
				// todo
			}
		}
	}

	SECTION("Functionality")
	{
		LibMath::Vector3 const base{ 2.5f, .5f, 2.f };
		LibMath::Vector3 const other{ 3.75f, 3.f, .75f };

		glm::vec3 const baseGlm{ 2.5f, .5f, 2.f };
		glm::vec3 const otherGlm{ 3.75f, 3.f, .75f };

		SECTION("Angle")
		{
			LibMath::Radian angle = base.AngleFrom(other);

			float angleGlm = glm::angle(glm::normalize(baseGlm), glm::normalize(otherGlm));

			CHECK(angle.Rad() == Catch::Approx(angleGlm));
		}

		SECTION("Cross")
		{
			LibMath::Vector3 cross = base.Cross(other);

			glm::vec3 crossGlm = glm::cross(baseGlm, otherGlm);

			CHECK_VECTOR3(cross, crossGlm);
		}

		SECTION("Dot")
		{
			float dot = base.Dot(other);

			float dotGlm = glm::dot(baseGlm, otherGlm);

			CHECK(dot == dotGlm);
		}

		SECTION("Distance")
		{
			{
				float distance = base.DistanceFrom(other);

				float distanceGlm = glm::distance(baseGlm, otherGlm);

				CHECK(distance == Catch::Approx(distanceGlm));
			}

			{
				float distanceSquare = base.DistanceSquaredFrom(other);

				float distanceSquareGlm = glm::distance2(baseGlm, otherGlm);

				CHECK(distanceSquare == Catch::Approx(distanceSquareGlm));
			}

			{
				float distance2D = base.Distance2DFrom(other);

				float distance2DGlm = glm::distance(glm::vec2(baseGlm), glm::vec2(otherGlm));

				CHECK(distance2D == Catch::Approx(distance2DGlm));
			}

			{
				float distance2DSquare = base.Distance2DSquaredFrom(other);

				float distance2DSquareGlm = glm::distance2(glm::vec2(baseGlm), glm::vec2(otherGlm));

				CHECK(distance2DSquare == Catch::Approx(distance2DSquareGlm));
			}
		}

		SECTION("Magnitude")
		{
			{
				float magnitude = base.Magnitude();

				float magnitudeGlm = glm::length(baseGlm);

				CHECK(magnitude == Catch::Approx(magnitudeGlm));
			}

			{
				float magnitudeSquare = base.MagnitudeSquared();

				float magnitudeSquareGlm = glm::length2(baseGlm);

				CHECK(magnitudeSquare == Catch::Approx(magnitudeSquareGlm));
			}
		}

		SECTION("Normal")
		{
			LibMath::Vector3 normalize = base;
			normalize.Normalize();

			glm::vec3 normalizeGlm = glm::normalize(baseGlm);

			CHECK_VECTOR3(normalize, normalizeGlm);
		}

		SECTION("ProjectOnto")
		{
			LibMath::Vector3 project = base;
			project.ProjectOnto(other);

			glm::vec3 projectGlm = glm::proj(baseGlm, otherGlm);

			CHECK_VECTOR3(project, projectGlm);
		}

		SECTION("ReflectOnto")
		{
			LibMath::Vector3 reflect = base;
			reflect.ReflectOnto(other);

			glm::vec3 reflectGlm = glm::reflect(baseGlm, glm::normalize(otherGlm));

			CHECK_VECTOR3(reflect, reflectGlm);
		}
	}

	SECTION("Extra")
	{
		LibMath::Vector3 const input{ 2.5f, -.5f, 2.f };
		{
			std::stringstream buffer;
			buffer << input;
			CHECK(buffer.str() == "{2.5,-0.5,2}");

			buffer << " extra";

			LibMath::Vector3 output;
			buffer >> output;
			CHECK(output == input);

			// Uncomment to display
			//std::cout << output;

			std::string extra;
			buffer >> extra;
			CHECK(extra == "extra");
		}

		{
			CHECK(input.String() == "{2.5,-0.5,2}");

			CHECK(input.StringLong() == "Vector3{ x:2.5, y:-0.5, z:2 }");
		}
	}

		SECTION(".Debug")
		{
	#if (defined _DEBUG) || (! defined NDEBUG)
			LibMath::Vector3 vector{ 2.5f, .5f, 2.f };
	
			CHECK_THROWS(vector[-1]);
			CHECK_THROWS(vector[3]);
	#endif // DEBUG
		}
}
