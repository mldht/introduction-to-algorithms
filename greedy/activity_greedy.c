#include <stdio.h>

struct activity
{
	int start;
	int end;
};


void find_opt_activities(struct activity * list, int *opt_list, int size, int *opt_count)
{
	opt_list[0] = 0;
	*opt_count = 1;
	int index = 1;
	int k = 0;
	while( index <  size)
	{
		if( list[index].start >= list[k].end)
		{
			opt_list[*opt_count] = index;
			(*opt_count)++;
			k = index;
		}
		index++;
	}
}

void find_opt_activities_recursive(struct activity *list, int *opt_list, int size, int index, int *opt_count)
{
	//if( index >= size )
	//{
//		return;
//	}

	int k = opt_list[*opt_count -1];
	while(index < size && list[index].start < list[k].end)
	{
		index++;
	}
	if( index < size)
	{
		opt_list[*opt_count] = index;
		*opt_count = *opt_count + 1;
		find_opt_activities_recursive(list, opt_list, size, index, opt_count);
	}

}

int main(void)
{
	struct activity activity_list[100] = 
	{
		{1, 4},
		{3, 5},
		{0, 6},
		{5, 7},
		{3, 9},
		{5, 9},
		{6, 10},
		{8, 11},
		{8, 12},
		{2, 14},
		{12, 16},	
	};

	int opt_activities[100];
	int opt_count = 0;
	find_opt_activities(activity_list, opt_activities, 11,  &opt_count);
	printf("%d\n", opt_count);
//	opt_count = 1;
//	opt_activities[0] = 0;
	find_opt_activities_recursive(activity_list, opt_activities, 11, 0, &opt_count);
	printf("%d\n", opt_count);
	return 0;
}


