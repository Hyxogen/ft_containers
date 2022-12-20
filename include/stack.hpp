#ifndef STACK_HPP
#define STACK_HPP

#include <vector.hpp>

namespace ft {

template <class T, class Container = ft::vector<T> > class stack {
      public:
        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;
	typedef typename Container::reference reference;
	typedef typename Container::const_reference const_reference;
        typedef Container container_type;

      protected:
        Container c;

      public:
        explicit stack(const Container &container = Container())
            : c(container) {}
        stack(const stack &other) : c(other.c) {}

        stack &operator=(const stack &other) {
                if (this != &other) {
                        c = other.c;
                }
                return *this;
        }

        bool empty() const { return c.empty(); }
        size_type size() const { return c.size(); }
        value_type &top() { return c.back(); }
        const value_type &top() const { return c.back(); }
        void push(const value_type &x) { return c.push_back(x); }
        void pop() { c.pop_back(); }

        friend bool operator==(const stack &lhs, const stack &rhs) {
                return lhs.c == rhs.c;
        }

        friend bool operator<(const stack &lhs, const stack &rhs) {
                return lhs.c < rhs.c;
        }
};

template <class T, class Container>
bool operator!=(const stack<T, Container> &lhs,
                const stack<T, Container> &rhs) {
        return !(lhs == rhs);
}

template <class T, class Container>
bool operator>(const stack<T, Container> &lhs,
               const stack<T, Container> &rhs) {
        return rhs < lhs;
}

template <class T, class Container>
bool operator<=(const stack<T, Container> &lhs,
                const stack<T, Container> &rhs) {
        return !(lhs > rhs);
}

template <class T, class Container>
bool operator>=(const stack<T, Container> &lhs,
                const stack<T, Container> &rhs) {
        return !(lhs < rhs);
}

}

#endif
