#ifndef MY_DOUBLY_LINKED_LIST_HPP
#define MY_DOUBLY_LINKED_LIST_HPP


/**
 * TODO: Implement DoublyLinkedList, its Node, and its Iterator!
 * 
 * I've left some methods filled out for you,
 * 	and stubbed out some structure, to reduce difficulty.
 * 
 * You may add or remove methods as you see fit,
 * 	as long as you can still pass all unit tests.
 * Although, it may be more difficult to do so. Your choice!
 * 
 * Notice we're inside a namespace here.
 * The DLL is inside a namespace called DoublyLinkedList,
 * 	which is itself inside a namespace called CPSC131
 * This means, if you'd like to play around with your class later,
 * 	you'll need to access it like so:
 * ::CPSC131::DoublyLinkedList::DoublyLinkedList<int> list;
 * 
 * Look into main.cpp and CPP_Tests.cpp for examples of using
 * 	the DLL and your BookStore. But don't worry too much, as you
 * 	only need to implement these classes
 * (main and tests are already done for you)
 */


//
#include <iostream>
#include <stdlib.h>
#include <stdexcept>


/**
 * Namespace for our classroom !
 */
namespace CPSC131
{
	/**
	 * Namespace to hold all things related to our DLL
	 */
	namespace DoublyLinkedList
	{
		/**
		 * Node class, which our DLL will use
		 * 
		 * The Professor realizes he could have made this an inline class (like the Iterator),
		 * but he is lazy.
		 */
		template <class T>
		class Node
		{
			public:
				
				/// CTORS
				Node() : prev_(nullptr), next_(nullptr) 
                {      
                }

				Node(T element)
                {
                    element_ = element;
                    prev_ = nullptr;
                    next_ = nullptr;
                }

                ~Node()
                {
                    prev_ = nullptr;
                    next_ = nullptr;
                }

				Node(T element, Node* prev, Node* next)
                {
                    element_ = element;
                    prev_ = prev;
                    next_ = next;
                }

				/// Set the pointer to the previous element
				void setPrevious(Node* prev)
                {
                    prev_ = prev;
                }
				
				/// Set the pointer to the previous element
				void setPrev(Node* prev)
                {
                    prev_ = prev;
                }
				
				/// Get a pointer to the previous element
				Node* getPrevious() 
                {
                    return prev_;
                }
				
				/// Get a pointer to the previous element
				Node* getPrev() 
                {
                    return prev_;
                }
				
				/// Set the pointer to the next node
				void setNext(Node* next) 
                {
                    next_ = next;
                }

				/// Get a pointer to the next node
				Node* getNext()
                {
                    return next_;
                }
				
				/// Set the element this node holds
				void setElement(T element)
                {
                    element_ = element;
                }
				
				/// Get the element this node holds
				T& getElement()
                {
                    return element_;
                }
				
				/// Return a reference to the element
				T& operator*()
                {
                    return element_;
                }
				
			private:
				T element_;
				Node* prev_;
				Node* next_;
		};
		
		/**
		 * Implement our DoublyLinkedList class !
		 */
		template <class T>
		class DoublyLinkedList
		{
			public:
				
				/**
				 * Nested Iterator class.
				 * This allows user code to refer to the Iterator's type as:
				 * 
				 * CPSC131::DoublyLinkedList::DoublyLinkedList<int>::Iterator
				 * 
				 * (as opposed to specifying the template argument two times)
				 */
				class Iterator
				{
					public:
						
						///	Constructor taking a head and tail pointer; YOUR WELCOME
						Iterator(Node<T>* head, Node<T>* tail) : head_(head), tail_(tail)
                        {
                            cursor_ = head_;
                        }

						// Default constructor
						Iterator() : head_(nullptr), tail_(nullptr), cursor_(nullptr)
						{}

						///	Constructor taking a head, tail, and cursor pointer; YOUR WELCOME
						Iterator(Node<T>* head, Node<T>* tail, Node<T>* cursor) : head_(head), tail_(tail), cursor_(cursor)
                        {}

						///	Get a pointer to the head node, or end() if this list is empty
						Node<T>* begin()
						{
							return head_;
						}

