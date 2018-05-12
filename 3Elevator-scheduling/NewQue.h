#ifndef  TEST1_H
#define  TEST1_H

#include<stdlib.h>
#include<iostream>
using namespace std;
class que
{	
	private:
		struct Que;								//新型队列
		struct Que *Head,*Now,*Tail; 			//头针,动针,尾针 
	public:
		que();									//构造 
		~que();									//析构 
		int front();							//返回首元素
		int back();								//返回尾元素 
		void DE_front();						//删除首元素
		void DE_back();							//删除尾元素
		void initial();							//初始化 
		int size();								//返回长度 
		void Add(const int n);					//增加元素 
		void Sort(const int n);					//按从小到大排序
		void clean(); 							//清空 
		int find(const int n);					//寻找某元素 
		void DE_find(const int n);				//删除所有该元素 
};

#include"NewQue.h"
#endif
