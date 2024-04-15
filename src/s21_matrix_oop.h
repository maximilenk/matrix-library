#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;
  double** matrix_;

  void CreateMatrix();
  void RemoveMatrix();
  S21Matrix Minor(int skip_row, int skip_column) const;

 public:
  S21Matrix();
  ~S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;

  int GetCols() const noexcept;
  int GetRows() const noexcept;
  void SetRows(const int rows);
  void SetCols(const int cols);

  void SumMatrix(const S21Matrix& other);
  bool EqMatrix(const S21Matrix& other) const noexcept;
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  bool operator==(const S21Matrix& other) const noexcept;

  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);

  double& operator()(const int i, const int j);
  double operator()(const int i, const int j) const;

  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;

  friend S21Matrix operator*(const double num, S21Matrix&);
  friend S21Matrix operator*(S21Matrix&, const double num);
};

#endif  // S21_MATRIX_OOP_H
