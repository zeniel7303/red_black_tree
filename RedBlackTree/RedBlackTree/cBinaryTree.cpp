#include "StdAfx.h"
#include "cBinaryTree.h"
#include <iostream>
using namespace std;


cBinaryTree::cBinaryTree(void)
: m_pRoot(NULL)
{
	//�ϴ� Nil(�� ��)Node�� ����
	m_pNil = new NODE;
	m_pNil->data = 0;
	m_pNil->pLeft = NULL;
	m_pNil->pRight = NULL;
	m_pNil->pParent = NULL;
	m_pNil->color = BLACK;		//Nil ��带 ������ �������� ������.
}

cBinaryTree::~cBinaryTree(void)
{
	this->Clear();

	//�Ҵ��̵� ������
	delete m_pNil;
	m_pNil = NULL;
}

//������ �߰�
void cBinaryTree::Push_Data(int data)
{
	//�����Ϳ����� ��带 �����.
	LPNODE newNode = CreateNode(data);

	//�߰��Ǵ� ���� �������� ���ϰ� �ȴ�.
	newNode->color = RED;

	//��Ʈ��尡 ���ٸ� ����ִ� ���̹Ƿ� 
	//��ũ��忡 ���ο� ���带 �����Ѵ�.
	if (m_pRoot == NULL){

		m_pRoot = newNode;
		//��Ʈ�� �������̴�.
		m_pRoot->color = BLACK;

		return;
	}


	//��Ʈ ��� ���� �ڽ��� ��ġ�ؾ��� �����ġ�� ã�� ����.
	LPNODE pNode = m_pRoot;

	while (pNode != m_pNil){

		//���� �˻��ϴ� ����� ���� Ǫ�� �Ǵ� ������ ũ�ٸ�....
		if (pNode->data > data){

			//�ش� ����� ������ �����?
			if (pNode->pLeft == m_pNil){
				pNode->pLeft = newNode;
				newNode->pParent = pNode;
				break;
			}

			//�ش� ��尡 �̹� �ִ�?
			else{
				//�׷��� �׿��ʳ���� �ٽ� üũ
				pNode = pNode->pLeft;
			}

		}

		//���� �˻������ ���� Ǫ�� �Ǵ� ������ �۴ٸ�...
		else if (pNode->data < data){

			//�ش� ����� �������� �����?
			if (pNode->pRight == m_pNil){
				pNode->pRight = newNode;
				newNode->pParent = pNode;
				break;
			}

			//�ش� ��尡 �̹� �ִ�?
			else{
				//�׷��� �� �����ʳ���� �ٽ� üũ
				pNode = pNode->pRight;
			}
		}

		else
		{
			return;
		}
	}

	//��ó��
	Push_After(newNode);
}

//���� ���
void cBinaryTree::PreOrderPrint()
{
	cout << "Pre Order : ";

	//��Ʈ ���� ���� ���
	this->PreOrderPrint(m_pRoot);

	cout << endl;
}

//���� ���
void cBinaryTree::InOrderPrint()
{
	cout << "In Order : ";

	//��Ʈ ���� ���� ���
	this->InOrderPrint(m_pRoot);

	cout << endl;
}

//���� ���
void cBinaryTree::PostOrderPrint()
{
	cout << "Post Order : ";

	//��Ʈ ���� ���� ���
	this->PostOrderPrint(m_pRoot);

	cout << endl;

}

//Tree ���� ����
void cBinaryTree::Clear()
{
	this->Clear(m_pRoot);
}


//�ش� ������ �� �ִ��� Ȯ��
bool cBinaryTree::IsContain(int data)
{
	LPNODE pFind = FindNode(data);

	return (pFind != NULL);
}

//(���� ����) Data �� ��� �ִ� ��带 �����Ѵ�.
void cBinaryTree::RemoveData(int data)
{
	//���� ��带 ã�´�.
	LPNODE pDel = FindNode(data);

	//���� �����͸� ��ã�Ҵٸ� ����
	if (pDel == NULL) return;

	RemoveNode(pDel);
}

//Ʈ���� ������ ����Ѵ�.
void cBinaryTree::PrintTreeInfo()
{
	PrintNodeInfo(m_pRoot, 0);
}


///////////////////////////////////////////////////////////////////////

