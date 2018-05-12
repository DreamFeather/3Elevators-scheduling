

#include"Floor.h"
#include"elevator.h"
#include"test.h"
#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
using namespace std;
int AskTime;							//请求次数 
Elevator E[4];							//搞3个电梯 
Floor F[11];							//搞10层楼 
int time=0,floor=0,target=0;					//从文件读入时间,楼层,目的地 
int Elevator::Finish=0;					//电梯任务完成为0 
que Wait_Time,Wait_Floor,Wait_Target;	//输入存放队列  
int AllAsk=0;								//计数所有请求 

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
			return 1;			//有相同目标	
		}
	}
	return 0;														//未接 
} 



void CallElv(const int f)					//该楼层是有请求楼层 
{
	if(ordered(f)==1)return ; 																	//已经被接了 
	int j;
	for(j=1;j<=3;j++)
	{
		if(E[j].status()==0&&E[j].Get_Arrival(f)==1)											//空闲 :一次分配 
		{
			if(j==1)
			{
				if(F[f].odd_Downstair.size()!=0||F[f].odd_Upstair.size()!=0)					//有去奇层的人 
				{
					E[j].Add_AskFloor(f);cout<<"电梯1"<<"接了"<<f<<"层任务\n";return;
				}
			}
			
			else if(j==2)
			{
				if(F[f].even_Downstair.size()!=0||F[f].even_Upstair.size()!=0)					//有去偶层的人 
				{
					E[j].Add_AskFloor(f);cout<<"电梯2"<<"接了"<<f<<"层任务\n";return;
				}
			}
			
			else if(j==3)																		//前面的都不载 
			{
				if(E[1].Order(f)==0&&F[f].odd_Downstair.size()+F[f].odd_Upstair.size()!=0)		//如果没接
				{
					E[j].Add_AskFloor(f);cout<<"电梯3"<<"接了"<<f<<"层任务\n";return ;
				}
				
				if(E[2].Order(f)==0&&F[f].even_Downstair.size()+F[f].even_Upstair.size()!=0)
				{
					E[j].Add_AskFloor(f);cout<<"电梯3"<<"接了"<<f<<"层任务\n";return ;
				}
				
			}						
			
		}
		
	}

	if(ordered(f)==1)return ;
	cout<<f<<" 第一次分配失败!\n";
	for(j=1;j<=3;j++)																			//稍忙 :二次分配 
	{
		if(E[j].Get_Arrival(f)==1)
		if(E[j].Get_Diretion()*(E[j].Get_CurrentFloor()-f)>=0)
		{
			if(j==1)
			{
				if(F[f].odd_Downstair.size()!=0||F[f].odd_Upstair.size()!=0)					//有去奇层的人 
				{
					E[j].Add_AskFloor(f);cout<<"电梯1"<<"接了"<<f<<"层任务\n";return;
				}
			} 
			
			else if(j==2)
			{
				if(F[f].even_Downstair.size()!=0||F[f].even_Upstair.size()!=0)					//有去偶层的人 
				{
					E[j].Add_AskFloor(f);cout<<"电梯2"<<"接了"<<f<<"层任务\n";return;
				}
			}
			
			else 
			{
				if(E[1].Order(f)==0&&F[f].odd_Downstair.size()+F[f].odd_Upstair.size()!=0)		//如果没接
				{
					E[j].Add_AskFloor(f);cout<<"电梯3"<<"接了"<<f<<"层任务\n";return ;
				}
				
				if(E[2].Order(f)==0&&F[f].even_Downstair.size()+F[f].even_Upstair.size()!=0)
				{
					E[j].Add_AskFloor(f);cout<<"电梯3"<<"接了"<<f<<"层任务\n";return ;
				}
			}
			
		}
		
	}
	
	if(ordered(f)==1)return ;
	cout<<f<<" 第二次分配失败!\n";
	if(j==4)																					//全忙 :三次(强行)分配 
	{
		int x=E[3].Load,y;
		if(E[2].Get_Arrival(f)==1&&F[f].odd_Downstair.size()+F[f].odd_Upstair.size()!=0)
		{
			y=E[2].Load;
			if(y-3<=x)
			{
				E[2].Add_AskFloor(f);	cout<<"电梯2"<<"接了"<<f<<"层任务\n"; 
			}
			else 
			{
				E[3].Add_AskFloor(f);	cout<<"电梯3"<<"接了"<<f<<"层任务\n";
			}
		}
		
		if(E[3].Order(f)==0)																		//三号电梯没接 
		if(E[1].Get_Arrival(f)==1&&F[f].even_Downstair.size()+F[f].even_Upstair.size()!=0)
		{
			y=E[1].Load;
			if(y-3<=x)
			{
				E[1].Add_AskFloor(f);	cout<<"电梯1"<<"接了"<<f<<"层任务\n"; system("pause"); 
			}
			else 
			{
				E[3].Add_AskFloor(f);	cout<<"电梯3"<<"接了"<<f<<"层任务\n";
			}
			
			return ;
		}
		
	}
	
}

