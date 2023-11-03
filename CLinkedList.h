#pragma once

#include <assert.h> // ����ó�� ���� �������� ���� �ڵ�


// 
// linked list�� ? ���� ��带 ������� �����ϴ� ������ ������ �ڷᱸ�� 
// ���� ����Ʈ�� ���� ��(������)�� ���� ���Ҹ� ����Ű�� ����(������), �׸��� ���� ����� �޸� �ּҸ� �����ϴ� ���� (������)�� �����Ǿ� ����.
// ���⼭ �迭���� �������� 
// �迭�� ǥ���Ǵ� ������ �������� �޸� ���������� ��ġ�� �ǹ��Ѵٸ� 
// ����Ʈ������ ������ �������� �޸� ���� ����, ��ġ�� �����ϰ� ���Ұ��� ������ �������� �ٷ�.
template <typename T>
class CListNode
{
	template <typename T>
	friend class CLinkedList;

	template <typename T>
	friend class CListIterator; 

	template <typename T>
	friend class CListReverseIterator;

private:
	CListNode()
	{
		m_pNext = nullptr; // ������ ������ nullptr�� �ʱ�ȭ �ϴ°��� ����
		m_pPrev = nullptr;
	}
	~CListNode()
	{

	}

private:
	T			  m_Data;  // ���� �����͸� ������ ����
	CListNode<T>* m_pNext;  // ���� ����� �ּҸ� ������ ����
	CListNode<T>* m_pPrev;   // ���� ����� �ּҸ� ������ ����

};

template <typename T>
class CListIterator // iterator�� ? �ݺ��� 
{
	template <typename T>
	friend class CLinkedList;

public: // iterator�� �ܺο��� ����� �����ϰ� ������ ������ public���� �۾�.
	CListIterator()
	{
		m_pNode = nullptr; // ������������ nullptr�� �ʱ�ȭ
	}

	~CListIterator()
	{

	}

private:
	typedef CListNode<T>* PNODE; 

private:
	PNODE m_pNode; // ���� iterator�� ��带 �ϳ� �������ְ� iterator�� �̿��Ͽ� ��忡�� �ʿ��� ������ ������ ����.

public:

	bool operator == (const CListIterator <T>& iter) // ������ �ִ� ����� �޸� �ּҰ� ���� ���
	{
	return m_pNode == iter.m_pNode; 
	}
	bool operator != (const CListIterator <T>& iter) // ������ �ִ� ����� �ּҰ� �ٸ� ���
	{
		return m_pNode != iter.m_pNode;
	}

	void operator ++ () // ���� ���� �ڵ����� �̵�
	{
		m_pNode = m_pNode->m_pNext;
	}
	void operator -- () // ���� ���� �̵�
	{
		m_pNode = m_pNode->m_pPrev;
	}
	T& operator * () // iterator�� ������ �� ��� �����͸� ��� ����� �� �ֵ��� ������ ���� ��ȯ�ϵ��� ����.
	{
		return m_pNode->m_Data;
	}
};

template <typename T>
class CListReverseIterator
{
	template <typename T>
	friend class CLinkedList;

public:
	CListReverseIterator()
	{
		m_pNode = nullptr;
	}

	~CListReverseIterator()
	{

	}

private:
	typedef CListNode<T>* PNODE;

private:
	PNODE m_pNode;

public:

	bool operator == (const CListReverseIterator <T>& iter)
	{
		return m_pNode == iter.m_pNode;
	}
	bool operator != (const CListReverseIterator <T>& iter)
	{
		return m_pNode != iter.m_pNode;
	}

	void operator ++ () // �ݴ����
	{
		m_pNode = m_pNode->m_pPrev;
	}
	void operator -- () // �ݴ����
	{
		m_pNode = m_pNode->m_pNext;
	}
	T& operator * ()
	{
		return m_pNode->m_Data;
	}
};

