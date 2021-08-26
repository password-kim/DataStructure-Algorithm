#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include "BinarySearchTree.h"
using namespace std;

// 이진 탐색 트리
// => 배열로 구현된 이진 탐색은 중간 삽입/삭제가 힘들다.
// => 따라서 이진 탐색 트리로 보완을 해야한다.

int main()
{
	BinarySearchTree bst;

	bst.Insert(20);
	bst.Insert(10);
	bst.Insert(30);
	bst.Insert(40);
	bst.Insert(50);
	bst.Insert(25);
	bst.Insert(26);

	//bst.Print_Inorder();

	bst.Delete(20);

	bst.Print();

}

