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


        mth::Matrix2   otherMat(1.7f, 3.2f, 4.2f, 6.f);
        glm::mat2      otherGlm(1.7f, 3.2f, 4.2f, 6.f);


        // Addition
        mth::Matrix2   myResult = myMat + otherMat;
        glm::mat2      glmResult = glmMat + otherGlm;

        CHECK_MAT2(myResult, glmResult);

        // Subtraction
        myResult = myMat - otherMat;
        glmResult = glmMat - otherGlm;


        CHECK_MAT2(myResult, glmResult);


        // Multiplication

        myMat = { 4.f, 3.f, 7.f, 8.f };
        glmMat = { 4.f, 3.f, 7.f, 8.f };

        otherMat = { 9.f, 2.f, 5.f, 6.f };
        otherGlm = { 9.f, 2.f, 5.f, 6.f };

        myResult = myMat * otherMat;
        glmResult = glmMat * otherGlm;

        CHECK_MAT2(myResult, glmResult);

        DISPLAY_MAT2(myResult, "Matrix product");
        DISPLAY_MAT2(glmResult, "glm matrix product");


    }
}