						// set cursor
						void setCursor(Node<T>* cursor)
						{
							cursor_ = cursor;
						}

						
						///	Get a node pointer representing "end" (aka "depleted"). Probably want to just use nullptr.
						Node<T>* end()
						{
							return tail_;
						}
						
						
						///	Get the node to which this iterator is currently pointing
						Node<T>* getCursor()
						{
							return cursor_;
						}
						
						/**
						 * Assignment operator
						 * Return a copy of this Iterator, after modification
						 */
						Iterator& operator=(const Iterator& other)
						{
							if (this != &other)
							{
								head_ = other.head_;
								tail_ = other.tail_;
								cursor_ = other.cursor_;
							}
							return *this;
						}
						
						///	Comparison operator
						bool operator==(const Iterator& other)
						{
							if (head_ == other.head_ && tail_ == other.tail_ 
							&& cursor_ == other.cursor_)
							{
								return true;
							}
							else
							{
								return false;
							}
						}
						
						///	Inequality comparison operator
						bool operator!=(const Iterator& other)
						{
							if (head_ != other.head_ || tail_ != other.tail_ || cursor_ != other.cursor_)
							{
								return true;
							}
							else
							{
								return false;
							}
						}
						
						/**
						 * Prefix increment operator
						 * Return a copy of this Iterator, after modification
						 */
						Iterator& operator++()
						{
							if (cursor_ != nullptr)
							{
								cursor_ = cursor_->getNext();
							}
							return *this;
						}
						
						/**
						 * Postfix increment
						 * Return a copy of this Iterator, BEFORE it was modified
						 */
						Iterator operator++(int)
						{
							Iterator temp = *this;
							if (cursor_ != nullptr)
							{
								cursor_ = cursor_->getNext();
							}
							return temp;
						}
						
						/**
						 * Prefix decrement operator
						 * Return a copy of this Iterator, after modification
						 */
						Iterator& operator--()
						{
							if (cursor_ != nullptr)
							{
								cursor_ = cursor_->getPrev();
							}
							return *this;
						}
						
						/**
						 * Postfix decrement operator
						 * Return a copy of this Iterator BEFORE it was modified
						 */
						Iterator operator--(int)
						{
							if (cursor_ != nullptr)
							{
								cursor_ = cursor_->getPrev();
							}
							else
							{
								cursor_ = tail_;
							}
							return *this;
						}
						
						/**
						 * AdditionAssignment operator
						 * Return a copy of the current iterator, after modification
						*/
						Iterator operator +=(size_t add)
						{
							if (cursor_ != nullptr)
							{
								for (size_t i = 0; i < add; i++)
								{
									if (cursor_ != nullptr)
									{
										cursor_ = cursor_->getNext();
									}
									else
									{
                                        cursor_ = nullptr;
									}
								}
							}
							return *this;
						}

						/**
						 * SubtractionAssignment operator
						 * Return a copy of the current iterator, after modification
						 */
						Iterator operator -=(size_t add)
						{
							if (cursor_ != nullptr)
							{
								for (size_t i = 0; i < add; i++)
								{
									if (cursor_ != nullptr)
									{
										cursor_ = cursor_->getPrev();
									}
									else
									{
										cursor_ = nullptr;
									}
								}
							}
							return *this;
						}
						
						/**
						 * AdditionAssignment operator, supporting positive or negative ints
						 */
						Iterator operator +=(int add)
						{
							if (cursor_ != nullptr)
							{
								if (add > 0)
								{
									for (int i = 0; i < add; i++)
									{
										if (cursor_ != nullptr)
										{
											cursor_ = cursor_->getNext();
										}
										else
										{
											cursor_ = nullptr;
										}
									}
								}
								else
								{
									for (int i = 0; i > add; i--)
									{
										if (cursor_ != nullptr)
										{
											cursor_ = cursor_->getPrev();
										}
										else
										{
											cursor_ = nullptr;
										}
									}
								}
							}
							return *this;
                        }
						
