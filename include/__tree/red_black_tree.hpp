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

        void rotate_left() {
                rbnode *new_root = right;

                right = new_root->left;
                if (new_root->left != NULL)
                        new_root->left->parent = this;
                new_root->parent = parent;
                if (parent != NULL) {
                        if (parent->left == this)
                                parent->left = new_root;
                        else
                                parent->right = new_root;
                }
                new_root->left = this;
                parent = new_root;
                return new_root;
        }
};

template <typename KeyType, typename ValueType>
struct rbtree {
        typedef rbnode<ValueType> node_type;
        
        node_type *_root;

        node_type* rotate_left(node_type *node) {
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
};

}
}

#endif /* RED_BLACK_TREE_HPP */