int Set(const int i)
{
	int U=0,D=0,j=0,l;
	if(i==1)											//奇电梯 
	{
				
		U=F[E[i].Get_CurrentFloor()].odd_Upstair.size();
		D=F[E[i].Get_CurrentFloor()].odd_Downstair.size();
		if(U>=D&&U!=0)									//去上人多还是去下人多 
		{
					
			while(F[E[i].Get_CurrentFloor()].odd_Upstair.size()!=0)
			{
				j=F[E[i].Get_CurrentFloor()].odd_Upstair.front();
				F[E[i].Get_CurrentFloor()].odd_Upstair.DE_front();
				E[i].Add_TargetFloor(j);
				E[i].Load++;
			}											//上人
			//E[i].Diretion=1;
			//E[i].Wait();						//停下接人
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
			}//上人
			//E[i].Diretion=-1;
			//print();
			//E[i].Wait();						//停下接人
			return -1; 
		}
		if(D==U&&U==0)
		{
			//E[i].Diretion=0;
			//print()
			//E[i].Wait();
			return 1; 
		}//没人,等待 
	}
			
	if(i==2)											//偶电梯
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
			}//上人
			//E[i].Diretion=1;
			//print();
			//E[i].Wait();						//停下接人 
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
			}//上人
			//E[i].Diretion=-1;
			//p
			//E[i].Wait();						//停下接人 
			return -1; 				//赋值Diretion; 
		}
		if(D==U&&U==0)
		{
				
			//E[i].Diretion=0;
			//p
			//E[i].Wait();
			return 0; 
			}//没人,等待
		}
			
	if(i==3)											//哪层都能停 
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
			cout<<"分配中"<<endl;
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
			//add something??? 下人 
			return 0; 
		}
				
	}
		
}


