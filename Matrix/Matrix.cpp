#include "Matrix.h"
#include <cstdio>
#include <cstring>

int Matrix::objectCount = 0;

Matrix::Matrix() {
    this->size = 0;
    this->data = nullptr;
    this->string = nullptr;
    objectCount ++;
}

Matrix::Matrix(int size, const int* data) {
    this->size = size;
    this->data = new int[size*size];
    this->string = nullptr;

    for (int i = 0; i < size*size; i++) {
        this->data[i] = data[i];
    }

    updateString();
    objectCount ++;
}

Matrix::Matrix(const Matrix &other) {
    this->size = other.size;

    if (other.data) {
        this->data = new int[size*size];
        for (int i = 0; i < size*size; i++) {
            this->data[i] = other.data[i];
        }
    } else {
        this->data = nullptr;
    }

    if (other.string) {
        this->string = new char[strlen(other.string) + 1];
        strcpy(this->string, other.string);
    } else {
        this->string = nullptr;
    }

    objectCount ++;
}

Matrix::~Matrix() {
    delete[] data;
    delete[] string;

    objectCount --;

}

int Matrix::stringLength(int size, const int* data) {

    if (data == nullptr || size == 0) {
        return 1;
    }

    int length = 1;

    for (int i = 0; i < size * size; i++) {
        int digits = 1;
        int num = data[i];

        //учёт отрицательных чисел
        if (num < 0) {
            digits++;
            num = -num;
        }

        while (num > 9) {
            digits++;
            num /= 10;
        }
        length += digits;
    }

    length += size * size - 1;

    return length;
}

void Matrix::updateString() {
    delete[] string;

    if (size == 0 || data == nullptr) {
        string = new char[1];
        string[0] = '\0';
        return;
    }

    int length = stringLength(size, data);
    string = new char[length];

    int pos = 0; // текущая позиция в строке

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {

            pos += sprintf(string + pos, "%d", data[i * size + j]); // сдвигаем на кол-во записанных символов

            if (j < size - 1) {
                string[pos++] = '\t';
            }
        }
        if (i < size - 1) {
            string[pos++] = '\n';
        }
    }

    string[pos] = '\0';
}

Matrix Matrix::sum(const Matrix &other) const {
    if (size != other.size || size == 0) {
        return Matrix(); // пустая матрица
    }

    Matrix result;
    result.size = this->size;
    result.data = new int[size*size];

    for (int i = 0; i < size*size; i++) {
        result.data[i] = this->data[i] + other.data[i];
    }

    result.updateString();
    return result;
}

Matrix Matrix::transpose() const {
    if (size == 0) {
        return Matrix();
    }

    Matrix result;
    result.size = size;
    result.data = new int[size * size];

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result.data[i * size + j] = data[j * size + i];
        }
    }

    result.updateString();
    return result;
}

const char* Matrix::getString() const {
    return string;
}

int Matrix::getSize() const {
    return size;
}

int* Matrix::getData() const {
    return data;
}

int Matrix::getObjectCount() {
    return objectCount;
}
