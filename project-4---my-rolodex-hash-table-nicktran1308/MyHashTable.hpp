#ifndef MY_HASH_TABLE_HPP
#define MY_HASH_TABLE_HPP


/**
 * TODO: Complete this class!
 */

/// Your welcome
#include <forward_list>
#include <functional>
#include <memory>
#include <string>

//	More includes ... ?
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>
#include <algorithm>
#include <functional>
#include <initializer_list>
#include <memory>
#include <type_traits>



///	Begin our class namespace
namespace CPSC131::MyHashTable
{
	//
	template<class VTYPE>
	class MyHashTable
	{
		//
		public:
			
			//
			static constexpr size_t DEFAULT_CAPACITY = 1024;
			static constexpr size_t ULLONG_WRAP_AT = 4294967295;
			
			/**
			 * Constructor
			 * 
			 * Probably easiest to do the following:
			 * 
			 *   1. Call on setCapacity() to set the table_'s capacity
			 */
			MyHashTable(size_t capacity = MyHashTable::DEFAULT_CAPACITY)
            {
                if (capacity < 1)
                {
                    capacity = MyHashTable::DEFAULT_CAPACITY;
                }
				size_ = 0;
                n_collisions_ = 0;
                setCapacity(capacity);
            }

			
			/**
			 * Copy constructor
			 */
			MyHashTable(const MyHashTable& other)
            {
                if (other.table_ == nullptr)
                {
                    throw std::bad_alloc();
                }
                setCapacity(other.capacity());
                for (size_t i = 0; i < other.capacity(); i++)
                {
                    table_[i] = other.table_[i];
                }
                size_ = other.size();
                n_collisions_ = other.n_collisions();
            }
	
			
			/**
			 * Destructor
			 * 
			 * Deallocate the table_ (array of std::forward_list 's), and set the table_ to nullptr
			 * Don't double-deallocate if the table_ is already a null pointer
			 */
			~MyHashTable()
            {
                if (table_ != nullptr)
                {
                    delete[] table_;
                    table_ = nullptr;
                }
            }
		
			
			/**
			 * Should return the capacity_ of this hash table_
			 * Meaning, the total number of rows in this hash table_
			 * Doesn't discern between used/unused/collided rows
			 */
			size_t capacity() const
            {
                return capacity_;
            }
			
			
			/**
			 * Should return the number of items currently in the hash table_
			 */
			size_t size() const
            {
                return size_;
            }
			
			
			/**
			 * Return true if the table_ is empty, false otherwise
			 */
			bool empty() const
            {
                return size_ == 0;
            }
			
			
			/**
			 * Should return the number of collisions currently present in the hash table_
			 */
			size_t n_collisions() const
            {
                return n_collisions_;
                // int collisions = 0;
                // for (size_t i = 0; i < capacity_; i++)
                // {
                //     int size = 0;
                //     for (auto it = table_[i].begin(); it != table_[i].end(); it++)
                //     {
                //         size++;
                //     }
                //     if (size > 1)
                //     {
                //         collisions += size - 1;
                //     }
                // }
                // return collisions;
            }
			

			/**
			 * Set the capacity for this table_.
			 * Changes the total number of hash table_ rows available.
			 * 
			 * Existing entries should survive the change,
			 * 	so you probably want to do the following:
			 * 
			 *  1. Keep the existing table_ array pointer in a temporary pointer
			 *  
			 *  2. Re-initialize 'this' to contain a new empty table_ of the right capacity
			 *  
			 *  3. The temporary pointer should now contain the OLD data (old table_),
			 *     while 'this' contains the brand new table_ of the new size.
			 * 
			 *  4. Iterate through all key/value pairs in the old data (temp pointer).
			 * 
			 *  5. For each key/value pair in the old data, call this->add() to insert
			 *     properly into the new table_.
			 *  
			 *  6. Deallocate the old table_ by calling `delete []` on the temporary pointer.
			 * 
			 * Don't forget to check whether the current table_ is a nullptr before you
			 *  decide to do iterations!
			 */
			void setCapacity(size_t c)
            {
                if (c == 0)
				{
					c = MyHashTable::DEFAULT_CAPACITY;
				}
				if (table_ != nullptr)
				{
					std::forward_list<std::pair<std::string, VTYPE>>* temp = table_;
					table_ = new std::forward_list<std::pair<std::string, VTYPE>>[c];
					if (table_ == nullptr)
					{
						throw std::bad_alloc();
					}
                    size_t oldc = capacity_;
                    n_collisions_ = 0;
					capacity_ = c;
                    for (size_t i = 0; i < oldc; i++)
                    {
                        for (auto it = temp[i].begin(); it != temp[i].end(); it++)
                        {
                            add(it->first, it->second);
                        }
                    }
					
					delete[] temp;
				}
				else
				{
					table_ = new std::forward_list<std::pair<std::string, VTYPE>>[c];
					if (table_ == nullptr)
					{
						throw std::bad_alloc();
					}
					capacity_ = c;
				}
            }
			
			
			///	Your welcome
			unsigned long long int hash(std::string key) const
			{
				return midSquareHash(key);
			}
			
