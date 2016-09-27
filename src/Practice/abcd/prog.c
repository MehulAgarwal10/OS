#include <stdio.h>

int recFact(int);
int itFact(int);


int main()
{

	printf("Enter a number : ");
	int num;
	scanf("%d",&num);

	int ans1,ans2;
	ans1 = recFact(num);
	ans2 = itFact(num);
	printf("Recursive : %d\nIterative : %d\n",ans1,ans2);
	
	int value=1,nextIntVal;
	double next, nextVal;
	while(1)
	{
		ans1 = recFact(value);
		nextVal = ans1 * (double)(value+1.00);
		nextIntVal = (int)(nextVal);
		printf("ans1 = %d, nextVal = %lf, nextIntVal = %d\n",ans1,nextVal,nextIntVal);
		if(nextIntVal < ans1)
		{
			printf("Max number : %d\n",value);
			break;
		}
		value++;
	}
}


