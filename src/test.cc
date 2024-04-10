#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(move, testleak) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  matrix2 = std::move(matrix1);
}

TEST(move, testleak1) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(std::move(matrix1));
}

TEST(ParametrizedConstructor, test1) {
  EXPECT_ANY_THROW({ S21Matrix test = S21Matrix(3, 0); });
}

TEST(ParametrizedConstructor, test2) {
  EXPECT_ANY_THROW({ S21Matrix test = S21Matrix(3, -2); });
}

TEST(ParametrizedConstructor, test3) {
  EXPECT_ANY_THROW({ S21Matrix test = S21Matrix(0, 0); });
}

TEST(ParametrizedConstructor, test4) {
  EXPECT_ANY_THROW({ S21Matrix test = S21Matrix(-1, 0); });
}

TEST(ParametrizedConstructor, test5) {
  EXPECT_ANY_THROW({ S21Matrix test = S21Matrix(-1, 4); });
}

TEST(CopyConstructor, test1) {
  EXPECT_NO_THROW({
    S21Matrix first = S21Matrix(3, 3);
    for (int i = 0; i < first.GetRows(); i++) {
      for (int j = 0; j < first.GetCols(); j++) {
        first(i, j) = i + j;
      }
    }
    S21Matrix second(first);
    for (int i = 0; i < first.GetRows(); i++) {
      for (int j = 0; j < first.GetCols(); j++) {
        EXPECT_EQ(first(i, j), second(i, j));
      }
    }
  });
}

TEST(CopyConstructor, test2) {
  EXPECT_NO_THROW({
    S21Matrix first = S21Matrix(3, 4);
    S21Matrix second(first);
    EXPECT_EQ(first.GetRows(), second.GetRows());
    EXPECT_EQ(first.GetCols(), second.GetCols());
  });
}



TEST(CopyConstructor, test4) {
  S21Matrix first(3, 3);
  EXPECT_NO_THROW(S21Matrix second(first); EXPECT_FALSE(&second == &first););
}

TEST(Getter, test1) {
  S21Matrix test(3, 3);
  EXPECT_EQ(test.GetRows(), 3);
  EXPECT_EQ(test.GetCols(), 3);
}

TEST(Getter, test2) {
  S21Matrix test(2, 4);
  EXPECT_EQ(test.GetRows(), 2);
  EXPECT_EQ(test.GetCols(), 4);
}

TEST(Getter, test3) {
  S21Matrix test(5, 1);
  EXPECT_EQ(test.GetRows(), 5);
  EXPECT_EQ(test.GetCols(), 1);
}

TEST(Getter, test4) {
  S21Matrix test = S21Matrix();
  EXPECT_EQ(test.GetRows(), 0);
  EXPECT_EQ(test.GetCols(), 0);
}

TEST(Getter, test5) {
  S21Matrix test(100, 100);
  EXPECT_EQ(test.GetRows(), 100);
  EXPECT_EQ(test.GetCols(), 100);
}

TEST(Setter, test1) {
  EXPECT_ANY_THROW({
    S21Matrix test = S21Matrix(3, 3);
    test.SetRows(0);
  });
}
TEST(Setter, test2) {
  EXPECT_ANY_THROW({
    S21Matrix test = S21Matrix(3, 3);
    test.SetRows(-1);
  });
}


TEST(Setter, test3) {
  EXPECT_ANY_THROW({
    S21Matrix test = S21Matrix(3, 3);
    test.SetColumns(-1);
  });
}

TEST(Setter, test4) {
  double result[2][1] = {{0}, {1}};
  EXPECT_NO_THROW({
    S21Matrix test = S21Matrix(2, 2);
    for (int i = 0; i < test.GetRows(); i++) {
      for (int j = 0; j < test.GetCols(); j++) {
        test(i, j) = i + j;
      }
    }
    test.SetColumns(1);
    EXPECT_EQ(test.GetCols(), 1);
    for (int i = 0; i < test.GetRows(); i++) {
      for (int j = 0; j < test.GetCols(); j++) {
        EXPECT_EQ(test(i, j), result[i][j]);
      }
    }
  });
}