void Run()
{
	int i,D,U,j;
	//seeFloorQue(F);
	for(i=1;i<=10;i++)						//分派任务给电梯 
	{
		//cout<<i<<"Wait:"<<F[i].Wait_number<<endl;
		while(F[i].Wait_number!=0)			//判断某层有无人 
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
		
		if(E[i].Get_NextAsk()==-1&&E[i].Get_NextTarget()==-1)	//电梯已完成分配任务,可能有人没下 可在while之前下 
		{
			cout<<"电梯"<<i<<" 时间:"<<E[i].Get_CurrentTime()<<" 无任务!"<<endl;
			E[i].Diretion=0; 
			E[i].Wait();
			continue;
		}
		
		if(E[i].Get_NextAsk()!=-1||E[i].Get_NextTarget()!=-1)					//有任务或方向 
		{
			
			if(i==1)																//奇电梯 
			{
				if(E[i].Get_Arrival(E[i].Get_CurrentFloor())==1)					//该层可停 
				{
					
					cout<<E[i].Find_Target(E[i].Get_CurrentFloor())<<" "<<E[i].Find_Ask(E[i].Get_CurrentFloor())<<endl;
					int Stop=0;
					//E[i].SortWay();
					
					if(E[i].Find_Target(E[i].Get_CurrentFloor())>=1)					//到达目的层 
					{
						
						int leave=E[i].Find_Target(E[i].Get_CurrentFloor());
						Elevator::Finish+=leave;
						E[i].Load-=leave;
						E[i].DE_Target(E[i].Get_CurrentFloor());
						Stop++;
					}
					if(E[i].Find_Ask(E[i].Get_CurrentFloor())>=1)							//到达请求层 可上人 
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
								while(F[E[i].Get_CurrentFloor()].odd_Downstair.size()!=0)				//该层奇等待队列不为空 
								{
									E[i].Add_TargetFloor(F[E[i].Get_CurrentFloor()].odd_Downstair.front());
									F[E[i].Get_CurrentFloor()].odd_Downstair.DE_front();
									E[i].Load++;
									Stop++;
								}
								
							}
							
							else if(E[i].Diretion==1)
							{
								while(F[E[i].Get_CurrentFloor()].odd_Upstair.size()!=0)		//该层奇等待队列不为空 
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
					if(Stop==0)					//任务已被其他电梯抢空
					{
						if(E[i].Diretion==1)
						E[i].Up_stair();
						else 
						E[i].Down_stair();
					//print()
					}
					else if(Stop!=0)			//做过任务需暂停 
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
				
				else 								//该层不可停 
				{
					cout<<"电梯"<<i<<":该层不停!"<<endl; 
					if(E[i].Diretion==1)
					E[i].Up_stair();
					else E[i].Down_stair();
				} 
				continue;							//该电梯已调度完 
			}
			
			if(i==2)											//偶电梯
			{
				if(E[i].Get_Arrival(E[i].Get_CurrentFloor()))					//该层可停 
				{
					int Stop=0;
					//E[i].SortWay();//system("pause");
					if(E[i].Find_Target(E[i].Get_CurrentFloor()))				//到达目的层 可下人 
					{
						int leave=E[i].Find_Target(E[i].Get_CurrentFloor());
						Elevator::Finish+=leave;
						E[i].Load-=leave;
						E[i].DE_Target(E[i].Get_CurrentFloor());
						Stop++;
					}
					
					if(E[i].Find_Ask(E[i].Get_CurrentFloor()))	//到达请求层 可上人 
					{
						//seeEleQue(E[2]);
						E[i].DE_Ask(E[i].Get_CurrentFloor());							//去掉该层指令 
						if(E[i].Load==0&&F[E[i].Get_CurrentFloor()].even_Downstair.size() + F[E[i].Get_CurrentFloor()].even_Upstair.size()!=0)
						{
							E[i].Diretion=Set(i);
							Stop++;
						}
						else 
						{
							if(E[i].Diretion==-1)											//向下走的 
							{
								while(F[E[i].Get_CurrentFloor()].even_Downstair.size()!=0)	//该层偶等待队列不为空 
								{
									E[i].Add_TargetFloor(F[E[i].Get_CurrentFloor()].even_Downstair.front());
									F[E[i].Get_CurrentFloor()].even_Downstair.DE_front();
									E[i].Load++;
									Stop++;
								}
								
							}
							
							else if(E[i].Diretion==1)										//向上走的 
							{
								while(F[E[i].Get_CurrentFloor()].even_Upstair.size()!=0)		//该层偶等待队列不为空 
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
					if(Stop==0)					//任务已被其他电梯抢空,直接走了 
					{
						if(E[i].Diretion==1)
						E[i].Up_stair();
						else E[i].Down_stair();
						//print()
					}
					else if(Stop!=0)			//做过任务需暂停 
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
				else 								//该层不可停 
				{
					if(E[i].Diretion==1)
					E[i].Up_stair();
					else E[i].Down_stair();
				} 
				continue;							//该电梯已调度完 
			}
			
			if(i==3)											//哪层都能停 
			{
				int Stop=0;
				if(E[i].Find_Target(E[i].Get_CurrentFloor())>=1)	//到达目的层 可下人 
				{
					cout<<"到达目的层!"<<endl;
					int leave=E[i].Find_Target(E[i].Get_CurrentFloor());
					Elevator::Finish+=leave;
					E[i].Load-=leave;
					E[i].DE_Target(E[i].Get_CurrentFloor());
					Stop++;
				}
				
				if(E[i].Find_Ask(E[i].Get_CurrentFloor())>=1)	//到达请求层 可上人 
				{
					cout<<"电梯"<<i<<":到达请求层!"<<endl;
					E[i].DE_Ask(E[i].Get_CurrentFloor());							//去掉该层指令 
					if(E[i].Load==0&&F[E[i].Get_CurrentFloor()].even_Downstair.size() + F[E[i].Get_CurrentFloor()].even_Upstair.size() + F[E[i].Get_CurrentFloor()].odd_Downstair.size()+F[E[i].Get_CurrentFloor()].odd_Upstair.size()!=0)
					{
						E[i].Diretion=Set(i);
						Stop++;
					}
					
					else 
					{
						if(E[i].Diretion==-1)											//向下走的 
						{
							while(F[E[i].Get_CurrentFloor()].even_Downstair.size()!=0)	//该层偶等待队列不为空 
							{
								E[i].Add_TargetFloor(F[E[i].Get_CurrentFloor()].even_Downstair.front());
								F[E[i].Get_CurrentFloor()].even_Downstair.DE_front();
								E[i].Load++;
								Stop++;
							}
							while(F[E[i].Get_CurrentFloor()].odd_Downstair.size()!=0)	//该层奇等待队列不为空 
							{ 
								E[i].Add_TargetFloor(F[E[i].Get_CurrentFloor()].odd_Downstair.front());
								F[E[i].Get_CurrentFloor()].odd_Downstair.DE_front();
								E[i].Load++;
								Stop++;
							}
							
						}
						
						else if(E[i].Diretion==1)										//向上走的 
						{
							while(F[E[i].Get_CurrentFloor()].even_Upstair.size()!=0)		//该层偶等待队列不为空 
							{ 
								E[i].Add_TargetFloor(F[E[i].Get_CurrentFloor()].even_Upstair.front());
								F[E[i].Get_CurrentFloor()].even_Upstair.DE_front();
								E[i].Load++;
								Stop++;
							}
							while(F[E[i].Get_CurrentFloor()].odd_Upstair.size()!=0)			//该层奇等待队列不为空 
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
				if(Stop==0)					//任务已被其他电梯抢空,直接走了 
				{
					if(E[i].Diretion==1)
					E[i].Up_stair();
					else E[i].Down_stair();
					//print()
				}
				else if(Stop!=0)			//做过任务需暂停 
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
		
		cout<<"剩余请求:"<<Wait_Time.size()<<endl;
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
		E[i].Set_Type(i);						//电梯类型1奇2偶3正常 
	}
	for(i=1;i<=10;i++)
	{
		F[i].Set_Layer(i);						//楼层 1~10 
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
		Ask();										//将时间到的请求输入楼层 
		Run();										//电梯运行1次 
		
	}
	out1.close();
	out2.close();
	out3.close();
	return 0;
}
