
/**
 * TODO: Complete this class!
 */

 /// Your welcome
#include <assert.h>
#include <iostream>
#include <string>


//
template <typename T>
class MyVector
{
public:

	/*******************
	 * Static constants
	 ******************/

	 /// Default capacity
	static constexpr size_t DEFAULT_CAPACITY = 64;

	/// Minimum capacity
	static constexpr size_t MINIMUM_CAPACITY = 8;

	/*****************************
	 * Constructors / Destructors
	 ****************************/

	 /// Normal constructor
	MyVector(size_t capacity = MyVector::DEFAULT_CAPACITY) {

		// TODO: Your code here
		if (capacity < MINIMUM_CAPACITY) {
			capacity = MINIMUM_CAPACITY;
		}

		capacity_ = capacity;
		size_ = 0;
		elements_ = new T[capacity_];
	}

	/// Copy constructor
	MyVector(const MyVector& other) {

		// TODO: Your code here
		elements_ = nullptr;
		copyOther(other);
	}

	/**
	 * Destructor
	 * Should call clear() so each element gets its destructor called.
	 * Then, de-allocate the internal array and make it a nullptr, if its not already a nullptr.
	 */
	~MyVector() {

		// TODO: Your code here
		clear();
		if (elements_ != nullptr) {
			delete[] elements_;
			elements_ = nullptr;
		}
	}

	/************
	 * Operators
	 ************/

	 ///	Assignment operator
	MyVector& operator=(const MyVector& rhs) {

		// TODO: Your code here
		if (this != &rhs) {
			clear();
			copyOther(rhs); 
		}
		return *this;
	}

	/// Operator overload to at()
	T& operator[](size_t index) const {

		// TODO: Your code here
		return at(index);
	}

	/************
	 * Accessors
	 ************/

	 /// Return the number of valid elements in our data
	size_t size() const {

		// TODO: Your code here
		return size_;
	}

	/// Return the capacity of our internal array
	size_t capacity() const {

		// TODO: Your code here
		return capacity_;
	}

	/**
	 * Check whether our vector is empty
	 * Return true if we have zero elements in our array (regardless of capacity)
	 * Otherwise, return false
	 */
	bool empty() const {

		// TODO: Your code here
		return size_ == 0;
	}

	/// Return a reference to the element at an index
	T& at(size_t index) const {

		// TODO: Your code here
		if (index < 0 || index >= size_) {
			throw std::range_error("");
		}
		return elements_[index];
	}

	/***********
	 * Mutators
	 ***********/

	 /**
	  * Reserve capacity in advance, if our capacity isn't currently large enough.
	  * Useful if we know we're about to add a large number of elements, and we'd like to avoid the overhead of many internal changes to capacity.
	  */
	void reserve(size_t capacity) {

		// TODO: Your code here
		if (capacity_ < capacity) {
			changeCapacity(capacity);
		}
	}

	/**
	 * Set an element at an index.
	 * Throws range error if outside the size boundary.
	 * Returns a reference to the newly set element (not the original)
	 */
	T& set(size_t index, const T& element) {

		// TODO: Your code here
		if (index < 0 || index >= size_) {
			throw std::range_error("");
		}

		if (&(elements_[index]) != &element) {
			elements_[index].~T();
		}

		elements_[index] = element;
		return elements_[index];
	}

	/**
	 * Add an element onto the end of our vector, increasing the size by 1
	 * Should rely on the insert() function to avoid repeating code.
	 * Returns a reference to the newly inserted element
	 */
	T& push_back(const T& element) {

		// TODO: Your code here
		return insert(size_, element);
	}

	/**
	 * Remove the last element in our vector, decreasing the size by 1
	 * Should rely on the erase() function to avoid repeating code.
	 * Returns the new size.
	 */
	size_t pop_back() {

		// TODO: Your code here
		return erase(size_ - 1);
	}

