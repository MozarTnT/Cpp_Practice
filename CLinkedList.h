#pragma once

#include <assert.h> // 예외처리 관련 에러사항 검출 코드


// 
// linked list란 ? 노드와 노드를 순서대로 나열하는 선형적 구조의 자료구조 
// 노드는 리스트의 원소 값(데이터)과 다음 원소를 가리키는 정보(포인터), 그리고 이전 노드의 메모리 주소를 저장하는 정보 (포인터)로 구성되어 있음.
// 여기서 배열과의 차이점은 
// 배열은 표현되는 순서가 물리적인 메모리 공간에서의 위치를 의미한다면 
// 리스트에서의 순서는 물리적인 메모리 저장 순서, 위치와 무관하게 원소간의 논리적인 순서만을 다룸.
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
		m_pNext = nullptr; // 포인터 변수는 nullptr로 초기화 하는것을 권장
		m_pPrev = nullptr;
	}
	~CListNode()
	{

	}

private:
	T			  m_Data;  // 실제 데이터를 저장할 변수
	CListNode<T>* m_pNext;  // 다음 노드의 주소를 저장할 변수
	CListNode<T>* m_pPrev;   // 이전 노드의 주소를 저장할 변수

};

template <typename T>
class CListIterator // iterator란 ? 반복자 
{
	template <typename T>
	friend class CLinkedList;

public: // iterator는 외부에서 사용이 가능하게 만들어야 함으로 public으로 작업.
	CListIterator()
	{
		m_pNode = nullptr; // 포인터임으로 nullptr로 초기화
	}

	~CListIterator()
	{

	}

private:
	typedef CListNode<T>* PNODE; 

private:
	PNODE m_pNode; // 현재 iterator가 노드를 하나 가지고있고 iterator를 이용하여 노드에서 필요한 정보를 뺴가는 역할.

public:

	bool operator == (const CListIterator <T>& iter) // 가지고 있는 노드의 메모리 주소가 같은 경우
	{
	return m_pNode == iter.m_pNode; 
	}
	bool operator != (const CListIterator <T>& iter) // 가지고 있는 노드의 주소가 다른 경우
	{
		return m_pNode != iter.m_pNode;
	}

	void operator ++ () // 다음 노드로 자동으로 이동
	{
		m_pNode = m_pNode->m_pNext;
	}
	void operator -- () // 이전 노드로 이동
	{
		m_pNode = m_pNode->m_pPrev;
	}
	T& operator * () // iterator를 역참조 할 경우 데이터를 얻어 사용할 수 있도록 데이터 값을 반환하도록 설정.
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

	void operator ++ () // 반대방향
	{
		m_pNode = m_pNode->m_pPrev;
	}
	void operator -- () // 반대방향
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
		m_pBegin = new NODE; //Begin과 End는 반드시 존재해야 하기에 생성자에서 동적 할당을 해줌.
		m_pEnd = new NODE;

		m_pBegin->m_pNext = m_pEnd; // 처음에 추가되는 노드가 없으므로 Begin의 다음 노드를 End로
		m_pEnd->m_pPrev = m_pBegin; // End의 이전 노드로 Begin을 지정.

		m_iSize = 0; // 변수 초기화
	}
	~CLinkedList()
	{
		clear();  // 리스트 클래스에서 메모리 누수 방지를 위해 소멸자에서 노드들을 삭제.
		delete m_pBegin; // 마지막으로 Begin과 End까지 삭제하면 동적 할당된 모든 메모리를 해제함.
		delete m_pEnd;
	}
private:
	typedef CListNode<T> NODE; // 리스트의 T타입과 노드의 T타입을 정확이 일치시키기 위해 typedef를 사용
	typedef CListNode<T> *PNODE; // 포인터 타입도 재정의

public:
	typedef CListIterator<T> iterator; // 외부에서 재정의된 타입에 접근 가능하도록 public으로 typedef 다시함
	typedef CListReverseIterator<T> reverse_iterator;


private:
	PNODE	 m_pBegin; // Begin 과 End 에 더미 노드를 생성. 리스트 안에 데이터를 넣은 상태에서 리스트 전체에 대한 반복처리를 해야 할 경우에 
	PNODE	 m_pEnd;   // 명시적으로 처음과 끝이 존재하기에 해당 작업이 수월해짐.
	int		 m_iSize; // 리스트에 추가된 크기, 실제 데이터를 가진 노드가 몇개인지 확인하는 변수 하나 생성.

