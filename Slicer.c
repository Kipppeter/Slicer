#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>
#include <string.h>
#include <math.h>

// General size limits
#define MAXTRIANGLES 100

#define MINSIDELENGTH 2
#define EXTRUSIONRADIUS 0.2

// InputType macros
#define INPUTDIGIT 0
#define INPUTCHAR 1

struct layer {
		int layerNum;
		double nX;
		double nY;
		double nZ;
		double v1X;
		double v1Y;
		double v1Z;
		double v2X;
		double v2Y;
		double v2Z;
		double v3X;
		double v3Y;
		double v3Z;
	} triangle[MAXTRIANGLES];
	
int InputType(char input[]);
void ReadInput(void);
void LineEq(double vector[], double point1[], double point2[]);

int main(void)
{
	ReadInput();

	return 0;
}

int InputType(char input[])
{
	int i;
	int inputLen = strlen(input);
	int notDigit;
	
	for(i = 0; i < inputLen; i++)
	{
		if(isdigit(input[i]) == 0)
		{
			if((i != 0) && (input[i] != '-'))
			{
				if((input[i] != 'e') && (input[i] != '.'))
				{
					notDigit = 1;
					break;
				}
			}
		}
	}
	
	if(notDigit == 1)
	{
		return INPUTCHAR;
	}
	else
	{
		return INPUTDIGIT;
	}
}

void ReadInput(void)
{
	char input[30];
	int iT;
	double val;
	int i = 0;
	int current = 0;
	while(input != '\0')
	{
		scanf("%s", input);
		iT = InputType(input);
		if(iT == INPUTDIGIT)
		{
			val = strtod(input, '\0');
			switch(i)
			{
				case 0:
					triangle[current].nX = val;
					break;
				case 1:
					triangle[current].nY = val;
					break;
				case 2:
					triangle[current].nZ = val;
					break;
				case 3:
					triangle[current].v1X = val;
					break;
				case 4:
					triangle[current].v1Y = val;
					break;
				case 5:
					triangle[current].v1Z = val;
					break;
				case 6:
					triangle[current].v2X = val;
					break;
				case 7:
					triangle[current].v2Y = val;
					break;
				case 8:
					triangle[current].v2Z = val;
					break;
				case 9:
					triangle[current].v3X = val;
					break;
				case 10:
					triangle[current].v3Y = val;
					break;
				case 11:
					triangle[current].v3Z = val;
					i = -1;
					current++;
					break;
			}
			i++;
		}
	}
}

void LineEq(double vector[], double point1[], double point2[])
{
	vector[0] = (point2[0] - point1[0]) / (point2[2] - point1[2]);
	vector[1] = (point2[1] - point1[1]) / (point2[2] - point1[2]);
	vector[2] = 1;
}
