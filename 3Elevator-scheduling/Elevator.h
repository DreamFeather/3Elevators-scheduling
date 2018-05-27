#include"NewQue.h"
using namespace std;
class Elevator
{
	private:
		int Type;							//1odd 2even 3normal
		int CurrentFloor;					//当前楼层1~10;
		int	CurrentTime;					//当前时间;
		que TargetFloor;					//目标楼层
		que AskFloor;						//请求楼层 
		int Door;							//-1关闭,1开启 
		int Arrival[11];					//能到的楼层 
	public:
		int Diretion;						//方向 -1下,0等待,1上
		int Load;							//(载重)乘客数量
		int NextFloor;								//下一目的地 
		static int Finish;							//完成任务总次数;
		void Set_Type(const int);					//设置类型
		Elevator();							 		//无参构造
		void Add_TargetFloor(const int);			//增加目标
		void DE_TargetFloor(const int);				//删除目标 
		void Add_AskFloor(const int);				//增加请求 
		int Get_CurrentTime(); 						//查看当前时间
		int Get_CurrentFloor();		 				//查看当前楼层
		int Get_Diretion();							//查看当前方向  
		void Wait();								//电梯空闲
		void Up_stair();							//上升1 
		void Down_stair();							//下降1 
		int Door_status();							//门状态 
		int status();								//电梯状态
		int Get_Arrival(const int n);				//到达许可	
		int Order(const int n);						//查看是否有该层 
		void SortWay();								//在当前方向上排序
		int Get_Asksize();							//请求队列情况 
		int Get_NextAsk();							//返回请求层 
		int Get_NextTarget();						//返回目标层 
		void DE_NextAsk();							//删除该请求 
		void DE_NextTarget();						//删除该目标 
		int Find_Target(const int);					//寻找指定层
		void DE_Target(const int);					//删除指定层
		int Find_Ask(const int);					//寻找指定层 
		void DE_Ask(const int);						//删除指定层 
};

void Elevator::Set_Type(const int n)
{
	Type=n;
	int i;
	switch(n)
	{
		case 1:for(i=1;i<=10;i++)
				{
					if(i%2==1)Arrival[i]=1;
					else Arrival[i]=0;
				}break;
				
		case 2:for(i=1;i<=10;i++)
				{
					if(i%2==0)Arrival[i]=1;
					else Arrival[i]=0;
				}Arrival[1]=1;break;
				
		case 3:for(i=1;i<=10;i++)Arrival[i]=1;break;
	} 
}

int Elevator::Get_Diretion()
{
	/*if(TargetFloor.size()==0&&AskFloor.size()==0)
	return 0;
	int i,j;
	if(TargetFloor.size()!=0)
	{
		if(TargetFloor.front()>=CurrentFloor)return 1;
		else return -1;
	}
	if(AskFloor.size()!=0)
	{
		if(AskFloor.front()>=CurrentFloor)return 1;
		else return -1;
	}*/
	return Diretion;
}

void Elevator::Add_TargetFloor(const int n)
{
	TargetFloor.Add(n);				//目标相同也要加 
}

void Elevator::DE_TargetFloor(const int n)
{
	TargetFloor.DE_find(n);
} 

void Elevator::Add_AskFloor(const int n)
{
	//if(Order==0)
	AskFloor.Add(n);				//请求相同不加 
}

int Elevator::Get_CurrentTime()
{
	return CurrentTime;
}

int Elevator::Get_CurrentFloor()
{
	return CurrentFloor;
}

Elevator::Elevator()
{
	CurrentFloor=1;
	CurrentTime=0;
	Load=0;
	Door=-1;
	NextFloor=0;
}

void Elevator::Wait()
{
	if(Door==1)Door=-1;
	CurrentTime++;
}

void Elevator::Up_stair()
{
	if(Door==1)Door=-1;
	CurrentFloor++;
	CurrentTime++;
}
void Elevator::Down_stair()
{
	if(Door==1)Door=-1;
	CurrentFloor--;
	CurrentTime++;
}

int Elevator::status()
{
	if(Load==0&&Diretion==0)return 0; 		//空闲 
	if(Load<=3)return 1;					//还行 
	return -1;								//忙 
}

int Elevator::Get_Arrival(const int n)			//1能到,0不能 
{
	return Arrival[n];
}

int Elevator::Order(const int n)
{
	return (TargetFloor.find(n)||AskFloor.find(n));
}

void Elevator::SortWay()
{
	int i=Get_Diretion();
	TargetFloor.Sort(i);
	AskFloor.Sort(i);
}

int Elevator::Get_Asksize()
{
	return AskFloor.size();
}

int Elevator::Get_NextAsk()
{
	return AskFloor.front();
}

int Elevator::Get_NextTarget()
{
	return TargetFloor.front();
}

void Elevator::DE_NextAsk()
{
	AskFloor.DE_front();
}

void Elevator::DE_NextTarget()
{
	TargetFloor.DE_front();
}

int Elevator::Find_Target(const int n)
{
	return TargetFloor.find(n);
}

void Elevator::DE_Target(const int n)
{
	TargetFloor.DE_find(n);
}

int Elevator::Find_Ask(const int n)
{
	return AskFloor.find(n);
}

void Elevator::DE_Ask(const int n)
{
	AskFloor.DE_find(n);
}
