

#include"Floor.h"
#include"elevator.h"
#include"test.h"
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

const string inpath="input.txt"; 
const string outpath1="output1.txt";
const string outpath2="output3.txt";
const string outpath3="output2.txt";
ifstream in;
ofstream out1,out2,out3;

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
	in.open(inpath.c_str(),ios::in);
	out1.open(outpath1.c_str(),ios::app);
	out2.open(outpath2.c_str(),ios::app);
	out3.open(outpath3.c_str(),ios::app);
}

void input()
{
	
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

int main()
{
	initial();
	in>>AskTime;
	input();
	while(AskTime!=Elevator::Finish)
	{
		Ask();										//��ʱ�䵽����������¥�� 
		Run();										//��������1�� 
		
	}
	out1.close();
	out2.close();
	out3.close();
	return 0;
}