//��� ����
cBinaryTree::LPNODE cBinaryTree::CreateNode(int data)
{
	LPNODE newNODE = new NODE;
	newNODE->data = data;

	//��������� ���� �ϴ� ���ʿ� Nil �� ���̰� ����
	newNODE->pLeft = m_pNil;
	newNODE->pRight = m_pNil;

	newNODE->pParent = NULL;

	return newNODE;
}

//��� �ı�
void cBinaryTree::DestoryNode(LPNODE pNode)
{
	//�������� ��尡 ��Ʈ���
	if (pNode == m_pRoot){
		m_pRoot = NULL;
	}
	delete pNode;
}

//��� ���� ( ���ŵɶ� ��ó������ ������ִ� �༮ )
void cBinaryTree::RemoveNode(LPNODE pNode)
{
	LPNODE pDelPosNewNode = NULL;		//�����忡 ���Ӱ� ��ġ�ϰ� �Ǵ� ���

	//������� ���� �ڽ��� ��� Nil �̶��..
	if (pNode->pLeft == m_pNil &&
		pNode->pRight == m_pNil)
	{
		//�θ����� �״��� �ڽ��� �̼������� �ƴ϶�� ���� �˷����Ѵ�.
		//�θ� �ִٸ�....
		if (pNode->pParent)
		{
			//���� �θ��� ���� �ڽ��̿���?
			if (pNode->pParent->pLeft == pNode){

				pNode->pParent->pLeft = m_pNil;

				//��ó���� ���� m_pNil ��忡 �ӽ÷� �θ� �־�����.
				m_pNil->pParent = pNode->pParent;

				//�������� ��忡 ���Ӱ� ��ġ�ϰ� �Ǵ� ���
				pDelPosNewNode = pNode->pParent->pLeft;
			}

			//���� �θ��� ������ �ڽ��̿���?
			else{

				pNode->pParent->pRight = m_pNil;

				//��ó���� ���� m_pNil ��忡 �ӽ÷� �θ� �־�����.
				m_pNil->pParent = pNode->pParent;

				//�������� ��忡 ���Ӱ� ��ġ�ϰ� �Ǵ� ���
				pDelPosNewNode = pNode->pParent->pRight;

			}
		}


		//�������� ��尡 �������� ��쿡�� �������� ��忡 ��ġ�ϰ� �Ǵ� ���� ��ó���� ����
		//�������� ��忡 ��ġ�ϴ� ��尡 Nil �ΰ�쿡�� üũ�� �ʿ��ϴ� 
		//�׷��� nilNode �� �ӽ÷� �θ� ������ ���̴�.
		if (pNode->color == BLACK)
			Remove_After(pDelPosNewNode);

		//�޸𸮿��� ������.
		DestoryNode(pNode);

	}//End if

	else
	{
		//������ ��尡 �������� �ڽ��� �ִٸ�..
		if (pNode->pLeft != m_pNil &&
			pNode->pRight != m_pNil)
		{
			//������ ����� ������ �ڽ��� �� ���� ��带 ��´�.
			LPNODE pLeftMinNode = this->GetLeftNode(pNode->pRight);

			//������ �ٲ�ġ��
			pNode->data = pLeftMinNode->data;

			//�ǿ��� ���� �״´�. ( ��� )
			RemoveNode(pLeftMinNode);
		}


		//�ڽ��� ���ʿ��� �ִٸ�....
		else{

			//�ڽ��� ���ʿ��� �ִٸ�...
			if (pNode->pLeft != m_pNil){

				//�������� ��忡 ���Ӱ� ��ġ�ϰ� �Ǵ� ���
				pDelPosNewNode = pNode->pLeft;

				//������� ���� Root ����� �̶��� 100 �� ���ʿ� �����ڽ��ϳ��� �ִ� ���°� �ȴ�.
				if (pNode->pParent == NULL){

					//��Ʈ ��尡 �ٲ�� ��쿡�� ��Ʈ��带 ����
					m_pRoot = pDelPosNewNode;
					m_pRoot->pParent = NULL;
					DestoryNode(pNode);
				}


				//�θ� �ִٸ�
				else{

					//������� ��尡 �θ��� ���� �ڽ��̿��ٸ�..
					if (pNode->pParent->pLeft == pNode){
						pNode->pParent->pLeft = pNode->pLeft;
					}

					//������� ����� �θ��� ������ �ڽ��̿��ٸ�...
					else {
						pNode->pParent->pRight = pNode->pLeft;
					}

					//������� ����� �����ڽ��� �θ��� ���� ������� ����� �θ�� ��ü
					pNode->pLeft->pParent = pNode->pParent;

					//������� ���� �÷��� Black �� ��쿡�� ��ó��
					if (pNode->color == BLACK)
						Remove_After(pDelPosNewNode);

					DestoryNode(pNode);
				}
			}// End if( pNode->pLeft != NULL );


			//�ڽ��� �����ʿ��� �ִٸ�...
			else{

				//�������� ��忡 ���Ӱ� ��ġ�ϰ� �Ǵ� ���
				pDelPosNewNode = pNode->pRight;

				//������� ���� Root ����� �̶��� 100 �� �����ʿ� �����ڽ��ϳ��� �ִ� ���°� �ȴ�.
				if (pNode->pParent == NULL){

					//��Ʈ ��尡 �ٲ�� ��쿡�� ��Ʈ��带 ����
					m_pRoot = pDelPosNewNode;
					m_pRoot->pParent = NULL;
					DestoryNode(pNode);
				}

				//�θ� �ִٸ�
				else{

					//������� ��尡 �θ��� ���� �ڽ��̿��ٸ�..
					if (pNode->pParent->pLeft == pNode){
						pNode->pParent->pLeft = pNode->pRight;
					}

					//������� ����� �θ��� ������ �ڽ��̿��ٸ�...
					else {
						pNode->pParent->pRight = pNode->pRight;
					}

					//������� ����� �����ڽ��� �θ��� ���� ������� ����� �θ�� ��ü
					pNode->pRight->pParent = pNode->pParent;

					//������� ���� �÷��� Black �� ��쿡�� ��ó��
					if (pNode->color == BLACK)
						Remove_After(pDelPosNewNode);

					DestoryNode(pNode);
				}
			}
		}
	}//End else
}


