#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <thread>
using namespace std;

// 해시 테이블

// map vs hash_map (C++11 표준 unordered_map)
// - map : Red-Black Tree구조.
//	- 추가/탐색/삭제 O(logN)
// - hash_map (unordered_map)
//	- 추가/탐색/삭제 O(1)
//	- 메모리를 내주고 속도를 취한다.

void TestTable()
{
	struct User
	{
		int userId = 0; // 1~999
		string username;
	};

	vector<User> users;
	users.resize(1000);

	// 777번 유저 정보 세팅
	users[777] = User{ 777, "PassWordKim" };

	// 777번 유저 이름은?
	string name = users[777].username;
	cout << name << endl;

	// 테이블
	// 키를 알면, 데이터를 단번에 찾을 수 있다!

	// BUT, 데이터가 많아지면 
	// 메모리 사용 요구량이 많이지기 때문에 비효율적..
}

void TestHash()
{
	struct User
	{
		int userId = 0; // 1~int32_max
		string username;
	};

	//       []
	// [][][][][][][][]
	vector<User> users;
	users.resize(1000);

	const int userId = 123456789;
	int key = (userId % 1000); // hash < 고유번호

	// 123456789번 유저 정보 세팅
	users[key] = User{ userId, "PassWordKim" };

	// 123456789번 유저 이름은?
	User& user = users[key];
	if (user.userId == userId)
	{
		string name = user.username;
		cout << name << endl;
	}

	// 충돌 문제
	// 충돌이 발생한 자리를 대신해서 다른 빈자리를 찾아나서면 된다
	// - 선형 조사법 (linear probing)
	// hash(key)+1 -> hash(key)+2
	// - 이차 조사법 (quadratic probing)
	// hash(key)+1^2 -> hash(key)+2^2
	// - etc..

	// 체이닝
}

// O(1)
void TestHashTableChaining()
{
	struct User
	{
		int userId = 0; // 1~int32_max
		string username;
	};

	// [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
	vector<vector<User>> users;
	users.resize(1000);

	const int userId = 123456789;
	int key = (userId % 1000); // hash < 고유번호

	// 123456789번 유저 정보 세팅
	users[key].push_back(User{ userId, "PassWordKim" });
	users[789].push_back(User{ 789, "Kun" });

	// 123456789번 유저 이름은?
	vector<User>& bucket = users[key];
	for (User& user : bucket)
	{
		if (user.userId == userId)
		{
			string name = user.username;
			cout << name << endl;
		}
	}
}

int main()
{
	//TestTable();
	//TestHash();
	TestHashTableChaining();
}

