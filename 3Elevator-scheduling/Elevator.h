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
#include"Elevator.cpp"

