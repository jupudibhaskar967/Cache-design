#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
uint64_t calculateaddress(uint64_t startadd,int index)
{
	return (startadd+index*8);	
}
void update(int **bank2,uint64_t bankrow, uint64_t address,uint64_t startadd)
{
	int inadd = address/8;
	int start = (inadd/8);
	start = start *8;
	int i,k=0;
	for(i=start;i<start+8;i++,k++)
	{	
		bank2[bankrow][k]=i*8;
	}
}
int main()
{

	
	int misscounter=0;	
	int **bank1;
	int **bank2;	
	int i,j,k;	
	uint64_t A=0;
	uint64_t B=1<<21;
	uint64_t C= (1<<21)+(1<<22);	
	bank1=(int **)calloc(512,sizeof(int *));
	bank2=(int **)calloc(512,sizeof(int *));
	for(i=0;i<512;i++)
	{
		bank1[i] = (int *)calloc(8,sizeof(int));
		bank2[i] = (int *)calloc(8,sizeof(int));
	}
	
	
	for(i=0;i<512;i++)
	{
		for(j=0;j<8;j++)
		{
			bank1[i][j] = -1;bank2[i][j] = -1;
		}
	}	
	int p=0;	
	for(i=0;i<128;i+=2)
	{
		for(j=0;j<128;j++)
		{
			for(k=0;k<128;k+=4)
			{				
				////////for A matrix start///////////
				uint64_t addressA = calculateaddress(A,i*1024+k);
				uint64_t bankrow = (addressA & 0x7fc0) >> 6;
				bool ishit=false;
				for(p=0;p<8;p++)
				{
					if(bank1[bankrow][p]==addressA)
					{
						ishit = true;						
						//printf("A(%d)(%d) is a hit for the address - %ld\n",i,k,addressA);
						
					}
					if(bank2[bankrow][p]==addressA)
					{
						ishit = true;						
						//printf("A(%d)(%d) is a hit for the address - %ld\n",i,k,addressA);
						
					}
				}
				if(ishit==false)
				{					
					//printf("A(%d)(%d) is a miss for the address - %ld\n",i,k,addressA);
					misscounter++;
					update(bank2,bankrow,addressA,A);
				}
				////////for A matrix end///////////
				
				
				
				////////for B matrix start///////////
				uint64_t addressB = calculateaddress(B,k*512+j);
				bankrow = (addressB & 0x7fc0) >> 6;
				ishit=false;
				for(p=0;p<8;p++)
				{
					if(bank1[bankrow][p]==addressB)
					{
						ishit = true;						
						//printf("B(%d)(%d) is a hit for the address - %ld\n",k,j,addressB);
						
					}
					if(bank2[bankrow][p]==addressB)
					{
						ishit = true;						
						//printf("B(%d)(%d) is a hit for the address - %ld\n",k,j,addressB);
						
					}
				}
				if(ishit==false)
				{					
					//printf("B(%d)(%d) is a miss for the address - %ld\n",k,j,addressB);	
					misscounter++;
					update(bank2,bankrow,addressB,B);					
				}
				////////for B matrix end///////////
				
				
				
			
			
			
				////////for C matrix start///////////	
				uint64_t addressC = calculateaddress(C,i*512+j);
				bankrow = (addressC & 0x7fc0) >> 6;
				ishit=false;
				for(p=0;p<8;p++)
				{
					if(bank1[bankrow][p]==addressC)
					{
						ishit = true;						
						//printf("C(%d)(%d) is a hit for the address - %ld\n",i,j,addressC);
						
					}
					if(bank2[bankrow][p]==addressC)
					{
						ishit = true;						
						//printf("C(%d)(%d) is a hit for the address - %ld\n",i,j,addressC);
						
					}
				}
				if(ishit==false)
				{					
					//printf("C(%d)(%d) is a miss for the address - %ld\n",i,j,addressC);
					misscounter++;
					update(bank2,bankrow,addressC,C);					
				}
				////////for C matrix end///////////
											
			}
		}
	}	
	printf("%d\n",misscounter);	
	return 0;
}
