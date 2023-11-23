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
	
	cout << "��������� ��������� ������������ ������ ��� ������ ���������� OpenMP" << endl;
	cout << "������� ���������� ���������� �������" << endl;
	cout << "���������. � ����� ������� �������� " << max_value << " �������" << endl;
	cout << "���������� ������� = ";
	
	while (flag_thread == true)
	{
		try
		{
			cin >> thread_input;
			value = stoi(thread_input);
	
			if (value < 0 || value > max_value)
				error_to_console("������� ����� ������� 1 ��� ������� ������. ������� �������� ��������",
					"���������� ������� = ");
			else
				omp_set_num_threads(value);
				flag_thread = false;

		}
		catch (invalid_argument)
		{
			error_to_console("����� ������������ �������. ������� �������� ��������",
							 "���������� ������� = ");
		}
	}
	cout << "������� ������ ������� = ";
	while (flag_matrix == true)
	{
		try
		{
			cin >> matrix_size;
			matrix = stoi(matrix_size);
			
			if (matrix < 0)
				error_to_console("������� ����� ������� 1. ������� �������� ��������",
								 "������� ������ ������� = ");
			else
				flag_matrix = false;
		}
		catch (invalid_argument)
		{
			error_to_console("����� ������������ �������. ������� �������� ��������",
							 "������� ������ ������� = ");
		}
	}
	// ������������� ������
	int** a = new int* [matrix];
	for (i = 0; i < matrix; i++)
		a[i] = new int[matrix];
	
	int** b = new int* [matrix];
	for (i = 0; i < matrix; i++)
		b[i] = new int[matrix];
	
	int** c = new int* [matrix];
	for (i = 0; i < matrix; i++)
		c[i] = new int[matrix];
	
	// ���������� ������
	for (i = 0; i < matrix; i++)
		for (j = 0; j < matrix; j++)
			a[i][j] = b[i][j] = i * j;
	
	cout << "��������� ������ ���� ������" << endl;
	t1 = omp_get_wtime();
	
	// �������� �������������� ����
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
	cout << "��������� ��������� ���� ������" << endl;
	
	for (i = 0; i < matrix; i++)
		delete a[i], b[i], c[i];
	delete[] a, b, c;

	cout << "����� ������ ��������� �� " << value 
		<< " ������� ��� ���������� ������� �������� " << matrix 
		<< " ��������� ��������� " << t2 - t1 << " ������" << endl;
	
	return 0;
}