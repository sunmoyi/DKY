#include "header.h"


void header()
{
	printf("\n/***************************************************************************\n\n");
	printf("\t\t\tSET - S-box Evaluation Toolbox\n\n");
	printf("\nVersion 0.9.\nDate: 25.02.2014\nEvaluation version, possible to display the results only to the screen.\n");
	printf("Program does not handle errors, so it is up to you to make sure that all is correct.\n");
	printf("\n***************************************************************************/\n");
}

void s_box_info (char *name)
{
	printf("\nName of the file: %s\n", name);
	printf("Input size M is %d\n", M);
	printf("Output size N is %d\n", N);
}


double get_time (clock_t finish, clock_t begin)
{
	double value;
	value = (double)(finish - begin) / CLOCKS_PER_SEC * 1000;
	printf("\nCalculations took %.2lf miliseconds to run\n", value);
	return value;
}