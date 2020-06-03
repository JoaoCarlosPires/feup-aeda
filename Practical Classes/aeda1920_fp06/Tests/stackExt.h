# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};


template <class T> 
bool StackExt<T>::empty() const
{
	return this->empty();
}


template <class T> 
T& StackExt<T>::top()
{
    return this->top();
}


template <class T> 
void StackExt<T>::pop()
{
    this->pop();
}


template <class T> 
void StackExt<T>::push(const T & val)
{
    this->push(val);
}

template <class T> 
T& StackExt<T>::findMin()
{
    StackExt<T> aux;
    T value = this->top();
    this->pop();
    while (!this->empty()) {
        if (this->top() < value) {
            value = this->top();
        }
        aux.push(this->top());
        this->pop();
    }
    while(!aux.empty()) {
        this->push(aux.top());
        aux.pop();
    }
    return value;
}

