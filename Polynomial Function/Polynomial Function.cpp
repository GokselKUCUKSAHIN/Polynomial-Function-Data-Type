#include "pch.h"
#include <iostream>
#include <math.h>
#include <sstream>

using namespace std;

class Data {

public:
	// Structure
	int powerOfX = 0;
	int powerOfY = 0;
	bool symbol = false;
	int value = 0;
	//
	Data(bool symbol, int value, int powX, int powY)
	{
		this->symbol = symbol;
		this->value = value;
		this->powerOfX = powX;
		this->powerOfY = powY;
	}
	Data()
	{
		//null constructor
	}
	//
	int CalculateNode(int x, int y);
	string PrintRow()
	{
		stringstream s;
		symbol == true ? s << " -(" : s << " +(";
		s << this->value << " X^" << powerOfX << " Y^" << powerOfY << ") ";
		return s.str();
	}
};
int Data::CalculateNode(int x, int y)
{
	if (symbol)
	{
		value *= -1;
	}
	return  (int)(value * pow(x, this->powerOfX)*pow(y, this->powerOfY));
}


class Node {

public:
	Data data;
	Node* next;
};

class List {
public:
	List(void)
	{
		first = NULL;
		size = 0;
	}
	~List(void)
	{
		while (IsEmpty() != true)
		{
			DeleteNode(0);
		}
	}
	bool IsEmpty();
	void Push(Data data);
	void DeleteNode(int index);
	Node* FindNode(int index);
	Node* InsertNode(int index, Data data);
	void PrintAll();
	int CalculateList(int x, int y);
	int size;
private:
	Node* first;
};

bool List::IsEmpty()
{
	return this->first == NULL;
}

void List::DeleteNode(int index)
{
	Node* prevNode = NULL;
	Node* currentNode = first;
	int currentIndex = 1;
	while (currentNode && index + 1 > currentIndex)
	{
		prevNode = currentNode;
		currentNode = currentNode->next;
		currentIndex++;
	}
	if (currentNode)
	{
		if (prevNode)
		{
			prevNode->next = currentNode->next;
			delete currentNode;
			size--;
		}
		else
		{
			first = currentNode->next;
			delete currentNode;
			size--;
		}
	}
}

Node* List::FindNode(int index)
{
	index++;
	if (index <= 0)
	{
		// Illegal index number
		return NULL;
	}
	int currentIndex = 1;
	Node*  currentNode = first;
	while (currentNode && index > currentIndex)
	{
		// Find Node and Node index
		currentNode = currentNode->next;
		currentIndex++;
	}
	if (index > 0 && currentNode == NULL)
	{
		// if index in range but currentNode still Null
		return NULL;
	}
	else
	{
		// You found it just return
		return currentNode;
	}
}

void List::Push(Data data)
{
	InsertNode(0, data);
}

Node* List::InsertNode(int index, Data data)
{
	if (index < 0)
	{
		return NULL;
	}
	int currentIndex = 1;
	Node* currentNode = first;
	while (currentNode && index > currentIndex)
	{
		currentNode = currentNode->next;
		currentIndex++;
	}
	if (index > 0 && currentNode == NULL)
	{
		return NULL;
	}
	//
	Node* newNode = new Node;
	newNode->data = data;
	if (index == 0)
	{
		// insert first
		newNode->next = first;
		first = newNode;
		size++;
	}
	else
	{
		newNode->next = currentNode->next;
		currentNode->next = newNode;
		size++;
	}
	return newNode;
}

void List::PrintAll()
{
	Node* currentNode = first;
	while (currentNode)
	{
		cout << currentNode->data.PrintRow();
		currentNode = currentNode->next;
	}
	cout << endl;
}

int List::CalculateList(int x, int y)
{
	int sum = 0;
	for (size_t i = 0; i < size; i++)
	{
		sum += FindNode(i)->data.CalculateNode(x, y);
	}
	return sum;
}

int main()
{
	cout << "Hello World!\n";
	//
	List test;
	Data d1(true, 2, 1, 3);
	Data d2(false, 3, 2, 4);
	Data d3(true, 10, 1, 1);
	cout << "is Empty: ";
	test.IsEmpty() == true ? cout << "yes" << endl : cout << "no" << endl;
	//
	test.Push(d1);
	cout << "is Empty: ";
	test.IsEmpty() == true ? cout << "yes" << endl : cout << "false" << endl;
	//
	test.PrintAll();
	test.Push(d2);
	//
	test.PrintAll();
	test.Push(d3);
	//
	cout << test.CalculateList(2, 4) << endl;
	//
	test.DeleteNode(1);
	test.PrintAll();
	//
	cout << test.CalculateList(2, 4) << endl;
	//
	cout << "END OF THE LINE";
}
//@JellyBeanci