						/**
						 * SubtractionAssignment operator, supporting positive or negative ints
						 */
						Iterator operator -=(int subtract)
						{
							if (cursor_ != nullptr)
							{
								if (subtract > 0)
								{
									for (int i = 0; i < subtract; i++)
									{
										if (cursor_ != nullptr)
										{
											cursor_ = cursor_->getPrev();
										}
										else
										{
											cursor_ = nullptr;
										}
									}
								}
								else
								{
									for (int i = 0; i > subtract; i--)
									{
										if (cursor_ != nullptr)
										{
											cursor_ = cursor_->getNext();
										}
										else
										{
											cursor_ = nullptr;
                                        }
									}
								}
							}
							return *this;
						}
						
						/**
						 * Dereference operator returns a reference to the ELEMENT contained with the current node
						 */
						T& operator*()
						{
							if (cursor_ != nullptr)
							{
								return cursor_->getElement();
							}
							else
							{
                                return head_->getElement();
							}
						}
					
					private:
						
						/// Pointer to the head node
						Node<T>* head_ = nullptr;
						
						/// Pointer to the tail node
						Node<T>* tail_ = nullptr;
						
						/**
						 * Pointer to the cursor node.
						 * This is only one way of letting the iterator traverse the linked list.
						 * You can change to a different method if you wish (and can still pass unit tests)
						 */
						Node<T>* cursor_ = nullptr;
						
					
					friend class DoublyLinkedList;
				};
								
				/// Your welcome
				DoublyLinkedList()
				{
					this->head_ = nullptr;
					this->tail_ = nullptr;
					this->size_ = 0;
				}
				
				///	Copy Constructor
				DoublyLinkedList(DoublyLinkedList& other)
				{
					if (this == &other)
					{
						return;
					}

					if (other.head_ == nullptr)
					{
						this->clear();
					}
					else
					{
						this->head_ = new Node<T>(other.head_->getElement());
						this->tail_ = this->head_;
						this->size_ = 1;
						Node<T>* temp = other.head_->getNext();
						while (temp != nullptr)
						{
							this->tail_->setNext(new Node<T>(temp->getElement()));
							this->tail_->getNext()->setPrev(this->tail_);
							this->tail_ = this->tail_->getNext();
							temp = temp->getNext();
							this->size_++;
						}
					}
				}
				
				
				/// DTOR: Your welcome
				~DoublyLinkedList()
				{
					this->clear();
				}
				
				/**
				 * Clear the list and assign the same value, count times.
				 * If count was 5, T was int, and value was 3,
				 * 	we'd end up with a list like {3, 3, 3, 3, 3}
				 */
				void assign(size_t count, const T& value)
				{
					this->clear();
					for (size_t i = 0; i < count; i++)
					{
						this->push_back(value);
					}
				}

				
				/**
				 * Clear the list and assign values from another list.
				 * The 'first' iterator points to the first item copied from the other list.
				 * The 'last' iterator points to the last item copied from the other list.
				 * 
				 * Example:
				 * 	Suppose we have a source list like {8, 4, 3, 2, 7, 1}
				 * 	Suppose first points to the 4
				 *	Suppose last points to the 7
				 * 	We should end up with our list becoming: {4, 3, 2, 7}
				 *
				 * If the user code sends out-of-order iterators,
				 * 	just copy from 'first' to the end of the source list
				 * Example: first=7, last=4 from the list above would give us:
				 * 	{7, 1}
				 */
				void assign(Iterator first, Iterator last)
				{
					this->clear();
					while (first != last)
					{
						this->push_back(*first);
						first++;
					}
				}
				
				/// Return a pointer to the head node, if any
				Node<T>* head()
				{
					return this->head_;
				}
				
				/// Return a pointer to the tail node, if any
				Node<T>* tail()
				{
					return this->tail_;
				}
				
				/**
				 * Return an iterator that points to the head of our list
				 */
				Iterator begin()
				{
					return Iterator(this->head_, this->tail_, this->head_);
				}
				
				/**
				 * Return an iterator that points to the last element (tail) of our list
				 */
				Iterator last()
				{
					return Iterator(this->head_, this->tail_, this->tail_);
				}
				
				/**
				 * Should return an iterator that represents being past the end of our nodes,
				 * or just that we are finished.
				 * You can make this a nullptr or use some other scheme of your choosing,
				 * 	as long as it works with the logic of the rest of your implementations.
				 */
				Iterator end()
				{
					return Iterator(this->head_, this->tail_, nullptr);
				}
				
