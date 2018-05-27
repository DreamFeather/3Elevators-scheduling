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

que::que()
{
	initial();
}

que::~que()
{
	clean();
}

struct que::Que									//链表原型 
{
	int Target;
	struct Que *next,*last;
};

int que::front()								//返回首元素
{
	if(Head==NULL)return -1;
	else return (Head->Target);
}

int que::back()									//返回尾元素
{
	if(Tail==NULL)return -1;
	else return (Tail->Target);
} 

void que::DE_front()							//删除首元素
{
	if(Head==NULL)return ;
	if(size()==1)
	{
		free(Head);Now=Head=Tail=NULL;return ;
	}
	Now=Head;
	Head=Head->next;
	Head->last=NULL; 
	free(Now);
}

void que::DE_back()							//删除尾元素
{
	if(Tail==NULL)return ;
	if(size()==1)
	{
		free(Tail);Now=Head=Tail=NULL;return ;
	}
	Now=Tail;
	Tail=Tail->last;
	Tail->next=NULL;
	free(Now);
} 


void que::initial()								//初始化 
{
	Now=Head=Tail=NULL;
}

int que::size()									//返回长度 
{
	int len=0;
	Now=Head; 
	while(Now!=NULL)
	{
		len++;Now=Now->next;
	}
	return len;
}

void que::Add(const int n)						//增加元素 
{
	if(Head==NULL)
	{
		Now=(struct Que*)malloc(sizeof(struct Que));
		Head=Tail=Now;
		Now->Target=n;
		Head->last=NULL;
		Tail->next=NULL;
	}
	else 
	{
		Now=(struct Que*)malloc(sizeof(struct Que));
		Tail->next=Now;
		Now->last=Tail;
		Now->Target=n;
		Tail=Now;
		Tail->next=NULL;
	}
}

void que::Sort(const int n)						//排序 -1递减,0,1递增 
{
	int len=size();
	int i,j,temp,w;
	for(i=0;i<len-1;i++)
	{
		for(j=0;j<len-i-1;j++)
		{
			for(w=0,Now=Head;w<j;w++)Now=Now->next;
			{
				if(n>=0) 
				if(Now->Target>Now->next->Target)
				{
					temp=Now->Target;
					Now->Target=Now->next->Target;
					Now->next->Target=temp;
				}
				if(n==-1)
				if(Now->Target<Now->next->Target)
				{
					temp=Now->Target;
					Now->Target=Now->next->Target;
					Now->next->Target=temp;
				}
			}

		}
	}
}

void que::clean()							//清空 
{
	Now=Head;
	while(Now!=NULL)
	{
		Tail=Now->next;
		free(Now);
		Now=Tail;
	}
	Now=Tail=Head=NULL;
}

int que::find(const int n)				//寻找某元素i个数,0无 
{
	int i=0;
	Now=Head;
	while(Now!=NULL)
	{
		if(Now->Target==n)i++;
		Now=Now->next;
	}
	return i;
}

void que::DE_find(const int n)
{
	Now=Head;
	while(Now!=NULL)
	{
		if(Now->Target==n)
		{
			if(size()==1)
			{
				free(Head);
				Head=Now=Tail=NULL;
				continue;
			}
			if(Now==Head)
			{
				Head=Head->next;
				free(Now);
				Now=Head;
				Now->last=NULL;
			}
			else if(Now==Tail)
			{
				Tail=Tail->last;
				free(Now);
				Now=Tail;
				Now->next=NULL;
			}
			else
			{
				struct Que *p,*q;
				p=Now->last;
				q=Now->next;
				p->next=q;
				q->last=p;
				free(Now);
				Now=p;
			}
			
		}
		
		Now=Now->next;
	}
}
#endif
