#ifndef  FLOOR_H
#define  FLOOR_H

#include"NewQue.h"
using namespace std; 
class Floor
{
	private: 
		int layer;								//楼层序号1~10;
	public:
		int Wait_number;						//等待人数 
		que odd_Upstair;						//奇层队列上 
		que odd_Downstair;						//奇层队列下
		que even_Upstair;						//偶层队列上
		que even_Downstair;						//偶层队列下 

	public:
		Floor();								//构造
		int IntoElevator(const int,const int);	//上电梯
		void AddToQueue(const int);				//增加排队
		void Set_Layer(const int);				//设置楼层
};
#include"Floor.cpp"
#endif 
