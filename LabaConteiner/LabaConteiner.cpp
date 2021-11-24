#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
using namespace std;

template<typename T>
class List
{
public:
	List();
	~List();

	void pop_front();
	void push_back(T data);
	void clear();
	int GetSize() { return Size; }
	T& operator[](const int index);
	void push_front(T data);
	void insert(T data, int index);
	void removeAt(int index);
	void pop_back();

private:
	template<typename T> // Very important line. No Delete
	class Node
	{
	public:
		Node* pNext;
		T data;
		Node(T data, Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	};
	int Size;
	Node<T>* head;
};
 

template<typename T>
List<T>::List()
{
	Size = 0;
	head = nullptr;
}


template<typename T>
List<T>::~List()
{
	clear();
}


template<typename T>
void List<T>::pop_front()
{
	Node<T>* temp = head;
	head = head->pNext;
	delete temp;
	Size--;
}

template<typename T>
void List<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T>* current = this->head;

		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node<T>(data);

	}
	Size++;
}

template<typename T>
void List<T>::clear()
{
	while (Size)
	{
		pop_front();
	}
}


template<typename T>
T& List<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* current = this->head;
	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}

template<typename T>
void List<T>::push_front(T data)
{
	head = new Node<T>(data, head);
	Size++;
}

template<typename T>
void List<T>::insert(T data, int index)
{
	if (index == 0)
	{
		push_front(data);
	}
	else
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}
		Node<T>* newNode = new Node<T>(data, previous->pNext);
		previous->pNext = newNode;
		Size++;
	}
}

template<typename T>
void List<T>::removeAt(int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}
		Node<T>* toDelete = previous->pNext;
		previous->pNext = toDelete->pNext;
		delete toDelete;
		Size--;
	}
}

template<typename T>
void List<T>::pop_back()
{
	removeAt(Size - 1);
}
 
int main()
{
	srand(time(0));
	setlocale(LC_ALL, "ru");
	List<int> lst;
	for (int i=0; i<100; i++)
	    lst.push_back((int)i);
	
	unsigned int start_time = clock();
	for (int i = 1; i < 10001; i++)
	{
		int index = rand() % lst.GetSize();
		int data = (int)rand() % 100;
		int v = rand() % 7;
		switch (v)
		{
		case 1: lst.push_back(data); cout << i << "  push_back: " << (int)data << endl; break;
		case 2: lst.insert(data, index); cout << i << "  insert: " << (int)data << ", " << index << endl; break;
		case 3: lst.push_front(data); cout << i << "  push_front: " << (int)data << endl; break;
		case 4: lst.pop_back(); cout << i << "  pop_back: " << endl; break;
		case 5: lst.removeAt(index); cout << i << "  removeAt: " << index << endl; break; 
		case 6: lst.pop_front(); cout << i << "  pop_front: " << endl; break;
		default:
			break;
		}
	}
	unsigned int end_time = clock();
	for (int i = 0; i < lst.GetSize(); i++)
	{
		cout << lst[i] << endl;
	}
	cout << "EndSize: " << lst.GetSize() << endl;
	cout << "Time: " << (float)(end_time - start_time)/1000.0;
	return 0;
}

