/* Ben Hokanson-Fasig
 * Discovering Modern C++ - Exercise 3.11.7
 * Specialize your stack implementation from Exercise 3.11.3 for bool.
 * Use an unsigned char for 8 bool as in Section 3.6.1.
 */




#include "stack.hpp"


template <size_t Size>
class stack<bool,Size>
{
    public:
        // Constructors
        stack() = default;
        stack(const bool& base) {push(base);}
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
        const bool& top() const
        {
            if (!empty()) {
                return access_element(size_-1);
            }
            else {
                throw std::domain_error("Stack is empty!");
            }
        }

        // Mutation functions
        void push(const bool& element)
        {
            if (!full()) {
                bool_proxy e = access_element(size_);
                e = element;
                size_ += 1;
            }
            else {
                throw std::domain_error("Stack is full!");
            }
        }

        void pop()
        {
            if (!empty()) {
                size_ -= 1;
            }
            else {
                throw std::domain_error("Stack is empty!");
            }
        }

        void clear()
        {
            for (int i=0; i<size_; ++i) {pop();}
            size_ = 0;
        }

    friend std::ostream& operator<<(std::ostream& os, const stack& stack)
    {
        if (!stack.full()) {os << "\n |   |";}
        for (int i=stack.size_-1; i>=0; --i) {
            os << "\n | " << stack.access_element(i) << " |";
        }
        os << "\n +---+ ";
        return os;
    }

    private:
        // Bool proxy for single bit access
        class bool_proxy
        {
            public:
                bool_proxy(unsigned char& byte, int p)
                : byte(byte), mask(1 << p) {}
                // Getter
                operator bool() const {return byte & mask;}
                // Setter
                bool_proxy& operator=(bool b) {
                    if (b) {byte |= mask;}
                    else {byte &= ~mask;}
                    return *this;
                }
            private:
                unsigned char& byte;
                unsigned char mask;
        };

        bool_proxy access_element(int i) {return {elements_[i/8], i%8};}

        bool access_element(int i) const {return (elements_[i/8] >> i%8) & 1;}

        

    // Attributes
    public:
        static const size_t max_size = Size;
        static const size_t max_char_size = (Size+7) / 8;
    private:
        size_t size_ = 0;
        size_t char_size_ = 0;
        std::vector<unsigned char> elements_{max_char_size};
};




int main()
{
    title("Stack of bools");
    stack<bool,10> a;
    std::cout << "stack<bool,10> a = " << a << std::endl;
    std::cout << "a.size() = " << a.size() << std::endl;
    std::cout << "a.max_size = " << a.max_size << std::endl;
    std::cout << "a.empty() = " << a.empty() << std::endl;

    // Popping empty stack throws domain_error
    // a.pop();

    // Checking top throws domain_error
    // a.top();

    std::cout << "a.push(true);" << std::endl;
    a.push(true);
    std::cout << "a=" << a << std::endl;
    std::cout << "a.size() = " << a.size() << std::endl;
    std::cout << "a.empty() = " << a.empty() << std::endl;

    std::cout << "a.pop();" << std::endl;
    a.pop();
    std::cout << "a=" << a << std::endl;
    std::cout << "a.size() = " << a.size() << std::endl;
    std::cout << "a.full() = " << a.full() << std::endl;

    std::cout << "for (int i=1; i<11; ++i) {a.push(i);}" << std::endl;
    for (int i=1; i<11; ++i) {a.push(i%3%2);}
    std::cout << "a=" << a << std::endl;
    std::cout << "a.size() = " << a.size() << std::endl;
    std::cout << "a.full() = " << a.full() << std::endl;

    // Adding another element throws domain_error
    // a.push(100);

    size_t stop = a.size();
    for (int i=0; i<stop; ++i) {
        std::cout << "a.top() = " << a.top() << "; a.pop()" << std::endl;
        a.pop();
    }

}