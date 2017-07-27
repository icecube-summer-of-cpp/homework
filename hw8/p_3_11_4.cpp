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
};


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
    a[0] = 2;
    a[1] = 1;
    a[2] = 0;
    a[3] = 2;
    a[4] = 4;
    std::cout << a << std::endl;
}