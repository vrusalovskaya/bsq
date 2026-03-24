#include <stdlib.h>
#include <stdio.h>
#include "sqr.h"
char *sqr1 = "..o..\n.o..o\n.....";

char *sqr2 = "...........................\n....o......................\n............o..............\n...........................\n....o......................\n...............o...........\n...........................\n......o..............o.....\n..o.......o................";


int b_len(char *sqr)
{
	int counter;

	counter = 0;
	while (sqr[counter] != '\n')
		counter++;
	return (counter);
}

int a_len(char *sqr)
{
	int counter;

	counter = 0;
	while (*sqr)
	{
		if (*sqr == '\n')
			counter++;
		sqr++;
	}
	return (counter + 1);
}

int str_len(char *str)
{
	int counter;

	counter = 0;
	while(str[counter])
		counter++;
	return(counter);
}

char** str_to_arr(char *str, int a, int b)
{
	int i;
	int j;
	char **arr;

	i = 0;
	j = 0;
	arr = malloc(sizeof(char*) * a);
	while (i < a)
	{
		while (*str != '\n' && j < b)
		{
			if (j == 0)
				arr[i] = malloc(sizeof(char) * b);
			arr[i][j] = *str;
			str++;
			j++;
		}
		j = 0;
		i++;
		str++;	
	}
	return (arr);
}


int look_for_sqr(char** str, int x, int y, int a, int b)
{
	int length;
	int dx;
	int dy;

	length = 2;
	dx = 0;
	dy = 0;
	while ((y + length - 1 < b) && (x + length - 1 < a))
	{
		while (dx < length)
		{
			if (str[y + length - 1][x + dx] != '.')
				return (length - 1);
			dx++;
		}
		while (dy < length)
		{
			if (str[y + dy][x + length - 1] != '.')
				return (length - 1);
			dy++;
		}
		length += 1;
	}
	return (length - 1);
}
//here I tried, but I could not fit in 25 lines
struct find_the_biggest_sqr(char **str, int a, int b)
{
	int x;
	int y;
	struct sqr biggest_sqr;
	
	x = 0;
	y = 0;
	biggest_sqr.x = 0;
	biggest_sqr.y = 0;
	biggest_sqr.length = 0;

	while (y < a)
	{
		while (x < b)
		{
			if (str[y][x] != ',')
				continue;
			length = look_for_sqr(str, x, y, a, b);
			if (length > biggest_sqr_length)
			{
				biggest_sqr.x = x;
				biggest_sqr.y = y;
				biggest_sqr.length = length;
			}
			if (x + biggest_sqr.length >= a)
				break ;
		}
		if (y + biggest_sqr_length >= b)
			break ;
	}
return (biggest_sqr);
}


int main(void)
{	
	int len11 = a_len(sqr1);
	int len12 = b_len(sqr1);

	printf("a len1: %i\n", len11);
	printf("b len1: %i\n", len12);

	int len21 = a_len(sqr2);
	int len22 = b_len(sqr2);

	printf("a len1: %i\n", len21);
	printf("b len1: %i\n", len22);


	char **arr3 = str_to_arr(sqr1, len11, len12);

	char **arr4 = str_to_arr(sqr2, len21, len22);

	for (int i = 0; i < len11; i++)
		printf("%s\n", arr3[i]);
	printf("\n");
	for (int i = 0; i < len21; i++)
		printf("%s\n", arr4[i]);

	printf("top left corner1: %i\n", look_for_sqr(arr3, 0, 0, len11, len12));
	printf("top left corner2: %i\n", look_for_sqr(arr4, 0, 0, len21, len22));


}
