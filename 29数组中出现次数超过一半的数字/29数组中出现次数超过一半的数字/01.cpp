#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <vector>
#define MAIN 1
using namespace std;

//基于Partition函数的O(n)的解法
int Partition(vector<int>& numbers,int start,int end)
{
	int pivot = numbers[start];
	while (start<end)
	{
		while (start<end&&numbers[end]>=pivot)
		{
			--end;
		}
		swap(numbers[start],numbers[end]);
		while(start<end&&numbers[start]<=pivot)
		{
			++start;
		}
		swap(numbers[start],numbers[end]);
	}
	return start;
}

void QuickSort(vector<int>& numbers,int start,int end)
{
	if (start<end)
	{
		int tmp = Partition(numbers, start, end);
		QuickSort(numbers, start, tmp - 1);
		QuickSort(numbers, tmp + 1, end);
	}
}
//利用partiton实现的快速排序 用到的是递归
void QSRT()
{
	int a[] = { 2, 4, 3, 8, 9, 6, 20, 7 };
	vector<int> num(a,a+sizeof(a)/sizeof(int));
	QuickSort(num, 0, num.size() - 1);
	for (auto it = num.begin(); it != num.end();it++)
	{
		cout << *it <<" ";
	}
	cout << endl;
}
bool CheckInvalidArray(vector<int>& numbers)
{
	bool flag_InputInvalid = false;
	if (numbers.size()<=0)
	{
		flag_InputInvalid = true;
	}
	return flag_InputInvalid;
}
bool CheckMoreThanHalf(vector<int>& numbers,int result)
{
	int num = count(numbers.begin(), numbers.end(), result);
	if (num>numbers.size()/2)
	{
		return true;
	}
	return false;
}
//第一中解法 利用partition函数特性和数组中位数为要找的结果 
int MoreThanHalfNum(vector<int>& numbers)
{
	if (CheckInvalidArray(numbers))
	{
		return 0;
	}

	int length = numbers.size();
	int middle = length >> 1;
	int start = 0;
	int end = length - 1;
	int index = Partition(numbers,start,end);
	while (index!=middle)
	{
		if (index>middle)
		{
			end = index - 1;
			index = Partition(numbers, start, end);
		}
		else
		{
			start = index + 1;
			index = Partition(numbers, start, end);
		}
	}
	int result = numbers[middle];
	if(!CheckMoreThanHalf(numbers,result))
		return 0;
	return result;
}
//第二种解法 剑指offer的第二种解法 利用数组特点 也是最简单的一种
int MoreThanHalfNum2(vector<int>& numbers)
{
	if (CheckInvalidArray(numbers))
	{
		return 0;
	}
	int result = numbers[0];
	int times = 1;
	for (int i = 0; i < numbers.size();i++)
	{
		if (times==0)
		{
			result = numbers[i];
			times = 1;
		}
		else if (numbers[i]==result)
		{
			times++;
		}
		else
		{
			times--;
		}
	}
	if (!CheckMoreThanHalf(numbers, result))
		return 0;
	return result;
}
//第三种解法 类似于第二种 来自牛客 每一轮消去两个不同的数，最后留下的就是我们要找的数
int MoreThanHalfNum3(vector<int>& numbers)
{
	vector<int> tmp(numbers);

	if (0==numbers.size())
	{
		return 0;
	}else if (1==numbers.size())
	{
		return numbers[0];
	}
	
	for (int i = 0; i < numbers.size();i++)
	{
		if (0==numbers[i])
		{
			continue;
		}
		for (int j = i + 1; j < numbers.size();j++)
		{
			if (numbers[i]!=numbers[j]&&numbers[j]!=0)
			{
				numbers[i] = 0;
				numbers[j] = 0;
				break;
			}
		}
	}
	int j = 0;
	for (int i = 0; i < numbers.size();i++)
	{
		if (numbers[i]!=0)
		{
			j = i;
		}
	}
	int num = count(tmp.begin(),tmp.end(),numbers[j]);
	if (num>numbers.size()/2)
	{
		return numbers[j];
	}
	else
	{
		return 0;
	}
}
void test01()
{
	int a[] = { 2, 4, 2, 2, 9, 20, 2, 2, 2 };
	vector<int> num(a, a + sizeof(a) / sizeof(int));
	//int tmp=MoreThanHalfNum(num);
	//int tmp=MoreThanHalfNum2(num);
	int tmp = MoreThanHalfNum3(num);
	cout << tmp << endl;
}

#if MAIN
int main(void)
{
	//QSRT();
	test01();
	return 0;
}
#endif