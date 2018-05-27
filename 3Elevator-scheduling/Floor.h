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

Floor::Floor()
{
	Wait_number=0;
} 

void Floor::AddToQueue(const int Target_floor)
{
	Wait_number++; 
	int x=0;
	if(Target_floor%2==0)x++;		else x+=2;
	if(Target_floor>=layer)x+=2;	else x+=0;
	//1 even_down 2 odd_down 3 even_up 4 odd_up
	switch	(x)
	{
		case 1:even_Downstair.Add(Target_floor);break;
		case 2:odd_Downstair.Add(Target_floor);break;
		case 3:even_Upstair.Add(Target_floor);break;
		case 4:odd_Upstair.Add(Target_floor);break;
	}
}

void Floor::Set_Layer(const int n)
{
	layer=n;
}
