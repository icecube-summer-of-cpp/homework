/* Ben Hokanson-Fasig
 * Discovering Modern C++ - Exercise 3.11.4
 * Add the methods begin() and end() for returning a begin and end iterator to
 * class vector. Add the types iterator and const_iterator to the class as well.
 * Note that pointers are models of the concept of random-access iterators.
 * Use the STL function sort for ordering vector entries to demonstrate that
 * your iterators work as they should.
 */


#include <algorithm>
#include <exception>
#include <iostream>
// #include <iterator>
#include <memory>


template <typename T>
class vector 
{
    private:
        int                   my_size;
        std::unique_ptr<T[]>  data;

        void check_size(int that_size) const
        {
            if (my_size != that_size)
            {
                throw std::domain_error("Vectors are not the same size");
            }
        }

        void check_index(int i) const
        {
            if (i < 0)
            {
                throw std::domain_error("Underflow when accessing vector");
            } 
            else if (i >= my_size)
            {
                throw std::domain_error("Overflow when accessing vector");
            }
        }

    public:
        // Constructors
        explicit vector(int size)
            : my_size(size), data( new T[my_size] ) {}

        vector()
            : my_size(0), data(0) {}

        // Destructor
        ~vector() = default;
        
        // Copy Constructor
        vector(const vector& that)
            : my_size(that.my_size), data(new T[my_size])
        {
            std::copy(&that.data[0], &that.data[that.my_size], &data[0]);
        }

        // Move Constructor
        vector(vector&&) = default;

        // Copy Assignment
        vector& operator=(const vector& that) 
        {
            check_size(that.my_size);
            std::copy(&that.data[0], &that.data[that.my_size], &data[0]);
            return *this;
        }

        // Move Assignment
        vector& operator=(vector&&) = default;


        // Getters
        int size() const { return my_size; }


        // Access operators
        const T& operator[](int i) const 
        {
            check_index(i);
            return data[i];
        }
                    
        T& operator[](int i) 
        {
            check_index(i);
            return data[i];
        }


        // Addition
        vector operator+(const vector& that) const 
        {
            check_size(that.my_size);
            vector sum(my_size);
            for (int i= 0; i < my_size; ++i) 
                sum[i] = data[i] + that[i];
            return sum;
        }


        // Iteration
        struct iter_entry
        {
            // Attributes
            T value;
            std::shared_ptr<iter_entry> next;

            // Constructor
            iter_entry() : next(nullptr) {}
            iter_entry(const T& val) : value(val), next(nullptr) {}
            // Destructor
            ~iter_entry() = default;
            // Copy Constructor
            iter_entry(const iter_entry&) = default;
            // Move Constructor
            iter_entry(iter_entry&&) = default;
            // Copy Assignment
            iter_entry& operator=(const iter_entry&) = default;
            // Move Assignment
            iter_entry& operator=(iter_entry&&) = default;

            // Link to next entry
            void link(iter_entry nxt) {next = std::make_shared<iter_entry>(nxt);}
        };

        struct iterator
        {
            // Attributes
            iter_entry curr;

            // Constructors
            iterator() = default;
            iterator(const iter_entry entry) : curr(entry) {};
            // Destructor
            ~iterator() = default;
            // Copy Constructor
            iterator(const iterator&) = default;
            // Move Constructor
            iterator(iterator&&) = default;
            // Copy Assignment
            iterator& operator=(const iterator&) = default;
            // Move Assignment
            iterator& operator=(iterator&&) = default;

            // Dereferencing
            T& operator*() {return curr.value;}

            // Incrementing
            iterator& operator++()
            {
                curr = *curr.next;
                return *this;
            }
            iterator& operator++(int)
            {
                iterator tmp(*this);
                curr = *curr.next;
                return tmp;
            }
        };


        iterator begin()
        {
            if (my_size==0) {return iterator();}
            iter_entry curr(data[my_size-1]);
            for (int i=my_size-2; i>=0; --i)
            {
                iter_entry prev(data[i]);
                prev.link(curr);
                std::cout << "  curr: " << curr.value << std::endl;
                std::cout << "  curr.next: " << curr.next.get() << std::endl;
                curr = prev;
            }
            std::cout << "  first: " << curr.value << std::endl;
            std::cout << "  first.next: " << curr.next.get() << std::endl;
            return iterator(curr);
        }

        iterator end()
        {
            return iterator();
        }
};


// // Iterator traits
// template<typename T>
// struct std::iterator_traits<iterator>
// {
//     using difference_type = std::ptrdiff_t;
//     using value_type = T;
//     using pointer = T*;
//     using reference = T&;
//     using iterator_category = std::random_access_iterator_tag;
// };


// Vector print function
template <typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& v)
{
  os << '[';
  for (int i= 0; i < v.size(); ++i) os << v[i] << ',';
  os << ']';
  return os;
};



int main()
{
    vector<int> a(5);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    a[3] = 2;
    a[4] = 5;
    std::cout << a << std::endl;

    std::cout << "begin" << std::endl;
    auto i = a.begin();
    std::cout << "value: " << i.curr.value << std::endl;
    std::cout << "next: " << i.curr.next.get() << std::endl;
    while (i.curr.next!=nullptr) {
        ++i;
        std::cout << "value: " << i.curr.value << std::endl;
        std::cout << "next: " << i.curr.next.get() << std::endl;
    }

    std::cout << "end" << std::endl;
    auto i2 = a.end();
    std::cout << "value: " << i2.curr.value << std::endl;
    std::cout << "next: " << i2.curr.next.get() << std::endl;
}