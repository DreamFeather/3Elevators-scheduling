#ifndef  FLOOR_H
#define  FLOOR_H

#include"NewQue.h"
using namespace std; 
class Floor
{
	private: 
		int layer;								//¥�����1~10;
	public:
		int Wait_number;						//�ȴ����� 
		que odd_Upstair;						//�������� 
		que odd_Downstair;						//��������
		que even_Upstair;						//ż�������
		que even_Downstair;						//ż������� 

	public:
		Floor();								//����
		int IntoElevator(const int,const int);	//�ϵ���
		void AddToQueue(const int);				//�����Ŷ�
		void Set_Layer(const int);				//����¥��
};
#include"Floor.cpp"
#endif 
