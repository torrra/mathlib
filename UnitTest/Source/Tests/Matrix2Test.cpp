#include <iostream>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>
#include <glm/gtx/matrix_operation.hpp>

#include "libmath/Arithmetic.h"
#include "libmath/Matrix2.h"

#define DISPLAY_MAT2(obj, title)\
std::cout << title << ":\n" << obj[0][0] << ' ' << obj[0][1]\
<< '\n' << obj[1][0] << ' ' << obj[1][1] << '\n';

#define CHECK_MAT2(mat1, mat2)\
CHECK(mth::almostEqual(mat1[0][0], mat2[0][0]));\
CHECK(mth::almostEqual(mat1[0][1], mat2[0][1]));\
CHECK(mth::almostEqual(mat1[1][0], mat2[1][0]));\
CHECK(mth::almostEqual(mat1[1][1], mat2[1][1]))


#define CHECK_M2_EQ(mat1, mat2)\
CHECK(mat1[0][0] == mat2[0][0]);\
CHECK(mat1[0][1] == mat2[0][1]);\
CHECK(mat1[1][0] == mat2[1][0]);\
CHECK(mat1[1][1] == mat2[1][1])



TEST_CASE("Matrix2", "[matrix] [all]")
{
    SECTION("Instanciation")
    {
        {
            mth::Matrix2    myMat;
            mth::Matrix2    toCopy(3.4f, 1.f, 4.6f, 0.7f);
            glm::mat2       glmMat(0.f);

            CHECK_MAT2(myMat, glmMat);

            myMat = toCopy;

            CHECK_MAT2(myMat, toCopy);

        }


    }

    SECTION("Operations")
    {
        mth::Matrix2    myMat(3.4f, 1.f, 4.6f, 0.7f);
        glm::mat2       glmMat(3.4f, 1.f, 4.6f, 0.7f);

        CHECK(myMat.Determinant() == glm::determinant(glmMat));

        CHECK_MAT2(myMat, glmMat);

        CHECK_MAT2(myMat.Adjugate(), glm::adjugate(glmMat));
        CHECK_MAT2(myMat.Inverse(), glm::inverse(glmMat));




    }
}
