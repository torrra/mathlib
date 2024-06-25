#include <iostream>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>
#include <glm/gtx/matrix_operation.hpp>

#include "libmath/Arithmetic.h"
#include "libmath/Matrix2.h"

// Display any matrix' content
#define DISPLAY_MAT2(obj, title)\
std::cout << title << ":\n" << obj[0][0] << ' ' << obj[0][1]\
<< '\n' << obj[1][0] << ' ' << obj[1][1] << '\n';

// Comparison compatible with both my libmath and glm
#define CHECK_MAT2(mat1, mat2)\
CHECK(ion::math::AlmostEqual(mat1[0][0], mat2[0][0]));\
CHECK(ion::math::AlmostEqual(mat1[0][1], mat2[0][1]));\
CHECK(ion::math::AlmostEqual(mat1[1][0], mat2[1][0]));\
CHECK(ion::math::AlmostEqual(mat1[1][1], mat2[1][1]))


// Comparison between two matrices (mine or from glm) without epsilon test
#define CHECK_M2_EQ(mat1, mat2)\
CHECK(mat1[0][0] == mat2[0][0]);\
CHECK(mat1[0][1] == mat2[0][1]);\
CHECK(mat1[1][0] == mat2[1][0]);\
CHECK(mat1[1][1] == mat2[1][1])



TEST_CASE("Matrix2", "[matrix][all]")
{
    SECTION("Instanciation")
    {
        {
            ion::math::Matrix2    myMat;
            ion::math::Matrix2    toCopy(3.4f, 1.f, 4.6f, 0.7f);
            glm::mat2       glmMat(0.f);

            CHECK_MAT2(myMat, glmMat);

            myMat = toCopy;

            CHECK_MAT2(myMat, toCopy);

        }


    }

    SECTION("Operations")
    {
        ion::math::Matrix2    myMat(3.4f, 1.f, 4.6f, 0.7f);
        glm::mat2       glmMat(3.4f, 1.f, 4.6f, 0.7f);

        CHECK(myMat.Determinant() == glm::determinant(glmMat));

        CHECK_MAT2(myMat, glmMat);

        CHECK_MAT2(myMat.Adjugate(), glm::adjugate(glmMat));
        CHECK_MAT2(myMat.Inverse(), glm::inverse(glmMat));


        ion::math::Matrix2   otherMat(1.7f, 3.2f, 4.2f, 6.f);
        glm::mat2      otherGlm(1.7f, 3.2f, 4.2f, 6.f);


        // Addition
        ion::math::Matrix2   myResult = myMat + otherMat;
        glm::mat2      glmResult = glmMat + otherGlm;

        CHECK_MAT2(myResult, glmResult);

        // Subtraction
        myResult = myMat - otherMat;
        glmResult = glmMat - otherGlm;

        CHECK_MAT2(myResult, glmResult);


        // Multiplication
        myResult = myMat * otherMat;
        glmResult = glmMat * otherGlm;

        CHECK_MAT2(myResult, glmResult);


        // Addition assignment
        myResult += myMat;
        glmResult += glmMat;

        CHECK_MAT2(myResult, glmResult);


        myResult -= otherMat;
        glmResult -= otherGlm;

        CHECK_MAT2(myResult, glmResult);

        myResult *= myMat;
        glmResult *= glmMat;

        CHECK_MAT2(myResult, glmResult);

        CHECK(myMat == myMat);
        CHECK_FALSE(myMat == myResult);

        CHECK(myMat != myResult);
        CHECK_FALSE(myMat != myMat);
    }
}