//��� Ŭ����
void cBinaryTree::Clear(LPNODE pNode)
{
	if (pNode == NULL || pNode == m_pNil) return;

	Clear(pNode->pLeft);
	Clear(pNode->pRight);

	DestoryNode(pNode);
}


//���� ���
void cBinaryTree::PreOrderPrint(LPNODE pNode)
{
	if (pNode == NULL || pNode == m_pNil) return;

	cout << pNode->data << " ";

	PreOrderPrint(pNode->pLeft);
	PreOrderPrint(pNode->pRight);
}

//���� ���
void cBinaryTree::InOrderPrint(LPNODE pNode)
{
	if (pNode == NULL || pNode == m_pNil) return;

	InOrderPrint(pNode->pLeft);

	cout << pNode->data << " ";

	InOrderPrint(pNode->pRight);
}

//���� ���
void cBinaryTree::PostOrderPrint(LPNODE pNode)
{
	if (pNode == NULL || pNode == m_pNil) return;

	PostOrderPrint(pNode->pLeft);
	PostOrderPrint(pNode->pRight);

	cout << pNode->data << " ";
}


//�ش� �������� ��带 ã�´�.
cBinaryTree::LPNODE cBinaryTree::FindNode(int data)
{
	LPNODE pNode = m_pRoot;

	while (pNode != NULL && pNode != m_pNil)
	{
		//ã������ �����Ͱ� ���� ��庸�� ũ�ٸ� ���� ���� Ÿ�� ����.
		if (pNode->data < data){
			pNode = pNode->pRight;
		}

		//ã������ �����Ͱ� ���� ��庸�� �۴ٸ� ���� ���� Ÿ�� ����.
		else if (pNode->data > data){
			pNode = pNode->pLeft;
		}

		//Bingo
		else{
			return pNode;
		}
	}

	//������� �Դٸ� ��ã���� 
	return NULL;
}

//�ش� ����� ���� ���� ��带 ��´�.
cBinaryTree::LPNODE cBinaryTree::GetLeftNode(LPNODE pNode)
{
	LPNODE pFind = pNode;

	while (pFind->pLeft != m_pNil)
		pFind = pFind->pLeft;

	return pFind;
}

