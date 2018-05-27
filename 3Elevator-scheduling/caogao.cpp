

#include"Floor.h"
#include"elevator.h"
#include"test.cpp"
#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
using namespace std;
int AskTime;							//������� 
Elevator E[4];							//��3������ 
Floor F[11];							//��10��¥ 
int time=0,floor=0,target=0;					//���ļ�����ʱ��,¥��,Ŀ�ĵ� 
int Elevator::Finish=0;					//�����������Ϊ0 
que Wait_Time,Wait_Floor,Wait_Target;	//�����Ŷ���  
int AllAsk=0;								//������������ 

char screen[1000];						//���������? 
char c[10],v[10];						//******* 
char *head=screen,*now;					//*******����  
string inpath="input.txt"; 
string outpath1="output1.txt";
string outpath2="output3.txt";
string outpath3="output2.txt";
ifstream in;
ofstream out1,out2,out3;
const char warning[]="��������Ϊ��!"; 
const char teller1[]="���������input.txt�Ƿ����!";
const char teller2[]="���ٴμ��input.txt�Ƿ�Ϊ���ļ������Ƿ���~.exe��ͬ�ļ�����!!!";
const string Error="	���������쳣!!!";


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
	int i,j=0;
	//system("cls");
	write("Time:");
	if(E[1].Get_CurrentTime()==0)write("0");
	else write(intochar(E[1].Get_CurrentTime()));
	write("\n");
	for(i=10;i>=1;i--)
	{
		if(i!=10)write(" "); 
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

void seeArrival(Elevator E[]);

int ordered(const int f)
{
	int i;
	for(i=1;i<=3;i++)
	{
		if(E[i].Order(f)==1)
		{
			//cout<<"Has ordered\n";				
			return 1;			//����ͬĿ��	
		}
	}
	return 0;														//δ�� 
} 

void seeStatus(Elevator E[]);
void seeFloorQue(Floor F[]);
void seeEleQue(Elevator E);

void CallElv(const int f)					//��¥����������¥�� 
{
	if(ordered(f)==1)return ; 																	//�Ѿ������� 
	int j;
	for(j=1;j<=3;j++)
	{
		if(E[j].status()==0&&E[j].Get_Arrival(f)==1)											//���� :һ�η��� 
		{
			if(j==1)
			{
				if(F[f].odd_Downstair.size()!=0||F[f].odd_Upstair.size()!=0)					//��ȥ������ 
				{
					E[j].Add_AskFloor(f);cout<<"����1"<<"����"<<f<<"������\n";return;
				}
			}
			
			else if(j==2)
			{
				if(F[f].even_Downstair.size()!=0||F[f].even_Upstair.size()!=0)					//��ȥż����� 
				{
					E[j].Add_AskFloor(f);cout<<"����2"<<"����"<<f<<"������\n";return;
				}
			}
			
			else if(j==3)																		//ǰ��Ķ����� 
			{
				if(E[1].Order(f)==0&&F[f].odd_Downstair.size()+F[f].odd_Upstair.size()!=0)		//���û��
				{
					E[j].Add_AskFloor(f);cout<<"����3"<<"����"<<f<<"������\n";return ;
				}
				
				if(E[2].Order(f)==0&&F[f].even_Downstair.size()+F[f].even_Upstair.size()!=0)
				{
					E[j].Add_AskFloor(f);cout<<"����3"<<"����"<<f<<"������\n";return ;
				}
				
			}						
			
		}
		
	}

	if(ordered(f)==1)return ;
	cout<<f<<" ��һ�η���ʧ��!\n";
	for(j=1;j<=3;j++)																			//��æ :���η��� 
	{
		if(E[j].Get_Arrival(f)==1)
		if(E[j].Get_Diretion()*(E[j].Get_CurrentFloor()-f)>=0)
		{
			if(j==1)
			{
				if(F[f].odd_Downstair.size()!=0||F[f].odd_Upstair.size()!=0)					//��ȥ������ 
				{
					E[j].Add_AskFloor(f);cout<<"����1"<<"����"<<f<<"������\n";return;
				}
			} 
			
			else if(j==2)
			{
				if(F[f].even_Downstair.size()!=0||F[f].even_Upstair.size()!=0)					//��ȥż����� 
				{
					E[j].Add_AskFloor(f);cout<<"����2"<<"����"<<f<<"������\n";return;
				}
			}
			
			else 
			{
				if(E[1].Order(f)==0&&F[f].odd_Downstair.size()+F[f].odd_Upstair.size()!=0)		//���û��
				{
					E[j].Add_AskFloor(f);cout<<"����3"<<"����"<<f<<"������\n";return ;
				}
				
				if(E[2].Order(f)==0&&F[f].even_Downstair.size()+F[f].even_Upstair.size()!=0)
				{
					E[j].Add_AskFloor(f);cout<<"����3"<<"����"<<f<<"������\n";return ;
				}
			}
			
		}
		
	}
	
	if(ordered(f)==1)return ;
	cout<<f<<" �ڶ��η���ʧ��!\n";
	if(j==4)																					//ȫæ :����(ǿ��)���� 
	{
		int x=E[3].Load,y;
		if(E[2].Get_Arrival(f)==1&&F[f].odd_Downstair.size()+F[f].odd_Upstair.size()!=0)
		{
			y=E[2].Load;
			if(y-3<=x)
			{
				E[2].Add_AskFloor(f);	cout<<"����2"<<"����"<<f<<"������\n"; 
			}
			else 
			{
				E[3].Add_AskFloor(f);	cout<<"����3"<<"����"<<f<<"������\n";
			}
		}
		
		if(E[3].Order(f)==0)																		//���ŵ���û�� 
		if(E[1].Get_Arrival(f)==1&&F[f].even_Downstair.size()+F[f].even_Upstair.size()!=0)
		{
			y=E[1].Load;
			if(y-3<=x)
			{
				E[1].Add_AskFloor(f);	cout<<"����1"<<"����"<<f<<"������\n"; system("pause"); 
			}
			else 
			{
				E[3].Add_AskFloor(f);	cout<<"����3"<<"����"<<f<<"������\n";
			}
			
			return ;
		}
		
	}
	
}

int Set(const int i)
{
	int U=0,D=0,j=0,l;
	if(i==1)											//����� 
	{
				
		U=F[E[i].Get_CurrentFloor()].odd_Upstair.size();
		D=F[E[i].Get_CurrentFloor()].odd_Downstair.size();
		if(U>=D&&U!=0)									//ȥ���˶໹��ȥ���˶� 
		{
					
			while(F[E[i].Get_CurrentFloor()].odd_Upstair.size()!=0)
			{
				j=F[E[i].Get_CurrentFloor()].odd_Upstair.front();
				F[E[i].Get_CurrentFloor()].odd_Upstair.DE_front();
				E[i].Add_TargetFloor(j);
				E[i].Load++;
			}											//����
			//E[i].Diretion=1;
			//E[i].Wait();						//ͣ�½���
			return 1; 
		}
		else if(D>U)
		{	
			while(F[E[i].Get_CurrentFloor()].odd_Downstair.size()!=0)
			{
				j=F[E[i].Get_CurrentFloor()].odd_Downstair.front();
				F[E[i].Get_CurrentFloor()].odd_Downstair.DE_front();
				E[i].Add_TargetFloor(j);
				E[i].Load++;
			}//����
			//E[i].Diretion=-1;
			//print();
			//E[i].Wait();						//ͣ�½���
			return -1; 
		}
		if(D==U&&U==0)
		{
			//E[i].Diretion=0;
			//print()
			//E[i].Wait();
			return 1; 
		}//û��,�ȴ� 
	}
			
	if(i==2)											//ż����
	{
		U=F[E[i].Get_CurrentFloor()].even_Upstair.size();
		D=F[E[i].Get_CurrentFloor()].even_Downstair.size();
		if(U>=D&&U!=0)
		{
			
			while(F[E[i].Get_CurrentFloor()].even_Upstair.size()!=0)
			{
				j=F[E[i].Get_CurrentFloor()].even_Upstair.front();
				F[E[i].Get_CurrentFloor()].even_Upstair.DE_front();
				E[i].Add_TargetFloor(j);
				E[i].Load++;
			}//����
			//E[i].Diretion=1;
			//print();
			//E[i].Wait();						//ͣ�½��� 
			return 1; 
		}
		else if(U<D)
		{
					
			while(F[E[i].Get_CurrentFloor()].even_Downstair.size()!=0)
			{
				j=F[E[i].Get_CurrentFloor()].even_Downstair.front();
				F[E[i].Get_CurrentFloor()].even_Downstair.DE_front();
				E[i].Add_TargetFloor(j);
				E[i].Load++;
			}//����
			//E[i].Diretion=-1;
			//p
			//E[i].Wait();						//ͣ�½��� 
			return -1; 				//��ֵDiretion; 
		}
		if(D==U&&U==0)
		{
				
			//E[i].Diretion=0;
			//p
			//E[i].Wait();
			return 0; 
			}//û��,�ȴ�
		}
			
	if(i==3)											//�Ĳ㶼��ͣ 
	{
		U=F[E[i].Get_CurrentFloor()].odd_Upstair.size()+F[E[i].Get_CurrentFloor()].even_Upstair.size();
		D=F[E[i].Get_CurrentFloor()].odd_Downstair.size()+F[E[i].Get_CurrentFloor()].even_Downstair.size();
		if(U>=D&&U!=0)
		{		
			while(F[E[i].Get_CurrentFloor()].odd_Upstair.size()!=0)
			{
				j=F[E[i].Get_CurrentFloor()].odd_Upstair.front();
				F[E[i].Get_CurrentFloor()].odd_Upstair.DE_front();
				E[i].Add_TargetFloor(j);
				E[i].Load++;
			}
			while(F[E[i].Get_CurrentFloor()].even_Upstair.size()!=0)
			{
				j=F[E[i].Get_CurrentFloor()].even_Upstair.front();
				F[E[i].Get_CurrentFloor()].even_Upstair.DE_front();
				E[i].Add_TargetFloor(j);
				E[i].Load++;
			}
			//E[i].Diretion=1;
			//p
			//E[i].Wait();
			return 1; 
		}
		else if(D>U)
		{
			cout<<"������"<<endl;
			while(F[E[i].Get_CurrentFloor()].odd_Downstair.size()!=0)
			{
				j=F[E[i].Get_CurrentFloor()].odd_Downstair.front();
				F[E[i].Get_CurrentFloor()].odd_Downstair.DE_front();
				E[i].Add_TargetFloor(j);
				E[i].Load++;
			}
			while(F[E[i].Get_CurrentFloor()].even_Downstair.size()!=0)
			{
				j=F[E[i].Get_CurrentFloor()].even_Downstair.front();
				F[E[i].Get_CurrentFloor()].even_Downstair.DE_front();
				E[i].Add_TargetFloor(j);
				E[i].Load++;
			}
			//E[i].Diretion=-1;
			//E[i].Wait();
			//p
			return -1; 
		}
		else if(D==U&&U==0)
		{
			//E[i].Diretion=0;
			//p
			//E[i].Wait();
			//add something??? ���� 
			return 0; 
		}
				
	}
		
}


void Run()
{
	int i,D,U,j;
	//seeFloorQue(F);
	for(i=1;i<=10;i++)						//������������� 
	{
		//cout<<i<<"Wait:"<<F[i].Wait_number<<endl;
		while(F[i].Wait_number!=0)			//�ж�ĳ�������� 
		{
			CallElv(i);
			F[i].Wait_number--;
		}
	}
	
	for(i=1;i<=3;i++)
	{
		if(E[i].Get_NextTarget()==-1)
		{
			if(E[i].Get_NextAsk()!=-1)
			{
				if(E[i].Get_NextAsk()-E[i].Get_CurrentFloor()<0)
				E[i].Diretion=-1;
				else E[i].Diretion=1;
			}
		}
		
		if(E[i].Get_NextAsk()==-1)
		{
			if(E[i].Get_NextTarget()!=-1)
			{
				if(E[i].Get_NextTarget()-E[i].Get_CurrentFloor()<0)
				E[i].Diretion=-1;
				else E[i].Diretion=1;
			}
		}
		
		if(E[i].Get_NextAsk()==-1&&E[i].Get_NextTarget()==-1)	//��������ɷ�������,��������û�� ����while֮ǰ�� 
		{
			cout<<"����"<<i<<" ʱ��:"<<E[i].Get_CurrentTime()<<" ������!"<<endl;
			E[i].Diretion=0; 
			E[i].Wait();
			continue;
		}
		
		if(E[i].Get_NextAsk()!=-1||E[i].Get_NextTarget()!=-1)					//��������� 
		{
			
			if(i==1)																//����� 
			{
				if(E[i].Get_Arrival(E[i].Get_CurrentFloor())==1)					//�ò��ͣ 
				{
					
					cout<<E[i].Find_Target(E[i].Get_CurrentFloor())<<" "<<E[i].Find_Ask(E[i].Get_CurrentFloor())<<endl;
					int Stop=0;
					//E[i].SortWay();
					
					if(E[i].Find_Target(E[i].Get_CurrentFloor())>=1)					//����Ŀ�Ĳ� 
					{
						
						int leave=E[i].Find_Target(E[i].Get_CurrentFloor());
						Elevator::Finish+=leave;
						E[i].Load-=leave;
						E[i].DE_Target(E[i].Get_CurrentFloor());
						Stop++;
					}
					if(E[i].Find_Ask(E[i].Get_CurrentFloor())>=1)							//��������� ������ 
					{
						
						E[i].DE_Ask(E[i].Get_CurrentFloor());
						if(E[i].Load==0&& F[E[i].Get_CurrentFloor()].odd_Downstair.size()+F[E[i].Get_CurrentFloor()].odd_Upstair.size()!=0)
						{
							E[i].Diretion=Set(i);
							Stop++;
						}
						else 
						{
							if(E[i].Diretion==-1)
							{
								while(F[E[i].Get_CurrentFloor()].odd_Downstair.size()!=0)				//�ò���ȴ����в�Ϊ�� 
								{
									E[i].Add_TargetFloor(F[E[i].Get_CurrentFloor()].odd_Downstair.front());
									F[E[i].Get_CurrentFloor()].odd_Downstair.DE_front();
									E[i].Load++;
									Stop++;
								}
								
							}
							
							else if(E[i].Diretion==1)
							{
								while(F[E[i].Get_CurrentFloor()].odd_Upstair.size()!=0)		//�ò���ȴ����в�Ϊ�� 
								{
									E[i].Add_TargetFloor(F[E[i].Get_CurrentFloor()].odd_Upstair.front());
									F[E[i].Get_CurrentFloor()].odd_Upstair.DE_front();
									E[i].Load++;
									Stop++;
								}
								
							}
							
							else if(E[i].Diretion==0)
							{
								U=Set(i); 
								cout<<U<<endl;
								E[i].Diretion=U;
								if(U!=0)Stop++;
							}	
							
						}
					}
					if(Stop==0)					//�����ѱ�������������
					{
						if(E[i].Diretion==1)
						E[i].Up_stair();
						else 
						E[i].Down_stair();
					//print()
					}
					else if(Stop!=0)			//������������ͣ 
					{
						//E[i].Diretion=0;
						if(E[i].Get_CurrentTime()<=2&&E[i].Get_CurrentFloor()==1)goto L1;
						out1<<E[i].Get_CurrentTime()<<" "<<E[i].Get_CurrentFloor()<<endl;					//print()
						L1:E[i].Wait(); 
					}
					
					/*else 
					{
						if(E[i].Diretion==1)
						E[i].Up_stair();
						else 
						E[i].Down_stair();
					}*/
				}
				
				else 								//�ò㲻��ͣ 
				{
					cout<<"����"<<i<<":�ò㲻ͣ!"<<endl; 
					if(E[i].Diretion==1)
					E[i].Up_stair();
					else E[i].Down_stair();
				} 
				continue;							//�õ����ѵ����� 
			}
			
			if(i==2)											//ż����
			{
				if(E[i].Get_Arrival(E[i].Get_CurrentFloor()))					//�ò��ͣ 
				{
					int Stop=0;
					//E[i].SortWay();//system("pause");
					if(E[i].Find_Target(E[i].Get_CurrentFloor()))				//����Ŀ�Ĳ� ������ 
					{
						int leave=E[i].Find_Target(E[i].Get_CurrentFloor());
						Elevator::Finish+=leave;
						E[i].Load-=leave;
						E[i].DE_Target(E[i].Get_CurrentFloor());
						Stop++;
					}
					
					if(E[i].Find_Ask(E[i].Get_CurrentFloor()))	//��������� ������ 
					{
						//seeEleQue(E[2]);
						E[i].DE_Ask(E[i].Get_CurrentFloor());							//ȥ���ò�ָ�� 
						if(E[i].Load==0&&F[E[i].Get_CurrentFloor()].even_Downstair.size() + F[E[i].Get_CurrentFloor()].even_Upstair.size()!=0)
						{
							E[i].Diretion=Set(i);
							Stop++;
						}
						else 
						{
							if(E[i].Diretion==-1)											//�����ߵ� 
							{
								while(F[E[i].Get_CurrentFloor()].even_Downstair.size()!=0)	//�ò�ż�ȴ����в�Ϊ�� 
								{
									E[i].Add_TargetFloor(F[E[i].Get_CurrentFloor()].even_Downstair.front());
									F[E[i].Get_CurrentFloor()].even_Downstair.DE_front();
									E[i].Load++;
									Stop++;
								}
								
							}
							
							else if(E[i].Diretion==1)										//�����ߵ� 
							{
								while(F[E[i].Get_CurrentFloor()].even_Upstair.size()!=0)		//�ò�ż�ȴ����в�Ϊ�� 
								{
									E[i].Add_TargetFloor(F[E[i].Get_CurrentFloor()].even_Upstair.front());
									F[E[i].Get_CurrentFloor()].even_Upstair.DE_front();
									E[i].Load++;
									Stop++;
								}
								
							}
							
							else if(E[i].Diretion==0)
							{
								U=Set(i);
								E[i].Diretion=U;
								if(U!=0)Stop++;
							}
							
						}
					}
					if(Stop==0)					//�����ѱ�������������,ֱ������ 
					{
						if(E[i].Diretion==1)
						E[i].Up_stair();
						else E[i].Down_stair();
						//print()
					}
					else if(Stop!=0)			//������������ͣ 
					{
						if(E[i].Get_CurrentTime()<=2&&E[i].Get_CurrentFloor()==1)goto L2;
						out2<<E[i].Get_CurrentTime()<<" "<<E[i].Get_CurrentFloor()<<endl;						//print()
						L2:E[i].Wait(); 
					}
					/*else 
					{
						if(E[i].Diretion==1)
						E[i].Up_stair();
						else E[i].Down_stair();
					}*/
				}
				else 								//�ò㲻��ͣ 
				{
					if(E[i].Diretion==1)
					E[i].Up_stair();
					else E[i].Down_stair();
				} 
				continue;							//�õ����ѵ����� 
			}
			
			if(i==3)											//�Ĳ㶼��ͣ 
			{
				int Stop=0;
				if(E[i].Find_Target(E[i].Get_CurrentFloor())>=1)	//����Ŀ�Ĳ� ������ 
				{
					cout<<"����Ŀ�Ĳ�!"<<endl;
					int leave=E[i].Find_Target(E[i].Get_CurrentFloor());
					Elevator::Finish+=leave;
					E[i].Load-=leave;
					E[i].DE_Target(E[i].Get_CurrentFloor());
					Stop++;
				}
				
				if(E[i].Find_Ask(E[i].Get_CurrentFloor())>=1)	//��������� ������ 
				{
					cout<<"����"<<i<<":���������!"<<endl;
					E[i].DE_Ask(E[i].Get_CurrentFloor());							//ȥ���ò�ָ�� 
					if(E[i].Load==0&&F[E[i].Get_CurrentFloor()].even_Downstair.size() + F[E[i].Get_CurrentFloor()].even_Upstair.size() + F[E[i].Get_CurrentFloor()].odd_Downstair.size()+F[E[i].Get_CurrentFloor()].odd_Upstair.size()!=0)
					{
						E[i].Diretion=Set(i);
						Stop++;
					}
					
					else 
					{
						if(E[i].Diretion==-1)											//�����ߵ� 
						{
							while(F[E[i].Get_CurrentFloor()].even_Downstair.size()!=0)	//�ò�ż�ȴ����в�Ϊ�� 
							{
								E[i].Add_TargetFloor(F[E[i].Get_CurrentFloor()].even_Downstair.front());
								F[E[i].Get_CurrentFloor()].even_Downstair.DE_front();
								E[i].Load++;
								Stop++;
							}
							while(F[E[i].Get_CurrentFloor()].odd_Downstair.size()!=0)	//�ò���ȴ����в�Ϊ�� 
							{ 
								E[i].Add_TargetFloor(F[E[i].Get_CurrentFloor()].odd_Downstair.front());
								F[E[i].Get_CurrentFloor()].odd_Downstair.DE_front();
								E[i].Load++;
								Stop++;
							}
							
						}
						
						else if(E[i].Diretion==1)										//�����ߵ� 
						{
							while(F[E[i].Get_CurrentFloor()].even_Upstair.size()!=0)		//�ò�ż�ȴ����в�Ϊ�� 
							{ 
								E[i].Add_TargetFloor(F[E[i].Get_CurrentFloor()].even_Upstair.front());
								F[E[i].Get_CurrentFloor()].even_Upstair.DE_front();
								E[i].Load++;
								Stop++;
							}
							while(F[E[i].Get_CurrentFloor()].odd_Upstair.size()!=0)			//�ò���ȴ����в�Ϊ�� 
							{
								E[i].Add_TargetFloor(F[E[i].Get_CurrentFloor()].odd_Upstair.front());
								F[E[i].Get_CurrentFloor()].odd_Upstair.DE_front();
								E[i].Load++;
								Stop++;
							}
							
						}
						else if(E[i].Diretion==0)
						{
							U=Set(i);
							E[i].Diretion=U;
							if(U!=0)Stop++;
						}
					}
				}	
				if(Stop==0)					//�����ѱ�������������,ֱ������ 
				{
					if(E[i].Diretion==1)
					E[i].Up_stair();
					else E[i].Down_stair();
					//print()
				}
				else if(Stop!=0)			//������������ͣ 
				{
					//print()
					if(E[i].Get_CurrentTime()<=2&&E[i].Get_CurrentFloor()==1)goto L3;
					out3<<E[i].Get_CurrentTime()<<" "<<E[i].Get_CurrentFloor()<<endl;
					L3:E[i].Wait(); 
				}
				
				/*else 
				{
					if(E[i].Diretion==1)
					E[i].Up_stair();
					else E[i].Down_stair();
				}*/
			}
			
				 
		}
		
	}
	
}


void Ask()
{
	if(Wait_Time.size()!=0)
	{
		
		cout<<"ʣ������:"<<Wait_Time.size()<<endl;
		while(Wait_Time.front()<=E[1].Get_CurrentTime())
		{
			cout<<"Loading Ask...";//<<endl;
			cout<<Wait_Time.front()<<endl;
			if(Wait_Time.size()==0)break; 
			F[Wait_Floor.front()].AddToQueue(Wait_Target.front());
			Wait_Time.DE_front();
			Wait_Floor.DE_front();
			Wait_Target.DE_front();
		}
		cout<<"Done Loaded or beyong Time!"<<endl;
	}
	else cout<<"No new Ask!"<<endl;
}


void initial()
{
	int i;
	for(i=1;i<=3;i++)
	{
		E[i].Set_Type(i);						//��������1��2ż3���� 
	}
	for(i=1;i<=10;i++)
	{
		F[i].Set_Layer(i);						//¥�� 1~10 
	}
}

void scan()
{
	in>>AskTime;
	if(AskTime==0)
	{
		system("cls");
		system("color 0c");cout<<endl<<endl<<endl;
		cout<<Error<<endl<<endl<<endl<<endl<<endl;
		Sleep(100);
		system("color 04");Sleep(100);
		system("color 07");
		int ret=MessageBox(NULL,TEXT(teller1),TEXT(warning),MB_YESNO|MB_ICONWARNING);
		if(ret==IDYES)
		{
			int ret2=MessageBox(NULL,TEXT(teller2),TEXT(warning),MB_OK|MB_ICONWARNING);
		}
		system("pause");
		exit(0);
	}
	int i=AskTime;
	while(i-->0)
	{
		in>>time>>floor>>target;
		Wait_Time.Add(time);
		Wait_Floor.Add(floor);
		Wait_Target.Add(target);
	}
	in.close();
}

void Fileinput()
{
	in.open(inpath.c_str(),ios::in);
	out1.open(outpath1.c_str(),ios::app);
	out2.open(outpath2.c_str(),ios::app);
	out3.open(outpath3.c_str(),ios::app);
	scan();
}

char input[40]="\0";
char outp1[40]="\0",outp2[40]="\0",outp3[40]="\0";

void checkin()
{
	char *x=input;
	char *p=x;
	while(*p++!='\0');
	char w[10]=".txt";
	char index[10]=":\\";
	if(strcmp(w,p-5)!=0)
	{
		cout<<"\tError,�����ı�����Ϊ.txt��ʽ!"<<endl;
		cout<<endl<<endl<<"\t������!"<<endl;
		exit(0);
	}
	
}

void checkout()
{
	char w[10]=".txt";char *p[3];
	p[0]=outp1;p[1]=outp2;p[2]=outp3;
	while(*p[0]++);while(*p[1]++);while(*p[2]++);
	int i=0;
	for(;i<3;i++)
	{
		if(strcmp(w,p[i]-5)!=0)
		{
			cout<<"\tError,����ı�����Ϊ.txt��ʽ!"<<endl;
			cout<<endl<<endl<<"\t������!"<<endl;
			exit(1);
		}
	}
}

void findpath(char *s,char *p,int i)
{
	char *x=p;
	char *q=s;
	while(*x++!='\0');
	while(*x--!='\\');x+=2;
	strncpy(s,p,(x-p));
	switch (i)
	{
		case 1:strcpy((s+(int)(x-p)),outpath1.c_str());break;
		case 2:strcpy((s+(int)(x-p)),outpath2.c_str());break;
		case 3:strcpy((s+(int)(x-p)),outpath3.c_str());break;
	}
}

void Cmdinput(int argc,char **agv)
{
	if(argc>2&&argc<5)
	{
		system("cls");
		system("color 0c");cout<<endl<<endl<<endl;
		cout<<"\t�ļ���Ŀ����,��ָ��һ�������ı�,��һ�������ı�����������ı�"<<endl;
		exit(0);
	}
	strcpy(input,agv[1]);
	checkin();
	in.open(input,ios::in);
	if(in==NULL)cout<<"!!!"<<endl;
	if(argc>2)
	{
		strcpy(outp1,agv[2]);
		strcpy(outp3,agv[3]);
		strcpy(outp2,agv[4]);
		checkout();
	}
	else 
	{
		findpath(outp1,agv[1],1);
		findpath(outp2,agv[1],2);
		findpath(outp3,agv[1],3);
		//cout<<outp2<<endl<<outp3<<endl;
	}
	//cout<<"���·��\n"<< outp1<<endl<<outp3<<endl<<outp2<<endl;
	out1.open(outp1,ios::app);
	out2.open(outp2,ios::app);
	out3.open(outp3,ios::app);
	scan();
}

int main(int argc,char *argv[])
{
	initial();
	if(argc<=1)
	Fileinput();
	else Cmdinput(argc,argv);
	int i=0;
	print();
	Display();
	while(AskTime!=Elevator::Finish)
	{
		i++;
		if(i>10000)return 0;
		Ask();										//��ʱ�䵽����������¥�� 
		Run();										//��������1�� 
		print();
		Display();
		
		seeStatus(E);
		seeFloorQue(F);
	}
	out1.close();
	out2.close();
	out3.close();
	return 0;
}
