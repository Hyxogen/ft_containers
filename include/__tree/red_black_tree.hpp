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
#include <utility.hpp>
// todo for debug purposes, remove
#include <cassert>
#include <iostream>
#include <string>

// TODO
// Check how to handle insert of a value that already exists

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

template <typename T> struct use_self : public std::unary_function<T, T> {
        typedef std::unary_function<T, T> base;
        typedef typename base::argument_type argument_type;
        typedef typename base::result_type result_type;

        const result_type &operator()(const argument_type &x) const {
                return x;
        }
};

template <typename Pair>
struct use_first
    : public std::unary_function<Pair, typename Pair::first_type> {
        typedef std::unary_function<Pair, typename Pair::first_type> base;
        typedef typename base::argument_type argument_type;
        typedef typename base::result_type result_type;

        const result_type &operator()(const argument_type &x) const {
                return x.first;
        }
};

enum rbcolor { RB_RED, RB_BLACK };

//TODO rename to rbside
struct rbdir {
        bool dir;

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

struct rbnode_base {
        typedef rbnode_base this_type;

        rbcolor color;
        this_type *right;
        this_type *left;
        this_type *parent;

        rbnode_base(rbcolor color = RB_BLACK, this_type *parent = NULL,
                    this_type *right = NULL, this_type *left = NULL)
                : color(color), right(right), left(left), parent(parent) {}

        void swap(this_type &other) {
                std::swap(color, other.color);
                std::swap(right, other.right);
                std::swap(left, other.left);
                std::swap(parent, other.parent);
        }
        
        inline this_type *get(const rbdir &dir) {
                if (dir == right_dir())
                        return right;
                return left;
        }

