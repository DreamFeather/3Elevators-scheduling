using namespace std;
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
	TargetFloor.Add(n);				//Ŀ����ͬҲҪ�� 
}

void Elevator::DE_TargetFloor(const int n)
{
	TargetFloor.DE_find(n);
} 

void Elevator::Add_AskFloor(const int n)
{
	//if(Order==0)
	AskFloor.Add(n);				//������ͬ���� 
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
	if(Load==0&&Diretion==0)return 0; 		//���� 
	if(Load<=3)return 1;					//���� 
	return -1;								//æ 
}

int Elevator::Get_Arrival(const int n)			//1�ܵ�,0���� 
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
