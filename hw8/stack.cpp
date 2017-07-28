/* Ben Hokanson-Fasig
 * Discovering Modern C++ - Exercise 3.11.8
 * Revise your stack implementation from Exercise 3.11.3 (and optionally that of
 * Exercise 3.11.7) with a user-defined size. The size is passed as the second
 * template argument. The default should be 4096.
 */



#include "stack.hpp"


template <typename T>
std::string center(T& original, int width, char fillchar)
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


template <typename T, size_t Size>
const T& stack<T,Size>::top() const
{
    if (!empty()) {
        return *elements_[size_-1];
    }
    else {
        throw std::domain_error("Stack is empty!");
    }
}

// Mutation functions
template <typename T, size_t Size>
void stack<T,Size>::push(const T& element)
{
    if (!full()) {
        elements_[size_] = std::make_unique<T>(element);
        size_ += 1;
    }
    else {
        throw std::domain_error("Stack is full!");
    }
}

template <typename T, size_t Size>
void stack<T,Size>::pop()
{
    if (!empty()) {
        size_ -= 1;
        elements_[size_].reset();
    }
    else {
        throw std::domain_error("Stack is empty!");
    }
}

template <typename T, size_t Size>
void stack<T,Size>::clear()
{
    for (int i=0; i<size_; ++i) {pop();}
    size_ = 0;
}


// template <typename T, size_t Size>
// std::ostream& operator<<(std::ostream& os, const stack<T,Size>& stack)
// {
//     int width = stack.width();
//     if (!stack.full()) {os << "\n | " << center("",width) << " |";}
//     for (int i=stack.size_-1; i>=0; --i) {
//         os << "\n | " << center(*stack.elements_[i],width) << " |";
//     }
//     os << "\n +-" << center("",width,'-') << "-+ ";
//     return os;
// }


// Width function
template <typename T, size_t Size>
const int stack<T,Size>::width() const
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