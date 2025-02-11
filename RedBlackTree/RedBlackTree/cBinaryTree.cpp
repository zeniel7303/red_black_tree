#include "StdAfx.h"
#include "cBinaryTree.h"
#include <iostream>
using namespace std;


cBinaryTree::cBinaryTree(void)
: m_pRoot(NULL)
{
	//일단 Nil(텅 빈)Node를 생성
	m_pNil = new NODE;
	m_pNil->data = 0;
	m_pNil->pLeft = NULL;
	m_pNil->pRight = NULL;
	m_pNil->pParent = NULL;
	m_pNil->color = BLACK;		//Nil 노드를 무조건 검은색을 가진다.
}

cBinaryTree::~cBinaryTree(void)
{
	this->Clear();

	//닐더미도 날린다
	delete m_pNil;
	m_pNil = NULL;
}

//데이터 추가
void cBinaryTree::Push_Data(int data)
{
	//데이터에대한 노드를 만든다.
	LPNODE newNode = CreateNode(data);

	//추가되는 노드는 빨간색을 지니게 된다.
	newNode->color = RED;

	//루트노드가 없다면 비어있는 것이므로 
	//루크노드에 새로운 도드를 대입한다.
	if (m_pRoot == NULL){

		m_pRoot = newNode;
		//루트는 검은색이다.
		m_pRoot->color = BLACK;

		return;
	}


	//루트 노드 부터 자신이 위치해야할 노드위치를 찾아 들어간다.
	LPNODE pNode = m_pRoot;

	while (pNode != m_pNil){

		//현제 검색하는 노드의 값이 푸쉬 되는 값보다 크다면....
		if (pNode->data > data){

			//해당 노드의 왼쪽이 비었니?
			if (pNode->pLeft == m_pNil){
				pNode->pLeft = newNode;
				newNode->pParent = pNode;
				break;
			}

			//해당 노드가 이미 있니?
			else{
				//그러면 그왼쪽놈부터 다시 체크
				pNode = pNode->pLeft;
			}

		}

		//현제 검색노드의 값이 푸쉬 되는 값보다 작다면...
		else if (pNode->data < data){

			//해당 노드의 오른쪽이 비었니?
			if (pNode->pRight == m_pNil){
				pNode->pRight = newNode;
				newNode->pParent = pNode;
				break;
			}

			//해당 노드가 이미 있니?
			else{
				//그러면 그 오른쪽놈부터 다시 체크
				pNode = pNode->pRight;
			}
		}

		else
		{
			return;
		}
	}

	//후처리
	Push_After(newNode);
}

//전위 출력
void cBinaryTree::PreOrderPrint()
{
	cout << "Pre Order : ";

	//루트 부터 전위 출력
	this->PreOrderPrint(m_pRoot);

	cout << endl;
}

//중위 출력
void cBinaryTree::InOrderPrint()
{
	cout << "In Order : ";

	//루트 부터 중위 출력
	this->InOrderPrint(m_pRoot);

	cout << endl;
}

//후위 출력
void cBinaryTree::PostOrderPrint()
{
	cout << "Post Order : ";

	//루트 부터 후위 출력
	this->PostOrderPrint(m_pRoot);

	cout << endl;

}

//Tree 완전 제거
void cBinaryTree::Clear()
{
	this->Clear(m_pRoot);
}


//해당 데이터 가 있는지 확인
bool cBinaryTree::IsContain(int data)
{
	LPNODE pFind = FindNode(data);

	return (pFind != NULL);
}

//(도전 과제) Data 가 들어 있는 노드를 삭제한다.
void cBinaryTree::RemoveData(int data)
{
	//지울 노드를 찾는다.
	LPNODE pDel = FindNode(data);

	//지울 데이터를 못찾았다면 리턴
	if (pDel == NULL) return;

	RemoveNode(pDel);
}

//트리의 정보를 출력한다.
void cBinaryTree::PrintTreeInfo()
{
	PrintNodeInfo(m_pRoot, 0);
}


///////////////////////////////////////////////////////////////////////

