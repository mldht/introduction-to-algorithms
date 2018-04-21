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


void worker_recursive(int *start, int *end, int flag[100][100], int result[100][100], int s, int e)
{
	if(flag[s][e] != 0 )
	{
		return ;
	}
	int i;
	for(i = s + 1; i < e; i++)
	{
		if(start[i] >= end[s] && end[i] <= start[e])
		{
			worker_recursive(start, end, flag, result, s, i);
			worker_recursive(start, end, flag, result, i, e);
			if(result[s][e] < result[s][i] + result[i][e] + 1)
			{
				result[s][e] = result[s][i] + result[i][e] + 1;
			}
		}
	}

	flag[s][e] = 1;
}

int main(void)
{
	int start[100] = {-1 ,1, 3, 0, 5, 4, 5, 6, 8, 8, 2, 12, 100000};
	int end[100] = {-1, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16, 10000};
	int result[100][100];
#ifdef BOTTOM_UP
	worker(start, end, result, 13);
#else
	int flag[100][100];
	int i, j;
	for(i = 0; i < 13; i++)
	{
		for(j = 0; j < 13; j++)
		{
			flag[i][j] = 0;
			result[i][j] = 0;
		}
	}
	worker_recursive(start, end, flag, result, 0, 12);
#endif		
	printf("result: %d\n", result[0][12]);
	return 0;
}
