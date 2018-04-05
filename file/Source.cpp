#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include<time.h>

int nz;

struct date
{
	int year;
	int m;
	int d;
};

struct k
{
	int * matr;
	double * matr1;
};

void main()
{
	setlocale(LC_ALL, ".1251");
	srand(time(NULL));
	FILE * file;
	while (true)
	{
		printf("Введите номер задания, 0-для выхода "); scanf("%d", &nz);
		if (nz == 0)
		{
			break;
		}
		else if (nz == 1)
		{
			/*1.	Дан файл, содержащий различные даты.
			Каждая дата - это число, месяц и год.
			Найти самую раннюю дату.*/
			unsigned int year;
			unsigned int m;
			unsigned int d;
			if ((file = fopen("time", "w")) != NULL)
			{
				for (int i = 0;i < 10;i++)
				{
					year = 1950 + rand() % 100;
					m = 1 + rand() % 11;
					d = 1 + rand() % 30;
					fprintf(file, "%2d.%2d.%4d\n", d, m, year);
				}
				fclose(file);
			}
			if ((file = fopen("time", "r")) != NULL)
			{
				date dates[10];
				for (int i = 0;i < 10;i++)
				{
					fscanf(file, "%2d.%2d.%4d",
						&dates[i].d, &dates[i].m, &dates[i].year);
				}
				fclose(file);
				for (int i = 0;i < 10;i++)
				{
					printf("%2d.%2d.%4d\n", dates[i].d, dates[i].m, dates[i].year);
				}
				int min_y = 5000;
				int ind_i = 0;
				for (int i = 0;i < 10;i++)
				{
					if (dates[i].year < min_y)
					{
						min_y = dates[i].year;
						ind_i = i;
					}
				}
				int b = 0;
				for (int i = 0;i < 10;i++)
				{
					if (i != ind_i)
					{
						if (dates[i].year == min_y)b = 1;
					}
				}
				if (b == 0)
				{
					printf("Самая раняя дата: %2d.%2d.%4d\n", dates[ind_i].d, dates[ind_i].m, dates[ind_i].year);
				}
			}
		}
		else if (nz == 2)
		{
			/*2.	Дан символьный файл f. Записать в файл g
			компоненты файла f в обратном порядке.*/
			FILE * nfile;
			if ((file = fopen("time", "r")) != NULL)
			{
				char r[10][11];
				int i = 0;
				while (fgets(r[i], sizeof(char) * 12, file) != 0)
				{
					i++;
				}
				for (int i = 0;i < 10;i++)
				{
					printf("%s\n", r[i]);
				}

				//while (r != '\n')
				//{
				//	/**/
				//	r = fgetc(file);
				//}

				/*if ((nfile = fopen("time1", "w")) != NULL)
				{
					fputc(r, nfile);
				}*/
				fclose(file);
				/*fclose(nfile);*/
			}
		}
		else if (nz == 8)
		{
			/*8.	Файл состоит из k компонент структуры, где каждая компонента
			содержит две матрицы : первая размерности m x n, вторая размерности m x l.
			Получить k произведений соответствующих матриц и записать их во второй
			файл. Вывести на экран содержимое первого и второго файлов.*/
			k ks[10];
			int m, n, l;
			printf("Введите количество столбцов "); scanf("%d", &m);
			printf("Введите количество строк "); scanf("%d", &n);
			printf("Введите количество строк для второй матрицы "); scanf("%d", &l);
			for (int i = 0;i < 10;i++)
			{
				ks[i].matr = (int*)malloc(m*n * sizeof(int));
				for (int j = 0;j < m*n;j++)
				{
					ks[i].matr[j] = 1 + rand() % 50;
				}
				ks[i].matr1 = (double*)malloc(m *l * sizeof(double));
				for (int j = 0;j < m*l;j++)
				{
					ks[i].matr1[j] = 1.5 + rand() % 50 / 1.1 + rand() % 50;
				}
			}


			int r = 0;
			if ((file = fopen("file1", "w")) != NULL)
			{
				for (int d = 0;d < 10;d++)
				{
					r = 0;
					for (int i = 0;i < m*n;i++)
					{
						if (r==m-1)
						{
							fprintf(file, "%d\n", ks[d].matr[i]);
							r = 0;
						}
						else
						{
							fprintf(file, "%d-", ks[d].matr[i]);							
							r++;
						}
					}						
					r = 0;
					for (int i = 0;i < m*l;i++)
					{
						if (r == m-1)
						{
							fprintf(file, "%2.2lf\n", ks[d].matr1[i]);
							r = 0;
						}
						else
						{
							fprintf(file, "%2.2lf-", ks[d].matr1[i]);
							r++;
						}
					}					
				}
			}
			fclose(file);
			if ((file = fopen("file1", "r")) != NULL)
			{
				k newK[10];
				int k = 0,sum=0;
				double k1, sum1=0;
				for (int h = 0;h < 10;h++)
				{
					sum = 0;
					sum1 = 0;
					for (int d = 0;d < m*n;d++)
					{
						fscanf(file, "%d-", &k);
						sum += k;
						printf("%d ", k);
					}
					for (int d = 0;d < m*l;d++)
					{
						fscanf(file, "%lf-", &k1);
						sum1 += k1;
						printf("%lf ", k1);
					}
					printf("\nСумма целых = %d\nСумма вещественных = %lf\n", sum, sum1);
				}
				
			}
			/*if ((file = fopen("fileBBB", "wb")) != NULL)
			{
				for (int i = 0;i < 10;i++)
				{
					(ks+i)->matr = (int*)malloc(m*n * sizeof(int));
					for (int j = 0;j < m*n;j++)
					{
						(ks + i)->matr[j] = 1 + rand() % 50;
					}
					(ks + i)->matr1 = (double*)malloc(m *l * sizeof(double));
					for (int j = 0;j < m*l;j++)
					{
						(ks + i)->matr1[j] = 1.5 + rand() % 50 / 1.1 + rand() % 50;
					}

					fwrite((ks + i), sizeof(k), 1, file);
				}
			}
			fclose(file);*/

			//printf("\n---------------------------\n");
			//if ((file = fopen("fileBBB", "rb")) != NULL)
			//{
			//	k newK[10];
			//	for (size_t i = 0; i < 10; i++)
			//	{
			//		fread(&newK[i], sizeof(k), 1, file);

			//		for (int j = 0;j < m*n;j++)
			//		{
			//			printf("%d\t", newK[i].matr[j]);
			//		}
			//		for (int j = 0;j < m*l;j++)
			//		{
			//			printf("%lf\t", newK[i].matr1[j]);
			//		}
			//		printf("\n ------- %i ------- \n",i);

			//		int rrr = 5;
			//		/*while ()
			//		{

			//		}*/
			//	}

			//	
			//}
			//fclose(file);
		}
		else
		{
			printf("Ошибка\n");
			continue;
		}
	}
}