TEST(Setter, test5) {
  double result[2][2] = {{0, 1}, {1, 2}};
  EXPECT_NO_THROW({
    S21Matrix test(3, 3);
    for (int i = 0; i < test.GetRows(); i++) {
      for (int j = 0; j < test.GetCols(); j++) {
        test(i, j) = i + j;
      }
    }
    test.SetRows(2);
    test.SetColumns(2);
    EXPECT_EQ(test.GetRows(), 2);
    EXPECT_EQ(test.GetCols(), 2);
    for (int i = 0; i < test.GetRows(); i++) {
      for (int j = 0; j < test.GetCols(); j++) {
        EXPECT_EQ(test(i, j), result[i][j]);
      }
    }
  });
}




TEST(EqMatrixTest, EqualMatrices) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{1, 2}, {3, 4}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_TRUE(mat1.EqMatrix(mat2));
  EXPECT_TRUE(mat2.EqMatrix(mat1));
}

TEST(EqMatrixTest, UnequalMatrices) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{5, 6}, {7, 8}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_FALSE(mat1.EqMatrix(mat2));
  EXPECT_FALSE(mat2.EqMatrix(mat1));
}

TEST(EqMatrixTest, UnequalSizes) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(3, 3);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_FALSE(mat1.EqMatrix(mat2));
  EXPECT_FALSE(mat2.EqMatrix(mat1));
}

TEST(SumMatrixTest, Addition) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{5, 6}, {7, 8}};
  double result[2][2] = {{6, 8}, {10, 12}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1.SumMatrix(mat2);

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), result[i][j]);
    }
  }
}

TEST(SumMatrixTest, DifferentSizes) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double matrix2[3][2] = {{7, 8}, {9, 10}, {11, 12}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(3, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_THROW(mat1.SumMatrix(mat2), std::length_error);
}

TEST(SumMatrixTest, EmptyMatrix) {
  double matrix[2][2] = {{1, 2}, {3, 4}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix();

  EXPECT_THROW(mat1.SumMatrix(mat2), std::length_error);
}

TEST(SubMatrixTest, SubtractMatrix) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{2, 1}, {1, 2}};
  double expected[2][2] = {{-1, 1}, {2, 2}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(2, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1.SubMatrix(mat2);

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), expected[i][j]);
    }
  }
}

TEST(SubMatrixTest, DifferentSizes) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double matrix2[3][2] = {{7, 8}, {9, 10}, {11, 12}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(3, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_THROW(mat1.SubMatrix(mat2), std::length_error);
}

TEST(SubMatrixTest, EmptyMatrix) {
  double matrix[2][2] = {{1, 2}, {3, 4}};

  S21Matrix mat1 = S21Matrix(2, 2);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix();

  EXPECT_THROW(mat1.SubMatrix(mat2), std::length_error);
}

TEST(MulNumberTest, MultiplyNumber) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double num = 2;
  double expected[2][2] = {{2, 4}, {6, 8}};

  S21Matrix mat = S21Matrix(2, 2);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  mat.MulNumber(num);

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), expected[i][j]);
    }
  }
}

TEST(MulNumberTest, MultiplyNumberZero) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double num = 0;
  double expected[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  mat.MulNumber(num);

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), expected[i][j]);
    }
  }
}

TEST(MulNumberTest, MultiplyNumberNegative) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double num = -1;
  double expected[2][2] = {{-1, -2}, {-3, -4}};

  S21Matrix mat = S21Matrix(2, 2);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  mat.MulNumber(num);

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), expected[i][j]);
    }
  }
}

TEST(MulNumberTest, MultiplyNumberFraction) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double num = 0.5;
  double expected[2][2] = {{0.5, 1}, {1.5, 2}};

  S21Matrix mat = S21Matrix(2, 2);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  mat.MulNumber(num);

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), expected[i][j]);
    }
  }
}
///////////////////////
TEST(MulMatrixTest, MultiplyMatrixIdentity) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double identity[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix identityMat = S21Matrix(3, 3);
  for (int i = 0; i < identityMat.GetRows(); i++) {
    for (int j = 0; j < identityMat.GetCols(); j++) {
      identityMat(i, j) = identity[i][j];
    }
  }

  mat.MulMatrix(identityMat);

  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      EXPECT_EQ(mat(i, j), matrix[i][j]);
    }
  }
}

