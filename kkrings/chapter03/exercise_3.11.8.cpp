/**
 * Solutions to exercise 3.11.3 and 3.11.8
 */

#include <cassert>
#include <iostream>
#include <vector>

/**
 * @brief Stack implementation for a generic value type
 *
 * The stack implementation supports a custom size, where the default
 * size is 4096.
 */
template<typename T, unsigned int max_size = 4096>
class stack
{
    public:
        using value_type = T;

        stack() = default;
        stack(const stack&) = default;
        stack(stack&&) = default;

        ~stack() = default;

        stack& operator=(const stack&) = default;
        stack& operator=(stack&&) = default;

        /**
         * @return Show last element.
         */
        T& top()
        {
            return data_.back();
        }

        /**
         * Remove last element.
         */
        void pop()
        {
            assert(!empty());
            data_.pop_back();
        }

        /**
         * Insert new element.
         * @param element New element
         */
        void push(const T& element)
        {
            assert(data_.size() < max_size);
            data_.push_back(element);
        }

        /**
         * Delete all entries;
         */
        void clear()
        {
            data_.clear();
        }

        /**
         * @return Number of elements
         */
        unsigned int size() const
        {
            return data_.size();
        }

        /**
         * @return Check whether stack is full.
         */
        bool full() const
        {
            return data_.size() == max_size;
        }

        /**
         * @return Check whether stack is empty.
         */
        bool empty() const
        {
            return data_.empty();
        }

    private:
        std::vector<T> data_;
};

int main()
{
    std::cout << "Create stack with custom size 2." << std::endl;
    stack<unsigned int, 2> stack;

    std::cout << "Is stack empty? " << (stack.empty() ? "True" : "False")
              << '.' << std::endl;

    std::cout << "Add element 0." << std::endl;
    stack.push(0);

    std::cout << "Is stack empty? " << (stack.empty() ? "True" : "False")
              << '.' << std::endl;

    std::cout << "Stack contains " << stack.size() << " element(s)."
              << std::endl;

    std::cout << "The last element is " << stack.top() << '.' << std::endl;

    std::cout << "Add element 1." << std::endl;
    stack.push(1);

    std::cout << "Is stack full? " << (stack.full() ? "True" : "False")
              << '.' << std::endl;

    // stack.push(2);

    std::cout << "Remove last element." << std::endl;
    stack.pop();

    std::cout << "Stack contains " << stack.size() << " element(s)."
              << std::endl;

    std::cout << "Delete all entries." << std::endl;
    stack.clear();

    std::cout << "Is stack empty? " << (stack.empty() ? "True" : "False")
              << '.' << std::endl;

    // stack.pop();
}
