# Отчёт по заданию с использованием CUDA

## Информация о программе

Программа осуществляет умножение квадратных матриц размером N*N при помощи библиотеки параллельного программирования CUDA. Программа написана с использованием языка программирования C++.

## Руководство по работе с программой

1. Запустить программу любым удобным способом (в зависимости от ОС и использующихся средств);
2. Ввести необходимое для работы программы количество потоков;
3. Ввести размеры квадратных матриц, используемых для вычислений;
4. Дождаться окончания работы программы и получить результат.

## Технические характеристики

* Процессор: Intel Core i5-13400
* Видеокарта: NVIDIA GeForce RTX 4060 (8 Gb)
* ОЗУ: 32 Гб DDR5
* ОС: Windows 11 22H2
* Версия драйвера видеокарты: 546.17
* ПО для запуска: Microsoft Visual Studio 2022, версия 17.8.1
* Версия CUDA: 12.3, V12.3.103

## Результаты исследования 

* Исследование зависимости скорости работы программы от количества потоков на блок

    Для исследования запуски производились для квадратных матриц размером 2000*2000. В качестве времени работы бралось среднее значение 5 запусков для каждого потока

    ![thread](./pictures/threads.jpg) 

* Исследование зависимости скорости работы программы от размера матриц

    Для исследования запуски производились для 16 потоков на блок. В качестве времени работы бралось среднее значение 5 запусков для различных размеров

    ![matrix](./pictures/matrix.jpg)

## Информация об обучающемся
* ФИО: Завьялов Олег Валерьевич
* Группа: ИТ-12МО