// red black tree implementation

// Copyright (C) 2022 Daan Meijer
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <cstddef>
#include <iterator.hpp>
#include <iterator>
#include <stdexcept>
// todo for debug purposes, remove
#include <cassert>
#include <iostream>
#include <string>

// TODO
// Check how to handle insert of a value that already exists
// Make rbtree take a Compare functor

namespace ft {
namespace detail {

struct rb_violation : public std::logic_error {

      private:
        const void *const _where;

      public:
        rb_violation(const std::string &what, const void *where)
            : std::logic_error(what), _where(where) {}

        inline const void *where() const { return _where; }
};

enum rbcolor { RB_RED, RB_BLACK };

struct rbdir {
        const bool dir;

      protected:
        rbdir(bool dir) : dir(dir) {}

      public:
        inline bool operator==(const rbdir &other) const {
                return dir == other.dir;
        }
        inline rbdir operator!() const { return rbdir(!dir); }
        inline rbdir opposite() const { return this->operator!(); }
};

template <bool Direction> struct base_dir : public rbdir {
        base_dir() : rbdir(Direction) {}
};

typedef base_dir<true> right_dir;
typedef base_dir<false> left_dir;

template <typename T> class rbnode {
        typedef rbnode this_type;

      public:
        T value;
        rbcolor color;

        this_type *parent;
        this_type *right;
        this_type *left;

        rbnode(rbcolor color = RB_BLACK, this_type *parent = NULL,
               this_type *right = NULL, this_type *left = NULL,
               const T &value = T())
            : value(value), color(color), parent(parent), right(right),
              left(left) {}

        ~rbnode() {}

        this_type *get(const rbdir &dir) {
                if (dir == right_dir())
                        return right;
                return left;
        }

        void set(const rbdir &dir, this_type *ptr) {
                if (dir == right_dir())
                        right = ptr;
                else
                        left = ptr;
        }

        inline rbdir get_dir() const {
                if (parent->left == this)
                        return left_dir();
                return right_dir();
        }

        static rbcolor node_color(const rbnode *node) {
                if (node == NULL)
                        return RB_BLACK;
                return node->color;
        }

        static this_type *bound(const rbdir &dir, this_type *node,
                                const this_type *const sentinel) {
                while (node->get(dir) != sentinel)
                        node = node->get(dir);
                return node;
        }

        static this_type *minimum(this_type *node,
                                  const this_type *const sentinel) {
                return bound(left_dir(), node, sentinel);
        }

        static this_type *maximum(this_type *node,
                                  const this_type *const sentinel) {
                return bound(right_dir(), node, sentinel);
        }

        static this_type *next(this_type *node, const this_type *sentinel,
                               const rbdir &dir) {
                if (node->get(dir) != sentinel) {
                        node = bound(dir.opposite(), node->get(dir), sentinel);
                } else {
                        this_type *parent = node->parent;
                        while (parent != sentinel
                               && node == parent->get(dir)) {
                                node = parent;
                                parent = parent->parent;
                        }
                        node = parent;
                }
                return node;
        }

        static this_type *predecessor(this_type *node,
                                      const this_type *sentinel) {
                return next(node, sentinel, left_dir());
        }

        static this_type *successor(this_type *node,
                                    const this_type *sentinel) {
                return next(node, sentinel, right_dir());
        }

        static bool
        mismatch(const this_type *lhs, const this_type *rhs,
                 const this_type *lhs_sentinel, const this_type *rhs_sentinel,
                 std::pair<const this_type *, const this_type *> **mpair) {
                if (lhs == lhs_sentinel || rhs == rhs_sentinel) {
                        if (lhs != lhs_sentinel || rhs != rhs_sentinel) {
                                *mpair = new std::pair<const this_type *,
                                                       const this_type *>(lhs,
                                                                          rhs);
                                return true;
                        } else {
                                return false;
                        }
                }
                if (lhs->value != rhs->value) {
                        *mpair = new std::pair<const this_type *,
                                               const this_type *>(lhs, rhs);
                        return true;
                }
                if (mismatch(lhs->left, rhs->left, lhs_sentinel, rhs_sentinel,
                             mpair))
                        return true;
                if (mismatch(lhs->right, rhs->right, lhs_sentinel,
                             rhs_sentinel, mpair))
                        return true;
                return false;
        }

        static std::size_t black_height(const this_type *node,
                                        const this_type *sentinel) {
                if (node == sentinel)
                        return 1;

                if (node_color(node) == RB_RED
                    && (node_color(node->left) == RB_RED
                        || node_color(node->right) == RB_RED))
                        return 0;

                const std::size_t left_height
                    = black_height(node->left, sentinel);
                const std::size_t right_height
                    = black_height(node->right, sentinel);

                if (left_height == 0 || right_height == 0
                    || left_height != right_height)
                        return 0;
                return left_height + (node_color(node) == RB_BLACK ? 1 : 0);
        }

        static bool is_valid(const this_type *node,
                             const this_type *sentinel) {
                return is_bst(node, sentinel)
                       && black_height(node, sentinel) != 0;
        }

        static void debug_print(const rbnode *node,
                                const rbnode *const sentinel,
                                const rbnode *const special = NULL,
                                std::size_t indent = 0) {
                std::cout << std::string(indent, ' ');
                if (node == sentinel) {

                        std::cout << '-' << std::endl;
                } else {
                        std::cout << (special == node ? "*" : "")
                                  << node->value << ","
                                  << (node->color == RB_BLACK ? 'B' : 'R')
                                  << std::endl;
                        debug_print(node->left, sentinel, special, indent + 4);
                        debug_print(node->right, sentinel, special,
                                    indent + 4);
                }
        }
};

template <typename T, typename Pointer, typename Reference>
struct rbtree_iterator {
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef rbnode<T> node_type;
        typedef rbtree_iterator<T, T *, T &> iterator;