template <typename T>
class CLinkedList
{
public:
	CLinkedList()
	{
		m_pBegin = new NODE; //Begin�� End�� �ݵ�� �����ؾ� �ϱ⿡ �����ڿ��� ���� �Ҵ��� ����.
		m_pEnd = new NODE;

		m_pBegin->m_pNext = m_pEnd; // ó���� �߰��Ǵ� ��尡 �����Ƿ� Begin�� ���� ��带 End��
		m_pEnd->m_pPrev = m_pBegin; // End�� ���� ���� Begin�� ����.

		m_iSize = 0; // ���� �ʱ�ȭ
	}
	~CLinkedList()
	{
		clear();  // ����Ʈ Ŭ�������� �޸� ���� ������ ���� �Ҹ��ڿ��� ������ ����.
		delete m_pBegin; // ���������� Begin�� End���� �����ϸ� ���� �Ҵ�� ��� �޸𸮸� ������.
		delete m_pEnd;
	}
private:
	typedef CListNode<T> NODE; // ����Ʈ�� TŸ�԰� ����� TŸ���� ��Ȯ�� ��ġ��Ű�� ���� typedef�� ���
	typedef CListNode<T> *PNODE; // ������ Ÿ�Ե� ������

public:
	typedef CListIterator<T> iterator; // �ܺο��� �����ǵ� Ÿ�Կ� ���� �����ϵ��� public���� typedef �ٽ���
	typedef CListReverseIterator<T> reverse_iterator;


private:
	PNODE	 m_pBegin; // Begin �� End �� ���� ��带 ����. ����Ʈ �ȿ� �����͸� ���� ���¿��� ����Ʈ ��ü�� ���� �ݺ�ó���� �ؾ� �� ��쿡 
	PNODE	 m_pEnd;   // ��������� ó���� ���� �����ϱ⿡ �ش� �۾��� ��������.
	int		 m_iSize; // ����Ʈ�� �߰��� ũ��, ���� �����͸� ���� ��尡 ����� Ȯ���ϴ� ���� �ϳ� ����.

public:
	// ���� �ڿ� �����͸� �߰��ϴ� push back ��� , & ���۷���(����)�� ����ϴ� ������ �Ϲ� T ������ ����ϸ� ��ü�� �����ϴ� �۾��� ��ȿ����
	void push_back(const T& data) // �����ϴ� ����� data�� ������ �����ϱ� ���� ���ȭ(const)
	{
		PNODE   pNode = new NODE; // ��带 ���� �ϳ� ����
		pNode->m_Data = data; // ��� �����͸� ������ Ÿ������ ����

		PNODE pPrev = m_pEnd->m_pPrev; // �ڿ� �߰��� �ؾ��ϹǷ� End�� ���� ��带 ���´�.

		pPrev->m_pNext = pNode; // ���� ���� ���� End ��� ���̿� ���� ������ ��带 �߰�.
		pNode->m_pPrev = pPrev;

		pNode->m_pNext = m_pEnd; // End ���� ���� ������ ��带 ���� (pNode�� ������ End��)
		m_pEnd->m_pPrev = pNode; // (End�� ������ ���� ���� ����)

		++m_iSize; // ���� ��尡 �ϳ� �߰��Ǿ����Ƿ� ����� 1 ����������
	}

	// �տ� �����͸� �߰��ϴ� push front ���  
	void push_front(const T& data)
	{
		PNODE pNode = new NODE; // ��带 �ϳ� ���� ����
		pNode->m_Data = data; // ��� �����͸� ������ Ÿ������ ����

		PNODE pNext = m_pBegin->m_pNext; // Begin�� Begin ���� ��� ���̿� ���� ������ ��带 �߰�

		pNode->m_pNext = pNext; // ���� ������ ����� �������� Begin�� ���� ��带 ����.
		pNext->m_pPrev = pNode; // Begin ���� ����� ���� ���� ���� ������ ��带 ��.

		m_pBegin->m_pNext = pNode; // Begin ����� ���� ���� ���� ������ ��带 ����
		pNode->m_pPrev = m_pBegin; // ���� ������ ����� ���� ���� Begin�� ����

		++m_iSize; // ���������� ��尡 �߰������� ����� 1 ����������
	}

	// ���� ��带 �ϳ� �����ִ� ��� 
	void pop_back() // ������ ��带 �����ִ� �����̱⿡ ������ ���ڸ� ���� �ʿ�� ����.
	{
		if (empty()) // ����Ʈ�� ���� ����ִٸ� 
			assert(false); //false�� �־��� ��� ���� �޼����� �߻�������.

		PNODE pDeleteNode = m_pEnd->m_pPrev; // ���� ������ ��带 ������ �ϹǷ� End�� ���� ��带 ���� �޾ƿ´�.

		PNODE pPrev = pDeleteNode->m_pPrev;  // ���� ����� ���� ��嵵 ���´�.

		pPrev->m_pNext = m_pEnd; // ���� ����� �������� End�� ����
		m_pEnd->m_pPrev = pPrev; // End�� �������� ���� ��带 �ش�.

		delete pDeleteNode; // ��带 ������. 

		--m_iSize; // ��尡 �ϳ� �������Ƿ� ����� 1 ���ҽ�Ŵ
	}

