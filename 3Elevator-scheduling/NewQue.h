#ifndef  TEST1_H
#define  TEST1_H

#include<stdlib.h>
#include<iostream>
using namespace std;
class que
{	
	private:
		struct Que;								//���Ͷ���
		struct Que *Head,*Now,*Tail; 			//ͷ��,����,β�� 
	public:
		que();									//���� 
		~que();									//���� 
		int front();							//������Ԫ��
		int back();								//����βԪ�� 
		void DE_front();						//ɾ����Ԫ��
		void DE_back();							//ɾ��βԪ��
		void initial();							//��ʼ�� 
		int size();								//���س��� 
		void Add(const int n);					//����Ԫ�� 
		void Sort(const int n);					//����С��������
		void clean(); 							//��� 
		int find(const int n);					//Ѱ��ĳԪ�� 
		void DE_find(const int n);				//ɾ�����и�Ԫ�� 
};

#include"NewQue.h"
#endif