        node_type *_current;
        const node_type *_sentinel;

        rbtree_iterator(const iterator &other)
            : _current(other._current), _sentinel(other._sentinel) {}
        rbtree_iterator(const node_type *current, const node_type *sentinel)
            : _current(const_cast<node_type *>(current)), _sentinel(sentinel) {
        }

        rbtree_iterator &operator=(const iterator &other) {
                if (this != &other) {
                        _current = other._current;
                        _sentinel = other._sentinel;
                }
                return *this;
        }

        inline bool operator==(const rbtree_iterator &other) const {
                return _current == other._current;
        }

        inline bool operator!=(const rbtree_iterator &other) const {
                return !(*this == other);
        }

        reference operator*() const { return _current->value; }
        pointer operator->() const { return &(this->operator*()); }

        // TODO check for performance loss by using this abstraction instead of
        // hardcoding operator++ and operator-- separately
        rbtree_iterator &advance(const rbdir &dir) {
                // TODO use node_type::next here
                _current = node_type::next(_current, _sentinel, dir);
                return *this;
        }

        rbtree_iterator &operator++() { return advance(right_dir()); }

        rbtree_iterator operator++(int) {
                const rbtree_iterator tmp(*this);
                advance(right_dir());
                return tmp;
        }

        rbtree_iterator &operator--() { return advance(left_dir()); }

        rbtree_iterator operator--(int) {
                const rbtree_iterator tmp(*this);
                advance(left_dir());
                return tmp;
        }
};

template <typename KeyType, typename ValueType, typename Allocator,
          typename Compare>
struct rbtree {
        typedef rbnode<ValueType> node_type;
        typedef KeyType key_type;
        typedef ValueType value_type;
        typedef Compare key_compare;
        typedef Allocator allocator_type;
        typedef std::size_t size_type;
        typedef value_type
            *pointer; // TODO make this use allocator member types
        typedef value_type &reference;
        typedef const value_type *const_pointer;
        typedef const value_type &const_reference;
        typedef rbtree_iterator<ValueType, ValueType *, ValueType &> iterator;
        typedef rbtree_iterator<ValueType, const ValueType *,
                                const ValueType &>
            const_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;

