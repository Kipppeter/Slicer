#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>

// General size limits
#define MAXTRIANGLES 2682
#define MAXLAYERS 1
#define MAXPOINTSPERLAYER 10
#define MAXERROR 0.2

#define MINSIDELENGTH 2
#define EXTRUSIONRADIUS 0.2

// InputType macros
#define INPUTDIGIT 0
#define INPUTCHAR 1

struct tess {
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
	
struct layer {
	double x;
	double y;
	} l[MAXPOINTSPERLAYER][MAXLAYERS];
	
int InputType(char input[]);
void ReadInput(void);
void LineEq(double vector[], double point1[], double point2[]);
void FlatLayer(double height, int layerNum);
void Dump(void);

int main(void)
{
	double begin = clock();
	ReadInput();
	Dump();
	double end = clock();
	printf("Start time: %f\nEnd time: %f\nTotal time: %f", begin, end, (end - begin)/CLOCKS_PER_SEC);
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
	
	FILE *fInput;
	
	fInput = fopen("sample.stl", "r");
	printf("FILE OPENED!\n");
	while(input != '\0')
	{
		printf("Reading value %d\n", i);
		if(current == MAXTRIANGLES)
		{
			break;
		}
		fscanf(fInput, "%s", input);
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
	printf("WHILE LOOP DONE!\n");
	fclose(fInput);
	printf("FILE CLOSED!\n");
}

void LineEq(double vector[], double point1[], double point2[])
{
	vector[0] = (point2[0] - point1[0]) / (point2[2] - point1[2]);
	vector[1] = (point2[1] - point1[1]) / (point2[2] - point1[2]);
	vector[2] = 1;
}

void FlatLayer(double height, int layerNum)
{
	int i;
	int j = 0;
	float layerHeight = height - (MAXERROR/2);
	int intersectingTriangles[MAXTRIANGLES] = {-1};
	
	for(i = 0; i < MAXTRIANGLES; i++)
	{
		if(triangle[i].v1Z <= layerHeight)
		{
			intersectingTriangles[j] = i;
			j++;
		}
		else if(triangle[i].v2Z <= layerHeight)
		{
			intersectingTriangles[j] = i;
			j++;
		}
		else if(triangle[i].v3Z <= layerHeight)
		{
			intersectingTriangles[j] = i;
			j++;
		}
	}
	
}

void Dump(void)
{
	int i, j;
	
	FILE *fOutput;
	
	fOutput = fopen("output.txt", "w");
	
	for(i = 0; i < MAXTRIANGLES; i++)
	{
		fprintf(fOutput, "Triangle %d\n", i);
		for(j = 0; j < 12; j++)
		{
			switch(j)
			{
				case 0:
					fprintf(fOutput, "nX: %f\n", triangle[i].nX);
					break;
				case 1:
					fprintf(fOutput, "nY: %f\n", triangle[i].nY);
					break;
				case 2:
					fprintf(fOutput, "nZ: %f\n", triangle[i].nZ);
					break;
				case 3:
					fprintf(fOutput, "v1X: %f\n", triangle[i].v1X);
					break;
				case 4:
					fprintf(fOutput, "v1Y: %f\n", triangle[i].v1Y);
					break;
				case 5:
					fprintf(fOutput, "v1Z: %f\n", triangle[i].v1Z);
					break;
				case 6:
					fprintf(fOutput, "v2X: %f\n", triangle[i].v2X);
					break;
				case 7:
					fprintf(fOutput, "v2Y: %f\n", triangle[i].v2Y);
					break;
				case 8:
					fprintf(fOutput, "v2Z: %f\n", triangle[i].v2Z);
					break;
				case 9:
					fprintf(fOutput, "v3X: %f\n", triangle[i].v3X);
					break;
				case 10:
					fprintf(fOutput, "v3Y: %f\n", triangle[i].v3Y);
					break;
				case 11:
					fprintf(fOutput, "v3Z: %f\n", triangle[i].v3Z);
					break;
			}
		}
		fprintf(fOutput, "\n");
	}
	fclose(fOutput);
}