//노드 생성
cBinaryTree::LPNODE cBinaryTree::CreateNode(int data)
{
	LPNODE newNODE = new NODE;
	newNODE->data = data;

	//만들어지는 노드는 일단 양쪽에 Nil 을 붙이고 시작
	newNODE->pLeft = m_pNil;
	newNODE->pRight = m_pNil;

	newNODE->pParent = NULL;

	return newNODE;
}

//노드 파괴
void cBinaryTree::DestoryNode(LPNODE pNode)
{
	//지워지는 노드가 루트라면
	if (pNode == m_pRoot){
		m_pRoot = NULL;
	}
	delete pNode;
}

//노드 제거 ( 제거될때 뒤처리까지 깔금해주는 녀석 )
void cBinaryTree::RemoveNode(LPNODE pNode)
{
	LPNODE pDelPosNewNode = NULL;		//지운노드에 새롭게 위치하게 되는 노드

	//지우려는 놈의 자식이 모두 Nil 이라면..
	if (pNode->pLeft == m_pNil &&
		pNode->pRight == m_pNil)
	{
		//부모한테 그대의 자식은 이세상사람이 아니라는 것을 알려야한다.
		//부모가 있다면....
		if (pNode->pParent)
		{
			//내가 부모의 왼쪽 자식이였니?
			if (pNode->pParent->pLeft == pNode){

				pNode->pParent->pLeft = m_pNil;

				//뒤처리를 위한 m_pNil 노드에 임시로 부모 넣어주자.
				m_pNil->pParent = pNode->pParent;

				//지워지는 노드에 새롭게 위치하게 되는 녀셕
				pDelPosNewNode = pNode->pParent->pLeft;
			}

			//내가 부모의 오른쪽 자식이였니?
			else{

				pNode->pParent->pRight = m_pNil;

				//뒤처리를 위한 m_pNil 노드에 임시로 부모 넣어주자.
				m_pNil->pParent = pNode->pParent;

				//지워지는 노드에 새롭게 위치하게 되는 녀셕
				pDelPosNewNode = pNode->pParent->pRight;

			}
		}


		//지워지는 노드가 검은색인 경우에만 지워지는 노드에 위치하게 되는 노드로 뒤처리를 하자
		//지워지는 노드에 위치하는 노드가 Nil 인경우에도 체크는 필요하다 
		//그래서 nilNode 에 임시로 부모를 대입한 것이다.
		if (pNode->color == BLACK)
			Remove_After(pDelPosNewNode);

		//메모리에서 날리자.
		DestoryNode(pNode);

	}//End if

	else
	{
		//삭제할 노드가 양쪽으로 자식이 있다면..
		if (pNode->pLeft != m_pNil &&
			pNode->pRight != m_pNil)
		{
			//삭제할 노드의 오른쪽 자식의 맨 왼쪽 노드를 얻는다.
			LPNODE pLeftMinNode = this->GetLeftNode(pNode->pRight);

			//데이터 바꿔치기
			pNode->data = pLeftMinNode->data;

			//맨왼쪽 놈이 죽는다. ( 재귀 )
			RemoveNode(pLeftMinNode);
		}


		//자식이 한쪽에만 있다면....
		else{

			//자식이 왼쪽에만 있다면...
			if (pNode->pLeft != m_pNil){

				//지워지는 노드에 새롭게 위치하게 되는 녀셕
				pDelPosNewNode = pNode->pLeft;

				//지우려는 놈이 Root 노드라면 이때는 100 퍼 왼쪽에 빨간자식하나만 있는 상태가 된다.
				if (pNode->pParent == NULL){

					//루트 노드가 바뀌는 경우에는 누트노드를 변경
					m_pRoot = pDelPosNewNode;
					m_pRoot->pParent = NULL;
					DestoryNode(pNode);
				}


				//부모가 있다면
				else{

					//지우려는 노드가 부모의 왼쪽 자식이였다면..
					if (pNode->pParent->pLeft == pNode){
						pNode->pParent->pLeft = pNode->pLeft;
					}

					//지우려는 노드의 부모의 오른쪽 자식이였다면...
					else {
						pNode->pParent->pRight = pNode->pLeft;
					}

					//지우려는 노드의 왼쪽자식의 부모을 현재 지우려는 노드의 부모로 교체
					pNode->pLeft->pParent = pNode->pParent;

					//지우려는 놈의 컬러가 Black 인 경우에만 뒤처리
					if (pNode->color == BLACK)
						Remove_After(pDelPosNewNode);

					DestoryNode(pNode);
				}
			}// End if( pNode->pLeft != NULL );


			//자식이 오른쪽에만 있다면...
			else{

				//지워지는 노드에 새롭게 위치하게 되는 녀셕
				pDelPosNewNode = pNode->pRight;

				//지우려는 놈이 Root 노드라면 이때는 100 퍼 오른쪽에 빨간자식하나만 있는 상태가 된다.
				if (pNode->pParent == NULL){

					//루트 노드가 바뀌는 경우에는 누트노드를 변경
					m_pRoot = pDelPosNewNode;
					m_pRoot->pParent = NULL;
					DestoryNode(pNode);
				}

				//부모가 있다면
				else{

					//지우려는 노드가 부모의 왼쪽 자식이였다면..
					if (pNode->pParent->pLeft == pNode){
						pNode->pParent->pLeft = pNode->pRight;
					}

					//지우려는 노드의 부모의 오른쪽 자식이였다면...
					else {
						pNode->pParent->pRight = pNode->pRight;
					}

					//지우려는 노드의 왼쪽자식의 부모을 현재 지우려는 노드의 부모로 교체
					pNode->pRight->pParent = pNode->pParent;

					//지우려는 놈의 컬러가 Black 인 경우에만 뒤처리
					if (pNode->color == BLACK)
						Remove_After(pDelPosNewNode);

					DestoryNode(pNode);
				}
			}
		}
	}//End else
}