      private:
        node_type *_root;
        node_type _sentinel;
        size_type _size;
        allocator_type _allocator;

      public:
        rbtree()
            : _root(&_sentinel),
              _sentinel(RB_BLACK, NULL, &_sentinel, &_sentinel), _size(0) {}

        ~rbtree() { destroy_tree(_root); }

        node_type *root() { return _root; }
        const node_type *root() const { return _root; }
        node_type *sentinel() { return &_sentinel; }
        const node_type *sentinel() const { return &_sentinel; }
        iterator begin() { return iterator(sentinel()->right, sentinel()); }
        iterator end() { return iterator(sentinel(), sentinel()); }
        const_iterator begin() const {
                return const_iterator(sentinel()->right, sentinel());
        }
        const_iterator end() const {
                return const_iterator(sentinel(), sentinel());
        }
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        reverse_iterator rend() { return reverse_iterator(begin()); }

        // TODO implement a node next abstraction etc. here so that you don't
        // have to pass the sentinel every time

        node_type *create_node(const value_type &value) {
                node_type *node = _allocator.allocate(1);
                try {
                        _allocator.construct(
                            node, node_type(RB_BLACK, NULL, sentinel(),
                                            sentinel(), value));
                } catch (...) {
                        _allocator.deallocate(node, 1);
                        throw;
                }
                return node;
        }

        bool comp(const value_type &a, const value_type &b) const {
                return key_compare()(a, b);
        }

        void insert(const value_type &value) {
                node_type *insert_node = _root;
                node_type *parent_node = sentinel();

                while (insert_node != sentinel()) {
                        parent_node = insert_node;
                        if (comp(value, parent_node->value))
                                insert_node = parent_node->left;
                        else
                                insert_node = parent_node->right;
                }

                node_type *node = create_node(value);

                node->parent = parent_node;
                if (parent_node == sentinel())
                        _root = node;
                else if (comp(node->value, parent_node->value))
                        parent_node->left = node;
                else
                        parent_node->right = node;
                node->left = sentinel();
                node->right = sentinel();
                node->color = RB_RED;

                // update iterator positions
                // TODO move this to a separate function
                if (sentinel()->left == sentinel()) {
                        sentinel()->left = node;
                        sentinel()->right = node;
                } else if (sentinel()->left->right != sentinel()) {
                        sentinel()->left = sentinel()->left->right;
                } else if (sentinel()->right->left != sentinel()) {
                        sentinel()->right = sentinel()->right->left;
                }

                insert_fix(node);
        }

        void transplant(node_type *to, node_type *from) {
                if (to->parent == sentinel())
                        _root = from;
                else if (to->parent->left == to)
                        to->parent->left = from;
                else
                        to->parent->right = from;
                from->parent = to->parent;
        }

        node_type *minimum(node_type *node) {
                assert(node != sentinel()
                       && "cannot take minumum of sentinel");
                return node_type::minimum(node, sentinel());
        }

        node_type *minimum() { return minimum(root()); }

        node_type *successor(node_type *node) {
                return node_type::next(node, sentinel(), right_dir());
        }

        node_type *predecessor(node_type *node) {
                return node_type::next(node, sentinel(), left_dir());
        }

      private:
        // TODO solve collision with other search with integral types
        node_type *search(node_type *start, const value_type &key) {
                node_type *current = start;
                while (current != sentinel() && current->value != key) {
                        if (comp(key, current->value))
                                current = current->left;
                        else
                                current = current->right;
                }
                return current;
        }

        const node_type *search(const node_type *start,
                                const value_type &key) const {
                const node_type *current = start;
                while (current != sentinel() && current->value != key) {
                        if (comp(key, current->value))
                                current = current->left;
                        else
                                current = current->right;
                }
                return current;
        }

      public:
        node_type *search(const value_type &value) {
                return search(root(), value);
        }

