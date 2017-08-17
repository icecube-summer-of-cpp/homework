/**
 * Solution to exercise 3.11.4
 */
#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>

namespace details
{
    /**
     * @brief Random access iterator for custom vector class
     */
    template<typename T>
    class iterator : public std::iterator<std::random_access_iterator_tag, T>
    {
        public:
            using difference_type = typename std::iterator<
                std::random_access_iterator_tag, T>::difference_type;

            /**
             * Create an iterator at the vector position @p element.
             * @param element Vector position
             */
            iterator(T* element = nullptr) : element_(element) {}

            iterator(const iterator&) = default;
            iterator(iterator&&) = default;

            ~iterator() = default;

            iterator& operator=(const iterator&) = default;
            iterator& operator=(iterator&&) = default;

            /**
             * @return Both iterators are at the same vector position.
             */
            bool operator==(const iterator& other) const
            {
                return element_ == other.element_;
            }

            /**
             * @return Both iterators are at different vector positions.
             */
            bool operator!=(const iterator& other) const
            {
                return element_ != other.element_;
            }

            /**
             * @return Element at current vector position
             */
            T& operator*() {return *element_;}

            /**
             * @return Current vector position
             */
            T* operator->() {return element_;}

            /**
             * Move to the next vector element.
             * @return Iterator at the current vector position
             */
            iterator operator++(int)
            {
                iterator tmp(*this);
                ++element_;
                return tmp;
            }

            /**
             * Move to the next vector element.
             */
            iterator& operator++()
            {
                ++element_;
                return *this;
            }

            /**
             * Move to the previous vector element.
             * @return Iterator at the current vector position
             */
            iterator operator--(int)
            {
                iterator tmp = *this;
                --element_;
                return tmp;
            }

            /**
             * Move to the previous vector element.
             */
            iterator& operator--()
            {
                --element_;
                return *this;
            }

            /**
             * Move forward n-times along vector.
             * @param n Distance between previous and new vector position
             * @return Iterator at new vector position
             */
            iterator operator+(difference_type n) const
            {
                return iterator(element_ + n);
            }

            friend iterator operator+(difference_type n, const iterator& it)
            {
                return iterator(n + it.element_);
            }

            /**
             * Move backwards n-times along vector.
             * @param n Distance between previous and new vector position
             * @return Iterator at new vector position
             */
            iterator operator-(difference_type n) const
            {
                return iterator(element_ - n);
            }

            friend iterator operator-(difference_type n, const iterator& it)
            {
                return iterator(n - it.element_);
            }

            /**
             * @return Distance between two vector positions
             */
            difference_type operator-(const iterator& other) const
            {
                return element_ - other.element_;
            }

            /**
             * @return Iterator points left from the current vector
             * position.
             */
            bool operator<(const iterator& other) const
            {
                return element_ < other.element_;
            }

            /**
             * @return Iterator points right from the current vector
             * position.
             */
            bool operator>(const iterator& other) const
            {
                return element_ > other.element_;
            }

            /**
             * @return Iterator points left from or at the current
             * vector position.
             */
            bool operator<=(const iterator& other) const
            {
                return element_ <= other.element_;
            }

            /**
             * @return Iterator points right from or at the current
             * vector position.
             */
            bool operator>=(const iterator& other) const
            {
                return element_ >= other.element_;
            }

            /**
             * Move forward n-times along vector.
             * @param n Distance between previous and new vector position
             */
            iterator& operator+=(difference_type n)
            {
                element_ += n;
                return *this;
            }

            /**
             * Move backwards n-times along vector.
             * @param n Distance between previous and new vector position
             */
            iterator& operator-=(difference_type n)
            {
                element_ -= n;
                return *this;
            }

            /**
             * @param n Distance between current and other vector
             * position
             * @return Element at distant vector position
             */
            T& operator[](difference_type n) const
            {
                return element_[n];
            }

        private:
            T* element_;
   };
};

/**
 * @brief Custom vector container class
 */
template<typename T>
class vector
{
    public:
        /**
         * Create an empty vector of size @p size.
         * @param size Vector size
         */
        explicit vector(unsigned int size = 0)
            : size_(size), data_(new T[size_])
        {}

        /**
         * Create a vector from a list of values.
         * @param vals List of values
         */
        vector(const std::initializer_list<T>& vals)
            : size_(vals.size()), data_(new T[size_])
        {
            std::copy(std::begin(vals), std::end(vals), &data_[0]);
        }

        vector(const vector& other) : size_(other.size_), data_(new T[size_])
        {
            std::copy(&other.data_[0], &other.data_[other.size_], &data_[0]);
        }

        vector(vector&&) = default;

        ~vector() = default;

        /**
         * Assign a list of values to the vector.
         * @param vals List of values
         */
        vector& operator=(const std::initializer_list<T>& vals)
        {
            assert(vals.size() == size_);
            std::copy(std::begin(vals), std::end(vals), &data_[0]);
            return *this;
        }

        vector& operator=(const vector& other)
        {
            assert(other.size_ == size_);
            std::copy(&other.data_[0], &other.data_[other.size_], &data_[0]);
            return *this;
        }

        vector& operator=(vector&&) = default;

        /**
         * Access vector element at index @p i.
         * @param i Index
         * @return Vector element
         */
        const T& operator[](int i) const
        {
            assert(i < size_);
            return data_[i];
        }

        /**
         * @return Size of vector
         */
        unsigned int size() const
        {
            return size_;
        }

        using iterator = details::iterator<T>;
        using const_iterator = details::iterator<const T>;

        /**
         * @return Iterator pointing to the first vector element
         */
        iterator begin()
        {
            return iterator(&data_[0]);
        }

        const_iterator begin() const
        {
            return const_iterator(&data_[0]);
        }

        /**
         * @return Iterator pointing to the last vector element
         */
        iterator end()
        {
            return iterator(&data_[size_]);
        }

        const_iterator end() const
        {
            return const_iterator(&data_[size_]);
        }

        /**
         * @return Iterator pointing to the first vector element; cannot
         * change the vector elements.
         */
        const_iterator cbegin() const
        {
            return const_iterator(&data_[0]);
        }

        /**
         * @return Iterator pointing to the last vector element; cannot
         * change the vector elements.
         */
        const_iterator cend() const
        {
            return const_iterator(&data_[size_]);
        }

    private:
        unsigned int size_;
        std::unique_ptr<T[]> data_;
};

int main()
{
    vector<double> v = {1., 0., 3., 2.};
    std::cout << "Created vector of size " << v.size() << '.' << std::endl;

    std::cout << "Sort vector." << std::endl;
    std::sort(v.begin(), v.end());

    std::cout << "Entries:" << std::endl;
    for (auto x : v)
    {
        std::cout << x << std::endl;
    }
}
