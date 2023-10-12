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

class Solution {
    //Write your code here
    Stack<char> s_;    // my stack
    Queue<char> q_;    // my queue
public:
	void pushCharacter(char c) { s_.push(c); }
	char popCharacter() { return s_.pop(); }
	void enqueueCharacter(char c) { q_.enqueue(c); }
	char dequeueCharacter() { return q_.dequeue(); }
};

int main() {
    // read the string s.
    string s;
    getline(cin, s);
    
  	// create the Solution class object p.
    Solution obj;
    
    // push/enqueue all the characters of string s to stack.
    for (int i = 0; i < s.length(); i++) {
        obj.pushCharacter(s[i]);
        obj.enqueueCharacter(s[i]);
    }
    
    bool isPalindrome = true;
    
    // pop the top character from stack.
    // dequeue the first character from queue.
    // compare both the characters.
    for (int i = 0; i < s.length() / 2; i++) {
        if (obj.popCharacter() != obj.dequeueCharacter()) {
            isPalindrome = false;
            
            break;
        }
    }
    
    // finally print whether string s is palindrome or not.
    if (isPalindrome) {
        cout << "The word, " << s << ", is a palindrome.";
    } else {
        cout << "The word, " << s << ", is not a palindrome.";
    }
    
    return 0;
}