TEST(MulMatrixTest, MultiplyMatrixArbitrary) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double matrix2[3][2] = {{2, 0}, {0, 2}, {1, 1}};
  double expected[2][2] = {{5, 7}, {14, 16}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(3, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  mat1.MulMatrix(mat2);

  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      EXPECT_EQ(mat1(i, j), expected[i][j]);
    }
  }
}

TEST(MulMatrixTest, MultiplyMatrixThrow) {
  double matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double matrix2[4][2] = {{2, 0}, {0, 2}, {1, 1}, {3, 3}};

  S21Matrix mat1 = S21Matrix(2, 3);
  for (int i = 0; i < mat1.GetRows(); i++) {
    for (int j = 0; j < mat1.GetCols(); j++) {
      mat1(i, j) = matrix1[i][j];
    }
  }

  S21Matrix mat2 = S21Matrix(4, 2);
  for (int i = 0; i < mat2.GetRows(); i++) {
    for (int j = 0; j < mat2.GetCols(); j++) {
      mat2(i, j) = matrix2[i][j];
    }
  }

  EXPECT_ANY_THROW({ mat1.MulMatrix(mat2); });
}


TEST(TransposeTest, SquareMatrix) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double expected[3][3] = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix transposed = mat.Transpose();

  for (int i = 0; i < transposed.GetRows(); i++) {
    for (int j = 0; j < transposed.GetCols(); j++) {
      EXPECT_EQ(transposed(i, j), expected[i][j]);
    }
  }
}

TEST(TransposeTest, RectangularMatrix) {
  double matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
  double expected[3][2] = {{1, 4}, {2, 5}, {3, 6}};

  S21Matrix mat = S21Matrix(2, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix transposed = mat.Transpose();

  for (int i = 0; i < transposed.GetRows(); i++) {
    for (int j = 0; j < transposed.GetCols(); j++) {
      EXPECT_EQ(transposed(i, j), expected[i][j]);
    }
  }
}

TEST(TransposeTest, SingleElementMatrix) {
  double matrix[1][1] = {{42}};
  double expected[1][1] = {{42}};

  S21Matrix mat = S21Matrix(1, 1);
  mat(0, 0) = matrix[0][0];

  S21Matrix transposed = mat.Transpose();

  EXPECT_EQ(transposed.GetRows(), 1);
  EXPECT_EQ(transposed.GetCols(), 1);
  EXPECT_EQ(transposed(0, 0), expected[0][0]);
}

TEST(TransposeTest, NonSquareMatrix) {
  double matrix[3][2] = {{1, 2}, {3, 4}, {5, 6}};
  double expected[2][3] = {{1, 3, 5}, {2, 4, 6}};

  S21Matrix mat = S21Matrix(3, 2);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix transposed = mat.Transpose();

  for (int i = 0; i < transposed.GetRows(); i++) {
    for (int j = 0; j < transposed.GetCols(); j++) {
      EXPECT_EQ(transposed(i, j), expected[i][j]);
    }
  }
}

TEST(CalcComplementsTest, SquareMatrix) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double expected[3][3] = {{-3, 6, -3}, {6, -12, 6}, {-3, 6, -3}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  S21Matrix complements = mat.CalcComplements();

  for (int i = 0; i < complements.GetRows(); i++) {
    for (int j = 0; j < complements.GetCols(); j++) {
      EXPECT_EQ(complements(i, j), expected[i][j]);
    }
  }
}

TEST(CalcComplementsTest, NonSquareMatrix) {
  double matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};

  S21Matrix mat = S21Matrix(2, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  EXPECT_THROW(S21Matrix complements = mat.CalcComplements(), std::length_error);
}

TEST(DeterminantTest, SingleElementMatrix) {
  double matrix[1][1] = {{5}};

  S21Matrix mat = S21Matrix(1, 1);
  mat(0, 0) = matrix[0][0];

  double determinant = mat.Determinant();

  EXPECT_EQ(determinant, matrix[0][0]);
}

TEST(DeterminantTest, SquareMatrix) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  double determinant = mat.Determinant();
  EXPECT_EQ(determinant, 0);
}

