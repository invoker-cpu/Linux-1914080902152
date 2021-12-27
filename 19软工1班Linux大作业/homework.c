#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
struct option longopts[] = {
    { "scanf",        required_argument,  NULL,  's'    },
    { "print",        no_argument,    NULL,     'p'    },
    {"calculator",     no_argument,     NULL,     'c'    },
    {"help",           no_argument,     NULL,     'h'    },
	{"game",           no_argument,     NULL,     'g'    },
};
char *l_opt_arg; /*选项参数字符 */

int main(int argc, char **argv)
{
    int oc;                     /*选项字符 */
    while((oc = getopt_long(argc, argv, ":fchpgs:", longopts, NULL)) != -1){
        switch (oc){
        case 's':
            l_opt_arg = optarg;
            printf("你输入的是 %s.\n",l_opt_arg);
            break;
        case 'p':
            printf("这里是输出例子。\n");
            break;
	case 'c':
		printf("这里是简单的计算器\n");
	    printf("请输入第一个数字:");
	    double a,b;
	    scanf("%lf",&a);
	    printf("请输入第二个数字:");
	    scanf("%lf",&b);
	    printf("请输入计算类型(+ - * /):");
	    double sum;
	    char cl;
	    cl = getchar();
	    scanf("%c",&cl);
	    switch(cl){
		case '+':
			    sum = a+b;
			    break;
		case '-':
			    sum = a-b;
			    break;
		case '*':
			    sum = a*b;
			    break;
		case '/':
			    sum = a/b;
			    break;
	    }
	    printf("计算结果:");
	    printf("%.2lf\n",sum);
	    break;
	case 'g':
		printf("猜数游戏\n");
		void rules();
		int num,c;
		void signtonumber(int num);
		rules();
		for(c=1;;c++)
		{
			printf("请输入玩家人数：(>1)");
			scanf("%d",&num);
			if(num<=1)
			{
				printf("请输入一个合法的数（ >1）！\n");
			}
			else
			{
				break;
			}
		}
		fflush(stdin);
		signtonumber(num);
		fflush(stdin);
		getchar();
			break;
	case 'h':
	    printf("这里是帮助\n");
	    printf("可输入的短指令有: p、s、c、g\n");
	    printf("可输入的长指令有: print、scanf、calculator、game\n");
		printf("输入的短指令格式为 -* (*可用上述短指令替代)\n");
		printf("输入的长指令格式为 --* (*可用上述长指令替代)\n");
	    break;
	case '?':
            printf("无效的选项！\n");
            break;
	case ':':
	    printf("缺少选项参数！\n");
	    break;
        }
    }
   return 0;}

void rules()
{
	printf("游戏规则如下：\n");
	printf("1.先输入参与的人数\n");
	printf("2.系统会随机给一个数（不显示），范围在1~100之间\n");
	printf("3.由第一位玩家输入一个在1~100范围内的数\n");
	printf("4.若猜中则显示“BINGO!”，并接受惩罚\n"); 
	printf("5.若未猜中则刷新范围，如系统随机数为51，玩家猜的数为15，则刷新范围为16~100\n"); 
	printf("6.未猜中则由下一位玩家猜数，猜的数应在刷新的范围内，之后同4.5点\n");  
	printf("7.其他玩家同第6点\n"); 
}

void signtonumber(int num)
{
	int b,i,j,weishu,key,guess,wei,answer,left=1,right=100;
	char a[100]="'\0'";
	char *p;
	srand((unsigned)time( NULL ) );
	answer=rand()%100+1;
	for(i=1;i<=num;i++)
	{
		key=1;
		guess=0;
		for(p=a;p<a+100;p++)
		{
			*p='\0';
		}
		printf("请第%d位玩家输入一个数：",i); 
		scanf("%s",a);
		for(weishu=0;a[weishu]!='\0';weishu++)
		{
			if(a[weishu]<'0' || a[weishu]>'9')
			{
				printf("请输入一个合理的数！\n");
				printf("现在的范围为%d~%d\n",left,right);
				i=i-1;
				key=0;
				break;
			}
		}
		if(key==1)
		{
			for(j=weishu-1,wei=1;j>=0;j--,wei=wei*10)
			{
				guess=guess+(a[j]-48)*wei;
			}
			if(guess<left || guess>right)
			{
				printf("请输入一个合理的数！\n");
				printf("现在的范围为%d~%d\n",left,right);
				i=i-1;
			}
			else
			{
				
				if(guess==answer)
				{
					printf("BINGO!\n"); 
					break;
				}
				else if(guess>answer)
				{
					right=guess-1;
					printf("现在的范围为%d~%d\n",left,right);
				}
				else if(guess<answer)
				{
					left=guess+1;
					printf("现在的范围为%d~%d\n",left,right);
				}
				if(i==num)i=0;
			}
		}
	}
}
