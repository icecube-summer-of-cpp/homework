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
        std::shared_ptr<T[]>  data;

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
            std::copy(&that.data.get(), &(that.data.get()+that.my_size), &data.get());
        }

        // Move Constructor
        vector(vector&&) = default;

        // Copy Assignment
        vector& operator=(const vector& that) 
        {
            check_size(that.my_size);
            std::copy(&that.data.get(), &(that.data.get()+that.my_size), &data.get());
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
            return data.get()+i;
        }
                    
        T& operator[](int i) 
        {
            check_index(i);
            return data.get()+i;
        }


        // Addition
        vector operator+(const vector& that) const 
        {
            check_size(that.my_size);
            vector sum(my_size);
            for (int i= 0; i < my_size; ++i) 
                sum.get()+i = (data.get()+i) + (that.get()+i);
            return sum;
        }


        struct iterator
        {
            // Attributes
            int pos = 0;
            int max;
            std::shared_ptr<T[]> data;

            // Constructors
            iterator() = default;
            iterator(const std::shared_ptr<T[]> p, const int size)
            : data(p), max(size) {};
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
            T& operator*()
            {
                if (pos<max) {return data.get()+pos;}
                else {throw std::domain_error("Iterator overflow");}
            }

            // Incrementing
            iterator& operator++()
            {
                ++pos;
                return *this;
            }
            iterator& operator++(int)
            {
                iterator tmp(*this);
                ++pos;
                return tmp;
            }
        };


        iterator begin()
        {
            if (my_size==0) {return iterator();}
            return iterator(data,my_size);
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
    a[3] = 4;
    a[4] = 5;
    std::cout << a << std::endl;

    auto i = a.begin();
    std::cout << *i << std::endl;
}