				/**
				 * Returns true if our list is empty
				 */
				bool empty() const
				{
					if (this->head_ == nullptr)
					{
						return true;
					}
					return false;
				}
				
				/**
				 * Returns the current size of the list
				 * Should finish in constant time!
				 * (keep track of the size elsewhere)
				 */
				size_t size() const
				{
					return this->size_;
				}
				
				/**
				 * Clears our entire list, making it empty
				 * Remember: All removal operations should be memory-leak free.
				 */
				void clear()
				{
					if (this->head_ == nullptr)
					{
						return;
					}
					Node<T>* temp = this->head_;
					Node<T>* previous = nullptr;
					while (temp != nullptr)
					{
						previous = temp;
						temp = temp->getNext();
						delete previous;
					}
					this->head_ = nullptr;
					this->tail_ = nullptr;
					this->size_ = 0;
				}
				
				/**
				 * Insert an element after the node pointed to by the pos Iterator
				 * 
				 * If the list is currently empty,
				 * 	ignore the iterator and just make the new node at the head/tail (list of length 1).
				 * 
				 * If the incoming iterator is this->end(), insert the element at the tail
				 * 
				 * Should return an iterator that points to the newly added node
				 * 
				 * To avoid repeated code, it might be a good idea to have other methods
				 * 	rely on this one.
				 */
				Iterator insert_after(Iterator pos, const T& value)
				{
					if (this->head_ == nullptr)
					{
						this->head_ = new Node<T>(value);
						this->tail_ = this->head_;
						this->size_ = 1;
						return Iterator(this->head_, this->tail_, this->head_);
					}
					if (pos == this->end())
					{
						this->tail_->setNext(new Node<T>(value));
						this->tail_->getNext()->setPrev(this->tail_);
						this->tail_ = this->tail_->getNext();
						this->size_++;
						return Iterator(this->head_, this->tail_, this->tail_);
					}
					Node<T>* temp = pos.getCursor();
					temp->setNext(new Node<T>(value, temp, temp->getNext()));
					if (temp->getNext()->getNext() != nullptr)
					{
						temp->getNext()->getNext()->setPrev(temp->getNext());
					}
					else
					{
						this->tail_ = temp->getNext();
					}
					this->size_++;
					return Iterator(this->head_, this->tail_, temp->getNext());
				}
				
				/**
				 * Insert a new element after the index pos.
				 * Should work with an empty list.
				 * 
				 * Should return an iterator pointing to the newly created node
				 * 
				 * To reduce repeated code, you may want to simply find
				 * 	an iterator to the node at the pos index, then
				 * 	send it to the other overload of this method.
				*/
				Iterator insert_after(size_t pos, const T& value)
				{
					if (this->head_ == nullptr)
					{
						this->head_ = new Node<T>(value);
						this->tail_ = this->head_;
						this->size_ = 1;
						return Iterator(this->head_, this->tail_, this->head_);
					}
					if (pos >= this->size_)
					{
						this->tail_->setNext(new Node<T>(value));
						this->tail_->getNext()->setPrev(this->tail_);
						this->tail_ = this->tail_->getNext();
						this->size_++;
						return Iterator(this->head_, this->tail_, this->tail_);
					}
					Node<T>* temp = this->head_;
					for (size_t i = 0; i < pos; i++)
					{
						temp = temp->getNext();
					}
					temp->setNext(new Node<T>(value, temp, temp->getNext()));
					if (temp->getNext()->getNext() != nullptr)
					{
						temp->getNext()->getNext()->setPrev(temp->getNext());
					}
					else
					{
						this->tail_ = temp->getNext();
					}
					this->size_++;
					return Iterator(this->head_, this->tail_, temp->getNext());
				}
				
