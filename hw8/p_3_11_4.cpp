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
        explicit vector(int size)
            : my_size(size), data( new T[my_size] ) {}

        vector()
            : my_size(0), data(0) {}

        vector(const vector& that)
            : my_size(that.my_size), data(new T[my_size])
        {
            std::copy(&that.data[0], &that.data[that.my_size], &data[0]);
        }

        vector& operator=(const vector& that) 
        {
            check_size(that.my_size);
            std::copy(&that.data[0], &that.data[that.my_size], &data[0]);
            return *this;
        }

        int size() const { return my_size; }

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

        vector operator+(const vector& that) const 
        {
            check_size(that.my_size);
            vector sum(my_size);
            for (int i= 0; i < my_size; ++i) 
                sum[i] = data[i] + that[i];
            return sum;
        }



        struct iterator_entry
        {
            iterator_entry(const T& value)
                : value(value), next(0) {}
            T value;
            iterator_entry* next;
        };


        class iterator
        {
            public:
                using value_type = T;

                iterator(iterator_entry* entry) : entry(entry) {}

                iterator operator++() {entry = entry->next; return *this;}
                iterator operator++(int) 
                {
                    iterator tmp(*this);
                    entry = entry->next;
                    return tmp;
                }

                T& operator*() {return entry->value;}
                T* operator->() {return entry->value;}

                bool operator==(const iterator& rhs)
                {return entry==rhs.entry;}

                bool operator!=(const iterator& rhs)
                {
                    std::cout << "neq: ";
                    std::cout << entry << "!=" << rhs.entry << std::endl;
                    return entry!=rhs.entry;}

            private:
                iterator_entry* entry;
        };

        class const_iterator
        {
            public:
                using value_type = T;

                const_iterator(iterator_entry* entry) : entry(entry) {}

                const_iterator operator++() {entry = entry->next; return *this;}
                const_iterator operator++(int) 
                {
                    const_iterator tmp(*this);
                    entry = entry->next;
                    return tmp;
                }

                const T& operator*() {return entry->value;}
                const T* operator->() {return entry->value;}

                bool operator==(const const_iterator& rhs)
                {return entry->value == rhs->value;}

                bool operator!=(const const_iterator& rhs)
                {return entry->value != rhs->value;}

            private:
                iterator_entry* entry;
        };


        iterator begin()
        {
            std::cout << "begin" << std::endl;
            if (my_size==0) {return iterator(0);}
            std::cout << "  not zero" << std::endl;
            iterator_entry curr(0);
            std::cout << "  setup curr" << std::endl;
            iterator_entry next(data[my_size-1]);
            std::cout << "  setup next" << std::endl;
            // std::cout << next.next;
            // std::cout << "  final: " << next.next << std::endl;
            for (int i=my_size-2; i>=0; --i)
            {
                std::cout << i << std::endl;
                std::cout << "  next=" << next.value;
                std::cout << " (" << next.next << ")" << std::endl;
                curr.value = data[i];
                std::cout << "  curr=" << curr.value;
                curr.next = &next;
                std::cout << "  curr.next=" << curr.next->value;
                std::cout << " (" << curr.next << ")" << std::endl;
                iterator_entry next = curr;
            }
            std::cout << "begin done" << std::endl;
            return iterator(&curr);
        }

        iterator end()
        {
            std::cout << "end" << std::endl;
            return iterator(0);
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

    std::cout << "start loop" << std::endl;
    for (auto b=a.begin(); b!=a.end(); b++)
    {
        std::cout << "loop" << std::endl;
        std::cout << *b << std::endl;
    }
}