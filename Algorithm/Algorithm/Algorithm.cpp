#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

#pragma region Vector
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
#pragma endregion

#pragma region List
template<typename T>
class Node
{
public:
    Node() : _prev(nullptr), _next(nullptr), _data(T())
    {

    }

    Node(const T& value) : _prev(nullptr), _next(nullptr), _data(value)
    {

    }
    
public:
    Node*   _prev;
    Node*   _next;
    T       _data;


};

template<typename T>
class Iterator
{
public:
    Iterator() : _node(nullptr)
    {

    }

    Iterator(Node<T>* node) : _node(node)
    {

    }

    // ++it
    Iterator& operator++()
    {
        _node = _node->_next;
        return _node;
    }

    // it++
    Iterator& operator++(int)
    {
        Iterator<T> temp = *this;
        _node = _node->_next;
        return temp;
    }

    // --it
    Iterator& operator--()
    {
        _node = _node->_prev;
        return _node;
    }

    // it--
    Iterator& operator--(int)
    {
        Iterator<T> temp = *this;
        _node = _node->_prev;
        return temp;
    }

    // *it
    T& operator*()
    {
        return _node->_data;
    }

    bool operator==(const Iterator& other)
    {
        return _node == other._node;
    }

    bool operator!=(const Iterator& other)
    {
        return _node != other._node;
    }

public:
    Node<T>* _node;
};

template<typename T>
class List
{
public:
    List() : _size(0)
    {
        // [head] <=> [tail]
        _head = new Node<T>();
        _tail = new Node<T>();
        _head->_next = _tail;
        _tail->_prev = _head;
    }

    ~List()
    {
        while (_size > 0)
            pop_back();

        delete _head;
        delete _tail;
    }

    void push_back(const T& value)
    {
        AddNode(_tail, value);
    }

    void pop_back()
    {
        RemoveNode(_tail->_prev);
    }

private:

    // [head] <=> [1] <=> [2] <=> [before] <=> [tail]
    // [head] <=> [1] <=> [2] <=> [newNode] <=> [before] <=> [tail]
    Node<T>* AddNode(Node<T>* before, const T& value)
    {
        Node<T>* newNode = new Node<T>(value);
        Node<T>* prevNode = before->_prev;

        prevNode->_next = newNode;
        newNode->_prev = prevNode;

        newNode->_next = before;
        before->_prev = newNode;

        _size++;

        return newNode;
    }

    // [head] <=> [prevNode] <=> [node] <=> [nextNode] <=> [tail]
    // [head] <=> [prevNode] <=> [nextNode] <=> [tail]
    Node<T>* RemoveNode(Node<T>* node)
    {
        Node<T>* prevNode = node->_prev;
        Node<T>* nextNode = node->_next;

        prevNode->_next = nextNode;
        nextNode->_prev = prevNode;

        delete node;

        _size--;

        return nextNode;
    }


    int size() { return _size; }


public:
    using iterator = Iterator<T>;

    iterator begin() { return iterator(_head->_next); }
    iterator end() { return iterator(_tail); }

    // it '앞에' 추가
    iterator insert(iterator it, const T& value)
    {
        Node<T>* node = AddNode(it._node, value);
        return iterator(node);
    }

    iterator erase(iterator it)
    {
        Node<T>* node = RemoveNode(it._node);
        return iterator(node);
    }

private:
    Node<T>*    _head;
    Node<T>*    _tail;
    int         _size;
};
#pragma endregion

#pragma region Stack
//Stack (LIFO Last-In-First-Out 후입선출)

template<typename T, typename Container = vector<int>>
class Stack
{
public:
    void push(const T& value)
    {
        _container.push_back(value);
    }

    void pop()
    {
        _container.pop_back();
    }

    T& top()
    {
        return _container.back();
    }

    bool empty() { return _container.empty(); }
    int size() { return _container.size(); }

private:
    Container _container;

};

#pragma endregion

#pragma region Queue

// Queue (FIFO First-In-First-Out 선입선출)

// front << [1][2][3][4] << rear(back)

template<typename T>
class ArrayQueue  // [][][front][][][back][][][][][]
{
public:
    ArrayQueue()
    {
        _container.resize(100);
    }

    void push(const T& value)
    {
        // TODO : 다 찼는지 체크
        if (_size == _container.size())
        {
            // 증설 작업
            int newSize = max(1, _size * 2);
            vector<T> newData;
            newData.resize(newSize);

            // 데이터 복사
            for (int i = 0; i < _size; i++)
            {
                int index = (_front + i) % _container.size();
                newData[i] = _container[index];
            }

            _container.swap(newData);
            _front = 0;
            _back = _size;
        }

        _container[_back] = value;
        _back = (_back + 1) % _container.size();
        _size++;
    }

