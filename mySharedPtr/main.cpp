#include <iostream>
#include <vector>

using namespace std;

class counter {
public:
	counter() : m_counter(new int(1)) {}

	counter(const counter& c) {
		m_counter = c.m_counter;
		++*m_counter;
	}

	counter& operator=(const counter&) = delete;

	~counter() {
		if (--*m_counter == 0)
			delete m_counter;
	}

	bool only() {
		return *m_counter == 1;
	}

	int get() {
		return *m_counter;
	}

	bool assign(const counter& c) {
		++*c.m_counter;
		if (--*m_counter == 0) {
			delete m_counter;
			m_counter = c.m_counter;
			return true;
		}
		m_counter = c.m_counter;
		return false;
	}

	friend ostream& operator<<(ostream& os, const counter& counter)
	{
		return os << "Counter Value : "
			<< *(counter.m_counter) << endl;
	}

private:
	int* m_counter;
};

template<typename T>
class mySharedPtr {
public:
	explicit mySharedPtr(T* obj = nullptr) :
		m_obj(obj) {}

	mySharedPtr(const mySharedPtr<T>& mptr) : 
		m_obj(mptr.m_obj), 
		m_Counter(mptr.m_Counter) {}

	mySharedPtr& operator=(const mySharedPtr<T>& mptr) {
		if (m_Counter.assign(mptr.m_Counter))
			delete m_obj;
		m_obj = mptr.m_obj;
		return *this;
	}

	~mySharedPtr() {
		if (m_Counter.only()) {
			//delete m_pCounter;
			delete m_obj;
		}
	}

	T& operator*() {
		return *m_obj;
	}

	T* operator->() {
		return m_obj;
	}

	int use_count() {
		return m_Counter.get();
	}

	friend ostream& operator<<(ostream& os, mySharedPtr<T>& sp)
	{
		return os << sp.use_count() << endl;
	}

private:
	T* m_obj;
	counter m_Counter;
};

//#include <iostream> 
//using namespace std;
//
//// Class representing a reference counter class 
//class Counter {
//public:
//	// Constructor 
//	Counter()
//		: m_counter(0) {};
//
//	Counter(const Counter& c) :
//		m_counter(c.m_counter) {
//			++m_counter;
//	}
//	Counter& operator=(const Counter&) = delete;
//
//	// Destructor 
//	~Counter()
//	{
//	}
//
//	void reset()
//	{
//		m_counter = 0;
//	}
//
//	unsigned int get()
//	{
//		return m_counter;
//	}
//
//	// Overload post/pre increment 
//	void operator++()
//	{
//		m_counter++;
//	}
//
//	void operator++(int)
//	{
//		m_counter++;
//	}
//
//	// Overload post/pre decrement 
//	void operator--()
//	{
//		m_counter--;
//	}
//	void operator--(int)
//	{
//		m_counter--;
//	}
//
//	// Overloading << operator 
//	friend ostream& operator<<(ostream& os, const Counter& counter)
//	{
//		return os << "Counter Value : "
//			<< counter.m_counter << endl;
//	}
//
//private:
//	unsigned int m_counter{};
//};
//
//// Class representing a shared pointer 
//template <typename T>
//
//class Shared_ptr {
//public:
//	// Constructor 
//	explicit Shared_ptr(T* ptr = nullptr)
//	{
//		m_ptr = ptr;
//		m_counter = new Counter();
//		if (ptr) {
//			(*m_counter)++;
//		}
//	}
//
//	// Copy constructor 
//	Shared_ptr(Shared_ptr<T>& sp)
//	{
//		m_ptr = sp.m_ptr;
//		m_counter = sp.m_counter;
//		(*m_counter)++;
//	}
//
//	// Reference count 
//	unsigned int use_count()
//	{
//		return m_counter->get();
//	}
//
//	// Get the pointer 
//	T* get()
//	{
//		return m_ptr;
//	}
//
//	// Overload * operator 
//	T& operator*() {
//		return *m_ptr;
//	}
//
//	// Overload -> operator 
//	T* operator->() {
//		return m_ptr;
//	}
//	// Destructor 
//	~Shared_ptr()
//	{
//		(*m_counter)--;
//		if (m_counter->get() == 0) {
//			delete m_counter;
//			delete m_ptr;
//		}
//	}
//
//	friend ostream& operator<<(ostream& os, Shared_ptr<T>& sp)
//	{
//		return os << "Address pointed : "
//			<< sp.get() << *(sp.m_counter) << endl;
//	}
//
//private:
//	// Reference counter 
//	Counter* m_counter;
//
//	// Shared pointer 
//	T* m_ptr;
//};
//

int main() {
	mySharedPtr<int> ptr1(new int(151));
	cout << "--- Shared pointers ptr1 ---\n";
	*ptr1 = 100;
	cout << " ptr1's value now: " << *ptr1 << endl;
	cout << ptr1;

	{
		// Shared pointer reference counter 
		// should have increased now to 2. 
		mySharedPtr<int> ptr2 = ptr1;
		cout << "--- Shared pointers ptr1, ptr2 ---\n";
		cout << ptr1;
		cout << ptr2;
		{
			// Shared pointer reference counter 
			// should have increased now to 3. 
			mySharedPtr<int> ptr3(ptr2);
			cout << "--- Shared pointers ptr1, ptr2, ptr3 ---\n";
			cout << ptr1;
			cout << ptr2;
			cout << ptr3;
		}

		// ptr3 is out of scope. 
		// It would have been destructed. 
		// So shared pointer reference counter 
		// should have decreased now to 2. 
		cout << "--- Shared pointers ptr1, ptr2 ---\n";
		cout << ptr1;
		cout << ptr2;
	}

	// ptr2 is out of scope. 
	// It would have been destructed. 
	// So shared pointer reference counter 
	// should have decreased now to 1. 
	cout << "--- Shared pointers ptr1 ---\n";
	cout << ptr1;
	return 0;

}