//재귀 클리어
void cBinaryTree::Clear(LPNODE pNode)
{
	if (pNode == NULL || pNode == m_pNil) return;

	Clear(pNode->pLeft);
	Clear(pNode->pRight);

	DestoryNode(pNode);
}


//전위 출력
void cBinaryTree::PreOrderPrint(LPNODE pNode)
{
	if (pNode == NULL || pNode == m_pNil) return;

	cout << pNode->data << " ";

	PreOrderPrint(pNode->pLeft);
	PreOrderPrint(pNode->pRight);
}

//중위 출력
void cBinaryTree::InOrderPrint(LPNODE pNode)
{
	if (pNode == NULL || pNode == m_pNil) return;

	InOrderPrint(pNode->pLeft);

	cout << pNode->data << " ";

	InOrderPrint(pNode->pRight);
}

//후위 출력
void cBinaryTree::PostOrderPrint(LPNODE pNode)
{
	if (pNode == NULL || pNode == m_pNil) return;

	PostOrderPrint(pNode->pLeft);
	PostOrderPrint(pNode->pRight);

	cout << pNode->data << " ";
}


//해당 데이터의 노드를 찾는다.
cBinaryTree::LPNODE cBinaryTree::FindNode(int data)
{
	LPNODE pNode = m_pRoot;

	while (pNode != NULL && pNode != m_pNil)
	{
		//찾으려는 데이터가 현제 노드보다 크다면 우측 으로 타고 들어간다.
		if (pNode->data < data){
			pNode = pNode->pRight;
		}

		//찾으려는 데이터가 현제 노드보다 작다면 좌측 으로 타고 들어간다.
		else if (pNode->data > data){
			pNode = pNode->pLeft;
		}

		//Bingo
		else{
			return pNode;
		}
	}

	//여기까지 왔다면 못찾았음 
	return NULL;
}

//해당 노드의 가장 왼쪽 노드를 얻는다.
cBinaryTree::LPNODE cBinaryTree::GetLeftNode(LPNODE pNode)
{
	LPNODE pFind = pNode;

	while (pFind->pLeft != m_pNil)
		pFind = pFind->pLeft;

	return pFind;
}