        const node_type *search(const value_type &value) const {
                return search(root(), value);
        }

        void delete_node(node_type *const node) {
                rbcolor old_color = node->color;
                node_type *moved_node = sentinel();

                if (node->left == sentinel()) {
                        moved_node = node->right;
                        transplant(node, node->right);
                } else if (node->right == sentinel()) {
                        moved_node = node->left;
                        transplant(node, node->left);
                } else {
                        node_type *min = minimum(node->right);
                        old_color = min->color;
                        moved_node = min->right;
                        if (min != node->right) {
                                transplant(min, min->right);
                                min->right = node->right;
                                min->right->parent = min;
                        } else {
                                moved_node->parent = min;
                        }
                        transplant(node, min);
                        min->left = node->left;
                        min->left->parent = min;
                        min->color = node->color;
                }

                // update iterator positions
                // TODO move this to a separate function
                if (node == sentinel()->left) {
                        sentinel()->left = predecessor(node);
                }
                if (node == sentinel()->right) {
                        sentinel()->right = successor(node);
                }

                destroy_node(node);
                if (old_color == RB_BLACK)
                        delete_fix(moved_node);
        }

        void delete_key(const value_type &value) {
                node_type *node = search(value);
                if (node != sentinel())
                        delete_node(node);
        }

        static void assert_equal(const rbtree &lhs, const rbtree &rhs) {
                std::pair<const node_type *, const node_type *> *mismatch;
                if (node_type::mismatch(lhs._root, rhs._root, lhs.sentinel(),
                                        rhs.sentinel(), &mismatch)) {
                        std::cerr << "lhs:" << std::endl;
                        node_type::debug_print(lhs._root, lhs.sentinel(),
                                               mismatch->first);
                        std::cerr << "rhs:" << std::endl;
                        node_type::debug_print(rhs._root, rhs.sentinel(),
                                               mismatch->second);
                        assert(0 && "lhs != rhs");
                }
        }

        friend bool operator==(const rbtree &lhs, const rbtree &rhs) {
                // TODO this code can probably be refactored to something
                // simpler using the sentinel
                if (lhs._root == lhs.sentinel() || rhs._root == rhs.sentinel())
                        return lhs._root == lhs.sentinel()
                               && rhs._root() == rhs.sentinel();
                return *lhs._root == *rhs._root;
        }

        bool is_bst(const node_type *node) const {
                if (node == sentinel())
                        return true;
                const node_type *const left = node->left;
                const node_type *const right = node->right;

                if (left != sentinel() && !comp(left->value, node->value))
                        return false;
                if (right != sentinel() && comp(right->value, node->value))
                        return false;
                return is_bst(left) && is_bst(right);
        }

        bool is_bst() const { return is_bst(root()); }

        std::size_t self_check(const node_type *node) const {
                if (node == sentinel()) {
                        assert(node->color == RB_BLACK
                               && "sentinel() is not black");
                        return 0;
                }

                const node_type *const left = node->left;
                const node_type *const right = node->right;

                if (node->color == RB_RED
                    && (left->color == RB_RED || right->color == RB_RED))
                        throw rb_violation("red violation", node);

                const std::size_t left_height = self_check(left);
                const std::size_t right_height = self_check(right);

                if (left_height != right_height)
                        throw rb_violation("black violation", node);

                if (left != sentinel() && !comp(left->value, node->value))
                        throw rb_violation("bst violation left side", node);
                if (right != sentinel() && comp(right->value, node->value))
                        throw rb_violation("bst violation right side", node);

                return left_height + (node->color == RB_BLACK ? 1 : 0);
        }

        void self_check() const { self_check(root()); }

        void print() const { node_type::debug_print(_root, sentinel()); }

      private:
        void tree_assert(int condition, const node_type *node,
                         const std::string &msg = "assertion failed") {
                if (!condition) {
                        node_type::debug_print(_root, sentinel(), node);
                        std::cerr << msg << std::endl;
                        assert(0);
                }
        }

