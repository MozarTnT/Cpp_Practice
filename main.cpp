#include <iostream>
#include <time.h>
#include "CLinkedList.h"
using namespace std;

struct _tagData
{
	int iData;
	//char cName[20];
};
bool DataSort(const _tagData& tSrc, const _tagData& tDest)
{
	return tSrc.iData > tDest.iData; // 부호를 바꾸면 오름차순이 내림차순으로 변경
}

int main()
{
	CLinkedList<int> listInt;

	for (int i = 0; i < 10; ++i)
	{
		listInt.push_back(i);
	}

	cout << "Size = " << listInt.size() << endl;

	CLinkedList<int>::iterator iter;
	CLinkedList<int>::iterator iterEnd = listInt.end();

	for (iter = listInt.begin(); iter != iterEnd; ++iter) //end를 만날때까지 반복
	{
		cout << *iter << endl;
	}

	CLinkedList<int>::reverse_iterator riter; 
	CLinkedList<int>::reverse_iterator riterEnd = listInt.rend();

	for (riter = listInt.rbegin(); riter != riterEnd; ++riter)
	{
		cout << *riter << endl;
	}

	CLinkedList<_tagData> dataList;

	cout << "====================== data list ===================" << endl;
	srand((unsigned int)time(0));

	for (int i = 0; i < 10; ++i)
	{
		_tagData tData;

		tData.iData = rand() % 100;

		dataList.push_back(tData);

		cout << tData.iData << endl;
	}

	cout << "=================== sort ==================" << endl;
	dataList.sort(DataSort);

	CLinkedList<_tagData>::iterator iterD;
	CLinkedList<_tagData>::iterator iterDEnd = dataList.end();

	for (iterD = dataList.begin(); iterD != iterDEnd; ++iterD)
	{
		cout << (*iterD).iData << endl;
	}

	return 0;
}