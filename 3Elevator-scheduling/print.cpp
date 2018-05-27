#include"Floor.h"
#include"Elevator.h"
#include<iostream>
#include<string.h>
using namespace std;
int AskTime;							//ÇëÇó´ÎÊý 
Elevator E[4];
Floor F[11];
int time,floor,target;
int Elevator::Finish=0;
que Wait_Time;
que Wait_Floor;
que Wait_Target;
int AllAsk;
char screen[1000];
char c[10],v[10];
char *head=screen,*now;

void Display()
{
	cout<<screen<<endl;
} 

char *rev(char f[])
{
	char *p=c;
	char *q=c;
	int i,j=0;
	for(i=strlen(f)-1;i>=0;i--,j++)
	{
		*(p+j)=f[i];
	}
	*(p+j)='\0';
	return q;
}

void write(char f[])
{
	char *e=f;
	while(*e!='\0')
	{
		*now++=*e++;
	}
}

char* intochar(int a)
{
	char *x=v;
	char *q=v;
	while(a>0)
	{
		*x++=a%10+48;
		a/=10;
	}
	*x='\0';
	q=rev(q);
	return q;
}

void print()
{
	now=head;
	int i,j;
	for(i=10;i>=1;i--)
	{
		write("F");
		write(intochar(i));
		write(": ");
		write("  ");
		for(j=1;j<=3;j++)
		{
			if(E[j].Get_CurrentFloor()==i)
			{
				write(" |");
				write(intochar(j));
				write("| ");
			}
			else  
			{
				write("     ");
			}
		}
		write("\n");
	}
	*now='\0';
}

void Run()
{
	
}

void Ask()
{
	while(Wait_Time.front()>=E[1].Get_CurrentTime())
	{
		F[Wait_Floor.front()].AddToQueue(Wait_Target.front());
		Wait_Time.DE_front();
		Wait_Floor.DE_front();
		Wait_Target.DE_front();
	}
}

void initial()
{
	int i;
	for(i=1;i<=3;i++)
	{
		E[i].Set_Type(i);
	}
	for(i=1;i<=10;i++)
	{
		F[i].Set_Layer(i);
	}
}

void input()
{
	int i=AskTime;
	while(i-->0)
	{
		cin>>time>>floor>>target;
		Wait_Time.Add(time);
		Wait_Floor.Add(floor);
		Wait_Target.Add(target);
	}
}

int main()
{
	initial();
	/*cin>>AskTime;
	while(AskTime!=Elevator::Finish)
	{
		Ask();
		Run();
	}*/
	print();
	Display();
}
