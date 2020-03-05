#include "func.h"
#include <algorithm>
#include <cmath>
#include <Windows.h>
using namespace std;
//插入排序
void insertSort(vector<int>& ivec)
{
	int tmp;
	for (int i = 0; i != ivec.size(); ++i)
	{
		tmp = ivec[i];
		for (int j = i - 1; j >= -1; --j)
		{
			if (j != -1 && tmp < ivec[j])
			{
				ivec[j + 1] = ivec[j];
			}
			else
			{
				ivec[j + 1] = tmp;
				break;
			}
		}
	}
}
//希尔排序
void shellSort(vector<int>& ivec)
{
	for (int step = ivec.size() / 2; step > 0; step /= 2)
	{
		int tmp;
		for (int i = 0; i != ivec.size(); ++i)
		{
			tmp = ivec[i];
			for (int j = i - step; j >= i % step - step; j -= step)
			{
				if (j != i % step - step && tmp < ivec[j])
				{
					ivec[j + step] = ivec[j];
				}
				else
				{
					ivec[j + step] = tmp;
					break;
				}
			}
		}
	}
}
//冒泡排序
void bubbleSort(vector<int>& ivec)
{
	for (int i = ivec.size() - 1; i > 0; --i)
	{
		bool flag = true;
		for (int j = 1; j <= i; ++j)
		{
			if (ivec[j-1] > ivec[j])
			{
				swap(ivec[j - 1], ivec[j]);
				flag = false;
			}
		}
		if (flag)
		{
			break;
		}
	}
}
//快速排序
void quick(vector<int>& ivec, int beg, int end)
{
	if (end > beg)
	{
		int pivot = ivec[beg];
		int left = beg, right = end;
		while (right != left)
		{
			while (right != left && ivec[right] >= pivot)
			{
				--right;
			}
			swap(ivec[left], ivec[right]);
			while (right != left && ivec[left] <= pivot)
			{
				++left;
			}
			swap(ivec[left], ivec[right]);
		}
		quick(ivec, beg, left - 1);
		quick(ivec, right + 1, end);
	}
}
void quickSort(vector<int>& ivec)
{
	quick(ivec, 0, ivec.size() - 1);
}
//选择排序
void selectSort(vector<int>& ivec)
{
	for (int i = 0; i != ivec.size(); ++i)
	{
		int min = i;
		for (int j = i; j != ivec.size(); ++j)
		{
			if (ivec[j] < ivec[min])
			{
				min = j;
			}
		}
		swap(ivec[i], ivec[min]);
	}
}
//堆排序
void adjustHeap(vector<int>& ivec, int aim, int sz)	//自aim结点向下调整aim结点，使之成为大顶堆
{
	int n = ivec[aim];
	for (int max = (aim + 1) * 2 - 1; max < sz; max = (aim + 1) * 2 - 1)
	{
		if (max + 1 < sz && ivec[max + 1] > ivec[max])
		{
			++max;
		}
		if (ivec[max] > n)
		{
			ivec[aim] = ivec[max];
			aim = max;
		}
		else
		{
			break;
		}
	}
	ivec[aim] = n;
}
void heapSort(vector<int>& ivec)
{
	//构建
	for (int i = ivec.size() / 2 - 1; i >= 0; --i)
	{
		adjustHeap(ivec, i, ivec.size());
	}
	//sort
	for (int i = ivec.size() - 1; i > 0; --i)
	{
		swap(ivec[0], ivec[i]);
		adjustHeap(ivec, 0, i);
	}
}
//归并排序
void merge(vector<int>& ivec, int low, int mid, int high)
{
	if (low < mid && mid < high + 1)
	{
		vector<int> tmp;
		int i = low, j = mid;
		while (i != mid && j != high + 1)
		{
			if (ivec[i] <= ivec[j])
			{
				tmp.push_back(ivec[i]);
				++i;
			}
			else
			{
				tmp.push_back(ivec[j]);
				++j;
			}
		}
		while (i != mid)
		{
			tmp.push_back(ivec[i++]);
		}
		while (j != high + 1)
		{
			tmp.push_back(ivec[j++]);
		}
		for (int k = 0; k != tmp.size(); ++k)
		{
			ivec[k + low] = tmp[k];
		}
	}
}
void recursiveMerge(vector<int>& ivec, int low, int high)
{
	if (low < high)
	{
		recursiveMerge(ivec, low, (low + high) / 2);
		recursiveMerge(ivec, (low + high) / 2 + 1, high);
		merge(ivec, low, (low + high) / 2 + 1, high);
	}
}
void mergeSort(vector<int>& ivec)
{
	recursiveMerge(ivec, 0, ivec.size() - 1);
}
//基数排序
void radix(vector<vector<int>>& r1, vector<vector<int>>& r2, int d)
{
	if (d % 2)
	{
		for (int i = 0; i != 10; ++i)
		{
			for (const int& num : r1[i])
			{
				r2[num % static_cast<int>(pow(10, d)) / static_cast<int>(pow(10, d - 1))].push_back(num);
			}
			r1[i].clear();
		}
	}
	else
	{
		for (int i = 0; i != 10; ++i)
		{
			for (const int& num : r2[i])
			{
				r1[num % static_cast<int>(pow(10, d)) / static_cast<int>(pow(10, d - 1))].push_back(num);
			}
			r2[i].clear();
		}
	}
}
void radixSort(vector<int>& ivec)	//只能对非负数进行排序
{
	vector<vector<int>> r1(10, vector<int>());
	vector<vector<int>> r2(10, vector<int>());
	r1[0] = ivec;
	int d = 1;
	while (d != 11)
	{
		radix(r1, r2, d);
		++d;
	}
	ivec.clear();
	for (int i = 0; i != 3; ++i)
	{
		for (const int& num : r1[i])
		{
			ivec.push_back(num);
		}
	}
}
//分别用随机数列，有序数列，单个数，空数列测试上述排序结果是否正确
//其中随机数列，有序数列打印排序时长
void test(void(*p)(vector<int>&))
{
	//random
	vector<int> t1;
	for (int i = 0; i != 3000; ++i)
	{
		t1.push_back(rand() * 100);
	}
	//sorted
	vector<int> t2;
	for (int i = 0; i != 3000; ++i)	//有序数超过3900快排会栈溢出
	{
		t2.push_back(i);
	}
	//one element
	vector<int> t3{ INT_MAX };
	//empty
	vector<int> t4;
	vector<int> cmp1 = t1, cmp2 = t2, cmp3 = t3, cmp4 = t4;
	sort(t1.begin(), t1.end());
	sort(t2.begin(), t2.end());
	sort(t3.begin(), t3.end());
	sort(t4.begin(), t4.end());
	//
	long long time1 = GetTickCount64();
	p(cmp1);
	long long time2 = GetTickCount64();
	p(cmp2);
	long long time3 = GetTickCount64();
	p(cmp3);
	p(cmp4);
	//
	cout << "随机数：" << (time2 - time1) << "ms\t\t" << "有序数：" << (time3 - time2) << "ms\t\t";
	if (cmp1 == t1 && cmp2 == t2 && cmp3 == t3 && cmp4 == t4)
	{
		cout << "pass" << endl;
	}
	else
	{
		cout << "failure" << endl;
	}
}