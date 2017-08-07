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
            std::shared_ptr<iter_entry> prev;
            std::shared_ptr<iter_entry> next;

            // Constructor
            iter_entry() : value(), prev(nullptr), next(nullptr) {}
            iter_entry(const T& val) : value(val), prev(nullptr), next(nullptr) {}
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
            void link(iter_entry nxt)
            {
                next = std::make_shared<iter_entry>(nxt);
                next->prev = std::make_shared<iter_entry>(*this);
            }
            void linkback(iter_entry prv)
            {
                prev = std::make_shared<iter_entry>(prv);
                prev->next = std::make_shared<iter_entry>(*this);
            }
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
            T* operator->() {return &curr.value;}

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

            // Decrementing
            iterator& operator--()
            {
                curr = *curr.prev;
                return *this;
            }
            iterator& operator--(int)
            {
                iterator tmp(*this);
                curr = *curr.prev;
                return tmp;
            }

            // Equality
            bool operator==(const iterator& rhs)
            {
                if (curr.value!=rhs.curr.value) {return false;}
                iterator a = *this;
                iterator b = rhs;
                while (a.curr.next!=nullptr && b.curr.next!=nullptr)
                {
                    ++a;
                    ++b;
                    if (a.curr.value!=b.curr.value) {return false;}
                }
                if (a.curr.next!=nullptr || b.curr.next!=nullptr) {return false;}
                else {return true;}
            }
            bool operator!=(const iterator& rhs) {return !(*this==rhs);}
        };

        iterator begin()
        {
            if (my_size==0) {return iterator();}
            iter_entry curr;
            for (int i=my_size-1; i>=0; --i)
            {
                iter_entry prev(data[i]);
                prev.link(curr);
                // std::cout << "  curr: " << curr.value << std::endl;
                // std::cout << "  curr.next: " << curr.next.get() << std::endl;
                curr = prev;
            }
            // std::cout << "  first: " << curr.value << std::endl;
            // std::cout << "  first.next: " << curr.next.get() << std::endl;
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


// template <typename T>
std::ostream& operator<<(std::ostream& os, const vector<int>::iterator& i)
{
    return os << "(" << i.curr.prev.get() << ")->" << i.curr.value
    << "->(" << i.curr.next.get() << ")";
}



int main()
{
    vector<int> a(5);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    a[3] = 2;
    a[4] = 5;
    std::cout << a << std::endl;

    std::cout << "\nbegin" << std::endl;
    auto i0 = a.begin();
    std::cout << "i0 = " << i0 << std::endl;
    while (i0.curr.next!=nullptr) {
        ++i0;
        std::cout << "i0 = " << i0 << std::endl;
    }

    std::cout << a << std::endl;

    std::cout << "\nend" << std::endl;
    auto i2 = a.end();
    std::cout << "i2 = " << i2 << std::endl;
    std::cout << "i2==i0 : 1=" << (i2==i0) << std::endl;

    std::cout << "\nincrementing" << std::endl;
    int inc_amount = 2;
    auto id = a.begin();
    for (int i=0; i<inc_amount; ++i)
    {
        std::cout << "id[" << i << "] = " << id << std::endl;
        ++id;
    }
    std::cout << "id[" << inc_amount << "] = " << id << std::endl;

    std::cout << "\ndecrementing" << std::endl;
    for (int i=inc_amount-1; i>=0; --i)
    {
        --id;
        std::cout << "id[" << i << "] = " << id << std::endl;
    }

    std::cout << "\ndereferencing" << std::endl;
    auto i3 = a.begin();
    std::cout << "*i3 = " << *i3 << std::endl;
    ++i3;
    std::cout << "*i3 = " << *i3 << std::endl;
    std::cout << "*i3++ = " << *i3++ << std::endl;

    struct val_container
    {
        int val;
        val_container() = default;
        val_container(const int v) : val(v) {}
    };
    vector<val_container> b(1);
    b[0] = val_container(10);
    auto ib = b.begin();
    std::cout << "ib->val = " << ib->val << std::endl;


    std::cout << "\nequality" << std::endl;
    auto i4 = a.begin();
    auto j = a.begin();
    std::cout << "same val, same pos" << std::endl;
    std::cout << "  i4 = " << i4 << std::endl;
    std::cout << "  j = " << j << std::endl;
    std::cout << "  1=" << (i4==j) << std::endl;

    std::cout << "same val, same pos (increment in equality)" << std::endl;
    std::cout << "  i4 next val = " << i4.curr.next->value << std::endl;
    std::cout << "  j next val = " << j.curr.next->value << std::endl;
    std::cout << "  1=" << (++i4==++j) << std::endl;

    ++j;
    std::cout << "different val, different pos" << std::endl;
    std::cout << "  i4 = " << i4 << std::endl;
    std::cout << "  j = " << j << std::endl;
    std::cout << "  0=" << (i4==j) << std::endl;
    
    ++j;
    std::cout << "same val, different pos" << std::endl;
    std::cout << "  i4 = " << i4 << std::endl;
    std::cout << "  j = " << j << std::endl;
    std::cout << "  0=" << (i4==j) << std::endl;
}