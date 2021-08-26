#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

// 이진 탐색(Binary Search)
// => 정렬된 배열을 이용해서 이진 탐색 가능
// => 연결 리스트로는 불가(연결 리스트는 임의 접근 불가)

vector<int> numbers;

void BinarySearch(int N)
{
	int left = 0;
	int right = (int)numbers.size() - 1;

	while (left <= right)
	{
		cout << "탐색 범위: " << left << " ~ " << right << endl;

		int mid = (left + right) / 2;

		if (N < numbers[mid])
		{
			cout << N << " < " << numbers[mid] << endl;
			right = mid - 1;
		}
		else if (N > numbers[mid])
		{
			cout << N << " > " << numbers[mid] << endl;
			left = mid + 1;
		}
		else
		{
			cout << "찾음!" << endl;
			break;
		}
	}
}

int main()
{
	numbers = vector<int>{ 1, 8, 15, 23, 32, 44, 56, 63, 81, 91 };
	
	BinarySearch(81);
}

