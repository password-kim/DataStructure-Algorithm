#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <thread>
#include "BinarySearchTree.h"
using namespace std;

// 이진 탐색 트리
// => 배열로 구현된 이진 탐색은 중간 삽입/삭제가 힘들다.
// => 따라서 이진 탐색 트리로 보완을 해야한다.

int main()
{
	BinarySearchTree bst;

	bst.Insert(30);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(10);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(20);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Insert(25);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Delete(20);
	bst.Print();
	this_thread::sleep_for(1s);

	bst.Delete(10);
	bst.Print();
	this_thread::sleep_for(1s);
	

	//bst.Print_Inorder();

}

