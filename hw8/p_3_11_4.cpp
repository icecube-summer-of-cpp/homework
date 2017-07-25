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
};


template <typename T>
std::ostream& operator<<(std::ostream& os, const vector<T>& v)
{
  os << '[';
  for (int i= 0; i < v.size(); ++i) os << v[i] << ',';
  os << ']';
  return os;
};



template <typename T>
struct list_entry
{
    list_entry(const T& value) : value(value), next(0) {}

    T              value;
    list_entry<T>* next;
};

template <typename T>
struct list_iterator
{
    list_iterator(list_entry<T>* entry) : entry(entry) {}
    bool operator!=(const list_iterator<T>& that) const 
    { return entry != that.entry; }

    list_iterator<T> operator++() 
    { entry= entry->next; return *this; }

    list_iterator<T> operator++(int) 
    {
        list_iterator<T> tmp(*this);
        entry= entry->next;
        return tmp;
    }
    T& operator*() { return entry->value; }
    T operator*() const { return entry->value; }

    private:
        list_entry<T>* entry;
};

template <typename T>
struct list
{
    list() : first(0), last(0) {}
    ~list() { while (first) { list_entry<T> *tmp= first->next; delete first; first= tmp; } }
    void append(const T& x) { last= (first ? last->next : first)= new list_entry<T>(x); }
    list_iterator<T> begin() const { return list_iterator<T>(first); }
    list_iterator<T> end() const { return list_iterator<T>(0); }

    list_entry<T> *first, *last;
};


template <typename T>
std::ostream& operator<<(std::ostream& os, const list<T>& l)
{
    for (list_iterator<T> it=l.begin();  it != l.end(); ++it) os << *it << ',';
    return os;
};



int main()
{
    vector<int> a(3);
    a[0] = 2;
    a[1] = 1;
    a[2] = 0;
    std::cout << a << std::endl;

    list<int> b;
    b.append(3);
    b.append(2);
    b.append(1);
    std::cout << b << std::endl;

}