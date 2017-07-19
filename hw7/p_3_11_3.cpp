/* Ben Hokanson-Fasig
 * Discovering Modern C++ - Exercise 3.11.3
 * Write a stack implementation for a generic value type. The maximal size of
 * the stack is defined in the class (hard-wired).
 * Provide the following functions:
 *   • Constructor;
 *   • Destructor if necessary;
 *   • top: show last element;
 *   • pop: remove last element (without returning);
 *   • push: insert new element;
 *   • clear: delete all entries;
 *   • size: number of elements;
 *   • full: whether stack is full;
 *   • empty: whether stack is empty.
 * Stack over- or underflow must throw an exception.
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


template <typename T>
class shortstack
{
    public:
        // Constructors
        shortstack()
        {
            elements_.resize(max_size);
            size_ = 0;
        }
        shortstack(const T& base)
        {
            elements_.resize(max_size);
            size_ = 0;
            push(base);
        }
        // Destructor
        ~shortstack() = default;
        // Copy Constructor
        shortstack(const shortstack&) = default;
        // Move Constructor
        shortstack(shortstack&&) = default;
        // Copy Assignment
        shortstack& operator=(const shortstack&) = default;
        // Move Assignment
        shortstack& operator=(shortstack&&) = default;

        // Inspection functions
        const int size() const {return size_;}
        const bool empty() const {return size_<=0;}
        const bool full() const {return size_>=max_size;}
        const T top() const
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
                elements_[size_] = std::make_shared<T>(element);
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
            for (std::shared_ptr<T> e : elements_) {e.reset();}
            size_ = 0;
        }

    friend std::ostream& operator<<(std::ostream& os, const shortstack& stack)
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
        static const int max_size = 10;
    private:
        int size_;
        std::vector<std::shared_ptr<T>> elements_;
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
    title("Shortstack of ints");
    shortstack<int> a;
    std::cout << "shortstack<int> a = " << a << std::endl;
    std::cout << "a.size() = " << a.size() << std::endl;
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
    for (int i=0; i<a.max_size; ++i) {
        std::cout << "a.top() = " << a.top() << "; a.pop()" << std::endl;
        a.pop();
    }

    // Adding another element throws domain_error
    // a.push(10);


    title("Shortstack of doubles");
    std::cout << "shortstack<double> b;\nfor (double i=0; i<2; i+=1/3.) {b.push(i);}" << std::endl;
    shortstack<double> b;
    for (double i=0; i<2; i+=1/3.) {b.push(i);}
    std::cout << "b=" << b << std::endl;
    std::cout << "b.size() = " << b.size() << std::endl;


    std::cout << "b.clear();" << std::endl;
    b.clear();
    std::cout << "b=" << b << std::endl;
    std::cout << "b.size() = " << b.size() << std::endl;


    title("Shortstack of pancakes");
    shortstack<pancake> p;
    for (int i=15; i>10; i-=2) {p.push(pancake{i});}
    std::cout << "p=" << p << std::endl;

}