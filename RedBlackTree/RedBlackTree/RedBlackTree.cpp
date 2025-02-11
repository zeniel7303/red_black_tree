// RedBlackTree.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "cBinaryTree.h"
#include <iostream>
using namespace std;

int main()
{
	cBinaryTree tree;

	while (true) {

		cout << "숫자 입력";
		int input;
		cin >> input;

		tree.Push_Data(input);

		tree.PrintTreeInfo();

		cout << endl;

	}

    return 0;
}

