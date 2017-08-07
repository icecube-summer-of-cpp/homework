/* Ben Hokanson-Fasig
 * Discovering Modern C++ - Exercise 3.11.8
 * Revise your stack implementation from Exercise 3.11.3 (and optionally that of
 * Exercise 3.11.7) with a user-defined size. The size is passed as the second
 * template argument. The default should be 4096.
 */

#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>


template <typename T>
std::string center(T& original, int width, char fillchar=' ')
{
    std::stringstream s;
    s << original;
    std::string origin = s.str();
    int num_spaces = width - origin.length();
    if (num_spaces<=0) {return origin;}
    else {
        std::string centered = "";
        for (int i=0; i<num_spaces; ++i) {
            if (i==num_spaces/2) {centered += origin;}
            centered += fillchar;
        }
        return centered;
    }
}


template <typename T, size_t Size=4096>
class stack
{
    public:
        // Constructors
        stack() = default;
        stack(const T& base)
        {
            push(base);
        }
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
        const T& top() const
        {
            if (!empty()) {
                return *elements_[size_-1];
            }
            else {
                throw std::domain_error("Stack is empty!");
            }
        }

        // Mutation functions
        void push(const T& element)
        {
            if (!full()) {
                elements_[size_] = std::make_unique<T>(element);
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
                elements_[size_].reset();
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
        const int width() const
        {
            int max_len = 0;
            for (int i=0; i<size_; ++i) {
                std::stringstream s;
                s << *elements_[i];
                int len = s.str().length();
                max_len = (len>max_len) ? len : max_len;
            }
            return max_len;
        }

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

std::ostream& operator<<(std::ostream& os, const pancake& p)
{
    // return os << (p.yummy ? "yummy" : "nasty") << " pancake with size " << p.size;
    os << "<";
    for (int i=0; i<p.size; ++i) {
        os << "=";
    }
    os << ">";
    return os;
}


template <typename T>
void title(const T& s)
{
    std::cout << "\n========== " << s << " ==========" << std::endl;
}


int main()
{
    title("Stack of ints");
    stack<int,10> a;
    std::cout << "stack<int,10> a = " << a << std::endl;
    std::cout << "a.size() = " << a.size() << std::endl;
    std::cout << "a.max_size = " << a.max_size << std::endl;
    std::cout << "a.empty() = " << a.empty() << std::endl;

    // Popping empty stack throws domain_error
    // a.pop();

    // Checking top throws domain_error
    // a.top();

    std::cout << "a.push(0);" << std::endl;
    a.push(0);
    std::cout << "a=" << a << std::endl;
    std::cout << "a.size() = " << a.size() << std::endl;
    std::cout << "a.empty() = " << a.empty() << std::endl;

    std::cout << "a.pop();" << std::endl;
    a.pop();
    std::cout << "a=" << a << std::endl;
    std::cout << "a.size() = " << a.size() << std::endl;
    std::cout << "a.full() = " << a.full() << std::endl;

    std::cout << "for (int i=1; i<11; ++i) {a.push(i);}" << std::endl;
    for (int i=1; i<11; ++i) {a.push(i);}
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


    title("Stack of doubles");
    std::cout << "stack<double> b;\nfor (double i=0; i<2; i+=1/3.) {b.push(i);}" << std::endl;
    stack<double> b;
    for (double i=0; i<2; i+=1/3.) {b.push(i);}
    std::cout << "b=" << b << std::endl;
    std::cout << "b.size() = " << b.size() << std::endl;
    std::cout << "b.max_size = " << b.max_size << std::endl;

    std::cout << "b.clear();" << std::endl;
    b.clear();
    std::cout << "b=" << b << std::endl;
    std::cout << "b.size() = " << b.size() << std::endl;


    title("Stack of pancakes");
    stack<pancake> p;
    for (int i=15; i>10; i-=2) {p.push(pancake{i});}
    std::cout << "p=" << p << std::endl;

}