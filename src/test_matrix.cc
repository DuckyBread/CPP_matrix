#include <gtest/gtest.h>

#include "matrix.h"

TEST(MatrixConstructor, test_1) { EXPECT_ANY_THROW(custom::Matrix a(0, 3)); }

TEST(MatrixConstructor, test_2) { EXPECT_ANY_THROW(custom::Matrix a(1, 0)); }

TEST(MatrixConstructor, test_3) { EXPECT_ANY_THROW(custom::Matrix a(-1, 2)); }

TEST(MatrixConstructor, test_4) { EXPECT_ANY_THROW(custom::Matrix a(1, -5)); }

TEST(MatrixConstructor, test_5) { EXPECT_ANY_THROW(custom::Matrix a(0, 0)); }

TEST(MatrixConstructor, test_6) { EXPECT_ANY_THROW(custom::Matrix a(-3, -6)); }

TEST(MatrixConstructor, test_7) {
  custom::Matrix a;
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }
  custom::Matrix b(a);
  EXPECT_NO_THROW(custom::Matrix(std::move(b)));
}

TEST(Methods, SetRows_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  EXPECT_ANY_THROW(a.SetRows(-1));
}

TEST(Methods, SetRows_2) {
  custom::Matrix a(2, 2);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  EXPECT_NO_THROW(a.SetRows(3));
  ASSERT_EQ(a(0, 0), 1);
  ASSERT_EQ(a(0, 1), 2);
  ASSERT_EQ(a(1, 0), 3);
  ASSERT_EQ(a(1, 1), 4);
  ASSERT_EQ(a(2, 0), 0);
  ASSERT_EQ(a(2, 1), 0);
}

TEST(Methods, SetCols_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  EXPECT_ANY_THROW(a.SetColumns(-1));
}

TEST(Methods, SetCols_2) {
  custom::Matrix a(2, 2);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  EXPECT_NO_THROW(a.SetColumns(3));
  ASSERT_EQ(a(0, 0), 1);
  ASSERT_EQ(a(0, 1), 2);
  ASSERT_EQ(a(0, 2), 0);
  ASSERT_EQ(a(1, 0), 3);
  ASSERT_EQ(a(1, 1), 4);
  ASSERT_EQ(a(1, 2), 0);
}

TEST(Methods, EqMatrix_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  custom::Matrix b(a);
  EXPECT_NO_THROW(a.EqMatrix(b));
  ASSERT_TRUE(a.EqMatrix(b));

  ASSERT_EQ(a(0, 0), b(0, 0));
  ASSERT_EQ(a(0, 1), b(0, 1));
  ASSERT_EQ(a(0, 2), b(0, 2));
  ASSERT_EQ(a(1, 0), b(1, 0));
  ASSERT_EQ(a(1, 1), b(1, 1));
  ASSERT_EQ(a(1, 2), b(1, 2));
  ASSERT_EQ(a(2, 0), b(2, 0));
  ASSERT_EQ(a(2, 1), b(2, 1));
  ASSERT_EQ(a(2, 2), b(2, 2));
}

TEST(Methods, EqMatrix_2) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  custom::Matrix b(a);
  b(1, 1) = 10.;
  EXPECT_NO_THROW(a.EqMatrix(b));
  ASSERT_FALSE(a.EqMatrix(b));

  ASSERT_EQ(a(0, 0), b(0, 0));
  ASSERT_EQ(a(0, 1), b(0, 1));
  ASSERT_EQ(a(0, 2), b(0, 2));
  ASSERT_EQ(a(1, 0), b(1, 0));

  ASSERT_NE(a(1, 1), b(1, 1));

  ASSERT_EQ(a(1, 2), b(1, 2));
  ASSERT_EQ(a(2, 0), b(2, 0));
  ASSERT_EQ(a(2, 1), b(2, 1));
  ASSERT_EQ(a(2, 2), b(2, 2));
}

TEST(Methods, EqMatrix_3) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  custom::Matrix b(2, 2);
  for (int i = 0, counter = 1; i < b.GetRows(); ++i) {
    for (int j = 0; j < b.GetColumns(); ++j) {
      b(i, j) = counter++;
    }
  }

  EXPECT_NO_THROW(a.EqMatrix(b));
  ASSERT_FALSE(a.EqMatrix(b));
}

TEST(Methods, SumMatrix_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  custom::Matrix b(a);
  EXPECT_NO_THROW(a.SumMatrix(b));
  ASSERT_EQ(a(0, 0), 2);
  ASSERT_EQ(a(0, 1), 4);
  ASSERT_EQ(a(0, 2), 6);
  ASSERT_EQ(a(1, 0), 8);
  ASSERT_EQ(a(1, 1), 10);
  ASSERT_EQ(a(1, 2), 12);
  ASSERT_EQ(a(2, 0), 14);
  ASSERT_EQ(a(2, 1), 16);
  ASSERT_EQ(a(2, 2), 18);
}

