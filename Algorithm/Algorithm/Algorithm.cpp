#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <thread>
#include <Windows.h>
using namespace std;

// 동적 계획법 (DP)

// LIS (Longest Increasing Sequence)

// Seq : 1 9 2 5 7
// 부분 수열 : 일부(0개 이상) 숫자를 지우고 남은 수열
// ex) 1 2 5 <= 순 증가 부분 수열
// ex) 1 9 5 7 <= 순 증가x 부분 수열

// LIS : 제일 긴 "순 증가 부분 수열"의 길이
// 1 2 5 7 => 길이: 4

int cache[100];
vector<int> seq;

int LIS(int pos)
{
	// - 기저 사항 => 있을수도 있고 없을수도 있다.

	// - 캐시 확인
	int& ret = cache[pos];
	if (ret != -1)
		return ret;

	// - 계획
	// seq : 1 9 2 5 7
	// 최소 seq[pos]는 있으니 1부터 시작
	ret = 1;
	// 1 9 => 길이: 2 => LIS(0) -> 1 + LIS(1)
	// 1 2 5 7 =>길이: 4 => LIS(0) -> 1 + LIS(2) -> 
	// 1 5 7 => 길이: 3
	// 1 7 => 길이: 2

	// - 구하기
	for (int next = pos + 1; next < seq.size(); next++)
		if (seq[pos] < seq[next])
			ret = max(ret, 1 + LIS(next));

	return ret;
}

int main()
{
	::memset(cache, -1, sizeof(cache));
	seq = vector<int>{ 9, 1, 2, 5, 7 };

	int ret = 0;
	// 무조건 seq[0]이 가장 작은 수라는 보장이 없으니 순회하여 구한다.
	for (int pos = 0; pos < seq.size(); pos++)
		ret = max(ret, LIS(pos));
}

