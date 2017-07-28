/* Ben Hokanson-Fasig
 * Discovering Modern C++ - Exercise 3.11.8
 * Revise your stack implementation from Exercise 3.11.3 (and optionally that of
 * Exercise 3.11.7) with a user-defined size. The size is passed as the second
 * template argument. The default should be 4096.
 */



// Include guard
#ifndef __STACK_HPP_INCLUDED__
#define __STACK_HPP_INCLUDED__

#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>


template <typename T>
std::string center(T& original, int width, char fillchar=' ');


template <typename T, size_t Size=4096>
class stack
{
    public:
        // Constructors
        stack() = default;
        stack(const T& base) {push(base);}
        // Destructor
        ~stack() = default;
        // Copy Constructor
        stack(const stack&) = default;
        // Move Constructor
        stack(stack&&) = default;
        // Copy Assignment
        stack& operator=(const stack&) = default;
        // Move Assignment
        stack& operator=(stack&&) = default;

        // Inspection functions
        const int size() const {return size_;}
        const bool empty() const {return size_<=0;}
        const bool full() const {return size_>=max_size;}
        const T& top() const;

        // Mutation functions
        void push(const T& element);
        void pop();
        void clear();

    friend std::ostream& operator<<(std::ostream& os, const stack& stack)
    {
        int width = stack.width();
        if (!stack.full()) {os << "\n | " << center("",width) << " |";}
        for (int i=stack.size_-1; i>=0; --i) {
            os << "\n | " << center(*stack.elements_[i],width) << " |";
        }
        os << "\n +-" << center("",width,'-') << "-+ ";
        return os;
    }

    private:
        // Width function
        const int width() const;

    // Attributes
    public:
        static const size_t max_size = Size;
    private:
        size_t size_ = 0;
        std::vector<std::unique_ptr<T>> elements_{max_size};
};



struct pancake
{
    int size;
    bool yummy=true;
    pancake() : size(0) {};
    pancake(int size) : size(size) {}
    pancake(int size, bool yummy) : size(size), yummy(yummy) {}
};

std::ostream& operator<<(std::ostream& os, const pancake& p);


template <typename T>
void title(const T& s)
{
    std::cout << "\n========== " << s << " ==========" << std::endl;
}


#endif
