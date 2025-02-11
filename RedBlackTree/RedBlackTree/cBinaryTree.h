#pragma once


//���� ��Ʈ���� ����
//1. ��� ���� ������ Ȥ�� �������� ������ �ִ�.
//2. ��Ʈ ���� �������̰� �ٳ�嵵 �������̴�.
//3. ��������� �ڽ��� ��� �������̿��� �ϰ�, ������ ����� �ڽ��� ������ �������.
//4. ��Ʈ��忡�� �ٳ������ ���� ����� ������ ����� ���� ����ο��� �����ϴ�.

class cBinaryTree
{
private:
	//����� ����
	enum NODEColor{ RED, BLACK };

	typedef struct tagNODE{
		int data;
		tagNODE* pLeft;			//���� �ڽ�
		tagNODE* pRight;		//������ �ڽ�
		tagNODE* pParent;		//�θ�
		NODEColor color;		//����� ����
	}NODE, *LPNODE;

private:
	LPNODE			m_pRoot;	//��Ʈ ���
	LPNODE			m_pNil;		//Nil ���� ���

public:
	cBinaryTree(void);
	~cBinaryTree(void);

	//������ �߰�
	void Push_Data(int data);

	//���� ���
	void PreOrderPrint();

	//���� ���
	void InOrderPrint();

	//���� ���
	void PostOrderPrint();

	//Tree ���� ����
	void Clear();

	//�ش� ������ �� �ִ��� Ȯ��
	bool IsContain(int data);

	//(���� ����) Data �� ��� �ִ� ��带 �����Ѵ�.
	void RemoveData(int data);

	//Ʈ���� ������ ����Ѵ�.
	void PrintTreeInfo();


	void Test_LeftRotate(){
		Rotate_Left(m_pRoot);
	}

	void Test_RightRotate(){
		Rotate_Right(m_pRoot);
	}

private:
	//��� ����
	LPNODE CreateNode(int data);

	//��� �ı�
	void DestoryNode(LPNODE pNode);

	//��� ���� ( ���ŵɶ� ��ó������ ������ִ� �༮ )
	void RemoveNode(LPNODE pNode);

	//��� Ŭ����
	void Clear(LPNODE pNode);

	//���� ���
	void PreOrderPrint(LPNODE pNode);

	//���� ���
	void InOrderPrint(LPNODE pNode);

	//���� ���
	void PostOrderPrint(LPNODE pNode);

	//�ش� �������� ��带 ã�´�.
	LPNODE FindNode(int data);

	//�ش� ����� ���� ���� ��带 ��´�.
	LPNODE GetLeftNode(LPNODE pNode);

	//����� ������ ����Ѵ�.
	void PrintNodeInfo(LPNODE pNode, int depth);

	//�Ǻ���� �߽����� ���� ȸ�� �Ѵ�.
	void Rotate_Left(LPNODE pPivot);

	//�Ǻ���� �߽����� ������ ȸ���Ѵ�.
	void Rotate_Right(LPNODE pPivot);

	//���Ӱ� ��带 �߰����� ��ó��
	void Push_After(LPNODE pNewNode);

	//��带 �������� ��ó��	( �Ű������� �����ϰ� ���� ������ ��忡 ��ġ�ϰ� �Ǵ� ��尡 ���´� )
	void Remove_After(LPNODE pNode);
};