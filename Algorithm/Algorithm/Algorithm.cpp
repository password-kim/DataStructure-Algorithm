#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

using NodeRef = shared_ptr<struct Node>;

struct Node
{
	Node(){}
	Node(const string& data) : data(data) {}

	string			data;
	vector<NodeRef>	children;
};

NodeRef CreateTree() // 트리의 생성
{
	NodeRef root = make_shared<Node>("R1 개발실");
	{
		NodeRef node = make_shared<Node>("디자인팀"); // 노드생성.
		root->children.push_back(node); // 자식노드를 부모노드에 연결.
		{
			NodeRef leaf = make_shared<Node>("전투"); // 노드생성.
			node->children.push_back(leaf); // 자식노드를 부모노드에 연결.
		}
		{
			NodeRef leaf = make_shared<Node>("경제");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("스토리");
			node->children.push_back(leaf);
		}
	}
	{
		NodeRef node = make_shared<Node>("프로그래밍팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("서버");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("클라");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("엔진");
			node->children.push_back(leaf);
		}
	}
	{
		NodeRef node = make_shared<Node>("아트팀");
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("배경");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("캐릭터");
			node->children.push_back(leaf);
		}
	}

	return root;
}

void PrintTree(NodeRef root, int depth)
{
	for (int i = 0; i < depth; i++) // 가독성을 높이기위해 자식으로 갈때마다 '-'를 추가.
		cout << "-";
	cout << root->data << endl;

	for (NodeRef& child : root->children) // 재귀적 특성을 이용해 자식을 불러온다.
		PrintTree(child, depth + 1);
}

// 깊이(depth) : 루트에서 어떤 노드에 노달하기 위해 거쳐야 하는 간선의 수
// 높이(height) : 가장 깊숙히 있는 노드의 깊이 (max(depth))
int GetHeight(NodeRef root)
{
	int height = 1;

	for (NodeRef& child : root->children) // 재귀적 특성을 이용해 트리의 높이를 구한다.
		height = max(height, GetHeight(child) + 1);

	return height;
}

int main()
{
	NodeRef root = CreateTree();

	PrintTree(root, 0);

	int height = GetHeight(root);
	cout << "Tree Height : " << height << endl;
}

