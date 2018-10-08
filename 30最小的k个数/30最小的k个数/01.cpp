#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <set>
#include <functional>
#include <vector>
#define MAIN 1

using namespace std;
//O(n)的算法，适合处理海量数据
//利用multiset的底层红黑树的特性
typedef multiset<int, greater<int>> intSet;
typedef multiset<int, greater<int>>::iterator setIterator;

const int COUNT=10000;
void GetLeastNumbers(const vector<int>& data,intSet& leastNumbers,int k)
{
	leastNumbers.clear();
	if (k<1||data.size()<k)
	{
		return;
	}
	vector<int>::const_iterator iter = data.begin();
	for (; iter != data.end();iter++)
	{
		if (leastNumbers.size()<k)
		{
			leastNumbers.insert(*iter);
		}
		else
		{
			setIterator iterGreatest = leastNumbers.begin();
			if ((*iter)<(*(leastNumbers.begin())))
			{
				leastNumbers.erase(iterGreatest);
				leastNumbers.insert(*iter);
			}
		}
	}
}



void test01()
{
	//void GetLeastNumbers(const vector<int>& data,intSet& leastNumbers,int k)
	
	vector<int> v;
	for (int i = 0; i < COUNT; i++)
	{
		v.push_back(rand()%10000);
	}
	intSet s;
	int k = 20;
	GetLeastNumbers(v,s,k);
	for (setIterator it = s.begin(); it != s.end();it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

#if MAIN
int main(void)
{
	test01();
	return 0;
}
#endif