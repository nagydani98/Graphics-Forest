#include "utils.h"

#include <math.h>
#include <time.h>
#include <stdlib.h>


double degree_to_radian(double degree)
{
	return degree * M_PI / 180.0;
}

double radian_to_degree(double degree)
{
	return degree / M_PI * 180.0;
}


