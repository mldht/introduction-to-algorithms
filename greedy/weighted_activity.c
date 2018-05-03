#include <stdio.h>

#define MAX_ACTIVITY_NUM	50

struct activity 
{
	int start;
	int end;
	int value;
};

int get_last_compatible_activity(struct activity *list, int activity_index)
{
	int i;
	for(i = activity_index - 1; i >= 0; i--)
	{
		if(list[i].end <= list[activity_index].start)
		{
			break;
		}
	}

	return i;
}

void get_max_valued_activities( struct activity *list, int size)
{
	int values[MAX_ACTIVITY_NUM];
	int compa_activitiy_map[MAX_ACTIVITY_NUM];

	int i;
	for(i = 0; i < size; i++)
	{
		values[i] = 0;
	}

	values[0] = list[0].value;

//	int j;
	for(i = 1; i < size; i++)
	{
/*		for(j = i - 1; j >= 0; j--)
		{
			if(list[j].end <= list[i].start)
			{
				break;
			}
		}
*/
		int compatible_index = get_last_compatible_activity(list, i);
		int tmp;
		if(compatible_index < 0)
		{
			tmp = 0;
		}
		else
		{
			 tmp =values[compatible_index];
		}

		if( tmp + list[i].value > values[i - 1])
		{
			values[i] = tmp + list[i].value;
		}
		else
		{	
			values[i] = values[i-1];
		}
	}
	
	printf("%d\n", values[size -1]);
}


int main(void)
{
	struct activity list[] = { {1, 4, 3}, {3, 5, 2}, {0, 6, 4}, 
								{5, 7, 8}, {3, 9, 2}, {5, 9, 5},
								{6, 10, 6}, {8, 11, 5},{8, 12, 7},
								{2, 14, 4}, {12, 16, 5}};

	get_max_valued_activities(list, 11);
	return 0;
}
