

//
#include "MyRolodex.hpp"
#include "MyHashTable.hpp"
#include "Address.hpp"

// g++ -W -pedantic -g -std=c++17 CPP_Tests.cpp MyRolodex.cpp -o main-tests

/**
 * TODO: Finish the implementation for this class
 */


//	More includes?
#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>
#include <vector>
#include <algorithm>
#include <functional>
#include <initializer_list>
#include <memory>
#include <type_traits>
#include <cassert>



//
namespace CPSC131::MyRolodex
{
	/// Your welcome
	MyRolodex::MyRolodex() // : table_()
    {
        
    }
	
	/**
	 * Return true if a person exists in the Rolodex
	 */
	bool MyRolodex::exists(std::string name) const
	{
        return table_.exists(name);
    }
	
	/**
	 * Allow the user to add an address using its parts.
	 * This should probably just call on the other overload
	 */
	void MyRolodex::add(std::string name, std::string line1, std::string line2, std::string city, std::string state, int zip, std::string country)
	{
        if (exists(name))
        {
            throw std::runtime_error("Cannot add key because it already exists: " + name);
        }
        Address address;
        address.line1 = line1;
        address.line2 = line2;
        address.city = city;
        address.state = state;
        address.zip = zip;
        address.country = country;

        table_.add(name, address);
    }
	
	/**
	 * Add an entry into the Rolodex
	 * The person's name is the key, and their Address is the value.
	 * The Address comes in the form of the Address struct, defined in another source file.
	 */
	void MyRolodex::add(std::string name, Address address)
	{
        if (exists(name))
        {
			throw std::runtime_error("Cannot add key because it already exists: " + name);
		}
		
        table_.add(name, address);
    }
	
	/**
	 * Return an address structure associated with a person
	 */
	Address MyRolodex::get(std::string name) const
	{
        if (!exists(name))
        {
            throw std::runtime_error("Cannot get key because it does not exist: " + name);
        }
        return table_.get(name);
    }
	
	/**
	 * Remove a person from the Rolodex
	 */
	void MyRolodex::remove(std::string name)
	{
        if (!exists(name))
        {
            throw std::runtime_error("Cannot remove key because it does not exist: " + name);
        }
        table_.remove(name);
	}
	
	/**
	 * Clear the Rolodex of all information.
	 * (Hint: The table also has this method)
	 */
	void MyRolodex::clear()
	{
        if (empty())
        {
            throw std::runtime_error("Cannot clear because the table is already empty");
        }
        table_.clear();
	}
	
	/**
	 * Return true if the Rolodex is empty, false otherwise
	 */
	bool MyRolodex::empty()
	{
		if (size() == 0)
        {
            return true;
        }
        return false;
	}
	
	/**
	 * Return the number of entries in this Rolodex
	 */
	size_t MyRolodex::size()
	{
		return table_.size();
	}
}

