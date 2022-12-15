/* 	Cesar Caballero
	z1944013	
	CS340 - 2
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.
*/

#ifndef STACK_H
#define STACK_H
#include <queue>

template<typename T>
class Stack
{
private:
    std::queue<T> q1;	// These queues are where the stack's elements 
    std::queue<T> q2;	// are to be saved.
    
public:
    bool empty() const;
    int size() const;
    const T& top();
    void push(const T &val);
    void pop();
};


// Note that the members of a template go into a .h file since 
// they are not compiled directly into a .o file like the members 
// of regular/non-template classes.




// Place your Stack class member implementations here.

//check if queue is empty returns true
template<typename T>
bool Stack<T>::empty() const
{
	if(q1.empty())
		return true;
	else
		return false;
}

//return total amount of numbers inside of queue 
template<typename T>
int Stack<T>::size() const
{
	return q1.size();
}

// return top value of stack (last value of queue)
template<typename T>
const T& Stack<T>::top()
{
	if(!q1.empty())
		return q1.front();
}

// add element into stack
template<typename T>
void Stack<T>::push(const T &val)
{
	q2.push(val); // add val to front of queue

	//loops through q1 adding each element into q2 temporarily and removing from q1 to keep it empty
	while(!q1.empty())
	{
		q2.push(q1.front());
		q1.pop();
	}	

	// swapping values of q2 and q1 by storing into another tempoarary queue 
	std::queue<T> temp_q = q1;
	q1 = q2;
	q2 = temp_q;
}

// remove element from the stack
template<typename T>
void Stack<T>::pop()
{
	if(q1.empty()) // wont do anything if trying to pop empty queue
		return;
	else
		q1.pop(); // remove value from queue
}
	

#endif // STACK_H
