#include "s21_matrix_oop.h"

using namespace std;

S21Matrix::S21Matrix() {
  this->rows_ = 0;
  this->cols_ = 0;
  this->matrix_ = nullptr;
  
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw std::length_error("Arguments less than 1");
        
  }
  this->rows_ = rows;
  this->cols_ = cols;

  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;

  this->matrix_ = new double *[other.rows_];
  for (int i = 0; i < other.rows_; i++) {
    this->matrix_[i] = new double[other.cols_];
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;

  this->matrix_ = new double *[other.rows_];
  for (int i = 0; i < other.rows_; i++) {
    this->matrix_[i] = new double[other.cols_];
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }

  for (int i = 0; i < other.rows_; i++) {
    delete[] other.matrix_[i];
  }

  delete[] other.matrix_;

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {

  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }

  delete[] matrix_;
}

//#################################################################################
int S21Matrix::GetRows(){
    return rows_;
}
int S21Matrix::GetCols(){
    return cols_;
}

double** S21Matrix::getMatrix() {
   return this->matrix_; 
}

void S21Matrix::SetRows(int rows){
  int tmpRows = 0;

  if (rows < 1) {
    throw std::length_error("Arguments less than 1");
  }

  S21Matrix temp(rows, this->cols_);
  if(this->rows_ < rows){
    tmpRows = this->rows_;
  }else{
    tmpRows = rows;
  }

  for (int i = 0; i < tmpRows; i++) {
    for (int j = 0; j < this->cols_; j++) {
      temp.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  deleteMatrix();
  *this = temp;   
}



void S21Matrix::SetColumns(int cols){
   int tmpCols = 0;

  if (cols < 1) {
    throw std::length_error("Arguments less than 1");
  }
  S21Matrix temp(this->rows_,cols);
  if(this->cols_ < cols){
    tmpCols = this->cols_;
  }else{
    tmpCols = cols;
  }

  for (int i = 0; i < this->rows_ ;i++) {
    for (int j = 0; j < tmpCols; j++) {
      temp.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  deleteMatrix();
  *this = temp;   
} 

//============================================================================

void S21Matrix::printMatrix() {

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {

      cout << matrix_[i][j];
      cout << " ";
    }
    cout << endl;
  }
}

void S21Matrix::feelMatrix(int num) {

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {

      this->matrix_[i][j] = num;
    }
  }
}

void S21Matrix::deleteMatrix(){
  if (this->matrix_ != nullptr) {
    for (int i = 0; i < this->rows_; i++) {
      delete[] this->matrix_[i];
    }
    delete[] this->matrix_;
    this->rows_ = 0;
    this->cols_ = 0;
    this->matrix_ = nullptr;
  }



}

void S21Matrix::matrix_reduction(int row, int col, const S21Matrix &tmp){
  int m_row = 0;
  int m_col = 0;
  for (int i = 0; i < this->rows_; i++) {
    if (i == row) {
      continue;
    }
    m_col = 0;
    for (int j = 0; j < this->cols_; j++) {
      if (j == col) {
        continue;
      }
      tmp.matrix_[m_row][m_col] = this->matrix_[i][j];
      m_col++;
    }
    m_row++;
  }
  

}
//==================================================================================

void S21Matrix::operator=(const S21Matrix &other) {

  this->rows_ = other.rows_;
  this->cols_ = other.cols_;

  this->matrix_ = new double *[other.rows_];
  for (int i = 0; i < other.rows_; i++) {
    this->matrix_[i] = new double[other.cols_];
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::operator=(S21Matrix &&other) {
  deleteMatrix();

  this->rows_ = other.rows_;
  this->cols_ = other.cols_;

  this->matrix_ = new double *[other.rows_];
  for (int i = 0; i < other.rows_; i++) {
    this->matrix_[i] = new double[other.cols_];
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
  other.deleteMatrix();
}

bool S21Matrix::operator==(const S21Matrix &other) {

  if (this->rows_ == other.rows_ && this->cols_ == other.cols_) {

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (this->matrix_[i][j] != other.matrix_[i][j]) {
          return false;
        }
      }
    }
  } else {
    return false;
  }
  return true;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  if(this->rows_ != other.rows_ && this->cols_ != other.cols_){
      throw std::length_error("different matrix dimensions");
  }

  
  S21Matrix res(this->rows_, this->cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[i][j] = other.matrix_[i][j] + this->matrix_[i][j];
    }
  }
  return res;
}

void S21Matrix::operator+=(const S21Matrix &other) {
  if(this->rows_ != other.rows_ && this->cols_ != other.cols_){
      throw std::length_error("different matrix dimensions");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j] + this->matrix_[i][j];
    }
  }
}

void S21Matrix::operator-=(const S21Matrix &other) {
  if(this->rows_ != other.rows_ && this->cols_ != other.cols_){
      throw std::length_error("different matrix dimensions");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = this->matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {

  if(this->rows_ != other.rows_ && this->cols_ != other.cols_){
      throw std::length_error("different matrix dimensions");
  }
  S21Matrix res(this->rows_, this->cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[i][j] = this->matrix_[i][j] - other.matrix_[i][j];
    }
  }
  return res;
}

S21Matrix S21Matrix::operator*(int a) {

  S21Matrix res(this->rows_, this->cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[i][j] = this->matrix_[i][j] * a;
    }
  }
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  if(this->cols_ != other.rows_){
    throw std::length_error("the number of columns of the first matrix is not equal to the number of rows of the second matrix");
  }

  S21Matrix res(this->rows_, other.cols_);
  for (int i = 0; i < res.rows_; i++) {
    for (int k = 0; k < res.cols_; k++) {
      for (int q = 0; q < this->cols_; q++) {
        res.matrix_[i][k] += this->matrix_[i][q] * other.matrix_[q][k];
      }
    }
  }

  return res;
}