TEST(Methods, SumMatrix_2) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  custom::Matrix b(2, 3);
  EXPECT_ANY_THROW(a.SumMatrix(b));
}

TEST(Methods, SumMatrix_3) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  custom::Matrix b(3, 2);
  EXPECT_ANY_THROW(a.SumMatrix(b));
}

TEST(Methods, SubMatrix_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  custom::Matrix b(a);
  EXPECT_NO_THROW(a.SubMatrix(b));
  ASSERT_EQ(a(0, 0), 0);
  ASSERT_EQ(a(0, 1), 0);
  ASSERT_EQ(a(0, 2), 0);
  ASSERT_EQ(a(1, 0), 0);
  ASSERT_EQ(a(1, 1), 0);
  ASSERT_EQ(a(1, 2), 0);
  ASSERT_EQ(a(2, 0), 0);
  ASSERT_EQ(a(2, 1), 0);
  ASSERT_EQ(a(2, 2), 0);
}

TEST(Methods, SubMatrix_2) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  custom::Matrix b(2, 3);
  EXPECT_ANY_THROW(a.SubMatrix(b));
}

TEST(Methods, SubMatrix_3) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  custom::Matrix b(3, 2);
  EXPECT_ANY_THROW(a.SubMatrix(b));
}

TEST(Methods, MulNumber_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  double b = -0.01;
  EXPECT_NO_THROW(a.MulNumber(b));
  ASSERT_EQ(a(0, 0), -0.01);
  ASSERT_EQ(a(0, 1), -0.02);
  ASSERT_EQ(a(0, 2), -0.03);
  ASSERT_EQ(a(1, 0), -0.04);
  ASSERT_EQ(a(1, 1), -0.05);
  ASSERT_EQ(a(1, 2), -0.06);
  ASSERT_EQ(a(2, 0), -0.07);
  ASSERT_EQ(a(2, 1), -0.08);
  ASSERT_EQ(a(2, 2), -0.09);
}

TEST(Methods, MulMatrix_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }
  custom::Matrix b(a);

  EXPECT_NO_THROW(a.MulMatrix(b));

  ASSERT_EQ(a(0, 0), 30);
  ASSERT_EQ(a(0, 1), 94);
  ASSERT_EQ(a(0, 2), 681);
  ASSERT_EQ(a(1, 0), 66);
  ASSERT_EQ(a(1, 1), 205);
  ASSERT_EQ(a(1, 2), 1482);
  ASSERT_EQ(a(2, 0), 102);
  ASSERT_EQ(a(2, 1), 316);
  ASSERT_EQ(a(2, 2), 2283);
}

TEST(Methods, MulMatrix_2) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }
  custom::Matrix b(2, 3);
  for (int i = 0, counter = 1; i < b.GetRows(); ++i) {
    for (int j = 0; j < b.GetColumns(); ++j) {
      b(i, j) = counter++;
    }
  }

  EXPECT_ANY_THROW(a.MulMatrix(b));
}

TEST(Methods, Transpose_1) {
  custom::Matrix a(3, 2);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }
  custom::Matrix b;
  EXPECT_NO_THROW(b = a.Transpose());

  ASSERT_EQ(b(0, 0), 1);
  ASSERT_EQ(b(0, 1), 3);
  ASSERT_EQ(b(0, 2), 5);
  ASSERT_EQ(b(1, 0), 2);
  ASSERT_EQ(b(1, 1), 4);
  ASSERT_EQ(b(1, 2), 6);
}

TEST(Methods, Determinant_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }
  a(0, 1) = 9.;
  double det;

  EXPECT_NO_THROW(det = a.Determinant());

  ASSERT_EQ(det, 42);
}

TEST(Methods, CalcComplements_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }
  custom::Matrix b;
  EXPECT_NO_THROW(b = a.CalcComplements());

  ASSERT_EQ(b(0, 0), -3);
  ASSERT_EQ(b(0, 1), 6);
  ASSERT_EQ(b(0, 2), -3);
  ASSERT_EQ(b(1, 0), 6);
  ASSERT_EQ(b(1, 1), -12);
  ASSERT_EQ(b(1, 2), 6);
  ASSERT_EQ(b(2, 0), -3);
  ASSERT_EQ(b(2, 1), 6);
  ASSERT_EQ(b(2, 2), -3);
}

TEST(Methods, CalcComplements_2) {
  custom::Matrix a(3, 2);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  EXPECT_ANY_THROW(custom::Matrix b = a.CalcComplements());
}

