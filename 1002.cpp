#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#define NUM_POLY 2

using namespace std;

class Item
{
public:
	int degree;
	double param;
	bool ismerged = false;
	bool operator < (const Item &item) const
	{
		return degree > item.degree;
	}
};

typedef struct poly
{
	int ItemNum = 0;
	vector<Item> polynomial;
}Poly;

int main(void)
{
	Poly result;
	result.polynomial.clear();
	for (int i = 0; i < NUM_POLY; i++)
	{
		Poly temp;
		cin >> temp.ItemNum;
		for (int j = 0; j < temp.ItemNum; j++)
		{
			Item TempItem;
			cin >> TempItem.degree >> TempItem.param;
			vector<Item>::iterator it;
			for (it = result.polynomial.begin(); it < result.polynomial.end(); it++)
			{
				if (it->degree == TempItem.degree)
				{
					it->param += TempItem.param;
					if (it->param == 0)
						result.ItemNum--;
					TempItem.ismerged = true;
					break;
				}
			}
			if (TempItem.ismerged == false)
			{
				result.polynomial.push_back(TempItem);
				result.ItemNum++;
			}
		}
	}
	cout << result.ItemNum;
	sort(result.polynomial.begin(), result.polynomial.end());
	for (int i = 0; i < result.ItemNum; i++)
	{
		//result.polynomial[i].param = (int)(result.polynomial[i].param * 10) * 1.0 / 10;
		if (result.polynomial[i].param == 0)
			continue;
		else
			cout << ' ' << result.polynomial[i].degree << ' ' << fixed << setprecision(1) << result.polynomial[i].param << endl;
	}
	//system("pause");
	return 0;
}