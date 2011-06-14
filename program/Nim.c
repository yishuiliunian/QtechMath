#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#define TMAX 10
int Statue[TMAX];
int *StaPtr;
int change[TMAX];
int first = 0;

void init(int* a, int b)
{
	int i;
	for(i=0;i<b;i++)
		a[i] = 0;
}

void PrnStatue(int *statue, int tiples)
{
	int i;
	printf("******************************************************************\n");
	printf("当前石子状态\n");
	for(i=0;i<tiples;i++)
	{
		printf("%d堆\t",i+1);
	}
	printf("\n");
	for(i=0;i<tiples;i++)
	{
		printf("%d\t",statue[i]);
	}
	printf("\n******************************************************************\n");
}

void Increase(int* columm,int tiples)
{
	int temp[tiples];
	columm = temp;
}

void UsageMessage()
{
	printf("请在CMD下运行。用法错误,请按照一下格式使用:\n \\
Nim.exe [-S:[]] [-T:[]] [-H:[]] [-F/-NF] \n \\
-S:[] : 总共石子数目。输入任意整数。\n \\
-T:[] : 所要分的堆数。输入任意整数。\n \\
-F    : 先手取子。\n \\
-NF   : 后手取子。\n \\
用法举例：\n \\
linux平台下：./Nim -T:3 -S:10  -F\n \\
windows平台下：Nim.exe -T:3 -S:10  -F\n");
}

void RandomTiple(int tiples , int sum)
{
	int i;
	int k;
	int random;
	if(tiples > TMAX)
	{
		Increase(Statue,tiples);
		init(Statue,tiples);
		Increase(change,tiples);
		init(change,tiples);
	}
	init(Statue,TMAX);
    for(i=0;i<tiples;i++)
	{
		if(i==tiples-1)
		{
			Statue[i]=sum;
			break;
		}
		{
			k = rand();
		//	printf("k=%d,sum=%d,random=%d\n",k,sum,k%(sum/2));
			random =k%(sum/2);
		}

//		for(;random > sum;random = 1);

//		printf("sumsss=%d\n",sum);
		sum = sum -random;
		Statue[i]=random;
	}
}


void ChangeStute(int* stute, int* change, int tiples)
{
	int i;
	for(i=0;i<tiples;i++) 
	{
		stute[i]=stute[i]-change[i];
	}
}

int SumStone(int* stute, int tiples)
{
	int i,sum=0;
	for(i=0;i<tiples;i++) sum = sum +stute[i];
	return sum;
}

void PrnGuize()
{
	printf("请遵守游戏规则：每次只能移动一堆。\n");
}


void  SG(int* statue,int* change, int tiples)
{
	int i,k=0;
	init(change,tiples);
	for(i=0;i<tiples;i++)
	{
		k=statue[i]^k;
	}
	if(k!=0)
	for(i=0;i<tiples;i++)
	{
	 	if(((statue[i]^k)<statue[i]))
	 	{
	 	change[i]=statue[i] - (statue[i]^k);
	 	return;
	 	}
	}

	for(i=0;i<tiples;i++)
	{
		if(statue[i] != 0)
		{
		change[i] = 1;
		return;
		}
	}

}


int TestChange(int *stute,int *change, int tiples)
{
	int i;
	int tempchange = 0;
	for(i=0;i<tiples;i++)
	{
		if(stute[i]-change[i] < 0) return 0;
		if(change[i] != 0)  tempchange++;
		if(tempchange>=2)  return 0;
	}
	if(tempchange = 0) return 0;
	return 1;
}


void BeginGame(int* stute, int* change, int tiples)
{
	int i;

	while(SumStone(stute,tiples) > 0)
	{
		if(first)
		{
			printf("请输入您的移动策略：\n");
			for(i=0;i<tiples;i++)
			{
				printf("第%d堆：",i+1);
				scanf("%d",&change[i]);
//				printf("\n");
			}
			if(!TestChange(stute,change,tiples))
			{
				PrnGuize();
				continue;
			}
			ChangeStute(stute,change,tiples);
			if(SumStone(stute,tiples) > 0) first =0;
			PrnStatue(stute,tiples);
		}
		else
		{
			printf("电脑取子：\n");
			SG(stute,change,tiples);
			
			printf("电脑策略：\n");
			for(i=0;i<tiples;i++)
			{
				printf("%d\t",change[i]);
			}
			printf("\n");
			ChangeStute(stute,change,tiples);
			PrnStatue(stute,tiples);
			if(SumStone(stute,tiples) > 0) first =1;
		}
}
	if(first==1) printf("你赢了！\n");
	else printf("电脑赢了。\n");
}




int main(int argc,char** argv)
{
	int stone_sum = 20;
	int tiples = 3;
	int hard = 0;

	//辅助变量
	int i;
	char *temp;
	if(argc != 4)
	{
		UsageMessage();
		return 0;
	}

	/*命令筛选 */
	for(i=1;i<=argc-1;i++)
	{
		if(!strncmp("-T:",argv[i],3))
		{
			temp = strstr(argv[i],":");
			temp++;
			tiples = atoi(temp);
			printf("分成了：\t%d堆\n",tiples);
		}
		if(!strncmp("-S:",argv[i],3))
		{
			temp = strstr(argv[i],":");
			temp++;
			stone_sum = atoi(temp);
			printf("总共石子数：\t%d\n",stone_sum);
		}
		if(!strncmp("-F",argv[i],2))
		{
			first = 1;
			printf("先手取子.\n");
		}
		if(!strncmp("-NF",argv[i],3))
		{
			first = 0;
			printf("后手取子.\n");
		}
	}

	RandomTiple(tiples,stone_sum);
	PrnStatue(Statue,tiples);
	BeginGame(Statue,change,tiples);
	return 0;
}
