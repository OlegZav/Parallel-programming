#include <iostream>
#include <string>
#include <locale.h>
#include <omp.h>
#include <stdio.h>

using namespace std;

void error_to_console(string out_string, string out_retry)
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cout << out_string << endl;
	cout << out_retry;
}

int main()
{	
	setlocale(LC_ALL, "Russian");

	int i, j, k, value, matrix, max_value;
	double t1, t2;
	bool flag_thread = true, flag_matrix = true;
	string thread_input, matrix_size;
	
	max_value = omp_get_max_threads();
	
	cout << "Программа вычисляет произведение матриц при помощи библиотеки OpenMP" << endl;
	cout << "Введите неоходимое количество потоков" << endl;
	cout << "Подсказка. В вашей системе доступно " << max_value << " потоков" << endl;
	cout << "Количество потоков = ";
	
	while (flag_thread == true)
	{
		try
		{
			cin >> thread_input;
			value = stoi(thread_input);
	
			if (value < 0 || value > max_value)
				error_to_console("Введено число меньшее 1 или большее лимита. Введите значение повторно",
					"Количество потоков = ");
			else
				omp_set_num_threads(value);
				flag_thread = false;

		}
		catch (invalid_argument)
		{
			error_to_console("Введён некорректный элемент. Введите значение повторно",
							 "Количество потоков = ");
		}
	}
	cout << "Введите размер матрицы = ";
	while (flag_matrix == true)
	{
		try
		{
			cin >> matrix_size;
			matrix = stoi(matrix_size);
			
			if (matrix < 0)
				error_to_console("Введено число меньшее 1. Введите значение повторно",
								 "Введите размер матрицы = ");
			else
				flag_matrix = false;
		}
		catch (invalid_argument)
		{
			error_to_console("Введён некорректный элемент. Введите значение повторно",
							 "Введите размер матрицы = ");
		}
	}
	// инициализация матриц
	int** a = new int* [matrix];
	for (i = 0; i < matrix; i++)
		a[i] = new int[matrix];
	
	int** b = new int* [matrix];
	for (i = 0; i < matrix; i++)
		b[i] = new int[matrix];
	
	int** c = new int* [matrix];
	for (i = 0; i < matrix; i++)
		c[i] = new int[matrix];
	
	// заполнение матриц
	for (i = 0; i < matrix; i++)
		for (j = 0; j < matrix; j++)
			a[i][j] = b[i][j] = i * j;
	
	cout << "Программа начала свою работу" << endl;
	t1 = omp_get_wtime();
	
	// основной вычислительный блок
	#pragma omp parallel for shared(a, b, c) private(i, j, k)
	for (i = 0; i < matrix; i++)
	{
		for (j = 0; j < matrix; j++)
		{
			c[i][j] = 0.0;
			for (k = 0; k < matrix; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
	}
	
	t2 = omp_get_wtime();
	cout << "Программа закончила свою работу" << endl;
	
	for (i = 0; i < matrix; i++)
		delete a[i], b[i], c[i];
	delete[] a, b, c;

	cout << "Время работы программы на " << value 
		<< " потоках для квадратной матрицы размером " << matrix 
		<< " элементов составило " << t2 - t1 << " секунд" << endl;
	
	return 0;
}