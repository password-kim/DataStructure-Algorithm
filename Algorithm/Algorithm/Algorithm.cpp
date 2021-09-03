#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <thread>
using namespace std;

// 상호 배타적 집합 (Disjoint Set)
// => 유니온-파인드 Union-Find

// 트리 구조를 이용한 상호 배타적 집합의 표현.
// 조직 구조?
// [1]		[3]
// [2]	 [4][5]
//			[0]

// 시간 복잡도 : 트리의 높이에 비례한 시간이 걸림
class NaiveDisjointSet
{
public:
	NaiveDisjointSet(int n) : _parent(n)
	{
		for (int i = 0; i < n; i++)
			_parent[i] = i;
	}

	// 니 대장이 누구니?
	int Find(int u)
	{
		if (u == _parent[u])
			return u;

		return Find(_parent[u]);
	}

	// u와 v를 합친다 (일단 u가 v 밑으로)
	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);

		if (u == v)
			return;

		_parent[u] = v;
	}

private:
	vector<int> _parent;
};

// 트리가 한쪽으로 기우는 문제를 해결?
// 트리를 합칠 때, 항상 [높이가 낮은 트리를] [높이가 높은 트리] 밑으로
// (Union-By-Rank) 랭크에 의한 합치기 최적화
// 시간 복잡도 O(Ackermann(n)) = O(1)
class DisjointSet
{
public:
	DisjointSet(int n) : _parent(n), _rank(n, 1)
	{
		for (int i = 0; i < n; i++)
			_parent[i] = i;
	}

	// 니 대장이 누구니?
	int Find(int u)
	{
		if (u == _parent[u])
			return u;

		//_parent[u] = Find(_parent[u]);
		//return _parent[u];

		return _parent[u] = Find(_parent[u]);
	}

	// u와 v를 합친다
	void Merge(int u, int v)
	{
		u = Find(u);
		v = Find(v);

		if (u == v)
			return;

		if (_rank[u] > _rank[v])
			swap(u, v);

		// rank[u] <= rank[v] 보장됨
		_parent[u] = v;

		if (_rank[u] == _rank[v])
			_rank[v]++;
	}

private:
	vector<int> _parent;
	vector<int> _rank;
};

int main()
{
	DisjointSet teams(1000);

	teams.Merge(10, 1);
	int teamId = teams.Find(1);
	int teamId2 = teams.Find(10);

	teams.Merge(3, 2);
	int teamId3 = teams.Find(3);
	int teamId4 = teams.Find(2);

	teams.Merge(1, 3);
	int teamId6 = teams.Find(1);
	int teamId7 = teams.Find(3);
}

