#include <iostream>

template<typename T>
class Stack;

template<typename T>
class Queue;

template<typename T>
class Node
{
	T value;
	Node *prev;
	Node *next;
	friend class Stack<T>;
	friend class Queue<T>;
public:
	Node(T val, Node *prev_ = nullptr, Node *next_ = nullptr)
		: value(val), prev(prev_), next(next_) {}
};

template<typename T>
class Stack
{
	Node<T> *top;
public:
	Node<T> *push(const T &val) {
		// new node points backward to the former top
		Node<T> *np = new Node<T>(val, top, nullptr);
		top = np;
		return top;
	}
	Node<T> *push(T &&val) {    // r-value method (c++11)
		// new node points backward to former top
		Node<T> *np = new Node<T>(val, top, nullptr);
		top = np;
		return top;
	}				
	bool empty() { return top == nullptr; }
	/** pop: @pre !empty() */
	T pop() {
		T val = std::move(top->value);
		Node<T> *expiring = top;
		top = top->prev;
		delete expiring;
		return val;
	}
	/** debug method */	
	void print() {
		Node<T> *p = top;
		while (p != nullptr) { 
			std::cout << p->value << "->";
			p = p->prev;
		};
		std::cout << "(base)\n";
	}
	
	/** constructor: creates an empty stack */
	Stack() : top(nullptr) {}
	/** destructor */
	~Stack() {
		Node<T> *p = top, *expiring;
		while (p != nullptr) { 
			expiring = p;
			p = p->prev;
			delete expiring;
			expiring = nullptr;
		};
	}
};

template<typename T>
class Queue
{
	Node<T> *head, *tail;
public:
	Node<T> *enqueue(const T &val) {
		// new node is pointed by the former tail
		Node<T> *np = new Node<T>(val, tail, nullptr);
		if (tail != nullptr) {
			tail->next = np;
		}
		tail = np;
		if (head == nullptr) head = tail;
		return tail;
	}
	Node<T> *enqueue(T &&val) {    // r-value method (c++11)
		// new node is pointed by the former tail
		Node<T> *np = new Node<T>(val, tail, nullptr);
		if (tail != nullptr) {
			tail->next = np;
		}
		tail = np;
		if (head == nullptr) head = tail;
		return tail;
	}
	
	bool empty() { return head == nullptr; }
	/** dequeue: @pre !empty() */
	T dequeue() {
		T val = std::move(head->value);
		Node<T> *expiring = head;
		if (head != tail) {
			head = head->next;
			head->prev = nullptr;
		} else {
			// queue had a single element before removing
			head = tail = nullptr;
		}
		delete expiring;
		return val;
	}
	/** debug method */	
	void print() {
		Node<T> *p = head;
		while (p != nullptr) { 
			std::cout << p->value << "->";
			p = p->next;
		};
		std::cout << "(end)\n";
	}
	
	/** constructor: creates an empty stack */
	Queue() : head(nullptr), tail(nullptr) {}
	/** destructor */
	~Queue() {
		Node<T> *p = head, *expiring;
		while (p != nullptr) { 
			expiring = p;
			p = p->next;
			delete expiring;
			expiring = nullptr;
		};
	}
};

using namespace std;
int main() 
{
	Node<int> *np = new Node<int>(3, nullptr, nullptr);
	int val;	
		
	Stack<int> s;
	s.print();
	s.push(1); s.print();
	s.push(2); s.print();
	s.push(3); s.print();
	s.push(4); s.print();

	while (!s.empty()) {
		val = s.pop(); cout << "poped: " << val << '\n'; s.print();	
	}
	
	cout << '\n';
	
	Queue<int> q;
	q.print();
	q.enqueue(1); q.print();
	q.enqueue(2); q.print();
	q.enqueue(3); q.print();
	q.enqueue(4); q.print();

	while (!q.empty()) {
		val = q.dequeue(); cout << "dequeued: " << val << '\n'; q.print();
	}
	return 0;
}
