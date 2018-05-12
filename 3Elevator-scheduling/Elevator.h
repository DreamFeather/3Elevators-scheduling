#include"NewQue.h"
using namespace std;
class Elevator
{
	private:
		int Type;							//1odd 2even 3normal
		int CurrentFloor;					//��ǰ¥��1~10;
		int	CurrentTime;					//��ǰʱ��;
		que TargetFloor;					//Ŀ��¥��
		que AskFloor;						//����¥�� 
		int Door;							//-1�ر�,1���� 
		int Arrival[11];					//�ܵ���¥�� 
	public:
		int Diretion;						//���� -1��,0�ȴ�,1��
		int Load;							//(����)�˿�����
		int NextFloor;								//��һĿ�ĵ� 
		static int Finish;							//��������ܴ���;
		void Set_Type(const int);					//��������
		Elevator();							 		//�޲ι���
		void Add_TargetFloor(const int);			//����Ŀ��
		void DE_TargetFloor(const int);				//ɾ��Ŀ�� 
		void Add_AskFloor(const int);				//�������� 
		int Get_CurrentTime(); 						//�鿴��ǰʱ��
		int Get_CurrentFloor();		 				//�鿴��ǰ¥��
		int Get_Diretion();							//�鿴��ǰ����  
		void Wait();								//���ݿ���
		void Up_stair();							//����1 
		void Down_stair();							//�½�1 
		int Door_status();							//��״̬ 
		int status();								//����״̬
		int Get_Arrival(const int n);				//�������	
		int Order(const int n);						//�鿴�Ƿ��иò� 
		void SortWay();								//�ڵ�ǰ����������
		int Get_Asksize();							//���������� 
		int Get_NextAsk();							//��������� 
		int Get_NextTarget();						//����Ŀ��� 
		void DE_NextAsk();							//ɾ�������� 
		void DE_NextTarget();						//ɾ����Ŀ�� 
		int Find_Target(const int);					//Ѱ��ָ����
		void DE_Target(const int);					//ɾ��ָ����
		int Find_Ask(const int);					//Ѱ��ָ���� 
		void DE_Ask(const int);						//ɾ��ָ���� 
};
#include"Elevator.cpp"

