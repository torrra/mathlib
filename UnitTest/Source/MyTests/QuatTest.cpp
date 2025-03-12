#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SILENT_WARNINGS
//#define GLM_FORCE_QUAT_DATA_WXYZ
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>

#include "math/Quaternion.hpp"
#include "math/Vector3.hpp"

#include <iostream>


#define CHECK_QUAT(q1, q2)\
CHECK(math::AlmostEqual(q1.GetW(), q2.w));\
CHECK(math::AlmostEqual(q1.GetX(), q2.x));\
CHECK(math::AlmostEqual(q1.GetY(), q2.y));\
CHECK(math::AlmostEqual(q1.GetZ(), q2.z))

#define CHECK_QUAT_EQUAL(q1, q2)\
CHECK(q1.GetW() == Catch::Approx(q2.w));\
CHECK(q1.GetX() == Catch::Approx(q2.x));\
CHECK(q1.GetY() == Catch::Approx(q2.y));\
CHECK(q1.GetZ() == Catch::Approx(q2.z))


#define CHECK_VECTOR3(vector, vectorGlm)\
CHECK(vector[0] == Catch::Approx(vectorGlm[0]));\
CHECK(vector[1] == Catch::Approx(vectorGlm[1]));\
CHECK(vector[2] == Catch::Approx(vectorGlm[2]))

#define CHECK_MATRIX4(matA, matB)\
for (int row = 0; row < 4; ++row)\
{\
	for (int column = 0; column < 4; ++column)\
	{\
		CHECK(matA[row][column] == Catch::Approx(matB[row][column]));\
	}\
}


TEST_CASE("Quaternion", "[all]")
{
	SECTION("Instanciation")
	{
		math::Quaternion<float> quat1(3.5f, 4.f, 5.8f, 5.f);
		math::Quaternion<float> quat2(1.5f, 4.7f, .8f, 56.f);

		glm::f32quat q1(3.5f, 4.f, 5.8f, 5.f);
		glm::f32quat q2(1.5f, 4.7f, .8f, 56.f);

		math::Vector3f vec1(7.5f, 5.6f, 5.f);
		math::Vector3f vec2;
		glm::vec3 v1(7.5f, 5.6f, 5.f);
		glm::vec3 v2;

		math::Quatf res = quat1 * quat2;
		glm::f32quat r = q1 * q2;

		//CHECK_QUAT(res, r);
		CHECK_QUAT_EQUAL(quat1, q1);
		CHECK_QUAT_EQUAL(res, r);
		CHECK_QUAT_EQUAL(quat1.Inverse(), glm::inverse(q1));
		CHECK_QUAT_EQUAL(quat1.Conjugate(), glm::conjugate(q1));


		//CHECK_VECTOR3(quat1.RotateVector(vec1), glm::)

		math::Matrix4f mat1 = quat1.RotationMatrix();
		glm::mat4      m1 = glm::mat4_cast(q1);

		//CHECK_MATRIX4(mat1, m1);
		auto resv = mat1 * math::Vector4f(vec1.X(), vec1.Y(), vec1.Z(), 1.f);
		auto rv = m1 * glm::vec4(v1.x, v1.y, v1.z, 1.f);

		float slerpT = 0.0002f;

		//CHECK_VECTOR3(resv, rv);

		//CHECK(glm::eulerAngles(q1).x == Catch::Approx(quat1.EulerAngles().GetX()));
		//CHECK(glm::eulerAngles(q1).y == Catch::Approx(quat1.EulerAngles().GetY()));
		//CHECK(glm::eulerAngles(q1).z == Catch::Approx(quat1.EulerAngles().GetZ()));

		std::cout << quat1.Length() << std::endl;

		std::cout << (quat1 * quat2).Length() << std::endl;

		CHECK(math::Dot(quat1, quat2) == Catch::Approx(glm::dot(q1, q2)));

		CHECK_QUAT_EQUAL((math::Quatf::Slerp(quat1.Normalized(), quat2.Normalized(), slerpT)), (glm::slerp(glm::normalize(q1), glm::normalize(q2), slerpT)));

		constexpr float x = 0.f, y = 15.f * DEG2RAD, z = 6.f * DEG2RAD;
		constexpr float x2 = 20.f * DEG2RAD, y2 = 35.f * DEG2RAD, z2 = 45.f * DEG2RAD;

		math::Quatf rot1 = math::Quatf(math::Radian(x), math::Radian(y), math::Radian(z));
		math::Quatf rot2 = math::Quatf(math::Radian(x2), math::Radian(y2), math::Radian(z2));
		glm::quat rotglm1 = glm::quat(glm::vec3{ x, y, z });
		glm::quat rotglm2 = glm::quat(glm::vec3{ x2, y2, z2 });

		CHECK_QUAT_EQUAL(rot1, rotglm1);

		CHECK_QUAT_EQUAL((rot1 * rot2), (rotglm1 * rotglm2));

		CHECK_VECTOR3(((rot1 * rot2).EulerAngles()), (glm::eulerAngles(rotglm1 * rotglm2)));

		std::cout << ((rot1 * rot2).EulerAngles()) * RAD2DEG << '\n' << glm::degrees(glm::eulerAngles(rotglm1 * rotglm2).x) << ' ' <<
			glm::degrees(glm::eulerAngles(rotglm1 * rotglm2).y) << ' ' << glm::degrees(glm::eulerAngles(rotglm1 * rotglm2).z) << '\n';

	}
}