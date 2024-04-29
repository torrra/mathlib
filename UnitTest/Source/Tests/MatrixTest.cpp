#include <iostream>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>

#include "libmath/Arithmetic.h"
#include "libmath/Matrix.h"

#define DISPLAY_MAT2(obj, title)\
std::cout << title << ":\n" << obj[0][0] << ' ' << obj[0][1]\
<< '\n' << obj[1][0] << ' ' << obj[1][1] << '\n';

#define CHECK_MAT2(mat1, mat2)\
CHECK(mth::almostEqual(mat1[0][0], mat2[0][0]));\
CHECK(mth::almostEqual(mat1[0][1], mat2[0][1]));\
CHECK(mth::almostEqual(mat1[1][0], mat2[1][0]));\
CHECK(mth::almostEqual(mat1[1][1], mat2[1][1]))


TEST_CASE("Matrix2", "[matrix] [all]")
{
    SECTION("Instanciation")
    {
        {
            mth::Matrix2    myMat;
            glm::mat2       glmMat(0.f);

            DISPLAY_MAT2(myMat, "my empty matrix");
            DISPLAY_MAT2(glmMat, "glm empty matrix");

            CHECK_MAT2(myMat, glmMat);
            
        }

	mth::Matrix2        identityMat(3.4f, 1.f, 4.6f, 0.7f);

	DISPLAY_MAT2(identityMat, "Before calling Identity()");

	identityMat.Identity();

	DISPLAY_MAT2(identityMat, "After calling Identity()");


    }
}
