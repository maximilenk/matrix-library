#include <gtest/gtest.h>

#include <iostream>

#include "s21_matrix_oop.h"

namespace {

TEST(Constructor, Default) {
  S21Matrix temp = S21Matrix();
  EXPECT_EQ(temp.GetRows(), 3);
  EXPECT_EQ(temp.GetCols(), 3);
}

TEST(Constructor, Parametrs) {
  S21Matrix temp = S21Matrix(5, 5);
  EXPECT_EQ(temp.GetRows(), 5);
  EXPECT_EQ(temp.GetCols(), 5);
}

TEST(Constructor, Copy) {
  S21Matrix temp = S21Matrix(5, 5);
  for (int i = 0; i < temp.GetRows(); i++) {
    for (int j = 0; j < temp.GetCols(); j++) temp(i, j) = i + j;
  }
  S21Matrix temp2 = temp;
  EXPECT_EQ(temp2.GetRows(), 5);
  EXPECT_EQ(temp2.GetCols(), 5);
  EXPECT_EQ(temp == temp2, true);
}

TEST(Constructor, Move) {
  S21Matrix temp = S21Matrix(5, 5);
  for (int i = 0; i < temp.GetRows(); i++) {
    for (int j = 0; j < temp.GetCols(); j++) temp(i, j) = i + j;
  }
  S21Matrix temp3 = temp;
  S21Matrix temp2 = std::move(temp);
  EXPECT_EQ(temp2.GetRows(), 5);
  EXPECT_EQ(temp2.GetCols(), 5);
  EXPECT_EQ(temp2, temp3);
}

TEST(Getter, RowsAndCols) {
  S21Matrix temp = S21Matrix();
  EXPECT_EQ(temp.GetRows(), 3);
  EXPECT_EQ(temp.GetCols(), 3);
}

TEST(Setter, RowsAndCols) {
  S21Matrix temp = S21Matrix(5, 5);
  for (int i = 0; i < temp.GetRows(); i++) {
    for (int j = 0; j < temp.GetCols(); j++) temp(i, j) = i + j;
  }
  temp.SetCols(6);
  temp.SetRows(6);
  for (int i = 5; i < temp.GetRows(); i++) {
    for (int j = 5; j < temp.GetCols(); j++) EXPECT_EQ(temp(i, j), 0);
  }
  EXPECT_EQ(temp.GetCols(), 6);
  EXPECT_EQ(temp.GetRows(), 6);
  temp.SetCols(4);
  temp.SetRows(4);
  for (int i = 0; i < temp.GetRows(); i++) {
    for (int j = 0; j < temp.GetCols(); j++) EXPECT_EQ(temp(i, j), i + j);
  }
  EXPECT_EQ(temp.GetCols(), 4);
  EXPECT_EQ(temp.GetRows(), 4);
}

TEST(Math, Sum) {
  S21Matrix temp = S21Matrix(5, 5);
  for (int i = 0; i < temp.GetRows(); i++) {
    for (int j = 0; j < temp.GetCols(); j++) temp(i, j) = i + j;
  }
  S21Matrix temp2 = temp + (-1) * temp;
  for (int i = 0; i < temp.GetRows(); i++) {
    for (int j = 0; j < temp.GetCols(); j++) EXPECT_EQ(temp2(i, j), 0);
  }
}

TEST(Math, Sub) {
  S21Matrix temp = S21Matrix(5, 5);
  for (int i = 0; i < temp.GetRows(); i++) {
    for (int j = 0; j < temp.GetCols(); j++) temp(i, j) = i + j;
  }
  S21Matrix temp1 = temp;
  S21Matrix temp2 = temp - temp1;
  for (int i = 0; i < temp2.GetRows(); i++) {
    for (int j = 0; j < temp2.GetCols(); j++) EXPECT_EQ(temp2(i, j), 0);
  }
}

TEST(Math, MulMatrix) {
  S21Matrix temp = S21Matrix(2, 2);
  for (int i = 0; i < temp.GetRows(); i++) {
    for (int j = 0; j < temp.GetCols(); j++) temp(i, j) = 2 + i + j;
  }
  S21Matrix temp2 = temp * temp;
  EXPECT_EQ(temp2(0, 0), 13);
  EXPECT_EQ(temp2(0, 1), 18);
  EXPECT_EQ(temp2(1, 0), 18);
  EXPECT_EQ(temp2(1, 1), 25);
}

TEST(Math, MulNumber) {
  S21Matrix temp = S21Matrix(2, 2);
  for (int i = 0; i < temp.GetRows(); i++) {
    for (int j = 0; j < temp.GetCols(); j++) temp(i, j) = 2 + i + j;
  }
  S21Matrix temp2 = temp * 3;
  S21Matrix temp3 = 3 * temp;
  EXPECT_EQ(temp2(0, 0), 6);
  EXPECT_EQ(temp2(0, 1), 9);
  EXPECT_EQ(temp2(1, 0), 9);
  EXPECT_EQ(temp2(1, 1), 12);
  EXPECT_EQ(temp2, temp3);
}

TEST(Operations, Transpose) {
  S21Matrix temp = S21Matrix(5, 5);
  for (int i = 0; i < temp.GetRows(); i++) {
    for (int j = 0; j < temp.GetCols(); j++) temp(i, j) = 2 + i + j;
  }
  S21Matrix temp2 = temp.Transpose();
  for (int i = 0; i < temp.GetRows(); i++) {
    for (int j = 0; j < temp.GetCols(); j++) EXPECT_EQ(temp(i, j), temp2(j, i));
  }
}

TEST(Operations, Calc) {
  S21Matrix temp = S21Matrix(2, 2);
  temp(0, 0) = 1;
  temp(0, 1) = 2;
  temp(1, 0) = 3;
  temp(1, 1) = 4;
  S21Matrix temp2 = temp.CalcComplements();
  EXPECT_EQ(temp2(0, 0), 4);
  EXPECT_EQ(temp2(0, 1), -3);
  EXPECT_EQ(temp2(1, 0), -2);
  EXPECT_EQ(temp2(1, 1), 1);
}

TEST(Operations, Det) {
  S21Matrix temp = S21Matrix();
  temp(0, 0) = 1;
  temp(0, 1) = 2;
  temp(0, 2) = 3;
  temp(1, 0) = 4;
  temp(1, 1) = 5;
  temp(1, 2) = 6;
  temp(2, 0) = 7;
  temp(2, 1) = 8;
  temp(2, 2) = 15;
  EXPECT_EQ(temp.Determinant(), -18);
}

TEST(Operations, Invers) {
  S21Matrix temp = S21Matrix(2, 2);
  temp(0, 0) = 1;
  temp(0, 1) = 2;
  temp(1, 0) = 3;
  temp(1, 1) = 4;
  S21Matrix temp2 = temp.InverseMatrix();
  EXPECT_EQ(temp2(0, 0), -2);
  EXPECT_EQ(temp2(0, 1), 1.5);
  EXPECT_EQ(temp2(1, 0), 1);
  EXPECT_EQ(temp2(1, 1), -0.5);
}

TEST(Operations, Index) {
  S21Matrix temp = S21Matrix(2, 2);
  temp(0, 0) = 1;
  temp(0, 1) = 2;
  temp(1, 0) = 3;
  temp(1, 1) = 4;
  S21Matrix temp2 = S21Matrix(2, 2);
  temp2(0, 0) = temp(0, 0);
  temp2(0, 1) = temp(0, 1);
  temp2(1, 0) = temp(1, 0);
  temp2(1, 1) = temp(1, 1);
  EXPECT_EQ(temp2(0, 0), 1);
  EXPECT_EQ(temp2(0, 1), 2);
  EXPECT_EQ(temp2(1, 0), 3);
  EXPECT_EQ(temp2(1, 1), 4);
}

TEST(Operator, Copy) {
  S21Matrix temp = S21Matrix(5, 5);
  for (int i = 0; i < temp.GetRows(); i++) {
    for (int j = 0; j < temp.GetCols(); j++) temp(i, j) = i + j;
  }
  S21Matrix temp2 = S21Matrix(5, 5);
  for (int i = 0; i < temp.GetRows(); i++) {
    for (int j = 0; j < temp.GetCols(); j++) temp(i, j) = i + j - 1;
  }
  temp2 = temp;
  EXPECT_EQ(temp2.GetRows(), 5);
  EXPECT_EQ(temp2.GetCols(), 5);
  EXPECT_EQ(temp == temp2, true);
}

}  // namespace