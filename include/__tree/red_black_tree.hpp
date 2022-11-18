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

#include <stdexcept>
#include <cstddef>
// todo for debug purposes, remove
#include <iostream>
#include <string>
#include <cassert>

namespace ft {
namespace detail {

enum rbcolor {
        RB_RED,
        RB_BLACK
};

template <typename T>
class rbnode {
        typedef rbnode this_type;
      public:
        T value;
        rbcolor color;
        
        this_type *parent;
        this_type *right;
        this_type *left;

        rbnode(const T &value = T(), rbcolor color = RB_BLACK,
               this_type *parent = NULL, this_type *right = NULL,
               this_type *left = NULL)
            : value(value), color(color), parent(parent), right(right),
              left(left) {}

        ~rbnode() {
                delete left;
                delete right;
        }

        static rbcolor node_color(const rbnode *node) {
                if (node == NULL)
                        return RB_BLACK;
                return node->color;
        }
        
        static bool is_bst(const this_type *node) {
                if (node == NULL)
                        return true;
                return (node->left == NULL
                        || (node->left->value < node->value
                            && is_bst(node->left)))
                       && (node->right == NULL
                           || (node->right->value > node->value
                               && is_bst(node->right)));
        }

        static bool
        mismatch(const this_type *lhs, const this_type *rhs,
                 std::pair<const this_type *, const this_type *>** mpair) {
                if (lhs == NULL || rhs == NULL) {
                        if (lhs != rhs) {
                                *mpair = new std::pair<const this_type *,
                                                          const this_type *>(
                                    lhs, rhs);
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
                if (mismatch(lhs->left, rhs->left, mpair))
                        return true;
                if (mismatch(lhs->right, rhs->right, mpair))
                        return true;
                return false;
        }

        static std::size_t black_height(const this_type *node) {
                if (node == NULL)
                        return 1;

                if (node_color(node) == RB_RED
                    && (node_color(node->left) == RB_RED
                        || node_color(node->right) == RB_RED))
                        return 0;

                const std::size_t left_height = black_height(node->left);
                const std::size_t right_height = black_height(node->right);

                if (left_height == 0 || right_height == 0
                    || left_height != right_height)
                        return 0;
                return left_height + right_height
                       + (node_color(node) == RB_BLACK ? 1 : 0);
        }

        static bool is_valid(const this_type *node) {
                return is_bst(node) && black_height(node) != 0;
        }

        static void debug_print(const rbnode *node,
                                const rbnode *special = NULL,
                                std::size_t indent = 0) {
                std::cout << std::string(indent, ' ');
                if (node == NULL) {
                        
                        std::cout << '-' << std::endl;
                } else {
                        std::cout << (special == node ? "*" : "")
                                  << node->value << ","
                                  << (node->color == RB_BLACK ? 'B' : 'R')
                                  << std::endl;
                        debug_print(node->left, special, indent + 4);
                        debug_print(node->right, special, indent + 4);
                }
        }
};

template <typename KeyType, typename ValueType, typename Allocator>
struct rbtree {
        typedef rbnode<ValueType> node_type;
        
      protected:
        typedef KeyType key_type;
        typedef ValueType value_type;
        typedef Allocator allocator_type;
        typedef std::size_t size_type;

      private:
        node_type *_root;
        size_type _size;
        allocator_type _allocator;
        
      public:
        rbtree() : _root(NULL), _size(0) {}

        ~rbtree() { destroy_tree(_root); }

        node_type *root() {
                return _root;
        }

        void insert(const value_type &value) {
                node_type *insert_node = _root;
                node_type *parent_node = NULL;

                while (insert_node != NULL) {
                        parent_node = insert_node;
                        if (value < parent_node->value)
                                insert_node = parent_node->left;
                        else
                                insert_node = parent_node->right;
                }

                node_type *node = _allocator.allocate(1);
                _allocator.construct(node, node_type(value));
                
                node->parent = parent_node;
                if (parent_node == NULL)
                        _root = node;
                else if (node->value < parent_node->value)
                        parent_node->left = node;
                else
                        parent_node->right = node;
                node->left = NULL;
                node->right = NULL;
                node->color = RB_RED;
                insert_fix(node);
        }

        static void assert_equal(const rbtree &lhs, const rbtree &rhs) {
                std::pair<const node_type *, const node_type *> *mismatch;
                if (node_type::mismatch(lhs._root, rhs._root, &mismatch)) {
                        std::cerr << "lhs:" << std::endl;
                        node_type::debug_print(lhs._root, mismatch->first);
                        std::cerr << "rhs:" << std::endl;
                        node_type::debug_print(rhs._root, mismatch->second);
                        assert(0 && "lhs != rhs");
                }
        }

        friend bool operator==(const rbtree &lhs, const rbtree &rhs) {
                if (lhs._root == NULL || rhs._root == NULL)
                        return lhs._root == rhs._root;
                return *lhs._root == *rhs._root;
        }

        bool is_bst() const {
                return _root == NULL || node_type::is_bst(_root);
        }

        bool is_valid() const {
                return node_type::node_color(_root) == RB_BLACK
                       && node_type::is_valid(_root);
        }

        void print() const {
                node_type::debug_print(_root, NULL);
        }

      private:
        void tree_assert(int condition, const node_type *node,
                         const std::string &msg = "assertion failed") {
                if (!condition) {
                        node_type::debug_print(_root, node);
                        std::cerr << msg << std::endl;
                        assert(0);
                }
        }

        void destroy_tree(node_type *node) {
                if (node == NULL)
                        return;
                destroy_tree(node->left);
                destroy_tree(node->right);
                _allocator.destroy(node);
                _allocator.deallocate(node, 1);
        }

      public: // TODO make private
        node_type* rotate_left(node_type *node) {
                tree_assert(node->right != NULL, node,
                            "cannot rotate further left on node");
                node_type *new_root = node->right;

                node->right = new_root->left;
                if (new_root->left != NULL)
                        new_root->left->parent = node;
                new_root->parent = node->parent;
                if (node->parent == NULL) {
                        _root = new_root;
                } else if (node == node->parent->left) {
                        node->parent->left = new_root;
                } else {
                        node->parent->right = new_root;
                }
                new_root->left = node;
                node->parent = new_root;
                return new_root;
        }

        node_type *rotate_right(node_type *node) {
                tree_assert(node->left != NULL, node,
                            "cannot rotate further right on node");
                node_type *new_root = node->left;

                node->left = new_root->right;
                if (new_root->right != NULL)
                        new_root->right->parent = node;
                new_root->parent = node->parent;
                if (node->parent == NULL) {
                        _root = new_root;
                } else if (node == node->parent->right) {
                        node->parent->right = new_root;
                } else {
                        node->parent->left = new_root;
                }
                new_root->right = node;
                node->parent = new_root;
                return new_root;
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
};

template <typename ValueType>
bool operator==(const rbnode<ValueType> &lhs, const rbnode<ValueType> &rhs) {
        if (lhs.value != rhs.value)
                return false;

        return ((lhs.left == NULL && rhs.left == NULL)
                || (rhs.left != NULL && *lhs.left == *rhs.left))
               && ((lhs.right == NULL && rhs.right == NULL)
                   || (rhs.right != NULL && *lhs.right == *rhs.right));
}


}
}

#endif /* RED_BLACK_TREE_HPP */
