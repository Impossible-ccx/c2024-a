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

//已经建立的哨兵不会被删除
class SkipList
{
protected:
	//点定义
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
	//左上角哨兵
	Node* guardFirst = new Node(0x80000000);
	//右上角哨兵
	Node* guardLast = new Node(0x7fffffff);
	//以1/3概率返回true，用来决定是否进入更高一层
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
	//往一个点后添加新点
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
	//删除节点以及节点上方节点
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
	//添加元素
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
								//到达起点哨兵，创建新哨兵,链接新的末尾哨兵
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
	//删除第一个对应值元素，没有此元素返回false
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
	//查找大于等于此元素的第一个元素，没有则返回末尾哨兵
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
	//打印链表结构
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