//노드의 정보를 출력한다.
void cBinaryTree::PrintNodeInfo(LPNODE pNode, int depth)
{
	if (pNode == NULL || pNode == m_pNil) return;

	//[(Root) Data : 100, Parent    ] --- Leaf
	//		[(Left) Data : 100, Parent 30 ]

	//뎁스만큼 공백 추가
	for (int i = 0; i < depth; i++){
		cout << "  ";
	}

	//Nil 노드면 Nil 출력하고 종료
	if (pNode == m_pNil){
		cout << "[ Nil~~~~~~~~~~~~~] " << endl;
		return;
	}

	if (pNode == m_pRoot)
		cout << "[(Root)";

	else
	{
		if (pNode->pParent->pLeft == pNode)
			cout << "[(Left)";
		else
			cout << "[(Right)";
	}

	cout << "Data:" << pNode->data;

	cout << ", Parent:";
	if (pNode->pParent != NULL)
		cout << pNode->pParent->data;
	else
		cout << " ";


	cout << "(" << ((pNode->color == RED) ? "RED" : "BLACK") << ")]" << endl;

	PrintNodeInfo(pNode->pLeft, depth + 1);
	PrintNodeInfo(pNode->pRight, depth + 1);

}




//피봇노드 중심으로 왼쪽 회전 한다.
void cBinaryTree::Rotate_Left(LPNODE pPivot)
{
	//피봇의 오른쪽자식
	LPNODE pRightChild = pPivot->pRight;

	//피봇의 오른쪽노드의 왼쪽 자식
	LPNODE pRightChildLeft = pRightChild->pLeft;

	//피봇의 오른쪽 노드의 왼쪽 자식이 Nil 이 아니라면...
	if (pRightChildLeft != m_pNil)
		pRightChildLeft->pParent = pPivot;
	pPivot->pRight = pRightChildLeft;

	//피폿의 오른쪽 자식의 부모를 피봇의 부모로
	pRightChild->pParent = pPivot->pParent;

	//피봇이 루트 노드 였다면 
	if (pPivot->pParent == NULL)
		m_pRoot = pRightChild;

	else
	{
		//피봇이 부모의 왼쪽 자식이였다면...
		if (pPivot->pParent->pLeft == pPivot)
			pPivot->pParent->pLeft = pRightChild;

		//피봇이 부모의 오른쪽 자식이였다면..
		else
			pPivot->pParent->pRight = pRightChild;
	}

	//마무리
	pRightChild->pLeft = pPivot;
	pPivot->pParent = pRightChild;
}

//피봇노드 중심으로 오른쪽 회전한다.
void cBinaryTree::Rotate_Right(LPNODE pPivot)
{
	//피봇의 왼쪽자식
	LPNODE pLeftChild = pPivot->pLeft;

	//피폿의 왼쪽자식의 오른족 자식
	LPNODE pLeftChildRight = pLeftChild->pRight;

	//피봇의 왼쪽 노드의 오른쪽 자식이 Nil 이 아니라면...
	if (pLeftChildRight != m_pNil)
		pLeftChildRight->pParent = pPivot;
	pPivot->pLeft = pLeftChildRight;

	pLeftChild->pParent = pPivot->pParent;

	//루트 노드였다면...
	if (pPivot->pParent == NULL)
		m_pRoot = pLeftChild;

	else
	{
		if (pPivot->pParent->pLeft == pPivot)
			pPivot->pParent->pLeft = pLeftChild;
		else
			pPivot->pParent->pRight = pLeftChild;
	}

	//마무리
	pLeftChild->pRight = pPivot;
	pPivot->pParent = pLeftChild;
}