	/**
	 * Insert an element at some index in our vector, increasing the size by 1
	 *
	 * Scoot all elements at index and beyond, one to the right. This
	 * makes a "hole" available at the index, where you can then place
	 * the new element.
	 *
	 * Returns a reference to the newly added element (not the original).
	 */
	T& insert(size_t index, const T& element) {

		// TODO: Your code here
		if (index < 0 || index > size_) {
			throw std::range_error("");
		}

		if (index == size_ && size_ == capacity_) {
			changeCapacity(capacity_ * 2);
		}

		for (size_t i = size_; i > index; i--) {
			elements_[i] = elements_[i - 1];
		}

		elements_[index] = element;
		++size_;
		return elements_[index];
	}

	/**
	 * Erase one element in our vector at the specified index, decreasing the size by 1.
	 *
	 * This means you'd then have to scoot elements to the left to fill the "hole"
	 * 	left by the erased element.
	 *
	 * Throws std::range_error if the index is out of bounds.
	 *
	 * Calls the erased element's destructor.
	 *
	 * Returns the new size.
	 */
	size_t erase(size_t index) {

		// TODO: Your code here
		if (index < 0 || index >= size_) {
			throw std::range_error("");
		}

		if (size_ * 3 < capacity_ && capacity_ / 2 >= MINIMUM_CAPACITY) {
			changeCapacity(capacity_ / 2);
		}

		elements_[index].~T();
		for (size_t i = index + 1; i < size_; ++i) {
			elements_[i - 1] = elements_[i];
			elements_[i].~T();
		}
		--size_;
		return size_;
	}

	/**
	 * Calls each element's destructor, then clears our internal
	 * data by setting size to zero and resetting the capacity.
	*/
	void clear() {

		// TODO: Your code here
		for (size_t i = 0; i < size_; ++i) {
			elements_[i].~T();
		}

		delete[] elements_;
		size_ = 0;
		capacity_ = MINIMUM_CAPACITY;
		elements_ = new T[capacity_];
	}

	/**
	 * Begin private members and methods.
	 * Private methods can often contain useful helper functions,
	 * or functions to reduce repeated code.
	*/
private:

	/// Number of valid elements currently in our vector
	size_t size_ = 0;

	/// Capacity of our vector; The actual size of our internal array
	size_t capacity_ = 0;

	/**
	 * Our internal array of elements of type T.
	 * Starts off as a null pointer.
	 */
	T* elements_ = nullptr;

	/**
	 * Helper function that is called whenever we need to change the capacity of our vector
	 * Should throw std::range_error when asked to change to a capacity that cannot hold our existing elements.
	 * It's probably a good idea to make an additional helper function that decides
	 * 	whether to change capacity at all (and to what new capacity), that your public functions can rely upon.
	 */
	void changeCapacity(size_t c) {

		// TODO: Your code here
		if (c < size_) {
			throw std::range_error("");
		}

		capacity_ = c;
		T* old = elements_;
		elements_ = new T[capacity_];
		for (size_t i = 0; i < size_; ++i) {
			elements_[i] = old[i];
			old[i].~T();
		}

		delete[] old;
	}

	/**
	 * Copy another vector's elements into our own, by value.
	 * Does not simply copy the other vector's array's pointer
	 * Does not care about matching the capacity exactly.
	 * This is a helper function relied upon by the copy constructor and the assignment operator,
	 * 	to avoid repeated code.
	 *
	 * You will probably want to make additional helper functions to make this one easier.
	 * Here is a suggested strategy for copying the internal array:
	 * 1. Deallocate the current array for 'this' (if it is already allocated)
	 * 2. Allocate a new array for 'this' of the appropriate size
	 * 3. Use a loop to copy elements one-by-one (by value)
	 * 4. Copy other relevant properties from the 'other' to 'this'
	 */
	void copyOther(const MyVector& other) {

		// TODO: Your code here
		if (elements_ != nullptr) {
			delete[] elements_;
		}

		elements_ = new T[other.capacity_];
		for (size_t i = 0; i < other.size_; ++i) {
			elements_[i] = other.elements_[i];
		}
		
		capacity_ = other.capacity_;
		size_ = other.size_;
	}
};


