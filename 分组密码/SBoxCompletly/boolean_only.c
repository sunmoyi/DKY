#include "header.h"

int bias_nonlinearity (int max)
{
	return max / (1 << (M + 1));
}


int is_bent(int max)
{
	if (((1 << (M - 1)) - (1 << (M/2 - 1))) == max)
		return 1;
	else
		return 0;
}


void wt_boolean (u8 *tt)
{
    int max = 0;
	int * res;

	res = (int *) malloc (m_shift * sizeof(int));

//	max = walsh_transform (tt, M, 1, res);
	
	free(res);
	
	printf ("Bias of nonlinearity is %d.\n", bias_nonlinearity (max));
	printf ("Degree of linearity is %d.\n", max);

	//for bent functions
	if (M % 2 == 0)
	{
		if (is_bent (max))
			printf("Boolean function is bent.\n");
		else
			printf("Boolean function is not bent.\n");
	}
	else
		printf("Boolean functions is not bent since it does not have even number of input variables.\n");
}
