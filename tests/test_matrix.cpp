#include <gtest/gtest.h>
#include <string>
#include <cstdint>
#include <sstream>
#include <list>
#include "matrix.h"
using namespace std;

TEST(Matrix, DefaultValue)
{
	Matrix<int> m1{ -1 };
	EXPECT_EQ(-1, m1[0][0]);
	EXPECT_EQ(-1, m1[10][10]);

	int v = m1[3][3];
	EXPECT_EQ(-1, v);

	Matrix<double> m2{ 0 };
	EXPECT_EQ(0, m2[0][0]);
	EXPECT_EQ(0, m2[10][10]);
	double d = m2[3][3];
	EXPECT_EQ(0, d);
}

TEST(Matrix, AssignValue)
{
	Matrix<int> m{ -1 };
	m[1][1] = 42;
	EXPECT_EQ(42, m[1][1]);
	EXPECT_EQ(-1, m[0][0]);
}

TEST(Matrix, MatrixSize)
{
	Matrix<int> m{ -1 };
	EXPECT_EQ(0, m.size());
	m[1][1] = 5;
	EXPECT_EQ(1, m.size());
	m[2][2] = 5;
	EXPECT_EQ(2, m.size());
}

TEST(Matrix, AssignDefaultValue)
{
	Matrix<int> m{ -1 };
	m[1][1] = 42;
	m[1][1] = -1;
	EXPECT_EQ(0, m.size());
}

TEST(Matrix, CanonicalEq)
{
	Matrix<int> m{ 0 };
	((m[100][100] = 314) = 0) = 217;
	EXPECT_EQ(217, m[100][100]);
}

TEST(Matrix, UnorderedIterate)
{
	Matrix<int> m{ 0 };
	for (int i = 0; i < 5; i++)
		m[i][i] = i * i;

	for (auto& it : m)
	{
		size_t i = get<0>(it->first);
		EXPECT_EQ(i, get<1>(it->first));
		EXPECT_EQ(i * i, it->second);
	}
}