public:
	// 가장 뒤에 데이터를 추가하는 push back 기능 , & 레퍼런스(참조)를 사용하는 이유는 일반 T 변수를 사용하면 객체를 복사하는 작업이 비효율적
	void push_back(const T& data) // 참조하는 대상의 data값 변경을 방지하기 위해 상수화(const)
	{
		PNODE   pNode = new NODE; // 노드를 새로 하나 생성
		pNode->m_Data = data; // 노드 데이터를 데이터 타입으로 지정

		PNODE pPrev = m_pEnd->m_pPrev; // 뒤에 추가를 해야하므로 End의 이전 노드를 얻어온다.

		pPrev->m_pNext = pNode; // 얻어온 이전 노드와 End 노드 사이에 새로 생성한 노드를 추가.
		pNode->m_pPrev = pPrev;

		pNode->m_pNext = m_pEnd; // End 노드와 새로 생성할 노드를 연결 (pNode의 다음을 End로)
		m_pEnd->m_pPrev = pNode; // (End의 이전을 새로 만든 노드로)

		++m_iSize; // 실제 노드가 하나 추가되었으므로 사이즈를 1 증가시켜줌
	}

	// 앞에 데이터를 추가하는 push front 기능  
	void push_front(const T& data)
	{
		PNODE pNode = new NODE; // 노드를 하나 새로 생성
		pNode->m_Data = data; // 노드 데이터를 데이터 타입으로 지정

		PNODE pNext = m_pBegin->m_pNext; // Begin과 Begin 다음 노드 사이에 새로 생성한 노드를 추가

		pNode->m_pNext = pNext; // 새로 생성한 노드의 다음노드로 Begin의 다음 노드를 지정.
		pNext->m_pPrev = pNode; // Begin 다음 노드의 이전 노드로 새로 생성한 노드를 줌.

		m_pBegin->m_pNext = pNode; // Begin 노드의 다음 노드로 새로 생성한 노드를 지정
		pNode->m_pPrev = m_pBegin; // 새로 생성한 노드의 이전 노드로 Begin을 지정

		++m_iSize; // 마찬가지로 노드가 추가됨으로 사이즈를 1 증가시켜줌
	}

	// 뒤의 노드를 하나 지워주는 기능 
	void pop_back() // 마지막 노드를 지워주는 역할이기에 별도의 인자를 받을 필요는 없음.
	{
		if (empty()) // 리스트가 만약 비어있다면 
			assert(false); //false를 넣어줄 경우 에러 메세지를 발생시켜줌.

		PNODE pDeleteNode = m_pEnd->m_pPrev; // 가장 마지막 노드를 지워야 하므로 End의 이전 노드를 먼저 받아온다.

		PNODE pPrev = pDeleteNode->m_pPrev;  // 지울 노드의 이전 노드도 얻어온다.

		pPrev->m_pNext = m_pEnd; // 이전 노드의 다음으로 End를 지정
		m_pEnd->m_pPrev = pPrev; // End의 이전으로 이전 노드를 준다.

		delete pDeleteNode; // 노드를 지워줌. 

		--m_iSize; // 노드가 하나 없어지므로 사이즈를 1 감소시킴
	}

	//앞의 노드를 하나 지워주는 기능
	void pop_front()
	{
		if (empty())
			assert(false);

		PNODE pDeleteNode = m_pBegin->m_pNext; // 지울 노드를 얻어옴. (현재 Begin의 다음노드)

		PNODE pNext = pDeleteNode->m_pNext; // 지울 노드의 다음 노드를 얻어오고 

		pNext->m_pPrev = m_pBegin; // 그 다음 노드의 이전 노드로 begin을 연결 (해당 노드와 begin을 연결)
		m_pBegin->m_pNext = pNext;

		delete pDeleteNode; // 노드를 지워줌.

		--m_iSize; // 사이즈를 1 감소
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

	// Begin과 End를 제외한 실제 추가한 노드의 삭제기능을 구현해보기.
	void clear()
	{
		PNODE pNode = m_pBegin->m_pNext; // Begin의 다음 노드로 pNode를 지정

		while (pNode != m_pEnd) // 새로 추가된 노드들의 Next(pNode)를 받아오다가 End를 만나면 반복을 종료하는 형태로 처리
		{
			PNODE pNext = pNode->m_pNext; // 동적할당한 노드들을 delete할 예정이기에 현재노드의 다음 노드를 미리 받아놓음. 지우기 전에 꼭 !

			delete pNode; // 현재 노드를 지워준다.

			pNode = pNext; // PNode의 다음 노드의 주소를 넣어준다.
		}

		m_iSize = 0; // 노드 사이즈 초기화

		m_pBegin->m_pNext = m_pEnd; // 다시 Begin과 End를 연결해줌. 
		m_pEnd->m_pPrev = m_pBegin;
	}

	int size() const // const가 붙어있으므로 멤버 함수 값의 변경 코드가 들어가면 안됨.
	{

		return m_iSize;
	}

	bool empty() const // 리스트가 비어있으면 true.아닐경우 false를 반환.
	{
		return m_iSize == 0;
	}

	public:
		iterator begin() const // begin()함수는 추가된 가장 첫번째 노드의 주소를 가지는 iterator를 반환
		{
			iterator iter; // 변수 하나 설정
			iter.m_pNode = m_pBegin->m_pNext; 
			return iter;
		}

		iterator end() const //end() 함수는 End 노드를 가지고 있는 iterator를 반환
		{
			iterator iter;
			iter.m_pNode = m_pEnd;
			return iter;
		}

		reverse_iterator rbegin() const //rbegin() 함수는 가장 마지막에 추가된 노드를 가진 reverse_iterator를 반환
		{
			reverse_iterator iter;
			iter.m_pNode = m_pEnd->m_pPrev;
			return iter;
		}
		
		reverse_iterator rend() const //rend()함수는 Begin 노드를 가진 reverse_iterator를 반환
		{
			reverse_iterator iter;
			iter.m_pNode = m_pBegin;
			return iter;
		}

		// 리스트를 정렬하는 기능
		
		void sort(bool (*pFunc)(const T&, const T&)) // 데어터 타입이 템플릿이다 보니 구조체나 클래스도 들어올 수 있음. 정렬하는 기준도 모호하기 때문에 반환값이 bool인 함수 포인터를 사용
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

