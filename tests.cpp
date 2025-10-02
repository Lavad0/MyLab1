#define CATCH_CONFIG_MAIN

#include "Catch2/catch_amalgamated.hpp"
#include "Catch2/catch_amalgamated.cpp"
#include "Matrix/Matrix.h"
#include <cstring>
#include <cstdio>

TEST_CASE("Matrix default constructor", "[Matrix]") {
    Matrix m;

    SECTION("Default matrix has size 0") {
        REQUIRE(m.getSize() == 0);
    }

    SECTION("Default matrix data is nullptr") {
        REQUIRE(m.getData() == nullptr);
    }

    SECTION("Default matrix string is nullptr") {
        REQUIRE(m.getString() == nullptr);
    }
}

TEST_CASE("Matrix constructor with parameters", "[Matrix]") {
    int data[] = {1, 2, 3, 4};
    Matrix m(2, data);

    SECTION("Size is correctly set") {
        REQUIRE(m.getSize() == 2);
    }

    SECTION("Data is correctly copied") {
        REQUIRE(m.getData()[0] == 1);
        REQUIRE(m.getData()[1] == 2);
        REQUIRE(m.getData()[2] == 3);
        REQUIRE(m.getData()[3] == 4);
    }

    SECTION("String is created") {
        const char* str = m.getString();
        REQUIRE(str != nullptr);
        //проверяем, чтобы все элементы были в строке
        REQUIRE(strstr(str, "1") != nullptr);
        REQUIRE(strstr(str, "2") != nullptr);
        REQUIRE(strstr(str, "3") != nullptr);
        REQUIRE(strstr(str, "4") != nullptr);
    }
}

TEST_CASE("Matrix copy constructor", "[Matrix]") {
    int data[] = {1, 2, 3, 4};
    Matrix original(2, data);
    Matrix copy(original);

    SECTION("Size is copied") {
        REQUIRE(copy.getSize() == original.getSize());
    }

    SECTION("Data is copied") {
        REQUIRE(copy.getData() != original.getData()); //проверка, что 2 объекта используют разные массивы
        REQUIRE(copy.getData()[0] == original.getData()[0]);
        REQUIRE(copy.getData()[1] == original.getData()[1]);
        REQUIRE(copy.getData()[2] == original.getData()[2]);
        REQUIRE(copy.getData()[3] == original.getData()[3]);
    }

    SECTION("String is copied") {
        REQUIRE(copy.getString() != original.getString()); //проверка, что 2 объекта используют разные строки
        REQUIRE(strcmp(copy.getString(), original.getString()) == 0);
    }
}

TEST_CASE("Matrix with single element", "[Matrix]") {
    int data[] = {42};
    Matrix m(1, data);

    SECTION("Single element matrix") {
        REQUIRE(m.getSize() == 1);
        REQUIRE(m.getData()[0] == 42);
    }

    SECTION("String of single element matrix") {
        const char* str = m.getString();
        REQUIRE(str != nullptr);
        REQUIRE(strstr(str, "42") != nullptr);
    }
}

TEST_CASE("Matrix with negative numbers", "[Matrix]") {
    int data[] = {-1, -2, 3, -4};
    Matrix m(2, data);

    SECTION("Negative numbers in data") {
        REQUIRE(m.getData()[0] == -1);
        REQUIRE(m.getData()[1] == -2);
        REQUIRE(m.getData()[2] == 3);
        REQUIRE(m.getData()[3] == -4);
    }

    SECTION("String contains negative numbers") {
        const char* str = m.getString();
        REQUIRE(str != nullptr);
        REQUIRE(strstr(str, "-1") != nullptr);
        REQUIRE(strstr(str, "-2") != nullptr);
        REQUIRE(strstr(str, "-4") != nullptr);
    }
}

TEST_CASE("Matrix sum operation", "[Matrix]") {
    SECTION("Sum of same size matrices") {
        int data1[] = {1, 2, 3, 4};
        int data2[] = {5, 6, 7, 8};
        Matrix m1(2, data1);
        Matrix m2(2, data2);

        Matrix result = m1.sum(m2);

        REQUIRE(result.getSize() == m1.getSize());
        REQUIRE(result.getData()[0] == data1[0] + data2[0]);
        REQUIRE(result.getData()[1] == data1[1] + data2[1]);
        REQUIRE(result.getData()[2] == data1[2] + data2[2]);
        REQUIRE(result.getData()[3] == data1[3] + data2[3]);
        REQUIRE(result.getString() != nullptr);
    }

    SECTION("Sum of different size matrices") {
        int data1[] = {1, 2, 3, 4};
        int data2[] = {1, 2};
        Matrix m1(2, data1);
        Matrix m2(1, data2);

        Matrix result = m1.sum(m2);

        REQUIRE(result.getSize() == 0);
        REQUIRE(result.getData() == nullptr);
        REQUIRE(result.getString() == nullptr);
    }
}

TEST_CASE("Matrix transpose operation", "[Matrix]") {
    SECTION("Transpose of 3x3 matrix") {
        int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        Matrix m(3, data);

        Matrix result = m.transpose();

        REQUIRE(result.getSize() == m.getSize());
        REQUIRE(result.getData()[0] == 1);
        REQUIRE(result.getData()[1] == 4);
        REQUIRE(result.getData()[2] == 7);
        REQUIRE(result.getData()[3] == 2);
        REQUIRE(result.getData()[4] == 5);
        REQUIRE(result.getData()[5] == 8);
        REQUIRE(result.getData()[6] == 3);
        REQUIRE(result.getData()[7] == 6);
        REQUIRE(result.getData()[8] == 9);
    }
}

TEST_CASE("Matrix string operations", "[Matrix]") {
    SECTION("String length calculation") {
        int data[] = {1, 22, 333, 4444};
        int length = Matrix::stringLength(2, data);

        REQUIRE(length == 14);
    }
}

TEST_CASE("Matrix object counter", "[Matrix]") {
    SECTION("Initial count should be zero") {
        REQUIRE(Matrix::getObjectCount() == 0);
    }

    SECTION("Count increases when creating objects") {
        int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        Matrix m1;
        REQUIRE(Matrix::getObjectCount() == 1);

        Matrix m2(3, data);
        REQUIRE(Matrix::getObjectCount() == 2);

    }

    SECTION("Count decreases when objects are destroyed") {
        {
            Matrix m1;
            REQUIRE(Matrix::getObjectCount() == 1);

            {
                Matrix m2;
                REQUIRE(Matrix::getObjectCount() == 2);
            }

            REQUIRE(Matrix::getObjectCount() == 1);
        }

        REQUIRE(Matrix::getObjectCount() == 0);
    }

    SECTION("Copy constructor affects counter") {
        int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        REQUIRE(Matrix::getObjectCount() == 0);

        Matrix original(3, data);
        REQUIRE(Matrix::getObjectCount() == 1);

        Matrix copy(original);
        REQUIRE(Matrix::getObjectCount() == 2);

    }
}