TEST(Methods, InverseMatrix_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }
  custom::Matrix b;
  EXPECT_ANY_THROW(b = a.InverseMatrix());
}

TEST(Methods, InverseMatrix_2) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }
  a(0, 1) = 9.;
  custom::Matrix b;
  EXPECT_NO_THROW(b = a.InverseMatrix());

  EXPECT_NEAR(b(0, 0), -0.0714286, 0.000001);
  EXPECT_NEAR(b(0, 1), -1.35714, 0.00001);
  EXPECT_NEAR(b(0, 2), 0.928571, 0.000001);
  EXPECT_NEAR(b(1, 0), 0.142857, 0.000001);
  EXPECT_NEAR(b(1, 1), -0.285714, 0.000001);
  EXPECT_NEAR(b(1, 2), 0.142857, 0.000001);
  EXPECT_NEAR(b(2, 0), -0.0714286, 0.000001);
  EXPECT_NEAR(b(2, 1), 1.30952, 0.00001);
  EXPECT_NEAR(b(2, 2), -0.738095, 0.000001);
}

TEST(ReloadOperators, operator_double_eq_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  custom::Matrix b(a);
  EXPECT_NO_THROW(b == a);
  ASSERT_TRUE(b == a);

  ASSERT_EQ(a(0, 0), b(0, 0));
  ASSERT_EQ(a(0, 1), b(0, 1));
  ASSERT_EQ(a(0, 2), b(0, 2));
  ASSERT_EQ(a(1, 0), b(1, 0));
  ASSERT_EQ(a(1, 1), b(1, 1));
  ASSERT_EQ(a(1, 2), b(1, 2));
  ASSERT_EQ(a(2, 0), b(2, 0));
  ASSERT_EQ(a(2, 1), b(2, 1));
  ASSERT_EQ(a(2, 2), b(2, 2));
}

TEST(ReloadOperators, operator_sum_eq_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  custom::Matrix c(a);
  EXPECT_NO_THROW(c += a);

  ASSERT_EQ(c(0, 0), 2);
  ASSERT_EQ(c(0, 1), 4);
  ASSERT_EQ(c(0, 2), 6);
  ASSERT_EQ(c(1, 0), 8);
  ASSERT_EQ(c(1, 1), 10);
  ASSERT_EQ(c(1, 2), 12);
  ASSERT_EQ(c(2, 0), 14);
  ASSERT_EQ(c(2, 1), 16);
  ASSERT_EQ(c(2, 2), 18);
}

TEST(ReloadOperators, operator_sub_eq_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  custom::Matrix c(a);
  EXPECT_NO_THROW(c -= a);

  ASSERT_EQ(c(0, 0), 0);
  ASSERT_EQ(c(0, 1), 0);
  ASSERT_EQ(c(0, 2), 0);
  ASSERT_EQ(c(1, 0), 0);
  ASSERT_EQ(c(1, 1), 0);
  ASSERT_EQ(c(1, 2), 0);
  ASSERT_EQ(c(2, 0), 0);
  ASSERT_EQ(c(2, 1), 0);
  ASSERT_EQ(c(2, 2), 0);
}

TEST(ReloadOperators, operator_mulNum_eq_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  double c = -3;
  EXPECT_NO_THROW(a *= c);

  ASSERT_EQ(a(0, 0), -3);
  ASSERT_EQ(a(0, 1), -6);
  ASSERT_EQ(a(0, 2), -9);
  ASSERT_EQ(a(1, 0), -12);
  ASSERT_EQ(a(1, 1), -15);
  ASSERT_EQ(a(1, 2), -18);
  ASSERT_EQ(a(2, 0), -21);
  ASSERT_EQ(a(2, 1), -24);
  ASSERT_EQ(a(2, 2), -27);
}

TEST(ReloadOperators, operator_mulMatrix_eq_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  custom::Matrix c(a);
  EXPECT_NO_THROW(c *= a);

  ASSERT_EQ(c(0, 0), 30);
  ASSERT_EQ(c(0, 1), 94);
  ASSERT_EQ(c(0, 2), 681);
  ASSERT_EQ(c(1, 0), 66);
  ASSERT_EQ(c(1, 1), 205);
  ASSERT_EQ(c(1, 2), 1482);
  ASSERT_EQ(c(2, 0), 102);
  ASSERT_EQ(c(2, 1), 316);
  ASSERT_EQ(c(2, 2), 2283);
}

