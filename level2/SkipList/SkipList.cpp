#include<bits/stdc++.h>
using namespace std;

class RandomClass
{
protected:
	static unsigned int seed;
public:
	static int GetRandInt()
	{
		seed = seed * seed + 2 * seed + unsigned(time(NULL)) * seed + 27 + 2 * seed * seed * seed;
		srand(seed);
		return rand();
	}
};
unsigned int RandomClass::seed = unsigned(time(NULL));

//�Ѿ��������ڱ����ᱻɾ��
class SkipList
{
protected:
	//�㶨��
	struct Node
	{
		int Val;
		Node(int val)
		{
			Val = val;
		}
		Node* PreNode = NULL;
		Node* NextNode = NULL;
		Node* UpNode = NULL;
		Node* DownNode = NULL;
	};
	//���Ͻ��ڱ�
	Node* guardFirst = new Node(0x80000000);
	//���Ͻ��ڱ�
	Node* guardLast = new Node(0x7fffffff);
	//��1/3���ʷ���true�����������Ƿ�������һ��
	bool CanUpgrate()
	{
		int a = RandomClass::GetRandInt() % 100;
		if (a < 50)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//��һ���������µ�
	Node* AttachNext(Node* newNode, Node* target)
	{
		Node* targetNext = target->NextNode;
		target->NextNode = newNode;
		target->NextNode->PreNode = target;
		target->NextNode->NextNode = targetNext;
		if (targetNext != NULL)
		{
			targetNext->PreNode = target->NextNode;
		}
		return target->NextNode;
	}
	//ɾ���ڵ��Լ��ڵ��Ϸ��ڵ�
	void DeleteNode(Node* target)
	{
		while (true)
		{
			target->PreNode->NextNode = target->NextNode;
			target->NextNode->PreNode = target->PreNode;
			if (target->UpNode == NULL)
			{
				free(target);
				break;
			}
			else
			{
				target = target->UpNode;
				free(target->DownNode);
			}
		}
	}
public:
	SkipList()
	{
		guardFirst->NextNode = guardLast;
	}
	//���Ԫ��
	void AddNode(int val)
	{
		Node* presentPositon = guardFirst;
		while (true)
		{
			if (presentPositon->NextNode->Val > val)
			{
				if (presentPositon->DownNode == NULL)
				{
					Node* newNode = AttachNext(new Node(val), presentPositon);
					while (CanUpgrate())
					{
						Node* UpperNode = new Node(newNode->Val);
						UpperNode->DownNode = newNode;
						newNode->UpNode = UpperNode;
						newNode = UpperNode;
						while(presentPositon->UpNode == NULL)
						{
							if (presentPositon->PreNode == NULL)
							{
								//��������ڱ����������ڱ�,�����µ�ĩβ�ڱ�
								Node* presentGuardFirst = presentPositon;
								guardFirst = new Node(0x80000000);
								guardFirst->DownNode = presentGuardFirst;
								presentGuardFirst->UpNode = guardFirst;
								Node* presentGuardLast = guardLast;
								guardLast = new Node(0x7fffffff);
								guardLast->DownNode = presentGuardLast;
								presentGuardLast->UpNode = guardLast;
								AttachNext(guardLast, guardFirst);
							}
							else
							{
								presentPositon = presentPositon->PreNode;
							}
						}
						presentPositon = presentPositon->UpNode;
						AttachNext(UpperNode, presentPositon);
					}
					break;
				}
				else
				{
					presentPositon = presentPositon->DownNode;
				}
			}
			else
			{
				presentPositon = presentPositon->NextNode;
			}
		}
	}
	//ɾ����һ����ӦֵԪ�أ�û�д�Ԫ�ط���false
	bool Delete(int target)
	{
		Node* presentPositon = guardFirst;
		while (true)
		{
			if (presentPositon->NextNode->Val == target)
			{
				if (presentPositon->DownNode != NULL)
				{
					presentPositon = presentPositon->DownNode;
				}
				else
				{
					DeleteNode(presentPositon->NextNode);
					return true;
				}
			}
			else
			{

				if (presentPositon->NextNode->Val > target)
				{
					if (presentPositon->DownNode == NULL)
					{
						return false;
					}
					else
					{
						presentPositon = presentPositon->DownNode;
					}
				}
				else
				{
					presentPositon = presentPositon->NextNode;
				}
			}
		}
	}
	//���Ҵ��ڵ��ڴ�Ԫ�صĵ�һ��Ԫ�أ�û���򷵻�ĩβ�ڱ�
	Node* GetCeil(int target)
	{
		Node* presentPositon = guardFirst;
		while (true)
		{
			if (presentPositon->NextNode->Val == target)
			{
				return presentPositon->NextNode;
			}
			else
			{

				if (presentPositon->NextNode->Val > target)
				{
					if (presentPositon->DownNode == NULL)
					{
						return presentPositon->NextNode;
					}
					else
					{
						presentPositon = presentPositon->DownNode;
					}
				}
				else
				{
					presentPositon = presentPositon->NextNode;
				}
			}
		}
	}
	//��ӡ����ṹ
	void PrintSkipList()
	{
		Node* presentH = guardFirst;
		Node* presentPosition;
		while (true)
		{
			presentPosition = presentH;
			while (presentPosition->NextNode->NextNode != NULL)
			{
				printf("%d", presentPosition->NextNode->Val);
				printf(" ");
				presentPosition = presentPosition->NextNode;
			}
			printf("\n");
			if (presentH->DownNode == NULL)
			{
				break;
			}
			else
			{
				presentH = presentH->DownNode;
			}
		}
		printf("-----------------\n");
	}
};


int main()
{
	SkipList* mySkipList = new SkipList();
	for (int i = 0; i < 10; i++)
	{
		//int a = RandomClass::GetRandInt() % 100;
		mySkipList->AddNode(i*2);
		mySkipList->PrintSkipList();
	}
	mySkipList->AddNode(15);
	mySkipList->PrintSkipList();
	mySkipList->Delete(15);
	mySkipList->PrintSkipList();
	return 0;
}