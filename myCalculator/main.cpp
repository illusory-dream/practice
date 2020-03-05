#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include <functional>
#include <cmath>
#include <iomanip>
using namespace std;
#define MIN_DOUBLE 1e-15
//char to operator
unordered_map<char, function<double(double, double)>> charToOper{
	{'+',std::plus<double>()},
	{'-',std::minus<double>()},
	{'*',std::multiplies<double>()},
	{'/',std::divides<double>()},
	{'%',[](double a,double b) {return static_cast<int>(a) % static_cast<int>(b); }}
};
//The Elem is a number or a operator
class Elem {
public:
	Elem(int i) :n(i), c('\0'), mark('n') {}
	Elem(char ch) :n(0), c(ch), mark('c') {}
	operator int() const
	{
		if ('n' == mark)
		{
			return n;
		}
		else
		{
			return c;
		}
	}
	char showType() const { return mark; }
private:
	char c;
	int n;
	char mark;
};
//中缀表达式->后缀表达式
vector<Elem> exprChange(const string& str)
{
	stack<char> stk;
	vector<Elem> ret;
	string num;
	for (char c : str)
	{
		if (c >= '0' && c <= '9')
		{
			num.push_back(c);
		}
		else
		{
			if (!num.empty())
			{
				Elem tmp(atoi(num.c_str()));
				ret.push_back(tmp);
				num = "";
			}
			if ('(' == c)
			{
				stk.push(c);
			}
			else if (')' == c)
			{
				while (stk.top() != '(')
				{
					Elem tmp(stk.top());
					ret.push_back(tmp);
					stk.pop();
				}
				stk.pop();
			}
			else
			{
				if ('+' == c || '-' == c)
				{
					while (!(stk.empty() || '(' == stk.top()))
					{
						Elem tmp(stk.top());
						ret.push_back(tmp);
						stk.pop();
					}
				}
				else
				{
					while (!(stk.empty() || '(' == stk.top() || '+' == stk.top() || '-' == stk.top()))
					{
						Elem tmp(stk.top());
						ret.push_back(tmp);
						stk.pop();
					}
				}
				stk.push(c);
			}
		}
	}
	if (!num.empty())
	{
		Elem tmp(atoi(num.c_str()));
		ret.push_back(tmp);
	}
	while (!stk.empty())
	{
		Elem tmp(stk.top());
		ret.push_back(tmp);
		stk.pop();
	}
	return ret;
}
bool doubleToInt(double d, int& ret)
{
	int i = static_cast<int>(d);
	if (abs(d - i) <= MIN_DOUBLE)
	{
		ret = i;
		return true;
	}
	++i;
	if (abs(d - i) <= MIN_DOUBLE)
	{
		ret = i;
		return true;
	}
	return false;
}
//expr为后缀表达式，ret通过引用返回运算结果
bool calc(const vector<Elem>& expr, double& ret)
{
	stack<double> nums;
	for (const auto &elem : expr)
	{
		if ('n' == elem.showType())
		{
			nums.push(elem);
		}
		else
		{
			if (nums.size() < 2)
			{
				return false;
			}
			double n2 = nums.top();
			nums.pop();
			double n1 = nums.top();
			nums.pop();
			//if double % double,return
			if ('%' == elem)
			{
				int in2, in1;
				if (!(doubleToInt(n2, in2) && doubleToInt(n1, in1)))
				{
					return false;
				}
				n2 = in2 + 0.5;
				n1 = in1 + 0.5;
			}
			nums.push(charToOper[static_cast<char>(elem)](n1, n2));
		}
	}
	if (nums.size() != 1)
	{
		return false;
	}
	if (!_finite(nums.top()))
	{
		return false;
	}
	ret = nums.top();
	return true;
}
int main()
{
	string input;
	cout << "请输入一行只包含 + - * / % 和小括号以及正整数的算式，其中不要出现空格。" << endl;
	while (cin >> input)
	{
		double result;
		if (calc(exprChange(input), result))
		{
			cout << fixed << setprecision(2) << result << endl;
		}
		else
		{
			cout << "算式可能不符合规范！" << endl;
			cout << "注：0不能做除数，小数之间不能取余。" << endl;
		}
		cout << "\n-------------------------------------" << endl;
		cout << "请输入一行只包含 + - * / % 和小括号以及正整数的算式，其中不要出现空格。" << endl;
	}
	return 0;
}
