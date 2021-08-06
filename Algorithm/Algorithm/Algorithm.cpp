#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class Vector
{
public:
    Vector()
    {

    }

    ~Vector()
    {
        if (_data)
            delete[] _data;
    }

    void push_back(const T& value)
    {
        if (_size == _capacity)
        {
            // 증설 작업
            int newCapacity = static_cast<int>(_capacity * 1.5);
            if (newCapacity == _capacity)
                newCapacity++;

            reserve(newCapacity);
        }

        // 데이처 저장
        _data[_size] = value;

        // 데이터 개수 증가
        _size++;
    }

    void reserve(int capacity)
    {
        if (_capacity >= capacity)
            return;

        _capacity = capacity;

        T* newData = new T[_capacity];

        // 데이터 복사
        for (int i = 0; i < _size; i++)
            newData[i] = _data[i];

        if (_data)
            delete[] _data;

        // 교체
        _data = newData;
    }

    void resize(int size)
    {
        _size = size; // _size에 내가 resize하길 원하는 size를 대입.

        if (size > _capacity) // 현재 _capacity가 resize되는 size보다 작다면 _capcity를 size만큼 증가.
            _capacity = size;

        T* newData = new T[_size]; // resize된 크기의 새로운 배열을 생성.

        if (_data) //_data가 nullptr이 아니라면 새로운 배열에 _data의 data를 복사 후 기존 _data해제.
        {
            for (int i = 0; i < _size; i++)
                newData[i] = _data[i];

            delete[] _data;
        }
        
        _data = newData; //_data를 새로운 배열로 change.
    }

    void pop_back() { _size--; } // size를 하나줄여서 맨 뒤의 요소를 pop!

    T& operator[](const int pos) { return _data[pos]; } 

    int size() { return _size; }
    int capacity() { return _capacity; }

    void clear()
    {
        if (_data) // 예외처리
        {
            delete[] _data;
            _data = new T[_capacity];
        }

        _size = 0;
    }


private:
    T* _data = nullptr;
    int _size = 0;
    int _capacity = 0;
};

int main()
{
    Vector<int> v;

    v.reserve(100); // default capacity를 100으로 설정.

    for (int i = 0; i < 100; i++) // v에 0부터 99까지의 숫자를 push_back하고 element와 size, capacity를 콘솔창에 출력.
    {
        v.push_back(i); 
        cout << v[i] << " " << v.size() << " " << v.capacity() << endl;
    }

    v.resize(10); // size를 10으로 resize.

    for (int i = 0; i < v.size(); i++) // resize된 v의 element, size, capacity를 콘솔창에 출력.
    {
        cout << v[i] << " " << v.size() << " " << v.capacity() << endl;
    }

    v.pop_back(); // v의 맨 뒤의 elements를 pop!

    for (int i = 0; i < v.size(); i++) // 다시 v의 element, size, capacity를 콘솔창에 출력.
    {
        cout << v[i] << " " << v.size() << " " << v.capacity() << endl;
    }
    


}

