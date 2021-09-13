#include <iostream>
#include <random>
#include <string>
#include <sstream>
#include <array>

template <typename T, int M, int N>
using Matrix = int[M][N];

template <int M, int N>
void setup_matrices(
	Matrix<int, M, N> &matA,
	Matrix<int, M, N> &matB)
{
	static std::random_device device;
	static std::mt19937 generator(device());

	static std::uniform_int_distribution<int> distribution(0, 1);

	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			matA[i][j] = distribution(generator);
			matB[i][j] = distribution(generator);
		}
	}
}

template <int M, int N>
void print_matrix(Matrix<int, M, N> &mat)
{
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			std::cout << mat[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

template <int M, int N, int P>
void multiply_matrices(
	Matrix<int, M, N>& matA,
	Matrix<int, N, P>& matB,
	Matrix<int, M, P>& matO)
{
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < P; ++j)
		{
			matO[i][j] = 0;
			for (int k = 0; k < N; ++k)
			{
				matO[i][j] += matA[i][k] * matB[k][j];
			}
		}
	}

}

template <int M, int N>
void add_matrices(
	Matrix<int, M, N>& matA,
	Matrix<int, M, N>& matB,
	Matrix<int, M, N>& matO)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			matO[i][j] = matA[i][j] + matB[i][j];
		}
	}
}

template <int M, int N>
void subtract_matrices(
	Matrix<int, M, N>& matA,
	Matrix<int, M, N>& matB,
	Matrix<int, M, N>& matO)
{
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			matO[i][j] = matA[i][j] - matB[i][j];
		}
	}
}

template <int N, int M>
int get_determinant(Matrix<int, N, M>& mat)
{
	return 0;
}


int get_determinant(Matrix<int, 2, 2>& mat)
{
	return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}


int get_determinant(Matrix<int, 3, 3>& mat)
{
	Matrix<int, 2, 2> matA = {
		{mat[1][1], mat[1][2]},
		{mat[2][1], mat[2][2]}
	};

	Matrix<int, 2, 2> matB = {
		{mat[1][0], mat[1][2]},
		{mat[2][0], mat[2][2]}
	};

	Matrix<int, 2, 2> matC = {
		{mat[1][0], mat[1][1]},
		{mat[2][0], mat[2][1]}
	};

	return mat[0][0] * get_determinant(matA)
		- mat[0][1] * get_determinant(matB)
		+ mat[0][2] * get_determinant(matC);
}

int get_determinant(Matrix<int, 4, 4>& mat)
{
	Matrix<int, 3, 3> matA = {
		{mat[1][1], mat[1][2], mat[1][3]},
		{mat[2][1], mat[2][2], mat[2][3]},
		{mat[3][1], mat[3][2], mat[3][3]}
	};

	Matrix<int, 3, 3> matB = {
		{mat[1][0], mat[1][2], mat[1][3]},
		{mat[2][0], mat[2][2], mat[2][3]},
		{mat[3][0], mat[3][2], mat[3][3]}
	};

	Matrix<int, 3, 3> matC = {
		{mat[1][0], mat[1][1], mat[1][3]},
		{mat[2][0], mat[2][1], mat[2][3]},
		{mat[3][0], mat[3][1], mat[3][3]}
	};

	Matrix<int, 3, 3> matD = {
		{mat[1][0], mat[1][1], mat[1][2]},
		{mat[2][0], mat[2][1], mat[2][2]},
		{mat[3][0], mat[3][1], mat[3][2]}
	};

	return mat[0][0] * get_determinant(matA)
		- mat[0][1] * get_determinant(matB)
		+ mat[0][2] * get_determinant(matC)
		- mat[0][3] * get_determinant(matD);
}

template <int M, int N>
void get_transposed(
	Matrix<int, M, N>& mat,
	Matrix<int, N, M>& matO)
{
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			matO[j][i] = mat[i][j];
		}
	}
}

void convert_matrix(
	Matrix<int, 3, 3>& mat,
	Matrix<int, 4, 4>& matO)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			matO[i][j] = mat[i][j];
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		matO[3][i] = 0;
		matO[i][3] = 0;
	}
	matO[3][3] = 1;
}

int main(int argc, char *argv[])
{
	Matrix<int, 3, 3> matA;
	Matrix<int, 3, 3> matB;

	setup_matrices(matA, matB);

	std::cout << "Matrix A" << std::endl;
	print_matrix<3, 3>(matA);

	std::cout << "Matrix B" << std::endl;
	print_matrix<3, 3>(matB);

	char buf[1024];
	while (1)
	{
		std::cout << "Command: ";
		std::cin.getline(buf, 1024);

		std::istringstream tokens(buf);

		std::string command;
		tokens >> command;

		if (command == "m")
		{
			Matrix<int, 3, 3> matO;
			multiply_matrices(matA, matB, matO);

			std::cout << "AxB" << std::endl;
			print_matrix<3, 3>(matO);
		}
		else if (command == "a")
		{
			Matrix<int, 3, 3> matO;
			add_matrices(matA, matB, matO);

			std::cout << "A+B" << std::endl;
			print_matrix<3, 3>(matO);
		}
		else if (command == "d")
		{
			Matrix<int, 3, 3> matO;
			subtract_matrices(matA, matB, matO);

			std::cout << "A-B" << std::endl;
			print_matrix<3, 3>(matO);
		}
		else if (command == "r")
		{
			int determinantA = get_determinant(matA);
			int determinantB = get_determinant(matB);

			std::cout << "Det(A): " << determinantA << std::endl;
			std::cout << "Det(B): " << determinantB << std::endl;
		}
		else if (command == "t")
		{
			Matrix<int, 3, 3> transposedA, transposedB;
			get_transposed(matA, transposedA);
			get_transposed(matB, transposedB);

			int determinantA = get_determinant(transposedA);
			int determinantB = get_determinant(transposedB);

			std::cout << "Transpose(A)" << std::endl;
			print_matrix<3, 3>(transposedA);

			std::cout << "Det(Transpose(A)): " << determinantA << std::endl;

			std::cout << "Transpose(B)" << std::endl;
			print_matrix<3, 3>(transposedB);

			std::cout << "Det(Transpose(B)): " << determinantB << std::endl;
		}
		else if (command == "h")
		{
			Matrix<int, 4, 4> convertedA, convertedB;
			
			convert_matrix(matA, convertedA);
			convert_matrix(matB, convertedB);

			int determinantA = get_determinant(convertedA);
			int determinantB = get_determinant(convertedB);

			std::cout << "Convert(A)" << std::endl;
			print_matrix<4, 4>(convertedA);

			std::cout << "Det(Convert(A)): " << determinantA << std::endl;

			std::cout << "Convert(B)" << std::endl;
			print_matrix<4, 4>(convertedB);

			std::cout << "Det(Convert(B)): " << determinantB << std::endl;
		}
		else if (command == "s")
		{
			setup_matrices(matA, matB);

			std::cout << "Matrix A" << std::endl;
			print_matrix<3, 3>(matA);
			
			std::cout << "Matrix B" << std::endl;
			print_matrix<3, 3>(matB);
		}
		else if (command == "q")
		{
			break;
		}
		else
		{
			std::cout << "Unknown Command." << std::endl;
		}
	}
}