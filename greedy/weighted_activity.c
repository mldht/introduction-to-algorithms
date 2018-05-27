#include <stdio.h>
#define M	100

struct activity
{
	int start;
	int end;
	int value;
};

int reconstruction[M][M];

void print_result(int i, int j)
{
	if( j - i <= 1 )
	{
		return;
	}
	int k = reconstruction[i][j];
//	if( k < 0)
//	{
//		return ;
//	}
	if(k > i && k < j)
	{

		printf("%d \n", k);
		print_result(i, k);
		print_result(k, j);
	}
}

void find_max_valued_activities(struct activity *list, int size, int result[M][M])
{
	int step;
	for( step = 2; step < size; step++)
	{
		int i, j, k;
		int tmp = 0;
		for(i = 0; i < size - step; i++)
		{
			j = i + step;
			for(k = i + 1; k < j; k++)
			{
				if(list[k].start >=list[i].end && list[k].end <= list[j].start)
				{
					int tmp = result[i][k] + result[k][j] + list[k].value;
					if( tmp > result[i][j] )
					{
						result[i][j] = tmp;
						reconstruction[i][j] = k;
					}
				}
			}
		}
	}

	print_result(0, size - 1);
}

int main(void)
{
	struct activity list[] = { {0, 0, 0},
								{1, 4, 3}, {3, 5, 2}, {0, 6, 4}, 
								{5, 7, 8}, {3, 9, 2}, {5, 9, 5},
								{6, 10, 6}, {8, 12, 7}, {12, 16, 5}, 
								{3000, 3000, 0} };

	int result[M][M];
	int i, j;
	for(i = 0; i < M; i++)
	{
		for(j = 0; j < M; j++)
		{
			result[i][j]  = 0;
			reconstruction[i][j] = -1;
		}
	}

	find_max_valued_activities(list, sizeof(list)/sizeof(list[0]), result);
	printf("%d\n", result[0][10]);
	return 0;
}