TEST(ReloadOperators, sum_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  custom::Matrix b(a), c;
  EXPECT_NO_THROW(c = b + a);

  ASSERT_EQ(c(0, 0), 2);
  ASSERT_EQ(c(0, 1), 4);
  ASSERT_EQ(c(0, 2), 6);
  ASSERT_EQ(c(1, 0), 8);
  ASSERT_EQ(c(1, 1), 10);
  ASSERT_EQ(c(1, 2), 12);
  ASSERT_EQ(c(2, 0), 14);
  ASSERT_EQ(c(2, 1), 16);
  ASSERT_EQ(c(2, 2), 18);
}

TEST(ReloadOperators, sub_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  custom::Matrix b(a), c;
  EXPECT_NO_THROW(c = b - a);

  ASSERT_EQ(c(0, 0), 0);
  ASSERT_EQ(c(0, 1), 0);
  ASSERT_EQ(c(0, 2), 0);
  ASSERT_EQ(c(1, 0), 0);
  ASSERT_EQ(c(1, 1), 0);
  ASSERT_EQ(c(1, 2), 0);
  ASSERT_EQ(c(2, 0), 0);
  ASSERT_EQ(c(2, 1), 0);
  ASSERT_EQ(c(2, 2), 0);
}

TEST(ReloadOperators, eq_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  custom::Matrix b;
  EXPECT_NO_THROW(b.operator=(a));
  ASSERT_EQ(b(0, 0), 1);
  ASSERT_EQ(b(0, 1), 2);
  ASSERT_EQ(b(0, 2), 3);
  ASSERT_EQ(b(1, 0), 4);
  ASSERT_EQ(b(1, 1), 5);
  ASSERT_EQ(b(1, 2), 6);
  ASSERT_EQ(b(2, 0), 7);
  ASSERT_EQ(b(2, 1), 8);
  ASSERT_EQ(b(2, 2), 9);
}

TEST(ReloadOperators, eq_2) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  custom::Matrix b;
  EXPECT_NO_THROW(b = a);
  ASSERT_EQ(b(0, 0), 1);
  ASSERT_EQ(b(0, 1), 2);
  ASSERT_EQ(b(0, 2), 3);
  ASSERT_EQ(b(1, 0), 4);
  ASSERT_EQ(b(1, 1), 5);
  ASSERT_EQ(b(1, 2), 6);
  ASSERT_EQ(b(2, 0), 7);
  ASSERT_EQ(b(2, 1), 8);
  ASSERT_EQ(b(2, 2), 9);
}

TEST(ReloadOperators, brackets_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  EXPECT_ANY_THROW(a(4, 3));
}

TEST(ReloadOperators, brackets_2) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  EXPECT_ANY_THROW(a(2, 4));
}

TEST(ReloadOperators, brackets_3) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  EXPECT_ANY_THROW(a(-1, 1));
}

TEST(ReloadOperators, brackets_4) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  EXPECT_ANY_THROW(a(0, -6));
}

TEST(ReloadOperators, constBrackets_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }
  const custom::Matrix b(a);

  const double c = b(0, 1);
  ASSERT_DOUBLE_EQ(2, c);
}

TEST(ReloadOperators, constBrackets_2) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }
  const custom::Matrix b(a);

  EXPECT_ANY_THROW((b(4, 1)));
}

TEST(ReloadOperators, MulMatrix_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }

  custom::Matrix b(a), c;
  EXPECT_NO_THROW(c = b * a);

  ASSERT_EQ(c(0, 0), 30);
  ASSERT_EQ(c(0, 1), 94);
  ASSERT_EQ(c(0, 2), 681);
  ASSERT_EQ(c(1, 0), 66);
  ASSERT_EQ(c(1, 1), 205);
  ASSERT_EQ(c(1, 2), 1482);
  ASSERT_EQ(c(2, 0), 102);
  ASSERT_EQ(c(2, 1), 316);
  ASSERT_EQ(c(2, 2), 2283);
}

TEST(ReloadOperators, MulNum_1) {
  custom::Matrix a(3, 3);
  for (int i = 0, counter = 1; i < a.GetRows(); ++i) {
    for (int j = 0; j < a.GetColumns(); ++j) {
      a(i, j) = counter++;
    }
  }
  custom::Matrix c;
  double b = -3.;

  EXPECT_NO_THROW(c = a * b);

  ASSERT_EQ(c(0, 0), -3);
  ASSERT_EQ(c(0, 1), -6);
  ASSERT_EQ(c(0, 2), -9);
  ASSERT_EQ(c(1, 0), -12);
  ASSERT_EQ(c(1, 1), -15);
  ASSERT_EQ(c(1, 2), -18);
  ASSERT_EQ(c(2, 0), -21);
  ASSERT_EQ(c(2, 1), -24);
  ASSERT_EQ(c(2, 2), -27);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