			/**
			 * Implement the "modified mid square" hash function,
			 * as described in the instructions.
			 */
			unsigned long long int midSquareHash(std::string key) const
            {
               // Start with sum = 1
               unsigned long long int sum = 1;
               // Iterate over each char in std::string
                for (size_t i = 0; i < key.length(); i++)
                {
                    sum *= key[i]; // multiply sum by value of current char
                    sum = sum % MyHashTable::ULLONG_WRAP_AT;// apply modulo to keep sum under control
                }
                unsigned long long int newhash = sum * sum; // multiply sum by itself
                std::string newhashstr = std::to_string(newhash);
                int len = newhashstr.length();
                int mid = len / 2;
                int start = mid / 2;
                // int end = start + mid;
                std::string newhashstrmid = newhashstr.substr(start, mid);
                unsigned long long int newhashmidint = std::stoull(newhashstrmid);
                return newhashmidint % capacity_;
            }
			
			
			/**
			 * Implement your own custom hash functions to compete on the Gradescope Leaderboard!
			 * Four stubs are provided to make experimentation a little easier.
			 * Only the best hash function will count towards the leaderboard.
			 */
			unsigned long long int myCustomHashFunction1(std::string key) const
			{
				if (key.empty()) {
                    return 0;
                }

                    const unsigned long long int prime1 = 31; 
                    const unsigned long long int prime2 = 37; 
                    const unsigned long long int factor = 11; 
                    unsigned long long int hash = 0;

                    for (char c : key) {
                        hash += c * prime1;
                        hash ^= (hash >> 15) + factor; 
                        hash *= prime2;
                }

                    return hash % capacity_;
			}
			unsigned long long int myCustomHashFunction2(std::string key) const
			{
                if (key.empty()) {
                    return 0;
                }

                     unsigned long long int hash = 263; 

                    for (char c : key) {
                        hash = ((hash << 5) + hash) + c;
                }

                    return hash % capacity_;
			}
			unsigned long long int myCustomHashFunction3(std::string key) const
			{
                if (key.empty()) {
                    return 0;
                }

                const unsigned long long int prime1 = 31;
                const unsigned long long int prime2 = 37;
                const unsigned long long int factor = 97;
                unsigned long long int hash = 0;

                for (char c : key) {
                    hash = (hash * prime1) ^ (c * prime2);
                    hash = (hash + factor) % capacity_;
                }

                return hash;
            }
			unsigned long long int myCustomHashFunction4(std::string key) const
			{
               if (key.empty()) {
                    return 0;
                }

                    const unsigned long long int prime1 = 263; 
                    const unsigned long long int prime2 = 269; 
                    const unsigned long long int factor = 131; 
                    unsigned long long int hash = 0;

                    for (char c : key) {
                        hash += c * prime1;
                        hash ^= (hash >> 31) + factor; 
                        hash *= prime2;
                }

                    return hash % capacity_;
			}
			/**
			 * Return true if a key exists in the table_, or false otherwise.
			 */
			bool exists(std::string key) const
			{
				if (table_ == nullptr)
                {
                    return false;
                }
                unsigned long long int hash = this->hash(key);
                for (auto it = table_[hash].begin(); it != table_[hash].end(); it++)
                {
                    if (it->first == key)
                    {
                        return true;
                    }
                }
                return false;
			}
			
			/**
			 * Add a key/value pair to this table_.
			 * If the key already exists, throw a runtime_error.
			 */
			void add(std::string key, VTYPE value)
			{
                if (exists(key))
                {
                    throw std::runtime_error("Cannot add key because it already exists: " + key);
                }
                if (table_ == nullptr)
                {
                    throw std::runtime_error("Cannot add key because table_ is null");
                }

                unsigned long long int hash = this->hash(key);
                // check for collision in forward_list
                int size = 0;
                for (auto it = table_[hash].begin(); it != table_[hash].end(); it++)
                {
                    size++;
                }
                if (size >= 1)
                {
                    this->n_collisions_++;
                }
                
                table_[hash].push_front(std::make_pair(key, value));
                size_++;
			}
			
