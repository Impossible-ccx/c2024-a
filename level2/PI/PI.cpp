#include<bits/stdc++.h>
using namespace std;
//ʵ��һ������߾���С����ֻ��������
class Hy_FixedNum
{
protected:
	//������С�����֣�С����40000λ������Ӧ�ù�����
	unsigned int integer;
	unsigned char decimal[5000];
public:
	Hy_FixedNum* Add(Hy_FixedNum* target)
	{
		Hy_FixedNum* result = new Hy_FixedNum();
		result->integer = this->integer + target->integer;
		unsigned char carry = 0;
		unsigned char F1;
		unsigned char F2;
		for (int i = 4999; i >= 0; i--)
		{
			F1 = this->decimal[i];
			F2 = target->decimal[i];
			if (F1 == 0xffffffff && carry == 1)
			{
				carry = 1;
				F1 = 0;
				result->decimal[i] = F1 + F2;
			}
			else
			{
				F1 += carry;
				if (F1 & F2 & 0x80000000)
				{
					carry = 1;
					result->decimal[i] = F1 + F2;
				}
				else
				{
					carry = 0;
					result->decimal[i] = F1 + F2;
				}
			}
		}
		if (carry == 1)
		{
			result->integer += 1;
		}
		else
		{
			;
		}
		return result;
	}
	Hy_FixedNum* Multi(Hy_FixedNum* target);
	Hy_FixedNum* Div(Hy_FixedNum* target);
};
int main()
{
	return 0;
}