TEST(DeterminantTest, SpecificNonZeroDeterminant) {
  double matrix[3][3] = {{1, 2, 2}, {4, 5, 5}, {7, 8, 9}};
  double expectedDeterminant = -3;

  S21Matrix mat = S21Matrix(3, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  double determinant = mat.Determinant();
  EXPECT_EQ(determinant, expectedDeterminant);
}

TEST(DeterminantTest, NonSquareMatrix) {
  double matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};

  S21Matrix mat = S21Matrix(2, 3);
  for (int i = 0; i < mat.GetRows(); i++) {
    for (int j = 0; j < mat.GetCols(); j++) {
      mat(i, j) = matrix[i][j];
    }
  }

  EXPECT_THROW(mat.Determinant(), std::length_error);
}

TEST(test_functional, inverese_3x3_3) {
  const int size = 3;
  S21Matrix given(size, size);
  S21Matrix expected(size, size);

  given(0, 0) = 2;
  given(0, 1) = 5;
  given(0, 2) = 7;
  given(1, 0) = 6;
  given(1, 1) = 3;
  given(1, 2) = 4;
  given(2, 0) = 5;
  given(2, 1) = -2;
  given(2, 2) = -3;

  expected(0, 0) = 1;
  expected(0, 1) = -1;
  expected(0, 2) = 1;
  expected(1, 0) = -38;
  expected(1, 1) = 41;
  expected(1, 2) = -34;
  expected(2, 0) = 27;
  expected(2, 1) = -29;
  expected(2, 2) = 24;
  ASSERT_TRUE(given.InverseMatrix() == expected);
}
//////////////////////////////////////////////////////
TEST(OperatorEqual, test1) {
  EXPECT_NO_THROW({
    S21Matrix check = S21Matrix(3, 4);
    for (int i = 0; i < check.GetRows(); i++) {
      for (int j = 0; j < check.GetCols(); j++) {
        check(i, j) = i + j;
      }
    }
    S21Matrix result = S21Matrix();
    result = check;
    EXPECT_EQ(result.GetRows(), check.GetRows());
    EXPECT_EQ(result.GetCols(), check.GetCols());
    for (int i = 0; i < result.GetRows(); i++) {
      for (int j = 0; j < result.GetCols(); j++) {
        EXPECT_EQ(result(i, j), check(i, j));
      }
    }
  });
}

TEST(OperatorEqual, test2) {
  EXPECT_NO_THROW({
    S21Matrix check = S21Matrix();
    for (int i = 0; i < check.GetRows(); i++) {
      for (int j = 0; j < check.GetCols(); j++) {
        check(i, j) = i + j;
      }
    }
    S21Matrix result = S21Matrix(2, 2);
    result = check;
    EXPECT_EQ(result.GetRows(), check.GetRows());
    EXPECT_EQ(result.GetCols(), check.GetCols());
    for (int i = 0; i < result.GetRows(); i++) {
      for (int j = 0; j < result.GetCols(); j++) {
        EXPECT_EQ(result(i, j), check(i, j));
      }
    }
  });
}
//////////////////////////////////////////////////////////////
TEST(OperatorPlus, test1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3.14;
  matrix_a(0, 1) = 0.56;
  matrix_a(1, 0) = -69.3;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -78.14;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -0.3;
  matrix_b(1, 1) = 2;

  result(0, 0) = -75;
  result(0, 1) = 0.56;
  result(1, 0) = -69.6;
  result(1, 1) = 2;

  ASSERT_TRUE((matrix_a + matrix_b) == result);
}



TEST(OperatorMinus, test1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;

  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;

  result(0, 0) = 10;
  result(0, 1) = 2;
  result(1, 0) = -3;
  result(1, 1) = -2;

   ASSERT_TRUE((matrix_a - matrix_b) == result);
}