void S21Matrix::operator*=(double a) {
 
  

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = this->matrix_[i][j] * a;
    }
  }
}

double & S21Matrix::operator()(int i, int j) {

  if(i >= this->rows_ || j >= this->cols_){
    throw std::length_error("index outside the matrix");

  }

  return this->matrix_[i][j];
}

//=================================================================================

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  if (this->rows_ == other.rows_ && this->cols_ == other.cols_) {

    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (this->matrix_[i][j] != other.matrix_[i][j]) {
          return false;
        }
      }
    }
  } else {
    return false;
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if(this->rows_ != other.rows_ && this->cols_ != other.cols_){
      throw std::length_error("different matrix dimensions");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = this->matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if(this->rows_ != other.rows_ && this->cols_ != other.cols_){
      throw std::length_error("different matrix dimensions");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = this->matrix_[i][j] - other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = this->matrix_[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {

  if(this->cols_ != other.rows_){
    throw std::length_error("the number of columns of the first matrix is not equal to the number of rows of the second matrix");
  }

  S21Matrix res(this->rows_, other.cols_);
  for (int i = 0; i < res.rows_; i++) {
    for (int k = 0; k < res.cols_; k++) {
      for (int q = 0; q < this->cols_; q++) {
        res.matrix_[i][k] += this->matrix_[i][q] * other.matrix_[q][k];
      }
    }
  }

  deleteMatrix();

  this->matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = res.matrix_[i][j];
    }
  }
}
//###############################################################################################

S21Matrix S21Matrix::Transpose() {

  S21Matrix res(this->cols_, this->rows_);
  for (int i = 0; i < this->rows_; i++) {
    for (int g = 0; g < this->cols_; g++) {
      res.matrix_[g][i] = this->matrix_[i][g];
    }
  }

  return res;
}

double S21Matrix::Determinant(){
  double res = 0;
  if ((this->matrix_ == nullptr) && (this->rows_ < 1)) {
    throw std::length_error("incorrect arguments");
  }
  if(this->rows_ != this->cols_){
    throw std::length_error("the matrix is not square");
  }

  if(this->cols_ == 1){
    res = this->matrix_[0][0];
  }else if(this->cols_ == 2){
    res =  this->matrix_[0][0] * this->matrix_[1][1] - this->matrix_[0][1] * this->matrix_[1][0];
  }else{
    double sign = 1, tmp_determinant = 0;
    for (int i = 0; i < this->cols_; i++){
      S21Matrix tmpMatrix(this->rows_ - 1, this->cols_ - 1);
      matrix_reduction(0, i, tmpMatrix);
      tmp_determinant = tmpMatrix.Determinant();
      res += tmp_determinant * sign * this->matrix_[0][i];
      sign*= -1;

      tmpMatrix.deleteMatrix();
    }

  }
 return res;
}


S21Matrix S21Matrix::CalcComplements(){

  double tmp_determinant;
  S21Matrix res(1, 1);

  if ((this->matrix_ == nullptr) && (this->rows_ < 1)) {
    throw std::length_error("incorrect arguments");
  }
  if(this->rows_ != this->cols_){
    throw std::length_error("the matrix is not square");
  }

  if(this->rows_ == 1){
    res.SetRows(1);
    res.SetColumns(1);

    res.matrix_[0][0] = 1;
  }else{
    res.SetRows(this->rows_);
    res.SetColumns(this->cols_);
    for (int i = 0; i < res.rows_; i++) {
      for (int j = 0; j < res.cols_; j++) {
        S21Matrix tmpMatrix(this->rows_ - 1, this->cols_ - 1);
        matrix_reduction(i, j, tmpMatrix);
        tmp_determinant = tmpMatrix.Determinant();
        res.matrix_[i][j] = tmp_determinant * pow(-1, i + j);

        tmpMatrix.deleteMatrix();

      }
    }
  }

  return res;


}

S21Matrix S21Matrix::InverseMatrix(){
  if(Determinant() == 0){
      throw std::length_error("the determinant of the matrix is 0");
  }

  double tmp_determinant = 0;
  tmp_determinant = Determinant();

  S21Matrix res(this->rows_, this->rows_);
  if(this->rows_ == 1){
    res.matrix_[0][0] = this->matrix_[0][0];
  }else{
    S21Matrix tmp_calc_compl;
    S21Matrix tmp_transpose;
    tmp_calc_compl = CalcComplements();
    tmp_transpose = tmp_calc_compl.Transpose();
    res = tmp_transpose * (1 / tmp_determinant);

    tmp_calc_compl.deleteMatrix();
    tmp_transpose.deleteMatrix();

  }

  return res;



}

















// int main() {

  
//   S21Matrix matrix_a(3, 2);
//   S21Matrix matrix_b(2, 3);
//   S21Matrix result(3, 3);

//   matrix_a(0, 0) = 3;
//   matrix_a(0, 1) = 2;
//   matrix_a(1, 0) = -6.6;
//   matrix_a(1, 1) = 0;

//   matrix_b(0, 0) = -7;
//   matrix_b(0, 1) = 0;
//   matrix_b(1, 0) = -3.5;
//   matrix_b(1, 1) = 2;

//   result(0, 0) = -28;
//   result(0, 1) = 4;
//   result(1, 0) = 46.2;
//   result(1, 1) = 0;

//   result = matrix_a * matrix_b;
//   result.printMatrix();

  
// }