				/**
				 * Erase the node pointed to by the Iterator's cursor.
				 * 
				 * If the 'pos' iterator does not point to a valid node,
				 * 	throw an std::range_error
				 * 
				 * Return an iterator to the node AFTER the one we erased,
				 * 	or this->end() if we just erased the tail
				 */
				Iterator erase(Iterator pos)
				{
					if (pos == this->end())
					{
						throw std::range_error("Iterator does not point to a valid node");
					}
					if (pos == this->begin())
					{
						this->head_ = this->head_->getNext();
						delete pos.getCursor();
						this->size_--;
						return Iterator(this->head_, this->tail_, this->head_);
					}
					if (pos == this->end())
					{
						this->tail_ = this->tail_->getPrev();
						delete pos.getCursor();
						this->size_--;
						return Iterator(this->head_, this->tail_, this->tail_);
					}
					Node<T>* temp = pos.getCursor();
					temp->getPrev()->setNext(temp->getNext());
					temp->getNext()->setPrev(temp->getPrev());
					delete temp;
					this->size_--;
					return Iterator(this->head_, this->tail_, pos.getCursor()->getNext());
				}
				
				/**
				 * Add an element just after the one pointed to by the 'pos' iterator
				 * 
				 * Should return an iterator pointing to the newly created node
				 */
				Iterator push_after(Iterator pos, const T& value)
				{
					if (pos == this->end())
					{
						this->tail_->setNext(new Node<T>(value));
						this->tail_->getNext()->setPrev(this->tail_);
						this->tail_ = this->tail_->getNext();
						this->size_++;
						return Iterator(this->head_, this->tail_, this->tail_);
					}
					Node<T>* temp = pos.getCursor();
					temp->setNext(new Node<T>(value, temp, temp->getNext()));
					if (temp->getNext()->getNext() != nullptr)
					{
						temp->getNext()->getNext()->setPrev(temp->getNext());
					}
					else
					{
						this->tail_ = temp->getNext();
					}
					this->size_++;
					return Iterator(this->head_, this->tail_, temp->getNext());
				}
				
				/**
				 * Add a new element to the front of our list.
				 */
				void push_front(const T& value)
				{
					if (this->head_ == nullptr)
					{
						this->head_ = new Node<T>(value);
						this->tail_ = this->head_;
						this->size_ = 1;
					}
					else
					{
						this->head_->setPrev(new Node<T>(value, nullptr, this->head_));
						this->head_ = this->head_->getPrev();
						this->size_++;
					}
				}
				
				/**
				 * Add an element to the end of this list.
				 * 
				 * Should return an iterator pointing to the newly created node.
				 */
				Iterator push_back(const T& value)
				{
					if (this->head_ == nullptr)
					{
						this->head_ = new Node<T>(value);
						this->tail_ = this->head_;
						this->size_ = 1;
						return Iterator(this->head_, this->tail_, this->head_);
					}
					this->tail_->setNext(new Node<T>(value));
					this->tail_->getNext()->setPrev(this->tail_);
					this->tail_ = this->tail_->getNext();
					this->size_++;
					return Iterator(this->head_, this->tail_, this->tail_);
				}
				
				/**
				 * Remove the node at the front of our list
				 * 
				 * Should throw an exception if our list is empty
				 */
				void pop_front()
				{
					if (this->head_ == nullptr)
					{
						throw std::range_error("List is empty");
					}
					if (this->head_ == this->tail_)
					{
						delete this->head_;
						this->head_ = nullptr;
						this->tail_ = nullptr;
						this->size_ = 0;
					}
					else
					{
						this->head_ = this->head_->getNext();
						delete this->head_->getPrev();
						this->head_->setPrev(nullptr);
						this->size_--;
					}
				}	
				
				/**
				 * Remove the node at the end of our list
				 * 
				 * Should throw an exception if our list is empty
				 */
				void pop_back()
				{
					if (this->head_ == nullptr)
					{
						throw std::range_error("List is empty");
					}
					if (this->head_ == this->tail_)
					{
						delete this->head_;
						this->head_ = nullptr;
						this->tail_ = nullptr;
						this->size_ = 0;
					}
					else
					{
						this->tail_ = this->tail_->getPrev();
						delete this->tail_->getNext();
						this->tail_->setNext(nullptr);
						this->size_--;
					}
				}
				
				/**
				 * Return a reference to the element at the front.
				 * 
				 * Throw an exception if the list is empty
				 */
				T& front()
				{
					if (this->head_ == nullptr)
					{
						throw std::range_error("List is empty");
					}
					return this->head_->getElement();	
				}
				