    void pop()
    {
        _front = (_front + 1) % _container.size();
        _size--;
    }

    T& front()
    {
        return _container[_front];
    }

    bool empty() { return _size == 0; }

    int size() { return _container.size(); }

private:
    vector<T> _container;

    int _front = 0;
    int _back = 0;
    int _size = 0;
};

template<typename T>
class ListQueue
{
public:
    void push(const T& value)
    {
        _container.push_back(value);
    }

    void pop()
    {
        _container.pop_front();
    }

    T& front()
    {
        return _container.front();
    }

    bool empty() { return _container.empty(); }

    int size() { return _container.size(); }

private:
    list<T> _container;
};

#pragma endregion  

#pragma region Graph기초
void CreateGraph1()
{
    struct Vertex
    {
        vector<Vertex*> edges;
    };

    vector<Vertex> v;
    v.resize(6);

    v[0].edges.push_back(&v[1]);
    v[0].edges.push_back(&v[3]);
    v[1].edges.push_back(&v[0]);
    v[1].edges.push_back(&v[2]);
    v[1].edges.push_back(&v[3]);
    v[3].edges.push_back(&v[4]);
    v[5].edges.push_back(&v[4]);

    // 0번 -> 3번 정점이 연결되어 있는지 확인.
    bool connected = false;
    for (Vertex* edge : v[0].edges)
    {
        if (edge == &v[3])
        {
            connected = true;
            break;
        }
    }
}

void CreateGraph2()
{

    // 연결된 목록을 따로 관리
    // adjacent[n] -> n번 정점과 연결된 정점 목록
    vector<vector<int>> adjacent(6);
    adjacent[0] = { 1, 3 };
    adjacent[1] = { 0, 2, 3 };
    adjacent[3] = { 4 };
    adjacent[5] = { 4 };

    
    // 0번 -> 3번 정점이 연결되어 있는지 확인.
    bool connected = false;
    for (int vertex : adjacent[0])
    {
        if (vertex == 3)
        {
            connected = true;
            break;
        }
    }

    // STL
    vector<int>& adj = adjacent[0];
    bool connected2 = (::find(adj.begin(), adj.end(), 3) != adj.end());
    
}

void CreateGraph3()
{

    // 연결된 목록을 따로 관리
    // [X][O][X][O][X][X]
    // [O][X][O][O][X][X]
    // [X][X][X][X][X][X]
    // [X][X][X][X][O][X]
    // [X][X][X][X][X][X]
    // [X][X][X][X][O][X]

    // 읽는 방법 : adjacent[from][to]
    // 행렬을 이용한 그래프 표현. (2차원 배열)
    // 메모리 소모가 심하긴 하지만, 빠른 접근 가능.
    // 간선이 많은 경우 이점이 있다.
    vector<vector<bool>> adjacent(6, vector<bool>(6, false));
    adjacent[0][1] = true;
    adjacent[0][3] = true;
    adjacent[1][0] = true;
    adjacent[1][2] = true;
    adjacent[1][3] = true;
    adjacent[3][4] = true;
    adjacent[5][4] = true;


    // 0번 -> 3번 정점이 연결되어 있는지 확인.
    bool connected = adjacent[0][3];

    vector<vector<int>> adjacent2 =
    {
        vector<int> { -1, 15, -1, 35, -1, -1 },
        vector<int> { 15, -1, 5, 10, -1, -1 },
        vector<int> { -1, -1, -1, -1, -1, -1 },
        vector<int> { -1, -1, -1, -1, 5, -1 },
        vector<int> { -1, -1, -1, -1, -1, -1 },
        vector<int> { -1, -1, -1, -1, 5, -1 },
    };

    adjacent[0][3];
    
}

void CreateGraph4()
{
    // 가중치가 추가된 그래프.
    // 갈수없는 곳은 -1, 갈수있는 곳은 가중치를 넣어줌.
    vector<vector<int>> adjacent =
    {
        vector<int> { -1, 15, -1, 35, -1, -1 },
        vector<int> { 15, -1, 5, 10, -1, -1 },
        vector<int> { -1, -1, -1, -1, -1, -1 },
        vector<int> { -1, -1, -1, -1, 5, -1 },
        vector<int> { -1, -1, -1, -1, -1, -1 },
        vector<int> { -1, -1, -1, -1, 5, -1 },
    };

    // 0번 -> 3번 정점이 연결되어 있는지 확인.
    if (adjacent[0][3] != -1)
        cout << adjacent[0][3] << endl;


}
#pragma endregion


int main()
{
    CreateGraph1();
    CreateGraph2();
    CreateGraph3();
    CreateGraph4();
}

