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
#include <stdexcept>
#include <type_traits.hpp>
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

//TODO use this

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

        rbnode(rbcolor color = RB_BLACK, const T &value = T(),
               this_type *parent = NULL, this_type *right = NULL,
               this_type *left = NULL)
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

        static bool is_bst(const this_type *node, const this_type *sentinel) {
                if (node == sentinel)
                        return true;
                return (node->left == sentinel
                        || (node->left->value < node->value
                            && is_bst(node->left, sentinel)))
                       && (node->right == sentinel
                           || (node->right->value > node->value
                               && is_bst(node->right, sentinel)));
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

        static std::size_t self_check(const this_type *node,
                                      const this_type *sentinel) {
                if (node == sentinel) {
                        assert(node->color == RB_BLACK
                               && "sentinel is not black");
                        return 0;
                }

                if (node->color == RB_RED
                    && (node->left->color == RB_RED
                        || node->right->color == RB_RED))
                        throw rb_violation("red violation", node);

                const std::size_t left_height
                    = self_check(node->left, sentinel);
                const std::size_t right_height
                    = self_check(node->right, sentinel);

                if (left_height != right_height)
                        throw rb_violation("black violation", node);

                assert(
                    (node->left == sentinel || node->left->value < node->value)
                    && "bst violation left side");
                assert((node->right == sentinel
                        || node->right->value > node->value)
                       && "bst violation right side");
                return left_height + (node->color == RB_BLACK ? 1 : 0);
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

template <typename KeyType, typename ValueType, typename Allocator>
struct rbtree {
        typedef rbnode<ValueType> node_type;
        typedef KeyType key_type;
        typedef ValueType value_type;
        typedef Allocator allocator_type;
        typedef std::size_t size_type;

      private:
        node_type *_root;
        node_type _sentinel;
        size_type _size;
        allocator_type _allocator;

      public:
        rbtree() : _root(&_sentinel), _sentinel(RB_BLACK), _size(0) {}

        ~rbtree() { destroy_tree(_root); }

        node_type *root() { return _root; }
        const node_type *root() const { return _root; }
        node_type *sentinel() { return &_sentinel; }
        const node_type *sentinel() const { return &_sentinel; }

        node_type *create_node(const value_type &value) {
                node_type *node = _allocator.allocate(1);
                try {
                        _allocator.construct(node, node_type(RB_BLACK, value,
                                                             sentinel(),
                                                             sentinel()));
                } catch (...) {
                        _allocator.deallocate(node, 1);
                        throw;
                }
                return node;
        }

        void insert(const value_type &value) {
                node_type *insert_node = _root;
                node_type *parent_node = sentinel();

                while (insert_node != sentinel()) {
                        parent_node = insert_node;
                        if (value < parent_node->value)
                                insert_node = parent_node->left;
                        else
                                insert_node = parent_node->right;
                }

                node_type *node = create_node(value);

                node->parent = parent_node;
                if (parent_node == sentinel())
                        _root = node;
                else if (node->value < parent_node->value)
                        parent_node->left = node;
                else
                        parent_node->right = node;
                node->left = sentinel();
                node->right = sentinel();
                node->color = RB_RED;
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
                /*
                if (node == sentinel())
                        return node;
                */
                while (node->left != sentinel())
                        node = node->left;
                return node;
        }

        node_type *minimum() { return minimum(root()); }

      private:
        // TODO solve collision with other search with integral types
        node_type *search(node_type *start, const value_type &key) {
                node_type *current = start;
                while (current != sentinel() && current->value != key) {
                        if (key < current->value)
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
                        if (key < current->value)
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

        bool is_bst() const {
                return _root == sentinel()
                       || node_type::is_bst(_root, sentinel());
        }

        bool is_valid() const {
                assert(sentinel()->color == RB_BLACK && "sentinel not black");
                return node_type::node_color(_root) == RB_BLACK
                       && node_type::is_valid(_root, sentinel());
        }

        void self_check() const {
                assert(node_type::node_color(_root) == RB_BLACK
                       && "root not black");
                try {
                        node_type::self_check(_root, sentinel());
                } catch (const rb_violation &ex) {
                        std::cerr << ex.what() << std::endl;
                        node_type::debug_print(
                            _root, sentinel(),
                            reinterpret_cast<const node_type *>(ex.where()));
                        assert(0);
                }
        }

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

      public: // TODO make private
        template <typename Direction>
        node_type *rotate(node_type *node, const Direction &dir) {
                /*
                tree_assert(node->get(dir.opposite()) != sentinel(),
                            "cannot rotate further");
                */
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
        
        node_type *rotate_left(node_type *node) {
                return rotate(node, left_dir());
                /*
                tree_assert(node->right != sentinel(), node,
                            "cannot rotate further left on node");
                node_type *new_root = node->right;

                node->right = new_root->left;
                if (new_root->left != sentinel())
                        new_root->left->parent = node;
                new_root->parent = node->parent;
                if (node->parent == sentinel()) {
                        _root = new_root;
                } else if (node == node->parent->left) {
                        node->parent->left = new_root;
                } else {
                        node->parent->right = new_root;
                }
                new_root->left = node;
                node->parent = new_root;
                return new_root;
                */
        }

        node_type *rotate_right(node_type *node) {
                return rotate(node, right_dir());
                /*
                tree_assert(node->left != sentinel(), node,
                            "cannot rotate further right on node");
                node_type *new_root = node->left;

                node->left = new_root->right;
                if (new_root->right != sentinel())
                        new_root->right->parent = node;
                new_root->parent = node->parent;
                if (node->parent == sentinel()) {
                        _root = new_root;
                } else if (node == node->parent->right) {
                        node->parent->right = new_root;
                } else {
                        node->parent->left = new_root;
                }
                new_root->right = node;
                node->parent = new_root;
                return new_root;
                */
        }

      private:
        void insert_fix(node_type *node) {
                while (node_type::node_color(node->parent) == RB_RED) {
                        if (node->parent == node->parent->parent->left) {
                                node_type *uncle = node->parent->parent->right;
                                if (node_type::node_color(uncle) == RB_RED) {
                                        node->parent->color = RB_BLACK;
                                        uncle->color = RB_BLACK;
                                        node->parent->parent->color = RB_RED;
                                        node = node->parent->parent;
                                } else {
                                        if (node == node->parent->right) {
                                                node = node->parent;
                                                rotate_left(node);
                                        }
                                        node->parent->color = RB_BLACK;
                                        node->parent->parent->color = RB_RED;
                                        rotate_right(node->parent->parent);
                                }
                        } else {
                                node_type *uncle = node->parent->parent->left;
                                if (node_type::node_color(uncle) == RB_RED) {
                                        node->parent->color = RB_BLACK;
                                        uncle->color = RB_BLACK;
                                        node->parent->parent->color = RB_RED;
                                        node = node->parent->parent;
                                } else {
                                        if (node == node->parent->left) {
                                                node = node->parent;
                                                rotate_right(node);
                                        }
                                        node->parent->color = RB_BLACK;
                                        node->parent->parent->color = RB_RED;
                                        rotate_left(node->parent->parent);
                                }
                        }
                }
                _root->color = RB_BLACK;
        }

        void delete_fix(node_type *node) {
                while (node != root() && node->color == RB_BLACK) {
                        if (node == node->parent->left) {
                                node_type *sibling = node->parent->right;
                                if (sibling->color == RB_RED) {
                                        sibling->color = RB_BLACK;
                                        node->parent->color = RB_RED;
                                        rotate_left(node->parent);
                                        sibling = node->parent->right;
                                }
                                if (sibling->left->color == RB_BLACK
                                    && sibling->right->color == RB_BLACK) {
                                        sibling->color = RB_RED;
                                        node = node->parent;
                                } else {
                                        if (sibling->right->color
                                            == RB_BLACK) {
                                                sibling->left->color
                                                    = RB_BLACK;
                                                sibling->color = RB_RED;
                                                rotate_right(sibling);
                                                sibling = node->parent->right;
                                        }
                                        sibling->color = node->parent->color;
                                        node->parent->color = RB_BLACK;
                                        sibling->right->color = RB_BLACK;
                                        rotate_left(node->parent);
                                        node = root();
                                }
                        } else {
                                node_type *sibling = node->parent->left;
                                if (sibling->color == RB_RED) {
                                        sibling->color = RB_BLACK;
                                        node->parent->color = RB_RED;
                                        rotate_right(node->parent);
                                        sibling = node->parent->left;
                                }
                                if (sibling->right->color == RB_BLACK
                                    && sibling->left->color == RB_BLACK) {
                                        sibling->color = RB_RED;
                                        node = node->parent;
                                } else {
                                        if (sibling->left->color == RB_BLACK) {
                                                sibling->right->color
                                                    = RB_BLACK;
                                                sibling->color = RB_RED;
                                                rotate_left(sibling);
                                                sibling = node->parent->left;
                                        }
                                        sibling->color = node->parent->color;
                                        node->parent->color = RB_BLACK;
                                        sibling->left->color = RB_BLACK;
                                        rotate_right(node->parent);
                                        node = root();
                                }
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
