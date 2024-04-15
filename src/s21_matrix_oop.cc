#include "s21_matrix_oop.h"

//конструктор
S21Matrix::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  CreateMatrix();
}

void S21Matrix::CreateMatrix() {
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

//деструктор
S21Matrix::~S21Matrix() { RemoveMatrix(); }

void S21Matrix::RemoveMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++)
      if (matrix_[i] != nullptr) delete[] matrix_[i];
    delete[] matrix_;
    cols_ = 0;
    rows_ = 0;
  }
}

//конструктор параметризированный
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1) throw std::logic_error("invalid size");
  CreateMatrix();
}

//конструктор копирования
S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrix();
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] = other.matrix_[i][j];
}

//конструктор переноса
S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

//геттеры
int S21Matrix::GetCols() const noexcept { return cols_; }

int S21Matrix::GetRows() const noexcept { return rows_; }

//сеттеры
void S21Matrix::SetRows(const int rows) {
  if (rows < 1) std::logic_error("invalide size");
  if (this->rows_ != rows) {
    S21Matrix temp(rows, this->cols_);
    for (int i = 0; i < temp.rows_ && i < this->rows_; i++)
      for (int j = 0; j < temp.cols_; j++)
        temp.matrix_[i][j] = this->matrix_[i][j];
    *this = std::move(temp);
  }
}

void S21Matrix::SetCols(const int cols) {
  if (cols < 1) std::logic_error("invalide size");
  if (this->cols_ != cols) {
    S21Matrix temp(this->rows_, cols);
    for (int i = 0; i < temp.rows_; i++)
      for (int j = 0; j < temp.cols_ && j < this->cols_; j++)
        temp.matrix_[i][j] = this->matrix_[i][j];
    *this = std::move(temp);
  }
}

// методы
bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  bool result = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) result = false;
  if (result) {
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++)
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-07) result = false;
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error("invalid size");
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] += other.matrix_[i][j];
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error("invalid size");
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) throw std::logic_error("invalid size");
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++)
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
    }
  }
  *this = std::move(result);
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) result.matrix_[j][i] = matrix_[i][j];
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) throw std::logic_error("invalid size");
  S21Matrix result(this->rows_, this->cols_);
  if (rows_ == 1)
    result.matrix_[0][0] = 1;
  else {
    double tmp;
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->rows_; j++) {
        S21Matrix min = this->Minor(i, j);
        tmp = min.Determinant();
        result.matrix_[i][j] = (pow(-1, (double)(i + j))) * tmp;
      }
    }
  }
  return result;
}

double S21Matrix::Determinant() const {
  if (this->rows_ != this->cols_) throw std::logic_error("invalid size");
  double result = 0;
  if (this->rows_ == 1)
    result = this->matrix_[0][0];
  else {
    double det;
    for (int i = 0; i < this->rows_; i++) {
      S21Matrix tmp = this->Minor(0, i);
      det = tmp.Determinant();
      result += this->matrix_[0][i] * det * (pow(-1.0, (double)i));
    }
  }
  return result;
}

S21Matrix S21Matrix::Minor(int skip_row, int skip_column) const {
  S21Matrix min(this->rows_ - 1, this->cols_ - 1);
  int m = 0;
  int n = 0;
  for (int i = 0; i < this->rows_; i++) {
    if (i == skip_row) i++;
    if (i != this->rows_) {
      for (int j = 0; j < this->rows_; j++) {
        if (j == skip_column) j++;
        if (j != this->rows_) {
          min.matrix_[m][n] = this->matrix_[i][j];
          n++;
        }
      }
    }
    n = 0;
    m++;
  }
  return min;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det = this->Determinant();
  if (fabs(det) < 1E-7) throw std::logic_error("determinant equals zero");
  S21Matrix tmp = this->CalcComplements();
  tmp.Transpose();
  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++) tmp.matrix_[i][j] /= det;
  return tmp;
}

//операторы

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result = *this;
  result += other;
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result = *this;
  result -= other;
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result = *this;
  result *= other;
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const noexcept {
  return this->EqMatrix(other);
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

S21Matrix operator*(const double num, S21Matrix& temp) {
  S21Matrix result = temp;
  result *= num;
  return result;
}

S21Matrix operator*(S21Matrix& temp, const double num) {
  S21Matrix result = temp;
  result *= num;
  return result;
}

double& S21Matrix::operator()(const int i, const int j) {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0)
    throw std::logic_error("invalide index");
  return matrix_[i][j];
}

double S21Matrix::operator()(const int i, const int j) const {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0)
    throw std::logic_error("invalide index");
  return matrix_[i][j];
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this == &other) return *this;
  this->RemoveMatrix();
  this->cols_ = other.cols_;
  this->rows_ = other.rows_;
  CreateMatrix();
  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++)
      this->matrix_[i][j] = other.matrix_[i][j];
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this == &other) return *this;
  this->RemoveMatrix();
  this->cols_ = other.cols_;
  this->rows_ = other.rows_;
  this->matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
  return *this;
}