//새롭게 노드를 추가한후 뒤처리
void cBinaryTree::Push_After(LPNODE pNewNode)
{
	LPNODE pTarget = pNewNode;

	//일단 타겟이 루트가 아니고 타겟의 부모가 빨간색이면 
	//빨간노드의 자식은 모두 검은색이여야 한다는 조건이
	//작살나서 계속 맞춰 주며 돌아야한다.
	while (pTarget->pParent != NULL && pTarget->pParent->color == RED)
	{
		//타겟노드의 부모가 할아버지 오른쪽 자식이라면..
		if (pTarget->pParent == pTarget->pParent->pParent->pRight)
		{
			//삼촌노드
			LPNODE pUncle = pTarget->pParent->pParent->pLeft;

			//삼촌노드가 빨간색인경우
			if (pUncle->color == RED)
			{
				//부모와 삼촌을 검은색으로
				pTarget->pParent->color = BLACK;
				pUncle->color = BLACK;

				//할아버지를 빨간색으로
				pTarget->pParent->pParent->color = RED;

				//할아버지를 타겟으로 다시 체크
				pTarget = pTarget->pParent->pParent;

			}

			//삼촌노드가 검은색이라면..
			else
			{
				//타겟노드가 부모의 왼쪽 자식이라면....
				if (pTarget == pTarget->pParent->pLeft)
				{
					LPNODE pNewTarget = pTarget->pParent;

					//부모를 중심으로 오른쪽회전
					Rotate_Right(pTarget->pParent);

					//이전 부모였던 노드를 Target 으로 이어서
					pTarget = pNewTarget;
				}

				//여기서부터는 Target 노드는 부모의 오른쪽 자식이됨

				//부모노드를 검은 색으로
				pTarget->pParent->color = BLACK;

				//할아버지노드를 빨간색으로 
				pTarget->pParent->pParent->color = RED;

				//할아버지 기준으로 좌회전
				Rotate_Left(pTarget->pParent->pParent);

				//끗
				break;

			}

		}

		//타겟노드의 부모가 할아버지 왼쪽 자식이라면...
		else
		{
			//삼촌노드
			LPNODE pUncle = pTarget->pParent->pParent->pRight;

			//삼촌노드가 빨간색인경우
			if (pUncle->color == RED)
			{
				//부모와 삼촌을 검은색으로
				pTarget->pParent->color = BLACK;
				pUncle->color = BLACK;

				//할아버지를 빨간색으로
				pTarget->pParent->pParent->color = RED;

				//할아버지를 타겟으로 다시 체크
				pTarget = pTarget->pParent->pParent;
			}

			//삼촌노드가 검은색이라면..
			else
			{
				//타겟노드가 부모의 오른쪽 자식이라면....
				if (pTarget == pTarget->pParent->pRight)
				{
					LPNODE pNewTarget = pTarget->pParent;

					//부모를 중심으로 왼쪽회전
					Rotate_Left(pTarget->pParent);

					//이전 부모였던 노드를 Target 으로 이어서
					pTarget = pNewTarget;
				}

				//여기서부터는 Target 노드는 부모의 왼쪽 자식이됨

				//부모노드를 검은 색으로
				pTarget->pParent->color = BLACK;

				//할아버지노드를 빨간색으로 
				pTarget->pParent->pParent->color = RED;

				//할아버지 기준으로 우회전
				Rotate_Right(pTarget->pParent->pParent);

				//끗
				break;
			}
		}
	}

	//그냥강제로 Root 는 블렉 
	m_pRoot->color = BLACK;
}

