#pragma once

class Matrix {

public:
    Matrix();
    Matrix(int size, const int* data);
    Matrix(const Matrix& other);
    ~Matrix();

    Matrix sum(const Matrix& other) const;
    Matrix transpose() const;
    static int stringLength(int size, const int* data);

    static int getObjectCount();
    const char* getString() const;
    int getSize() const;
    int* getData() const;



private:
    int size;
    int* data;
    char* string;
    static int objectCount;

    void updateString();
    //static int stringLength(int size, const int* data);
};