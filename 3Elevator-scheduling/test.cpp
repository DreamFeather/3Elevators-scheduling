#include<iostream>
using namespace std;
void seeArrival(Elevator E[])
{
	int i,j;
	for(i=1;i<=3;i++)
	{
		cout<<i<<": ";
		for(j=1;j<=10;j++)
		{
			cout<<j<<":"<<E[i].Get_Arrival(j)<<" ";
		}
		cout<<endl;
	}
}

void seeStatus(Elevator E[])
{
	int i,j;
	for(i=1;i<=3;i++)
	{
		cout<<"����"<<i<<":";
		cout<<"CurrentFloor: "<<E[i].Get_CurrentFloor()<<" CurrentTime: "<<E[i].Get_CurrentTime()<<" Diretion: "<<E[i].Get_Diretion();
		cout<<" Load: "<<E[i].Load<<endl;
	}
}

void seeEleQue(Elevator E)
{
	cout<<"Floor: "<<E.Get_CurrentFloor()<<endl;
	cout<<"TargetQue:";
	if(E.Get_NextTarget()!=-1)cout<<E.Get_NextTarget();
	else cout<<0;
	cout<<endl;
	cout<<"AskQue:";
	if(E.Get_NextAsk()!=-1)
	cout<<E.Get_NextAsk();
	else cout<<0;
	cout<<endl;
}

void seeFloorQue(Floor F[])
{
	int i;
	for(i=10;i>=1;i--)
	{
		cout<<i<<"��:";
		if(F[i].even_Downstair.size()!=0)	cout<<"even_Downż����"<<F[i].even_Downstair.size()<<"��";
		if(F[i].even_Upstair.size()!=0)	cout<<"even_Upż����"<<F[i].even_Upstair.size()<<"��";
		if(F[i].odd_Downstair.size()!=0)	cout<<"odd_Down������"<<F[i].odd_Downstair.size()<<"��";
		if(F[i].odd_Upstair.size()!=0)	cout<<"odd_Up������"<<F[i].odd_Upstair.size()<<"��"; 
		cout<<endl;
	}
}
