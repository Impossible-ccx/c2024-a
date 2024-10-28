#include<bits/stdc++.h>
using namespace std;
//实现一个定点高精度小数，只保存正数
class Hy_FixedNum
{
protected:
	//整数与小数部分，小数定40000位二进制应该够用了
	unsigned int integer;
	unsigned char decimal[5000];
	//万位专用
	static bool tMoveRight(unsigned char* target, int length)
	{
		bool result = false;
		target += length - 1;
		if (*target & 0x01)
		{
			result = true;
		}
		*target >>= 1;
		target--;
		for (int i = 1; i < length; i++)
		{
			if (*target & 0x01)
			{
				*(target + 1) |= 0x80;
			}
			*target = *target >>= 1;
			target--;
		}
		return result;
	}
	static bool tMoveLeft(unsigned char* target, int length)
	{
		bool result = false;
		if (*target & 0x80)
		{
			result = true;
		}
		*target <<= 1;
		target++;
		for (int i = 1; i < length; i++)
		{
			if (*target & 0x80)
			{
				*(target - 1) += 1;
			}
			*target = *target <<= 1;
			target++;
		}
		return true;
	}
	static void hMoveLeft(Hy_FixedNum* target)
	{
		target->integer <<= 1;
		if (tMoveLeft(target->decimal, 5000))
		{
			target->integer += 1;
		}
	}
	static void hMoveRight(Hy_FixedNum* target)
	{
		tMoveRight(target->decimal, 5000);
		if (target->integer & 0x00000001)
		{
			target->decimal[0] |= 0x80;
		}
		target->integer >>= 1;
	}
	static void tAddTo(unsigned char* Source, unsigned char* target, int length)
	{
		unsigned char carry = 0;
		unsigned char F1;
		unsigned char F2;
		//下面完成了加法
		for (int i = length - 1; i >= 0; i--)
		{
			F1 = Source[i];
			F2 = target[i];
			if (F1 == 0xffffffff && carry == 1)
			{
				carry = 1;
			}
			else
			{
				F1 += carry;
				if (F1 & F2 & 0xf0000000)
				{
					carry = 1;
					target[i] = F1 + F2;
				}
				else
				{
					carry = 0;
					target[i] = F1 + F2;
				}
			}
		}
	}
	//num1整数位乘以num2小数位
	static Hy_FixedNum* MultiIntDecimal(Hy_FixedNum* num1, Hy_FixedNum* num2)
	{
		int Intn = num1->integer;
		Hy_FixedNum* newNum2 = new Hy_FixedNum();
		Hy_FixedNum* result = new Hy_FixedNum();
		for (int i = 0; i < 5000; i++)
		{
			newNum2->decimal[i] = num2->decimal[i];
		}
		for (int i = 0; i < 5000; i++)
		{
			if (Intn & 0x00000001)
			{
				result = Add(result, newNum2);
			}
			Intn >>= 1;
			hMoveLeft(newNum2);
			if (Intn == 0)
			{
				delete(newNum2);
				return result;
			}
		}
	}
	static void Attach(int t, unsigned char* target)
	{
		switch (t)
		{
		case 1 :
			*target |= 0x80;
			break;
		case 2:
			*target |= 0x40;
			break;
		case 3:
			*target |= 0x20;
			break;
		case 4:
			*target |= 0x10;
			break;
		case 5:
			*target |= 0x08;
			break;
		case 6:
			*target |= 0x04;
			break;
		case 7:
			*target |= 0x02;
			break;
		case 8:
			*target |= 0x01;
			break;
		}
	}
	//
public:
	static Hy_FixedNum* Add(Hy_FixedNum* Num1, Hy_FixedNum* Num2)
	{
		Hy_FixedNum* result = new Hy_FixedNum();
		result->integer = Num1->integer + Num2->integer;
		unsigned char carry = 0;
		unsigned char F1;
		unsigned char F2;
		for (int i = 4999; i >= 0; i--)
		{
			F1 = Num1->decimal[i];
			F2 = Num2->decimal[i];
			if (F1 == 0xff && carry == 1)
			{
				carry = 1;
				result->decimal[i] = F2;
			}
			else
			{
				F1 += carry;
				if (F1 & F2 & 0x80)
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
	static Hy_FixedNum* Multi(Hy_FixedNum* Num1, Hy_FixedNum* Num2)
	{
		unsigned char* N1 = (unsigned char*)malloc(sizeof(unsigned char) * 10000);
		unsigned char* N2 = (unsigned char*)malloc(sizeof(unsigned char) * 10000);
		unsigned char result[10000];
		Hy_FixedNum* Result = new Hy_FixedNum();
		for (int i = 0; i < 5000; i++)
		{
			N1[i + 5000] = Num1->decimal[i];
			N2[i + 5000] = Num2->decimal[i];
		}
		for (int i = 0; i < 5000; i++)
		{
			if (tMoveRight(N2, 10000))
			{
				tAddTo(N1, result, 10000);
			}
			tMoveLeft(N1, 10000);
		}
		for (int i = 0; i < 5000; i++)
		{
			Result->decimal[i] = result[i];
		}
		Hy_FixedNum* ls = Result;
		Hy_FixedNum* lst = MultiIntDecimal(Num1, Num2);
		Result = Add(ls, lst);
		delete(lst);
		delete(ls);
		ls = Result;
		lst = MultiIntDecimal(Num2, Num1);
		Result = Add(ls, lst);
		delete(lst);
		delete(ls);
		Result->integer += Num1->integer * Num2->integer;
		free(N2);
		free(N1);
		return Result;
	}
	//前者是否大于后者
	static bool Gt(Hy_FixedNum* Num1, Hy_FixedNum* Num2)
	{
		if (Num1->integer > Num2->integer)
		{
			return true;
		}
		else if(Num1->integer < Num2->integer)
		{
			return false;
		}
		for (int i = 0; i < 5000; i++)
		{
			if (Num1->decimal[i] > Num2->decimal[i])
			{
				return true;
			}
			else if (Num1->decimal[i] < Num2->decimal[i])
			{
				return false;
			}
		}
		return false;
	}
	static bool Gt0(Hy_FixedNum* target)
	{
		if (target->integer > 0)
		{
			return true;
		}
		for (int i = 0; i < 5000; i++)
		{
			if (target->decimal[i] > 0)
			{
				return true;
			}
		}
		return false;
	}
	static Hy_FixedNum* Sub(Hy_FixedNum* Num1, Hy_FixedNum* Num2)
	{
		Hy_FixedNum* result = new Hy_FixedNum();
		for (int i = 0; i < 5000; i++)
		{
			result->decimal[i] = Num1->decimal[i];
		}
		result->integer = Num1->integer - Num2->integer;
		unsigned char* pRent;
		for (int i = 4999; i >= 0; i--)
		{
			if (result->decimal[i] >= Num2->decimal[i])
			{
				result->decimal[i] -= Num2->decimal[i];
			}
			else
			{
				if (i == 0)
				{
					result->integer -= 1;
					result->decimal[i] = 0xff - Num2->decimal[i] + result->decimal[i];
				}
				else
				{
					pRent = &result->decimal[i - 1];
					while (*pRent == 0)
					{
						pRent -= 1;
						if (pRent == result->decimal)
						{
							result->integer -= 1;
							break;
						}
						else
						{
							pRent--;
						}
					}
					*pRent -= 1;
					result->decimal[i] = 0xff - Num2->decimal[i] + result->decimal[i];
				}
			}
		}
		return result;
	}
	//左被除数，右除数
	static Hy_FixedNum* Div(Hy_FixedNum* Num1, Hy_FixedNum* Num2)
	{
		Hy_FixedNum* DivisionS = new Hy_FixedNum();
		Hy_FixedNum* Division = new Hy_FixedNum();
		Hy_FixedNum* ls = new Hy_FixedNum();
		Division->integer = Num2->integer;
		for (int i = 0; i < 5000; i++)
		{
			Division->decimal[i] = Num2->decimal[i];
		}
		DivisionS->integer = Num1->integer;
		for (int i = 0; i < 5000; i++)
		{
			DivisionS->decimal[i] = Num1->decimal[i];
		}
		Hy_FixedNum* result = new Hy_FixedNum();
		int multiple = 0;
		while (Gt(DivisionS, Division))
		{
			hMoveLeft(Division);
			multiple++;
		}
		int TT = 1;
		unsigned char* DivTar = result->decimal;
		while (Gt0(Division))
		{
			hMoveRight(Division);
			if (Gt(DivisionS, Division))
			{
				ls = DivisionS;
				DivisionS = Sub(ls, Division);
				delete(ls);
				Attach(TT, DivTar);
			}
			TT++;
			DivTar++;
			if (TT > 8)
			{
				TT = 1;
			}
			if (DivTar == result->decimal + 4999)
			{
				break;
			}
		}
		delete(Division);
		delete(DivisionS);
		for (int i = 0; i < multiple; i++)
		{
			hMoveLeft(result);
		}
		return result;
	}
	static int Mod(int mods, Hy_FixedNum* target);
	void Print()
	{
		Hy_FixedNum* ls = new Hy_FixedNum();
		Hy_FixedNum* lst = new Hy_FixedNum();
		lst->integer = 10;
		for (int i = 0; i < 5000; i++)
		{
			ls->decimal[i] = this->decimal[i];
		}
		printf("%d.", this->integer);
		for (int i = 0; i < 5000; i++)
		{
			printf("%d", Mod(10, ls));
			ls = Multi(lst, ls);
			ls->integer = 0;
		}
		delete(lst);
		delete(ls);
	}
};
int main()
{
	return 0;
}