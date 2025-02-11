#pragma once


//레드 블렉트리의 조건
//1. 모든 노드는 검은색 혹은 빨간색을 가지고 있다.
//2. 루트 노드는 검은색이고 잎노드도 검은색이다.
//3. 빨간노드의 자식은 모두 검은색이여야 하고, 검은색 노드의 자식의 색상은 상관없다.
//4. 루트노드에서 잎노느까지 가는 경로의 검은색 노드의 수는 모든경로에서 동일하다.

class cBinaryTree
{
private:
	//노드의 색상
	enum NODEColor{ RED, BLACK };

	typedef struct tagNODE{
		int data;
		tagNODE* pLeft;			//왼쪽 자식
		tagNODE* pRight;		//오른쪽 자식
		tagNODE* pParent;		//부모
		NODEColor color;		//노드의 색상
	}NODE, *LPNODE;

private:
	LPNODE			m_pRoot;	//루트 노드
	LPNODE			m_pNil;		//Nil 더미 노드

public:
	cBinaryTree(void);
	~cBinaryTree(void);

	//데이터 추가
	void Push_Data(int data);

	//전위 출력
	void PreOrderPrint();

	//중위 출력
	void InOrderPrint();

	//후위 출력
	void PostOrderPrint();

	//Tree 완전 제거
	void Clear();

	//해당 데이터 가 있는지 확인
	bool IsContain(int data);

	//(도전 과제) Data 가 들어 있는 노드를 삭제한다.
	void RemoveData(int data);

	//트리의 정보를 출려한다.
	void PrintTreeInfo();


	void Test_LeftRotate(){
		Rotate_Left(m_pRoot);
	}

	void Test_RightRotate(){
		Rotate_Right(m_pRoot);
	}

private:
	//노드 생성
	LPNODE CreateNode(int data);

	//노드 파괴
	void DestoryNode(LPNODE pNode);

	//노드 제거 ( 제거될때 뒤처리까지 깔금해주는 녀석 )
	void RemoveNode(LPNODE pNode);

	//재귀 클리어
	void Clear(LPNODE pNode);

	//전위 출력
	void PreOrderPrint(LPNODE pNode);

	//중위 출력
	void InOrderPrint(LPNODE pNode);

	//후위 출력
	void PostOrderPrint(LPNODE pNode);

	//해당 데이터의 노드를 찾는다.
	LPNODE FindNode(int data);

	//해당 노드의 가장 왼쪽 노드를 얻는다.
	LPNODE GetLeftNode(LPNODE pNode);

	//노드의 정보를 출려한다.
	void PrintNodeInfo(LPNODE pNode, int depth);

	//피봇노드 중심으로 왼쪽 회전 한다.
	void Rotate_Left(LPNODE pPivot);

	//피봇노드 중심으로 오른쪽 회전한다.
	void Rotate_Right(LPNODE pPivot);

	//새롭게 노드를 추가한후 뒤처리
	void Push_After(LPNODE pNewNode);

	//노드를 삭제한후 뒤처리	( 매개변수로 삭제하고 난후 삭제한 노드에 위치하게 되는 노드가 들어온다 )
	void Remove_After(LPNODE pNode);
};