//노드를 삭제한후 뒤처리	( 매개변수로 삭제하고 난후 삭제한 노드에 위치하게 되는 노드가 들어온다 )
void cBinaryTree::Remove_After(LPNODE pNode)
{
	LPNODE pTarget = pNode;
	LPNODE pSibling = NULL;		//pTarget 노드의 이웃노드

	//루트노드가 이니고 검은색노드 일때 만....
	while (pTarget->pParent != NULL && pTarget->color == BLACK)
	{
		//현제 체크중인 타겟 노드가 부모의 왼쪽자식이라면...
		if (pTarget == pTarget->pParent->pLeft)
		{
			//형제노드는 부모의 오른쪽 자식
			pSibling = pTarget->pParent->pRight;

			//형제노드가 빨간색이라면...
			if (pSibling->color == RED)
			{
				//형제의 컬러를 검은색으로 바꾸고
				pSibling->color = BLACK;

				//부모의 색을 빨간색으로 바꾼 후
				pTarget->pParent->color = RED;

				//부모를 중심으로 왼쪽 회전
				Rotate_Left(pTarget->pParent);

				//이 다음 반복문부터는 형제노드는 검은색이 되어있을 것이다.
				//( 빨간색 노드의 자식은 모두 검은색이기 때문이다 )
			}

			//형제 노드가 검은색이라면...
			else
			{
				//형제의 자식도 모두 검은색이라면...
				if (pSibling->pLeft->color == BLACK &&
					pSibling->pRight->color == BLACK)
				{
					//형제의 색을 빨간색으로 바꾸고
					pSibling->color = RED;

					//부모를기준으로 다시 체크
					pTarget = pTarget->pParent;
				}


				//형제의 자식이 모두 검은색이 아니라면...
				else
				{

					//형제의 왼쪽자식만 빨간색 이라면...
					if (pSibling->pLeft->color == RED)
					{
						//형제의 왼쪽자식의 색을 검은색으로..
						pSibling->pLeft->color = BLACK;

						//형제의 색을 빨간색으로...
						pSibling->color = RED;

						//형제 노드를 중심으로 오른쪽 회전
						Rotate_Right(pSibling);

						//위에서 회전을 했으니...
						//형제노드를 부모의 오른쪽으로 다시 갱신
						pSibling = pTarget->pParent->pRight;

						//이로인하여 형제의 오른쪽자식이 빨간색이라는 문제로 회피함
					}


					//여기까지 온다면 형제의 오른쪽자식능 빨간색노드가 된다.

					//형제의 컬러는 현제 부모의 컬러로...
					pSibling->color = pTarget->pParent->color;

					//부모의 컬러는  컬러로 검은색으로...
					pTarget->pParent->color = BLACK;

					//형제의 오른쪽자식 컬러로 검은색으로...
					pSibling->pRight->color = BLACK;

					//부모기준으로 왼쪽 회전
					Rotate_Left(pTarget->pParent);

					//체크되는 타겟 노드를 루트노드로 ( 참고로 이구문으로 while 문을 빠져나가게 되고 함수 종료직전 Root 노드는 검은색이 된다. )
					pTarget = m_pRoot;
				}
			}

		}//현제 체크중인 타겟 노드가 부모의 왼쪽자식이라면( END )


		//현제 체크중인 타겟 노드가 부모의 오른쪽 자식이라면...
		else
		{
			//형제노드는 부모의 왼쪽 자식
			pSibling = pTarget->pParent->pLeft;

			//형제노드가 빨간색이라면...
			if (pSibling->color == RED)
			{
				//형제의 컬러를 검은색으로 바꾸고
				pSibling->color = BLACK;

				//부모의 색을 빨간색으로 바꾼 후
				pTarget->pParent->color = RED;

				//부모를 중심으로 오른쪽 회전
				Rotate_Right(pTarget->pParent);

				//이 다음 반복문부터는 형제노드는 검은색이 되어있을 것이다.
				//( 빨간색 노드의 자식은 모두 검은색이기 때문이다 )
			}

			//형제 노드가 검은색이라면...
			else
			{
				//형제의 자식도 모두 검은색이라면...
				if (pSibling->pLeft->color == BLACK &&
					pSibling->pRight->color == BLACK)
				{
					//형제의 색을 빨간색으로 바꾸고
					pSibling->color = RED;

					//부모를기준으로 다시 체크
					pTarget = pTarget->pParent;
				}


				//형제의 자식이 모두 검은색이 아니라면...
				else
				{

					//형제의 오른쪽자식만 빨간색 이라면...
					if (pSibling->pRight->color == RED)
					{
						//형제의 오른쪽자식의 색을 검은색으로..
						pSibling->pRight->color = BLACK;

						//형제의 색을 빨간색으로...
						pSibling->color = RED;

						//형제 노드를 중심으로 왼쪽 회전
						Rotate_Left(pSibling);

						//위에서 회전을 했으니...
						//형제노드를 부모의 왼쪽으로 다시 갱신
						pSibling = pTarget->pParent->pLeft;

						//이로인하여 형제의 왼쪽자식이 빨간색이라는 문제로 회피함
					}


					//여기까지 온다면 형제의 오른쪽자식능 빨간색노드가 된다.

					//형제의 컬러는 현제 부모의 컬러로...
					pSibling->color = pTarget->pParent->color;

					//부모의 컬러는  컬러로 검은색으로...
					pTarget->pParent->color = BLACK;

					//형제의 오른쪽자식 컬러로 검은색으로...
					pSibling->pRight->color = BLACK;

					//부모기준으로 오른쪽 회전
					Rotate_Right(pTarget->pParent);

					//체크되는 타겟 노드를 루트노드로 ( 참고로 이구문으로 while 문을 빠져나가게 되고 함수 종료직전 Root 노드는 검은색이 된다. )
					pTarget = m_pRoot;
				}
			}

		}//현제 체크중인 타겟 노드가 부모의 오른쪽자식이라면( END )
	}

	//종료되기직전 타겟노드를 검은색으로..
	pTarget->color = BLACK;

}