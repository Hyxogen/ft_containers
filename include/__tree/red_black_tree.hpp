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
        rbcolor color;
        T value;
        
        this_type *parent;
        this_type *right;
        this_type *left;

        rbnode(rbcolor color, const T &value = T(), this_type *parent = NULL,
               this_type *right = NULL, this_type *left = NULL)
            : color(color), value(value), parent(parent), right(right),
              left(left) {}

        static rbcolor node_color(const rbnode *node) {
                if (node == NULL)
                        return RB_BLACK;
                return node->color;
        }

        bool is_bst() {
                return (
                    (left == NULL || (left->value < value && left->is_bst()))
                    && (right == NULL
                        || (right->value > value && right->is_bst())));
        }
        
        std::size_t black_height() {
                if (color == RB_RED
                    && (node_color(left) == RB_RED
                        || node_color(right) == RB_RED))
                        throw std::logic_error("red violation");

                std::size_t left_height
                    = left == NULL ? 0 : left->black_height();
                std::size_t right_height
                    = right == NULL ? 0 : right->black_height();

                if ((left != NULL && left->value >= value)
                    || (right != NULL && right->value <= value))
                        throw std::logic_error("bst violation");

                if (left_height != right_height)
                        throw std::logic_error("black violation");
                return color == RB_BLACK ? left_height + 1
                                                    : left_height;
        }

        static void debug_print(const rbnode *node, std::size_t indent = 0,
                                const rbnode *special = NULL) {
                std::cout << std::string(indent, ' ');
                if (node == NULL) {
                        
                        std::cout << '-' << std::endl;
                } else {
                        std::cout << (special == node ? "*" : "")
                                  << node->value << ","
                                  << (node->color == RB_BLACK ? 'B' : 'R')
                                  << std::endl;
                        debug_print(node->left, indent + 4, special);
                        debug_print(node->right, indent + 4, special);
                }
        }
};

template <typename KeyType, typename ValueType>
struct rbtree {
        typedef rbnode<ValueType> node_type;
        
        node_type *_root;

        rbtree() : _root(NULL) {}

        void print_error(const node_type *node, const std::string &msg) {
                node_type::debug_print(_root, 0, node);
                std::cerr << msg << std::endl;
        }

        node_type* rotate_left(node_type *node) {
                if (node->right == NULL) {
                        print_error(node,
                                    "cannot rotate further left on node");
                        assert(0);
                }
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

        node_type* rotate_right(node_type *node) {
                if (node->left == NULL) {
                        print_error(node,
                                    "cannot rotate further right on node");
                        assert(0);
                }
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

        void insert(node_type *node) {
                node_type *insert_node = _root;
                node_type *parent_node = NULL;

                while (parent_node != NULL) {
                        parent_node = insert_node;
                        if (node->value < parent_node->value)
                                insert_node = parent_node->left;
                        else
                                insert_node = parent_node->right;
                }
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