TEST(OperatorMultNum, test1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix result(2, 2);

  matrix_a(0, 0) = -78.14;
  matrix_a(0, 1) = 0;
  matrix_a(1, 0) = -0.3;
  matrix_a(1, 1) = 2;

  result(0, 0) = -781.4;
  result(0, 1) = 0;
  result(1, 0) = -3;
  result(1, 1) = 20;

  ASSERT_TRUE((matrix_a * 10) == result);
}
////////////////////////////////////////
TEST(OperatorEquality, EqualMatrices) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{1, 2}, {3, 4}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(2, 2);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  EXPECT_TRUE(matrixA == matrixB);
  EXPECT_TRUE(matrixB == matrixA);
}

TEST(OperatorEquality, DifferentMatrices) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{1, 2}, {4, 3}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(2, 2);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  EXPECT_FALSE(matrixA == matrixB);
  EXPECT_FALSE(matrixB == matrixA);
}

TEST(OperatorEquality, DifferentSizes) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(3, 3);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  EXPECT_FALSE(matrixA == matrixB);
  EXPECT_FALSE(matrixB == matrixA);
}

TEST(OperatorAssignment, Assignment) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(2, 2);
  matrixB = matrixA;

  EXPECT_EQ(matrixB.GetRows(), matrixA.GetRows());
  EXPECT_EQ(matrixB.GetCols(), matrixA.GetCols());

  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      EXPECT_EQ(matrixB(i, j), matrixA(i, j));
    }
  }
}



TEST(OperatorAssignment, DifferentSizes) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(3, 3);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  matrixB = matrixA;

  EXPECT_EQ(matrixB.GetRows(), matrixA.GetRows());
  EXPECT_EQ(matrixB.GetCols(), matrixA.GetCols());

  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      EXPECT_EQ(matrixB(i, j), matrixA(i, j));
    }
  }
}
/////////////////////////////////////////////


TEST(OperatorPlusEqual, PlusEqual) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{2, 3}, {4, 5}};
  double result[2][2] = {{3, 5}, {7, 9}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(2, 2);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  matrixA += matrixB;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorPlusEqual, PlusEqual_DifferentSizes) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[3][3] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(3, 3);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  EXPECT_THROW({ matrixA += matrixB; }, std::length_error);

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), matrix1[i][j]);
    }
  }
}
///////////////////////////////////////
TEST(OperatorMinusEqual, MinusEqual) {
  double matrix1[2][2] = {{1, 2}, {3, 4}};
  double matrix2[2][2] = {{2, 3}, {4, 5}};
  double result[2][2] = {{-1, -1}, {-1, -1}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix1[i][j];
    }
  }

  S21Matrix matrixB = S21Matrix(2, 2);
  for (int i = 0; i < matrixB.GetRows(); i++) {
    for (int j = 0; j < matrixB.GetCols(); j++) {
      matrixB(i, j) = matrix2[i][j];
    }
  }

  matrixA -= matrixB;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorMultiplyEqual, MultiplyEqual_Scalar) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double scalar = 2;
  double result[2][2] = {{2, 4}, {6, 8}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix[i][j];
    }
  }

  matrixA *= scalar;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorMultiplyEqual, MultiplyEqual_Scalar_Zero) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double scalar = 0;
  double result[2][2] = {{0, 0}, {0, 0}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix[i][j];
    }
  }

  matrixA *= scalar;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorMultiplyEqual, MultiplyEqual_Scalar_Negative) {
  double matrix[2][2] = {{1, 2}, {3, 4}};
  double scalar = -1;
  double result[2][2] = {{-1, -2}, {-3, -4}};

  S21Matrix matrixA = S21Matrix(2, 2);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix[i][j];
    }
  }

  matrixA *= scalar;

  EXPECT_EQ(matrixA.GetRows(), 2);
  EXPECT_EQ(matrixA.GetCols(), 2);

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), result[i][j]);
    }
  }
}

TEST(OperatorParentheses, test1) {
  double matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  S21Matrix matrixA = S21Matrix(3, 3);
  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      matrixA(i, j) = matrix[i][j];
    }
  }

  for (int i = 0; i < matrixA.GetRows(); i++) {
    for (int j = 0; j < matrixA.GetCols(); j++) {
      EXPECT_EQ(matrixA(i, j), matrix[i][j]);
    }
  }
}






























int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}