				/**
				 * Return a reference to the element at the back.
				 * 
				 * Throw an exception if the list is empty
				 */
				T& back()
				{
					if (this->head_ == nullptr)
					{
						throw std::range_error("List is empty");
					}
					return this->tail_->getElement();
				}
				
				/**
				 * Return the element at an index
				 * 
				 * Should throw a range_error is out of bounds
				 */
				T& at(size_t index)
				{
					if (index >= this->size_)
					{
						throw std::range_error("Index out of bounds");
					}
					Node<T>* temp = this->head_;
					for (size_t i = 0; i < index; i++)
					{
						temp = temp->getNext();
					}
					return temp->getElement();
				}
				
				/**
				 * Reverse the current list
				 * 
				 * It might be easy to consider the following:
				 * - Create a temp empty list
				 * - Iterate through the current list
				 * - For each item in the current list, push to the FRONT (not back)
				 * - Assign the current list to the temp list
				 * - Discard the temp list
				 */
				void reverse()
				{
					if (this->head_ == nullptr)
					{
						return;
					}
					Node<T>* temp = this->head_;
					this->head_ = this->tail_;
					this->tail_ = temp;
					while (temp != nullptr)
					{
						Node<T>* temp2 = temp->getNext();
						temp->setNext(temp->getPrev());
						temp->setPrev(temp2);
						temp = temp2;
					}
				}
				
				/**
				 * I bet you're happy I'm not making you do this.
				 * No tests will be run against this function,
				 * 	but feel free to try it out, as a challenge!
				 * 
				 * If I were doing this and didn't care too much for efficiency,
				 * 	I would probably create an extra helper function to swap two
				 * 	positions in the current list.
				 * Then I would simply sweep through the list and perform
				 *  the bubble-sort algorithm. Perhaps selection sort.
				 * 
				 * If you want a huge challenge, try implementing quicksort.
				 * 
				 * (but again, don't worry about this method; it will not be tested)
				 */
				void sort()
				{
					if (this->head_ == nullptr)
					{
						return;
					}
					Node<T>* temp = this->head_;
					while (temp != nullptr)
					{
						Node<T>* temp2 = temp->getNext();
						while (temp2 != nullptr)
						{
							if (temp->getElement() > temp2->getElement())
							{
								T temp3 = temp->getElement();
								temp->setValue(temp2->getElement());
								temp2->setValue(temp3);
							}
							temp2 = temp2->getNext();
						}
						temp = temp->getNext();
					}	
				}
				
				/**
				 * Assignment operator
				 * 
				 * Clear this list and fill it with the others' values
				 * (by value, not by reference)
				 * 
				 * Return a reference to this list
				 */
				DoublyLinkedList<T>& operator =(DoublyLinkedList<T>& other)
				{
					if (this == &other)
					{
						return *this;
					}
					this->clear();
					Node<T>* temp = other.head_;
					while (temp != nullptr)
					{
						this->push_back(temp->getElement());
						temp = temp->getNext();
					}
					return *this;
				}
				
				/**
				 * Return true if the lists are "equal"
				 * 
				 * "Equal" here is defined as:
				 * - Same size
				 * - Elements at the same indexes would return true for their own comparison operators
				 * 
				 * In other words: "They contain all the same values"
				 * (no need to be references to each other)
				 */
				bool operator ==(DoublyLinkedList<T>& other)
				{
					if (this->size_ != other.size_)
					{
						return false;
					}
					Node<T>* temp = this->head_;
					Node<T>* temp2 = other.head_;
					while (temp != nullptr)
					{
						if (temp->getElement() != temp2->getElement())
						{
							return false;
						}
						temp = temp->getNext();
						temp2 = temp2->getNext();
					}
					return true;
				}
				
				/**
				 * Return true if the lists are "not equal"
				 * 
				 * See the operator== stub for definition of "equal"
				 * 
				 * Probably want to avoid repeated code by relying on the other operator
				 */
				bool operator !=(DoublyLinkedList<T>& other)
				{
					return !(*this == other);
				}
				
			private:
				
				Node<T>* head_ = nullptr;
				Node<T>* tail_ = nullptr;
				size_t size_ = 0;
		};
	}
}

#endif

