#include <__tree/red_black_tree.hpp>

namespace ft {
namespace detail {
rbnode_base::rbnode_base(rbcolor color, rbnode_base *right, rbnode_base *left,
                         rbnode_base *parent)
    : color(color), right(right), left(left), parent(parent) {}

#ifndef FT_INLINE
rbside rbnode_base::side() const {
#ifdef FT_DEBUG
    assert(parent != NULL && "cannot get side of a root node");
#endif
    if (parent->left == this) {
        return RB_LEFT;
    }
    return RB_RIGHT;
}

void rbnode_base::swap(rbnode_base &other) {
    std::swap(color, other.color);
    std::swap(right, other.right);
    std::swap(left, other.left);
    std::swap(parent, other.parent);
}

rbnode_base *rbnode_base::get_side(const rbside side) {
    if (side == RB_LEFT) {
        return left;
    }
    return right;
}

const rbnode_base *rbnode_base::get_side(const rbside side) const {
    if (side == RB_LEFT) {
        return left;
    }
    return right;
}

void rbnode_base::set_side(const rbside side, rbnode_base *node) {
    if (side == RB_LEFT) {
        left = node;
    } else {
        right = node;
    }
}

const rbnode_base *rbnode_base::bound(const rbside side) const {
    const rbnode_base *node = this;
    while (node->get_side(side) != NULL) {
        node = node->get_side(side);
    }
    return node;
}

rbnode_base *rbnode_base::bound(const rbside side) {
    return const_cast<rbnode_base *>(
        static_cast<const rbnode_base *>(this)->bound(side));
}
#endif

const rbnode_base *rbnode_base::next(const rbside side) const {
    const rbnode_base *node = this;
    if (node->get_side(side) != NULL) {
        node = node->get_side(side)->bound(!side);
    } else {
        rbnode_base *node_parent = node->parent;
        // TODO try to remove the NULL check
        while (node_parent != NULL && node == node_parent->get_side(side)) {
            node = node_parent;
            node_parent = node_parent->parent;
        }
        if (node->get_side(side) != node_parent) {
            node = node_parent;
        }
    }
    return node;
}

rbnode_base *rbnode_base::next(const rbside side) {
    return const_cast<rbnode_base *>(
        static_cast<const rbnode_base *>(this)->next(side));
}

#ifndef FT_INLINE

rbnode_base *rbnode_base::predecessor() { return next(RB_LEFT); }
rbnode_base *rbnode_base::successor() { return next(RB_RIGHT); }
const rbnode_base *rbnode_base::predecessor() const { return next(RB_LEFT); }
const rbnode_base *rbnode_base::successor() const { return next(RB_RIGHT); }
rbnode_base *rbnode_base::minimum() { return bound(RB_LEFT); }
rbnode_base *rbnode_base::maximum() { return bound(RB_LEFT); }

rbcolor rbnode_base::get_color(const rbnode_base *const node) {
    if (node == NULL) {
        return RB_BLACK;
    }
    return node->color;
}
#endif
}
}
