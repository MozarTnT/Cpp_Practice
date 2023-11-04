#pragma once

#include <assert.h>
// 클래스에 템플릿을 적용하는 방법은 2가지
// 멤버함수마다 따로 적용하거나 , 클래스 전체에 적용하거나.


template <typename T>

class CListNode
{
	// 생성자,소멸자를 private로 하면 외부에서 이 객체 생성,해제를 못함.
	// friend를 사용하면 외부에서는 사용이 안되지만 LinkedList에서만 접근이 가능하게 만듬.
	template <typename T> // 타입을 알려주고 friend 처리를 해줘야함.
	friend class CLinkedList_2;

private:
	CListNode()
	{
		m_pPrev = nullptr;
		m_pNext = nullptr;
	}
	~CListNode()
	{

	}

private:
	T	m_Data; // 데이터
	CListNode<T>* m_pPrev; // 이전 노드 주소
	CListNode<T>* m_pNext; // 다음 노드 주소
};


template <typename T>

class CLinkedList_2
{
public:

	CLinkedList_2()
	{
		m_pBegin = new NODE;
		m_pEnd = new NODE;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;
	}

	~CLinkedList_2()
	{
		PNODE pNode = m_pBegin;
		
		while (pNode != nullptr)
		{
			PNODE pNext = pNode->m_pNext;
			delete pNode;
			pNode = pNext;
		}
	}
private:
	typedef CListNode<T>  NODE;
	typedef CListNode<T>* PNODE;

private:
	PNODE m_pBegin;
	PNODE m_pEnd;
	int m_iSize;

public:
	void push_back(const T& data)
	{
		//데이터를 저장할 노드
		PNODE pNode = new NODE;

		pNode->m_Data = data;

		PNODE pPrev = m_pEnd->m_pPrev;

		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;

		pNode->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pNode;

		++m_iSize;
	}

	void push_front(const T& data)
	{

		PNODE pNode = new NODE;

		pNode->m_Data = data;

		PNODE pNext = m_pBegin->m_pNext;

		pNode->m_pNext = pNext;
		pNext->m_pPrev = pNode;

		pNode->m_pPrev = m_pBegin;
		m_pBegin->m_pNext = pNode;

		++m_iSize;
	}

	void pop_back()
	{
		if (empty())
			assert(false);

		PNODE pDeleteNode = m_pEnd->m_pPrev;
		
		PNODE pPrev = pDeleteNode->m_pPrev;
		pPrev->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pPrev;

		delete pDeleteNode;

		--m_iSize;

	}

	void pop_front()
	{
		if (empty())
			assert(false);

		PNODE pDeleteNode = m_pBegin->m_pNext;

		PNODE pNext = pDeleteNode->m_pNext;
		pNext->m_pPrev = m_pBegin;
		m_pBegin->m_pNext = pNext;

		delete pDeleteNode;

		--m_iSize;
	}

	T front() const
	{
		if (empty())
			assert(false);


		return m_pBegin->m_pNext->m_Data;
	}

	T back() const
	{
		if (empty())
			assert(false);


		return m_pEnd->m_pPrev->m_Data;
	}

	int size() const
	{
		return m_iSize;
	}

	bool empty() const
	{
		return m_iSize == 0;
	}

	
};

