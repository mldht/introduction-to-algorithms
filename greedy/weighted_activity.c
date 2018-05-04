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

int get_last_compatible_activity2(struct activity *list, int activity_index)
{
	int left_index = 0;
	int right_index = activity_index - 1;
	while(left_index <= right_index)
	{
		if(left_index == right_index)
		{
			if(list[right_index].end <= list[activity_index].start)
			{
				return right_index;
			}
			else
			{
				return right_index - 1;
			}
		}
		else
		{
			int mid = (left_index + right_index) / 2;
			if(list[mid].end < list[activity_index].start)
			{
				left_index = mid + 1;
			}
			else if( list[mid].end > list[activity_index].start)
			{
				right_index = mid - 1;
			}
			else
			{
				return mid;
			}
		}
	}
}


void get_max_valued_activities( struct activity *list, int size)
{
	int values[MAX_ACTIVITY_NUM];
	int compa_activity_map[MAX_ACTIVITY_NUM];
	int activity_select_flag[MAX_ACTIVITY_NUM];

	int i;
	for(i = 0; i < size; i++)
	{
		values[i] = 0;
	}
	compa_activity_map[0] = -1;
	activity_select_flag[0] = 1;

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
		int compatible_index = get_last_compatible_activity2(list, i);

		compa_activity_map[i] = compatible_index;

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
			activity_select_flag[i] = 1;
		}
		else
		{	
			values[i] = values[i-1];
			activity_select_flag[i] = 0;
		}
	}
	
	printf("%d\n", values[size -1]);



	for( i = size-1; i >= 0;)
	{
		if(activity_select_flag[i] == 1)
		{
			printf("activity: %d, value: %d \n", i, list[i].value);
			i = compa_activity_map[i];
		}
		else
		{
			i--;
		}

	}

	printf("\n");
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