	//���� ��带 �ϳ� �����ִ� ���
	void pop_front()
	{
		if (empty())
			assert(false);

		PNODE pDeleteNode = m_pBegin->m_pNext; // ���� ��带 ����. (���� Begin�� �������)

		PNODE pNext = pDeleteNode->m_pNext; // ���� ����� ���� ��带 ������ 

		pNext->m_pPrev = m_pBegin; // �� ���� ����� ���� ���� begin�� ���� (�ش� ���� begin�� ����)
		m_pBegin->m_pNext = pNext;

		delete pDeleteNode; // ��带 ������.

		--m_iSize; // ����� 1 ����
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

	// Begin�� End�� ������ ���� �߰��� ����� ��������� �����غ���.
	void clear()
	{
		PNODE pNode = m_pBegin->m_pNext; // Begin�� ���� ���� pNode�� ����

		while (pNode != m_pEnd) // ���� �߰��� ������ Next(pNode)�� �޾ƿ��ٰ� End�� ������ �ݺ��� �����ϴ� ���·� ó��
		{
			PNODE pNext = pNode->m_pNext; // �����Ҵ��� ������ delete�� �����̱⿡ �������� ���� ��带 �̸� �޾Ƴ���. ����� ���� �� !

			delete pNode; // ���� ��带 �����ش�.

			pNode = pNext; // PNode�� ���� ����� �ּҸ� �־��ش�.
		}

		m_iSize = 0; // ��� ������ �ʱ�ȭ

		m_pBegin->m_pNext = m_pEnd; // �ٽ� Begin�� End�� ��������. 
		m_pEnd->m_pPrev = m_pBegin;
	}

	int size() const // const�� �پ������Ƿ� ��� �Լ� ���� ���� �ڵ尡 ���� �ȵ�.
	{

		return m_iSize;
	}

	bool empty() const // ����Ʈ�� ��������� true.�ƴҰ�� false�� ��ȯ.
	{
		return m_iSize == 0;
	}

	public:
		iterator begin() const // begin()�Լ��� �߰��� ���� ù��° ����� �ּҸ� ������ iterator�� ��ȯ
		{
			iterator iter; // ���� �ϳ� ����
			iter.m_pNode = m_pBegin->m_pNext; 
			return iter;
		}

		iterator end() const //end() �Լ��� End ��带 ������ �ִ� iterator�� ��ȯ
		{
			iterator iter;
			iter.m_pNode = m_pEnd;
			return iter;
		}

		reverse_iterator rbegin() const //rbegin() �Լ��� ���� �������� �߰��� ��带 ���� reverse_iterator�� ��ȯ
		{
			reverse_iterator iter;
			iter.m_pNode = m_pEnd->m_pPrev;
			return iter;
		}
		
		reverse_iterator rend() const //rend()�Լ��� Begin ��带 ���� reverse_iterator�� ��ȯ
		{
			reverse_iterator iter;
			iter.m_pNode = m_pBegin;
			return iter;
		}

		// ����Ʈ�� �����ϴ� ���
		
		void sort(bool (*pFunc)(const T&, const T&)) // ������ Ÿ���� ���ø��̴� ���� ����ü�� Ŭ������ ���� �� ����. �����ϴ� ���ص� ��ȣ�ϱ� ������ ��ȯ���� bool�� �Լ� �����͸� ���
		{
			for (PNODE pFirst = m_pBegin->m_pNext; pFirst != m_pEnd->m_pPrev; pFirst = pFirst->m_pNext)
			{
				for (PNODE pSecond = pFirst->m_pNext; pSecond != m_pEnd; pSecond = pSecond->m_pNext)
				{
					if (pFunc(pFirst->m_Data, pSecond->m_Data))
					{
						T temp = pFirst->m_Data;
						pFirst->m_Data = pSecond->m_Data;
						pSecond->m_Data = temp;
					}
				}
			}

		}


};

