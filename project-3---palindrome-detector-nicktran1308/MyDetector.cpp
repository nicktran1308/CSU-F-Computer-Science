

/**
 * TODO: Complete these class definitions
 */

/// Starter includes (YW)
#include "MyDetector.hpp"
#include "MyStack.hpp"
#include "MyQueue.hpp"

//
namespace CPSC131::PalindromeDetector
{
	/// YOUR WELCOME
	MyDetector::MyDetector() {}
	
	//
	bool MyDetector::isPalindrome(std::string s)
	{
		MyStack<char> stack;
		MyQueue<char> queue;
		
		//Push character to stack and enqueue char to queu 
		for (char c : s)
		{
			if (std::isalpha(c))
			{
			char lowercase_c = std::tolower(c);
			stack.push(lowercase_c);
			queue.enqueue(lowercase_c);
			}
		}

		//Remove from both and change until its equal for Palindrome
		while (!stack.empty() && !queue.empty())
		{
			if (std::tolower(stack.top()) != std::tolower(queue.front()))
			{
				return false;
			}
			stack.pop();
			queue.dequeue();
		}
		return true;
	}
}












