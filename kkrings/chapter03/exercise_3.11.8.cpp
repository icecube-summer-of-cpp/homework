/**
 * Solutions to exercise 3.11.3, 3.11.7, and 3.11.8
 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>

/**
 * @brief Stack implementation for a generic value type
 * The stack implementation supports a custom size, where the default
 * size is 4096, and is based on a non-dynamic array approach.
 */
template<typename T, unsigned int max_size = 4096>
class stack
{
    public:
        stack() : size_(0), data_(new T[max_size]) {};

        stack(const stack& other) : size_(other.size()), data_(new T[max_size])
        {
            std::copy(&other.data_[0], &other.data_[other.size()], &data_[0]);
        }

        stack(stack&&) = default;

        ~stack() = default;

        stack& operator=(const stack& other)
        {
            assert(other.size() == size());
            std::copy(&other.data_[0], &other.data_[other.size()], &data_[0]);
            return *this;
        }

        stack& operator=(stack&&) = default;

        /**
         * @return Show last element.
         */
        T& top()
        {
            if (empty())
            {
                throw std::underflow_error("The stack is empty.");
            }

            return data_[size_ - 1];
        }

        /**
         * Remove last element.
         */
        void pop()
        {
            if (empty())
            {
                throw std::underflow_error("The stack is empty.");
            }

            --size_;
        }

        /**
         * Insert new element.
         * @param element New element
         */
        void push(const T& element)
        {
            if (full())
            {
                throw std::overflow_error("The stack is full.");
            }

            data_[size_] = element;
            ++size_;
        }

        /**
         * Delete all entries;
         */
        void clear()
        {
            size_ = 0;
        }

        /**
         * @return Number of elements
         */
        unsigned int size() const
        {
            return size_;
        }

        /**
         * @return Check whether stack is full.
         */
        bool full() const
        {
            return size() == max_size;
        }

        /**
         * @return Check whether stack is empty.
         */
        bool empty() const
        {
            return size() == 0;
        }

    private:
        std::unique_ptr<T[]> data_;
        unsigned int size_;
};

/**
 * @brief Specialized stack implementation for booleans
 * Save 8 booleans into one byte based on char.
 */
template<unsigned int max_size>
class stack<bool, max_size>
{
    public:
        stack() : size_(0), data_(new unsigned char[real_max_size()]) {}

        stack(const stack& other)
            : size_(other.size()), data_(new unsigned char[real_max_size()])
        {
            std::copy(
                &other.data_[0], &other.data_[real_max_size()], &data_[0]);
        }

        stack(stack&&) = default;

        ~stack() = default;

        stack& operator=(const stack& other)
        {
            assert(other.real_max_size() == real_max_size());

            std::copy(
                &other.data_[0], &other.data_[real_max_size()], &data_[0]);

            return *this;
        }

        stack& operator=(stack&&) = default;

        bool top() const
        {
            if (empty())
            {
                throw std::underflow_error("The stack is empty.");
            }

            return (data_[(size_ - 1) / 8] >> (size_ - 1) % 8) & 1;
        }

        void pop()
        {
            if (empty())
            {
                throw std::underflow_error("The stack is empty.");
            }

            --size_;
        }

        void push(bool element)
        {
            // unset last bit
            data_[size_ / 8] &= ~(1 << size_ % 8);

            if (full())
            {
                throw std::overflow_error("The stack is full.");
            }

            if (element)
            {
                // set last bit
                data_[size_ / 8] |= (1 << size_ % 8);
            }

            ++size_;
        }

        void clear()
        {
            size_ = 0;
        }

        unsigned int size() const
        {
            return size_;
        }

        bool full() const
        {
            return size() == max_size;
        }

        bool empty() const
        {
            return size() == 0;
        }

    private:
        /**
         * @return Actual size of underlying data array
         */
        unsigned int real_max_size() const
        {
            return (max_size + 7) / 8;
        }

        std::unique_ptr<unsigned char[]> data_;
        unsigned int size_;
};

int main()
{
    std::cout << "Create stack of integers with custom size 2." << std::endl;
    stack<unsigned int, 2> su;

    std::cout << "Is stack empty? " << (su.empty() ? "True" : "False")
              << '.' << std::endl;

    try
    {
        su.top();
    }
    catch (std::underflow_error& e)
    {
        std::cerr << "Tried to show last element of empty stack and failed."
                  << std::endl;
    }

    std::cout << "Add element 0." << std::endl;
    su.push(0);

    std::cout << "Is stack empty? " << (su.empty() ? "True" : "False")
              << '.' << std::endl;

    std::cout << "Stack contains " << su.size() << " element(s)."
              << std::endl;

    std::cout << "The last element is " << su.top() << '.' << std::endl;

    std::cout << "Add element 1." << std::endl;
    su.push(1);

    std::cout << "The last element is " << su.top() << '.' << std::endl;

    std::cout << "Is stack full? " << (su.full() ? "True" : "False")
              << '.' << std::endl;

    try
    {
        su.push(2);
    }
    catch (std::overflow_error& e)
    {
        std::cerr << "Tried to push to full stack and failed." << std::endl;
    }

    std::cout << "Remove last element." << std::endl;
    su.pop();

    std::cout << "Stack contains " << su.size() << " element(s)."
              << std::endl;

    std::cout << "The last element is " << su.top() << '.' << std::endl;

    std::cout << "Delete all entries." << std::endl;
    su.clear();

    std::cout << "Is stack empty? " << (su.empty() ? "True" : "False")
              << '.' << std::endl;

    std::cout << "Create stack of booleans with custom size 2." << std::endl;
    stack<bool, 2> sb;

    std::cout << "Is stack empty? " << (sb.empty() ? "True" : "False")
              << '.' << std::endl;

    try
    {
        sb.top();
    }
    catch (std::underflow_error& e)
    {
        std::cerr << "Tried to show last element of empty stack and failed."
                  << std::endl;
    }

    std::cout << "Add element true." << std::endl;
    sb.push(true);

    std::cout << "Is stack empty? " << (sb.empty() ? "True" : "False")
              << '.' << std::endl;

    std::cout << "Stack contains " << sb.size() << " element(s)."
              << std::endl;

    std::cout << "The last element is " << (sb.top() ? "true" : "false") << '.'
              << std::endl;

    std::cout << "Add element false." << std::endl;
    sb.push(false);

    std::cout << "The last element is " << (sb.top() ? "true" : "false") << '.'
              << std::endl;

    std::cout << "Is stack full? " << (sb.full() ? "True" : "False")
              << '.' << std::endl;

    try
    {
        sb.push(false);
    }
    catch (std::overflow_error& e)
    {
        std::cerr << "Tried to push to full stack and failed." << std::endl;
    }

    std::cout << "Remove last element." << std::endl;
    sb.pop();

    std::cout << "Stack contains " << sb.size() << " element(s)."
              << std::endl;

    std::cout << "The last element is " << (sb.top() ? "true" : "false") << '.'
              << std::endl;

    std::cout << "Delete all entries." << std::endl;
    sb.clear();

    std::cout << "Is stack empty? " << (sb.empty() ? "True" : "False")
              << '.' << std::endl;

    try
    {
        sb.pop();
    }
    catch (std::underflow_error& e)
    {
        std::cerr << "Tried to pop from empty stack and failed." << std::endl;
    }

    std::cout << "Add element false." << std::endl;
    sb.push(false);

    std::cout << "The last element is " << (sb.top() ? "true" : "false") << '.'
              << std::endl;
}