        inline void set(const rbdir &dir, this_type *ptr) {
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

	static rbcolor get_color(const this_type *const node) {
		if (node == NULL) {
			return RB_BLACK;
		}
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
};

template <typename T> struct rbnode : public rbnode_base {
        typedef rbnode this_type;
        T value;

        rbnode(rbcolor color = RB_BLACK, this_type *parent = NULL,
               this_type *right = NULL, this_type *left = NULL,
               const T &value = T())
            : rbnode_base(color, parent, right, left), value(value) {}

        ~rbnode() {}

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
                if (mismatch(static_cast<const this_type *>(lhs->left),
                             static_cast<const this_type *>(rhs->left),
                             lhs_sentinel, rhs_sentinel, mpair))
                        return true;
                if (mismatch(static_cast<const this_type *>(lhs->right),
                             static_cast<const this_type *>(rhs->right),
                             lhs_sentinel, rhs_sentinel, mpair))
                        return true;
                return false;
        }

        static void debug_print(const rbnode *node,
                                const rbnode *const sentinel,
                                const rbnode *const special = NULL,
                                std::size_t indent = 0) {
                std::cout << std::string(indent, ' ');
                if (node == sentinel) {

                        std::cout << '-' << std::endl;
                } else {
                        std::cout
                            << (special == node ? "*" : "") << node->value
                            << ","
                            << (rbnode_base::get_color(node) == RB_BLACK ? 'B'
                                                                         : 'R')
                            << std::endl;
                        debug_print(static_cast<const rbnode *>(node->left),
                                    sentinel, special, indent + 4);
                        debug_print(static_cast<const rbnode *>(node->right),
                                    sentinel, special, indent + 4);
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
        
        reference operator*() const { return _current->value; }
        pointer operator->() const { return &(this->operator*()); }

        // TODO check for performance loss by using this abstraction instead of
        // hardcoding operator++ and operator-- separately
        rbtree_iterator &advance(const rbdir &dir) {
                // TODO use node_type::next here
                _current = static_cast<node_type *>(
                    node_type::next(_current, _sentinel, dir));
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

// See lwg defect 179
template <typename T, typename PointerA, typename ReferenceA,
          typename PointerB, typename ReferenceB>
inline bool operator==(const rbtree_iterator<T, PointerA, ReferenceA> &lhs,
                       const rbtree_iterator<T, PointerB, ReferenceB> &rhs) {
        return lhs._current == rhs._current;
}

template <typename T, typename PointerA, typename ReferenceA,
          typename PointerB, typename ReferenceB>
inline bool operator!=(const rbtree_iterator<T, PointerA, ReferenceA> &lhs,
                       const rbtree_iterator<T, PointerB, ReferenceB> &rhs) {
        return !(lhs == rhs);
}

template <typename KeyType, typename ValueType, typename KeyExtract,
          typename Compare, typename Allocator>
struct rbtree_base_types {
        typedef KeyType key_type;
        typedef ValueType value_type;
        typedef rbnode<value_type> node_type;
        typedef Compare key_compare;
        typedef Allocator allocator_type;
        typedef std::size_t size_type;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::reference reference;
        typedef typename Allocator::const_pointer const_pointer;
        typedef typename Allocator::const_reference const_reference;
        typedef rbtree_iterator<value_type, value_type *, value_type &>
            iterator;
        typedef rbtree_iterator<value_type, const value_type *,
                                const value_type &>
            const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef KeyExtract key_extract_type;
};

template <typename KeyType, typename PairType, typename Compare,
          typename Allocator>
struct rbtree_base
    : public rbtree_base_types<KeyType, PairType, use_first<PairType>, Compare,
                               Allocator> {
        typedef rbtree_base_types<KeyType, PairType, use_first<PairType>,
                                  Compare, Allocator>
            base;
        // TODO add value_compare type
        using typename base::node_type;
        using typename base::key_type;
        using typename base::value_type;
        using typename base::key_compare;
        using typename base::allocator_type;
        using typename base::size_type;
        using typename base::iterator;
        using typename base::const_iterator;
        using typename base::reverse_iterator;
        using typename base::const_reverse_iterator;
        using typename base::key_extract_type;
};

template <typename KeyType, typename Compare, typename Allocator>
struct rbtree_base<KeyType, KeyType, Compare, Allocator>
    : public rbtree_base_types<KeyType, KeyType, use_self<KeyType>, Compare,
                               Allocator> {
        typedef rbtree_base_types<KeyType, KeyType, use_self<KeyType>, Compare,
                                  Allocator>
            base;
        // TODO add value_compare type
        using typename base::node_type;
        using typename base::key_type;
        using typename base::value_type;
        using typename base::key_compare;
        using typename base::allocator_type;
        using typename base::size_type;
        using typename base::iterator;
        using typename base::const_iterator;
        using typename base::reverse_iterator;
        using typename base::const_reverse_iterator;
        using typename base::key_extract_type;
};

template <typename KeyType, typename ValueType, typename Compare,
          typename Allocator>
struct rbtree_base_alloc
    : public rbtree_base<KeyType, ValueType, Compare, Allocator> {
        typedef rbtree_base<KeyType, ValueType, Compare, Allocator> base;

        using typename base::node_type;
        using typename base::key_type;
        using typename base::value_type;
        using typename base::key_compare;
        using typename base::allocator_type;
        using typename base::size_type;
        using typename base::iterator;
        using typename base::const_iterator;
        using typename base::reverse_iterator;
        using typename base::const_reverse_iterator;
        using typename base::key_extract_type;
        // TODO add value_compare type
        
      protected:
        node_type *_root;
        allocator_type _allocator;

        rbtree_base_alloc(const allocator_type &alloc = allocator_type())
            : _root(NULL),
              _allocator(alloc) {}

        // This copy constructor only copies the allocator
        // It will not copy any nodes
        // TODO remove as it is confusing
        rbtree_base_alloc(const rbtree_base_alloc &other)
            : _root(NULL),
              _allocator(other._allocator) {}

        ~rbtree_base_alloc() { destroy_tree(_root); }

        void swap(rbtree_base_alloc &other) {
                std::swap(_root, other._root);
                std::swap(_allocator, other._allocator);
        }

        void destroy_node(node_type *node) {
                _allocator.destroy(node);
                _allocator.deallocate(node, 1);
        }

        void destroy_tree(node_type *node) {
                if (node == sentinel())
                        return;
                destroy_tree(static_cast<node_type *>(node->left));
                destroy_tree(static_cast<node_type *>(node->right));
                destroy_node(node);
        }

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

      public:
        node_type *root() { return _root; }
        const node_type *root() const { return _root; }
        node_type *sentinel() { return NULL; }
        const node_type *sentinel() const { return NULL; }
};

template <typename KeyType, typename ValueType, typename Compare,
          typename Allocator>
struct rbtree
    : public rbtree_base_alloc<KeyType, ValueType, Compare, Allocator> {
        typedef rbtree_base_alloc<KeyType, ValueType, Compare, Allocator> base;
        using typename base::node_type;
        using typename base::key_type;
        using typename base::value_type;
        using typename base::key_compare;
        using typename base::allocator_type;
        using typename base::size_type;
        using typename base::iterator;
        using typename base::const_iterator;
        using typename base::reverse_iterator;
        using typename base::const_reverse_iterator;
        using typename base::key_extract_type;
        //typedef typename base::value_type value_type;
         // TODO add value_compare type
 
      private:
        using base::_root;
        size_type _size;
        const key_extract_type _key_extract;
        key_compare _key_compare;
	rbnode_base _anchor;

      public:
        rbtree()
            : base(), _size(0), _key_extract(), _key_compare(),
              _anchor(RB_BLACK, NULL, NULL, NULL) {}

        rbtree(const key_compare &comp, const allocator_type &alloc)
            : base(alloc), _size(0), _key_extract(), _key_compare(comp),
              _anchor(RB_BLACK, NULL, NULL, NULL) {}

        template <typename InputIt>
        rbtree(InputIt first, InputIt last,
               const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type())
            : base(alloc), _size(0), _key_extract(), _key_compare(comp),
              _anchor(RB_BLACK, NULL, NULL, NULL) {
                insert(first, last);
        }

        rbtree(const rbtree &other)
            : base(other), _size(0), _key_extract(),
              _key_compare(other._key_compare),
              _anchor(RB_BLACK, NULL, NULL, NULL) {
                insert(other.begin(), other.end());
        }

        // TODO remove these two and make everything that use it refer to base
        using base::sentinel;
        using base::root;

        iterator begin() {
                return iterator(static_cast<node_type *>(anchor()->right),
                                sentinel());
        }
        iterator end() {
                return iterator(static_cast<node_type *>(anchor()),
                                sentinel());
        }
        const_iterator begin() const {
                return const_iterator(
                    static_cast<const node_type *>(anchor()->right),
                    sentinel());
        }
        const_iterator end() const {
                return const_iterator(static_cast<const node_type *>(anchor()),
                                      sentinel());
        }
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rbegin() const {
                return const_reverse_iterator(end());
        }
        const_reverse_iterator rend() const {
                return const_reverse_iterator(begin());
        }
        rbnode_base *anchor() { return &_anchor; }
        const rbnode_base *anchor() const { return &_anchor; }
        //TODO add const_reverse_iterator

        bool comp(const value_type &a, const value_type &b) const {
                return _key_compare(_key_extract(a), _key_extract(b));
        }

        void insert_fix_iterators(rbnode_base *inserted_node) {
                if (anchor()->left == sentinel()) {
                        anchor()->left = inserted_node;
                        anchor()->right = inserted_node;
                } else if (anchor()->left->right != sentinel()) {
                        anchor()->left = anchor()->left->right;
                } else if (anchor()->right->left != sentinel()) {
                        anchor()->right = anchor()->right->left;
                }
        }

        ft::pair<iterator, bool> insert(const value_type &value) {
                node_type *insert_node = root();
                node_type *parent_node = sentinel();

                while (insert_node != sentinel()) {
                        parent_node = insert_node;
                        if (comp(value, parent_node->value)) {
                                insert_node = static_cast<node_type *>(
                                    parent_node->left);
                        } else if (comp(parent_node->value, value)) {
                                insert_node = static_cast<node_type *>(
                                    parent_node->right);
                        } else {
                                return ft::make_pair(
                                    iterator(parent_node, sentinel()), false);
                        }
                }
                node_type *node = base::create_node(value);

                node->parent = parent_node;
                if (parent_node == sentinel())
                        _root = node;
                else if (comp(node->value, parent_node->value))
                        parent_node->left = node;
                else
                        parent_node->right = node;
                node->color = RB_RED;

                insert_fix_iterators(node);
                insert_fix(node);
                return ft::make_pair(iterator(node, sentinel()), true);
        }

        template <typename InputIt>
        void insert(InputIt first, InputIt last) {
                for (; first != last; ++first) {
                        insert(*first);
                }
        }

        rbnode_base *transplant(rbnode_base *to, rbnode_base *from) {
                if (to->parent == sentinel())
                        _root = static_cast<node_type *>(from);
                else if (to->parent->left == to)
                        to->parent->left = from;
                else
                        to->parent->right = from;
		if (from != NULL)
                	from->parent = to->parent;
		return to->parent;
        }

        rbnode_base *minimum(rbnode_base *node) {
                assert(node != sentinel()
                       && "cannot take minumum of sentinel");
                return node_type::minimum(node, sentinel());
        }

        rbnode_base *minimum() { return minimum(root()); }

        rbnode_base *successor(rbnode_base *node) {
                return node_type::next(node, sentinel(), right_dir());
        }

        rbnode_base *predecessor(rbnode_base *node) {
                return node_type::next(node, sentinel(), left_dir());
        }

      private:
        // TODO solve collision with other search with integral types
        node_type *search(node_type *start, const value_type &key) {
                node_type *current = start;
                while (current != sentinel()) {
                        if (comp(key, current->value)) {
                                current
                                    = static_cast<node_type *>(current->left);
                        } else if (comp(current->value, key)) {
                                current
                                    = static_cast<node_type *>(current->right);
                        } else {       
                                break;
                        }
                }
                return current;
        }

        const node_type *search(const node_type *start,
                                const value_type &key) const {
                const node_type *current = start;
                while (current != sentinel()) {
                        if (comp(key, current->value)) {
                                current = static_cast<const node_type *>(
                                    current->left);
                        } else if (comp(current->value, key)) {
                                current = static_cast<const node_type *>(
                                    current->right);
                        } else {
                                break;
                        }
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
                rbnode_base *moved_node = sentinel();
		rbnode_base *parent = sentinel();

                if (node->left == sentinel()) {
                        moved_node = node->right;
                        parent = transplant(node, node->right);
                } else if (node->right == sentinel()) {
                        moved_node = node->left;
                        parent = transplant(node, node->left);
                } else {
                        rbnode_base *min = minimum(node->right);
                        old_color = min->color;
                        moved_node = min->right;
                        if (min != node->right) {
                                parent = transplant(min, min->right);
                                min->right = node->right;
                                min->right->parent = min;
                        } else {
                                parent = min;
                        }
                        transplant(node, min);
                        min->left = node->left;
                        min->left->parent = min;
                        min->color = node->color;
                }

                // update iterator positions
                // TODO move this to a separate function
                if (node == anchor()->left) {
                        anchor()->left = predecessor(node);
                }
                if (node == anchor()->right) {
                        anchor()->right = successor(node);
                }

                base::destroy_node(node);
                if (old_color == RB_BLACK)
                        delete_fix(moved_node, parent);
        }

        void delete_key(const value_type &value) {
                node_type *node = search(value);
                if (node != sentinel())
                        delete_node(node);
        }

        void swap(rbtree &other) {
                std::swap(_size, other._size);
                std::swap(_key_compare, other._key_compare);
                base::swap(other);
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
                const node_type *const left
                    = static_cast<const node_type *>(node->left);
                const node_type *const right
                    = static_cast<const node_type *>(node->right);

                if (left != sentinel() && !comp(left->value, node->value))
                        return false;
                if (right != sentinel() && comp(right->value, node->value))
                        return false;
                return is_bst(left) && is_bst(right);
        }

        bool is_bst() const { return is_bst(root()); }

        std::size_t self_check(const node_type *node) const {
                if (node == sentinel()) {
                        assert(rbnode_base::get_color(node) == RB_BLACK
                               && "sentinel() is not black");
                        return 0;
                }

                const node_type *const left
                    = static_cast<const node_type *>(node->left);
                const node_type *const right
                    = static_cast<const node_type *>(node->right);

                if (rbnode_base::get_color(node) == RB_RED
                    && (rbnode_base::get_color(left) == RB_RED
                        || rbnode_base::get_color(right) == RB_RED))
                        throw rb_violation("red violation", node);

                const std::size_t left_height = self_check(left);
                const std::size_t right_height = self_check(right);

                if (left_height != right_height)
                        throw rb_violation("black violation", node);

                if (left != sentinel() && !comp(left->value, node->value))
                        throw rb_violation("bst violation left side", node);
                if (right != sentinel() && comp(right->value, node->value))
                        throw rb_violation("bst violation right side", node);

                return left_height
                       + (rbnode_base::get_color(node) == RB_BLACK ? 1 : 0);
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

        node_type *rotate(rbnode_base *node, const rbdir &dir) {
                tree_assert(node->get(dir.opposite()) != sentinel(), static_cast<node_type*>(node),
                            "cannot rotate further");
                node_type *new_root
                    = static_cast<node_type *>(node->get(dir.opposite()));

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
        void insert_fix(rbnode_base *node) {
                while (rbnode_base::get_color(node->parent) == RB_RED) {
                        const rbdir parent_dir = node->parent->get_dir();
                        rbnode_base *uncle
                            = node->parent->parent->get(parent_dir.opposite());
                        if (rbnode_base::get_color(uncle) == RB_RED) {
                                node->parent->color = RB_BLACK;
                                uncle->color = RB_BLACK;
                                node->parent->parent->color = RB_RED;
                                node = node->parent->parent;
                        } else {
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
        void delete_fix(rbnode_base *node, rbnode_base *parent) {
                while (node != root()
                       && rbnode_base::get_color(node) == RB_BLACK) {
                        const rbdir dir
                            = node != sentinel()
                                  ? node->get_dir()
                                  : (parent->left == sentinel()
                                         ? static_cast<rbdir>(left_dir())
                                         : static_cast<rbdir>(right_dir()));
                        rbnode_base *sibling = parent->get(dir.opposite());
                        if (rbnode_base::get_color(sibling) == RB_RED) {
                                sibling->color = RB_BLACK;
                                parent->color = RB_RED;
                                rotate(parent, dir);
                                sibling = parent->get(dir.opposite());
                        }
                        if (rbnode_base::get_color(sibling->get(dir))
                                == RB_BLACK
                            && rbnode_base::get_color(
                                   sibling->get(dir.opposite()))
                                   == RB_BLACK) {
                                sibling->color = RB_RED;
                                node = parent;
                                parent = parent->parent;
                        } else {
                                if (rbnode_base::get_color(
                                        sibling->get(dir.opposite()))
                                    == RB_BLACK) {
                                        sibling->get(dir)->color = RB_BLACK;
                                        sibling->color = RB_RED;
                                        rotate(sibling, dir.opposite());
                                        sibling = parent->get(dir.opposite());
                                }
                                sibling->color = parent->color;
                                parent->color = RB_BLACK;
                                sibling->get(dir.opposite())->color = RB_BLACK;
                                rotate(parent, dir);
                                node = root();
                        }
                }
                if (node != sentinel()) {
                        node->color = RB_BLACK;
                }
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