			/**
			 * Should return a reference to the VTYPE value associated to the provided key.
			 * If the key/value pair isn't in the table_, a runtime_error should be thrown.
			 */
			VTYPE& get(std::string key) const
			{
                if (!exists(key))
                {
                    throw std::runtime_error("Cannot get key because it does not exist: " + key);
                }
                unsigned long long int hash = this->hash(key);
                for (auto it = table_[hash].begin(); it != table_[hash].end(); it++)
                {
                    if (it->first == key)
                    {
                        return it->second;
                    }
                }
                throw std::runtime_error("Cannot get key because it does not exist: " + key);
			}
			
			/**
			 * In a single std::forward_list, return every key currently present in the table_
			 * 
			 * If no keys exist (empty table_), just return an empty std::forward_list.
			 * 
			 * It's okay that when sorted == false, std::forward_list::push_front will
			 *  return your keys in backwards-order, as there is no guarantee
			 *  of properly-ordered keys anyway.
			 * 
			 * However, if the caller passes sorted=true, you should sort the keys
			 * 	as a last step before returning them.
			 * 	Try using the built-in method std::forward_list::sort
			 */
			std::forward_list<std::string> getAllKeys(bool sorted = false) const
			{
                std::forward_list<std::string> keys;
                if (table_ == nullptr)
                {
                    return keys;
                }
                for (size_t i = 0; i < capacity_; i++)
                {
                    for (auto it = table_[i].begin(); it != table_[i].end(); it++)
                    {
                        keys.push_front(it->first);
                    }
                }
                if (sorted)
                {
                    keys.sort();
                }
                return keys;
			}
			
			/**
			 * Remove a key/value pair that corresponds to the provided key.
			 * If no such key exists, throw a runtime_error.
			 */
			void remove(std::string key)
			{
                if (!exists(key))
                {
                    throw std::runtime_error("Cannot remove key because it does not exist: " + key);
                }
                unsigned long long int hash = this->hash(key);
                auto pre = table_[hash].before_begin();
                for (auto it = table_[hash].begin(); it != table_[hash].end(); it++)
                {
                    if (it->first == key)
                    {
                        table_[hash].erase_after(pre);
                        size_--;
                        return;
                    }
                    pre = it;
                }
			}
			
			/**
			 * Remove all entries in this table_
			 * Iterate over each table_ row and call clear on the row's list
			 */
			void clear()
			{
                for (size_t i = 0; i < capacity_; i++)
                {
                    table_[i].clear();
                }
                size_ = 0;
			}
			
			/**
			 * Assignment Operator
			 */
			MyHashTable<VTYPE>& operator=(const MyHashTable<VTYPE>& other)
			{
                if (this == &other)
                {
                    return *this;
                }
                if (table_ != nullptr)
                {
                    delete[] table_;
                }
                capacity_ = other.capacity_;
                size_ = other.size_;
                n_collisions_ = other.n_collisions_;
                table_ = new std::forward_list<std::pair<std::string, VTYPE>>[capacity_];
                for (int i = 0; i < capacity_; i++)
                {
                    table_[i] = other.table_[i];
                }
                return *this;
			}
			
		//
		private:
			
			/**
			 * Keeps track of the capacity of this hash table_
			 * (total number of rows in the table_, whether used or not)
			 * (does not care about collisions)
			 */
			size_t capacity_ = 0;
			
			/**
			 * Keeps track of the total number of items currently in
			 * the hash table_
			 */
			size_t size_ = 0;
			
			/**
			 * Keeps track of the number of collisions currently present in the table_
			 */
			size_t n_collisions_ = 0;
			
			/**
			 * The actual hash table_.
			 * We'll make this a fixed-sized array,
			 *   but dynamically allocated so we can resize whenever we need.
			 * 
			 * Try to imagine each table_ row is actually a complete forward_list.
			 * In a perfect situation where a table_ has no collisions, each list
			 *   will simply contain one item.
			 * 
			 * One "item" in this case refers to an std::pair<std::string, VTYPE>,
			 *   where the first part of the pair is the key and the second
			 *   is the value (of type VTYPE).
			 */
			std::forward_list<std::pair<std::string, VTYPE>> * table_ = nullptr;
	};
}

#endif