        void destroy_node(node_type *node) {
                _allocator.destroy(node);
                _allocator.deallocate(node, 1);
        }

        void destroy_tree(node_type *node) {
                if (node == sentinel())
                        return;
                destroy_tree(node->left);
                destroy_tree(node->right);
                destroy_node(node);
        }

        node_type *rotate(node_type *node, const rbdir &dir) {
                tree_assert(node->get(dir.opposite()) != sentinel(), node,
                            "cannot rotate further");
                node_type *new_root = node->get(dir.opposite());

                node->set(dir.opposite(), new_root->get(dir));
                if (new_root->get(dir) != sentinel())
                        new_root->get(dir)->parent = node;
                new_root->parent = node->parent;
                if (node->parent == sentinel())
                        _root = new_root;
                else if (node == node->parent->get(dir))
                        node->parent->set(dir, new_root);
                else
                        node->parent->set(dir.opposite(), new_root);
                new_root->set(dir, node);
                node->parent = new_root;
                return new_root;
        }

      public: // TODO delete these two functions
        node_type *rotate_left(node_type *node) {
                return rotate(node, left_dir());
        }

        node_type *rotate_right(node_type *node) {
                return rotate(node, right_dir());
        }

      private:
        void insert_fix(node_type *node) {
                while (node_type::node_color(node->parent) == RB_RED) {
                        const rbdir parent_dir = node->parent->get_dir();
                        node_type *uncle
                            = node->parent->parent->get(parent_dir.opposite());
                        if (node_type::node_color(uncle) == RB_RED) {
                                node->parent->color = RB_BLACK;
                                uncle->color = RB_BLACK;
                                node->parent->parent->color = RB_RED;
                                node = node->parent->parent;
                        } else {
                                const rbdir node_dir = node->get_dir();
                                if (node
                                    == node->parent->get(
                                        parent_dir.opposite())) {
                                        node = node->parent;
                                        rotate(node, parent_dir);
                                }
                                node->parent->color = RB_BLACK;
                                node->parent->parent->color = RB_RED;
                                rotate(node->parent->parent,
                                       parent_dir.opposite());
                        }
                }
                _root->color = RB_BLACK;
        }

        void delete_fix(node_type *node) {
                while (node != root() && node->color == RB_BLACK) {
                        const rbdir dir = node->get_dir();
                        node_type *sibling = node->parent->get(dir.opposite());
                        if (sibling->color == RB_RED) {
                                sibling->color = RB_BLACK;
                                node->parent->color = RB_RED;
                                rotate(node->parent, dir);
                                sibling = node->parent->get(dir.opposite());
                        }
                        if (sibling->get(dir)->color == RB_BLACK
                            && sibling->get(dir.opposite())->color
                                   == RB_BLACK) {
                                sibling->color = RB_RED;
                                node = node->parent;
                        } else {
                                if (sibling->get(dir.opposite())->color
                                    == RB_BLACK) {
                                        sibling->get(dir)->color = RB_BLACK;
                                        sibling->color = RB_RED;
                                        rotate(sibling, dir.opposite());
                                        sibling = node->parent->get(
                                            dir.opposite());
                                }
                                sibling->color = node->parent->color;
                                node->parent->color = RB_BLACK;
                                sibling->get(dir.opposite())->color = RB_BLACK;
                                rotate(node->parent, dir);
                                node = root();
                        }
                }
                node->color = RB_BLACK;
        }
};

template <typename ValueType>
bool operator==(const rbnode<ValueType> &lhs, const rbnode<ValueType> &rhs) {
        if (lhs.value != rhs.value)
                return false;

        return ((lhs.left == lhs.sentinel() && rhs.left == rhs.sentinel())
                || (rhs.left != rhs.sentinel() && *lhs.left == *rhs.left))
               && ((lhs.right == lhs.sentinel() && rhs.right == rhs.sentinel())
                   || (rhs.right != rhs.entinel()
                       && *lhs.right == *rhs.right));
}

}
}

#endif /* RED_BLACK_TREE_HPP */