//����� ������ ����Ѵ�.
void cBinaryTree::PrintNodeInfo(LPNODE pNode, int depth)
{
	if (pNode == NULL || pNode == m_pNil) return;

	//[(Root) Data : 100, Parent    ] --- Leaf
	//		[(Left) Data : 100, Parent 30 ]

	//������ŭ ���� �߰�
	for (int i = 0; i < depth; i++){
		cout << "  ";
	}

	//Nil ���� Nil ����ϰ� ����
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




//�Ǻ���� �߽����� ���� ȸ�� �Ѵ�.
void cBinaryTree::Rotate_Left(LPNODE pPivot)
{
	//�Ǻ��� �������ڽ�
	LPNODE pRightChild = pPivot->pRight;

	//�Ǻ��� �����ʳ���� ���� �ڽ�
	LPNODE pRightChildLeft = pRightChild->pLeft;

	//�Ǻ��� ������ ����� ���� �ڽ��� Nil �� �ƴ϶��...
	if (pRightChildLeft != m_pNil)
		pRightChildLeft->pParent = pPivot;
	pPivot->pRight = pRightChildLeft;

	//������ ������ �ڽ��� �θ� �Ǻ��� �θ��
	pRightChild->pParent = pPivot->pParent;

	//�Ǻ��� ��Ʈ ��� ���ٸ� 
	if (pPivot->pParent == NULL)
		m_pRoot = pRightChild;

	else
	{
		//�Ǻ��� �θ��� ���� �ڽ��̿��ٸ�...
		if (pPivot->pParent->pLeft == pPivot)
			pPivot->pParent->pLeft = pRightChild;

		//�Ǻ��� �θ��� ������ �ڽ��̿��ٸ�..
		else
			pPivot->pParent->pRight = pRightChild;
	}

	//������
	pRightChild->pLeft = pPivot;
	pPivot->pParent = pRightChild;
}

//�Ǻ���� �߽����� ������ ȸ���Ѵ�.
void cBinaryTree::Rotate_Right(LPNODE pPivot)
{
	//�Ǻ��� �����ڽ�
	LPNODE pLeftChild = pPivot->pLeft;

	//������ �����ڽ��� ������ �ڽ�
	LPNODE pLeftChildRight = pLeftChild->pRight;

	//�Ǻ��� ���� ����� ������ �ڽ��� Nil �� �ƴ϶��...
	if (pLeftChildRight != m_pNil)
		pLeftChildRight->pParent = pPivot;
	pPivot->pLeft = pLeftChildRight;

	pLeftChild->pParent = pPivot->pParent;

	//��Ʈ ��忴�ٸ�...
	if (pPivot->pParent == NULL)
		m_pRoot = pLeftChild;

	else
	{
		if (pPivot->pParent->pLeft == pPivot)
			pPivot->pParent->pLeft = pLeftChild;
		else
			pPivot->pParent->pRight = pLeftChild;
	}

	//������
	pLeftChild->pRight = pPivot;
	pPivot->pParent = pLeftChild;
}


//���Ӱ� ��带 �߰����� ��ó��
void cBinaryTree::Push_After(LPNODE pNewNode)
{
	LPNODE pTarget = pNewNode;

	//�ϴ� Ÿ���� ��Ʈ�� �ƴϰ� Ÿ���� �θ� �������̸� 
	//��������� �ڽ��� ��� �������̿��� �Ѵٴ� ������
	//�ۻ쳪�� ��� ���� �ָ� ���ƾ��Ѵ�.
	while (pTarget->pParent != NULL && pTarget->pParent->color == RED)
	{
		//Ÿ�ٳ���� �θ� �Ҿƹ��� ������ �ڽ��̶��..
		if (pTarget->pParent == pTarget->pParent->pParent->pRight)
		{
			//���̳��
			LPNODE pUncle = pTarget->pParent->pParent->pLeft;

			//���̳�尡 �������ΰ��
			if (pUncle->color == RED)
			{
				//�θ�� ������ ����������
				pTarget->pParent->color = BLACK;
				pUncle->color = BLACK;

				//�Ҿƹ����� ����������
				pTarget->pParent->pParent->color = RED;

				//�Ҿƹ����� Ÿ������ �ٽ� üũ
				pTarget = pTarget->pParent->pParent;

			}

			//���̳�尡 �������̶��..
			else
			{
				//Ÿ�ٳ�尡 �θ��� ���� �ڽ��̶��....
				if (pTarget == pTarget->pParent->pLeft)
				{
					LPNODE pNewTarget = pTarget->pParent;

					//�θ� �߽����� ������ȸ��
					Rotate_Right(pTarget->pParent);

					//���� �θ𿴴� ��带 Target ���� �̾
					pTarget = pNewTarget;
				}

				//���⼭���ʹ� Target ���� �θ��� ������ �ڽ��̵�

				//�θ��带 ���� ������
				pTarget->pParent->color = BLACK;

				//�Ҿƹ�����带 ���������� 
				pTarget->pParent->pParent->color = RED;

				//�Ҿƹ��� �������� ��ȸ��
				Rotate_Left(pTarget->pParent->pParent);

				//��
				break;

			}

		}

		//Ÿ�ٳ���� �θ� �Ҿƹ��� ���� �ڽ��̶��...
		else
		{
			//���̳��
			LPNODE pUncle = pTarget->pParent->pParent->pRight;

			//���̳�尡 �������ΰ��
			if (pUncle->color == RED)
			{
				//�θ�� ������ ����������
				pTarget->pParent->color = BLACK;
				pUncle->color = BLACK;

				//�Ҿƹ����� ����������
				pTarget->pParent->pParent->color = RED;

				//�Ҿƹ����� Ÿ������ �ٽ� üũ
				pTarget = pTarget->pParent->pParent;
			}

			//���̳�尡 �������̶��..
			else
			{
				//Ÿ�ٳ�尡 �θ��� ������ �ڽ��̶��....
				if (pTarget == pTarget->pParent->pRight)
				{
					LPNODE pNewTarget = pTarget->pParent;

					//�θ� �߽����� ����ȸ��
					Rotate_Left(pTarget->pParent);

					//���� �θ𿴴� ��带 Target ���� �̾
					pTarget = pNewTarget;
				}

				//���⼭���ʹ� Target ���� �θ��� ���� �ڽ��̵�

				//�θ��带 ���� ������
				pTarget->pParent->color = BLACK;

				//�Ҿƹ�����带 ���������� 
				pTarget->pParent->pParent->color = RED;

				//�Ҿƹ��� �������� ��ȸ��
				Rotate_Right(pTarget->pParent->pParent);

				//��
				break;
			}
		}
	}

	//�׳ɰ����� Root �� �� 
	m_pRoot->color = BLACK;
}

//��带 �������� ��ó��	( �Ű������� �����ϰ� ���� ������ ��忡 ��ġ�ϰ� �Ǵ� ��尡 ���´� )
void cBinaryTree::Remove_After(LPNODE pNode)
{
	LPNODE pTarget = pNode;
	LPNODE pSibling = NULL;		//pTarget ����� �̿����

	//��Ʈ��尡 �̴ϰ� ��������� �϶� ��....
	while (pTarget->pParent != NULL && pTarget->color == BLACK)
	{
		//���� üũ���� Ÿ�� ��尡 �θ��� �����ڽ��̶��...
		if (pTarget == pTarget->pParent->pLeft)
		{
			//�������� �θ��� ������ �ڽ�
			pSibling = pTarget->pParent->pRight;

			//������尡 �������̶��...
			if (pSibling->color == RED)
			{
				//������ �÷��� ���������� �ٲٰ�
				pSibling->color = BLACK;

				//�θ��� ���� ���������� �ٲ� ��
				pTarget->pParent->color = RED;

				//�θ� �߽����� ���� ȸ��
				Rotate_Left(pTarget->pParent);

				//�� ���� �ݺ������ʹ� �������� �������� �Ǿ����� ���̴�.
				//( ������ ����� �ڽ��� ��� �������̱� �����̴� )
			}

			//���� ��尡 �������̶��...
			else
			{
				//������ �ڽĵ� ��� �������̶��...
				if (pSibling->pLeft->color == BLACK &&
					pSibling->pRight->color == BLACK)
				{
					//������ ���� ���������� �ٲٰ�
					pSibling->color = RED;

					//�θ𸦱������� �ٽ� üũ
					pTarget = pTarget->pParent;
				}


				//������ �ڽ��� ��� �������� �ƴ϶��...
				else
				{

					//������ �����ڽĸ� ������ �̶��...
					if (pSibling->pLeft->color == RED)
					{
						//������ �����ڽ��� ���� ����������..
						pSibling->pLeft->color = BLACK;

						//������ ���� ����������...
						pSibling->color = RED;

						//���� ��带 �߽����� ������ ȸ��
						Rotate_Right(pSibling);

						//������ ȸ���� ������...
						//������带 �θ��� ���������� �ٽ� ����
						pSibling = pTarget->pParent->pRight;

						//�̷����Ͽ� ������ �������ڽ��� �������̶�� ������ ȸ����
					}


					//������� �´ٸ� ������ �������ڽĴ� ��������尡 �ȴ�.

					//������ �÷��� ���� �θ��� �÷���...
					pSibling->color = pTarget->pParent->color;

					//�θ��� �÷���  �÷��� ����������...
					pTarget->pParent->color = BLACK;

					//������ �������ڽ� �÷��� ����������...
					pSibling->pRight->color = BLACK;

					//�θ�������� ���� ȸ��
					Rotate_Left(pTarget->pParent);

					//üũ�Ǵ� Ÿ�� ��带 ��Ʈ���� ( ����� �̱������� while ���� ���������� �ǰ� �Լ� �������� Root ���� �������� �ȴ�. )
					pTarget = m_pRoot;
				}
			}

		}//���� üũ���� Ÿ�� ��尡 �θ��� �����ڽ��̶��( END )


		//���� üũ���� Ÿ�� ��尡 �θ��� ������ �ڽ��̶��...
		else
		{
			//�������� �θ��� ���� �ڽ�
			pSibling = pTarget->pParent->pLeft;

			//������尡 �������̶��...
			if (pSibling->color == RED)
			{
				//������ �÷��� ���������� �ٲٰ�
				pSibling->color = BLACK;

				//�θ��� ���� ���������� �ٲ� ��
				pTarget->pParent->color = RED;

				//�θ� �߽����� ������ ȸ��
				Rotate_Right(pTarget->pParent);

				//�� ���� �ݺ������ʹ� �������� �������� �Ǿ����� ���̴�.
				//( ������ ����� �ڽ��� ��� �������̱� �����̴� )
			}

			//���� ��尡 �������̶��...
			else
			{
				//������ �ڽĵ� ��� �������̶��...
				if (pSibling->pLeft->color == BLACK &&
					pSibling->pRight->color == BLACK)
				{
					//������ ���� ���������� �ٲٰ�
					pSibling->color = RED;

					//�θ𸦱������� �ٽ� üũ
					pTarget = pTarget->pParent;
				}


				//������ �ڽ��� ��� �������� �ƴ϶��...
				else
				{

					//������ �������ڽĸ� ������ �̶��...
					if (pSibling->pRight->color == RED)
					{
						//������ �������ڽ��� ���� ����������..
						pSibling->pRight->color = BLACK;

						//������ ���� ����������...
						pSibling->color = RED;

						//���� ��带 �߽����� ���� ȸ��
						Rotate_Left(pSibling);

						//������ ȸ���� ������...
						//������带 �θ��� �������� �ٽ� ����
						pSibling = pTarget->pParent->pLeft;

						//�̷����Ͽ� ������ �����ڽ��� �������̶�� ������ ȸ����
					}


					//������� �´ٸ� ������ �������ڽĴ� ��������尡 �ȴ�.

					//������ �÷��� ���� �θ��� �÷���...
					pSibling->color = pTarget->pParent->color;

					//�θ��� �÷���  �÷��� ����������...
					pTarget->pParent->color = BLACK;

					//������ �������ڽ� �÷��� ����������...
					pSibling->pRight->color = BLACK;

					//�θ�������� ������ ȸ��
					Rotate_Right(pTarget->pParent);

					//üũ�Ǵ� Ÿ�� ��带 ��Ʈ���� ( ����� �̱������� while ���� ���������� �ǰ� �Լ� �������� Root ���� �������� �ȴ�. )
					pTarget = m_pRoot;
				}
			}

		}//���� üũ���� Ÿ�� ��尡 �θ��� �������ڽ��̶��( END )
	}

	//����Ǳ����� Ÿ�ٳ�带 ����������..
	pTarget->color = BLACK;

}