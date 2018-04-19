#include <stdio.h>

void printItems(int optItems[100][100], int start, int end);

void worker(int *start, int *end, int result[100][100], int size)
{

	int optItems[100][100];
	int i, j;
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			result[i][j] = 0;
			optItems[i][j] = 0;
		}
	}


	int len;
	for(len = 2; len < size; len++)
	 {
		for(i = 0; i < size - len; i++)
		{
			j = i + len;
			for(int k = i + 1; k < j; k++)
			{
				if( start[k]>= end[i] && end[k] <= start[j])
				 {
					 if( result[i][j] < result[i][k] + result[k][j] + 1)
					 {
						 result[i][j] = result[i][k] + result[k][j] + 1;
						 optItems[i][j] = k;
					 }
				 }
			}
		}
	 }

	printItems( optItems, 0, size - 1 ); 
	printf("\n");
}


void printItems(int optItems[100][100], int start, int end)
{
	int k = optItems[start][end];
	if( k > start && k < end )
	{
		printItems(optItems, start, k);
		printItems(optItems, k, end);
		printf("%d ", k);
	}
}

int main(void)
{
	int start[100] = {-1 ,1, 3, 0, 5, 4, 5, 6, 8, 8, 2, 12, 100000};
	int end[100] = {-1, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16, 10000};
	int result[100][100];
	worker(start, end, result, 13);
	printf("result: %d\n", result[0][12]);
	return 0;
}
