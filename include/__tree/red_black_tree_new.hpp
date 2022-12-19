#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#ifdef FT_DEBUG
#include <cassert>
#include <cstddef>
#endif
//TODO can this include be removed?
#include <algorithm>
#include <functional>
#include <iterator.hpp>
#include <iterator>
#include <limits>
#include <utility.hpp>
#include <algorithm.hpp>

// TODO add option to disable attributes
#define FORCE_INLINE __attribute__((always_inline))

// TODO make own implementation of std::is_empty with __is_empty to be able to
// turn it off

// TODO add insertion tests

namespace ft {
namespace detail {

enum rbcolor { RB_RED, RB_BLACK };
typedef bool rbside;
const rbside RB_LEFT = false;
const rbside RB_RIGHT = true;

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

struct rbnode_base {
        rbcolor color;
        rbnode_base *right;
        rbnode_base *left;
        rbnode_base *parent;

        // TODO move implementation to cpp file
        rbnode_base(rbcolor color, rbnode_base *right, rbnode_base *left,
                    rbnode_base *parent)
            : color(color), right(right), left(left), parent(parent) {}

        /* TODO check if inlining makes a difference */
        inline rbside side() const {
#ifdef FT_DEBUG
                assert(parent != NULL && "cannot get side of a root node");
#endif
                if (parent->left == this) {
                        return RB_LEFT;
                }
                return RB_RIGHT;
        }

        inline void swap(rbnode_base &other) {
                std::swap(color, other.color);
                std::swap(right, other.right);
                std::swap(left, other.left);
                std::swap(parent, other.parent);
        }

        inline rbnode_base *get_side(const rbside side) {
                if (side == RB_LEFT) {
                        return left;
                }
                return right;
        }

        inline const rbnode_base *get_side(const rbside side) const {
                if (side == RB_LEFT) {
                        return left;
                }
                return right;
        }

        inline void set_side(const rbside side, rbnode_base *node) {
                if (side == RB_LEFT) {
                        left = node;
                } else {
                        right = node;
                }
        }

        inline const rbnode_base *bound(const rbside side) const {
                const rbnode_base *node = this;
                while (node->get_side(side) != NULL) {
                        node = node->get_side(side);
                }
                return node;
        }

        inline rbnode_base *bound(const rbside side) {
                return const_cast<rbnode_base *>(
                    static_cast<const rbnode_base *>(this)->bound(side));
        }

        // TODO move to cpp file
        const rbnode_base *next(const rbside side) const {
                const rbnode_base *node = this;
                if (node->get_side(side) != NULL) {
                        node = node->get_side(side)->bound(!side);
                } else {
                        rbnode_base *node_parent = node->parent;
                        // TODO try to remove the NULL check
                        while (node_parent != NULL
                               && node == node_parent->get_side(side)) {
                                node = node_parent;
                                node_parent = node_parent->parent;
                        }
                        if (node->get_side(side) != node_parent) {
                                node = node_parent;
                        }
                }
                return node;
        }

        rbnode_base *next(const rbside side) {
                return const_cast<rbnode_base *>(
                    static_cast<const rbnode_base *>(this)->next(side));
        }

        inline rbnode_base *predecessor() { return next(RB_LEFT); }
        inline rbnode_base *successor() { return next(RB_RIGHT); }
        inline const rbnode_base *predecessor() const { return next(RB_LEFT); }
        inline const rbnode_base *successor() const { return next(RB_RIGHT); }
        inline rbnode_base *minimum() { return bound(RB_LEFT); }
        inline rbnode_base *maximum() { return bound(RB_LEFT); }

        inline static rbcolor get_color(const rbnode_base *const node) {
                if (node == NULL) {
                        return RB_BLACK;
                }
                return node->color;
        }
};

template <typename T> struct rbnode : public rbnode_base {
        T value;

        rbnode(rbcolor color, rbnode_base *right, rbnode_base *left,
               rbnode_base *parent, const T &value)
            : rbnode_base(color, right, left, parent), value(value) {}
};

template <typename Compare, bool Empty = __is_empty(Compare)>
struct rbtree_base_compare : public Compare {
      protected:
        rbtree_base_compare() : Compare() {}
        rbtree_base_compare(const Compare &other) : Compare(other) {}

        inline Compare &get_compare() { return *this; }
        inline const Compare &get_compare() const { return *this; }

        template <typename T> bool compare(const T &lhs, const T &rhs) {
                return Compare::operator()(lhs, rhs);
        }

        template <typename T> bool compare(const T &lhs, const T &rhs) const {
                return Compare::operator()(lhs, rhs);
        }

        FORCE_INLINE void swap(rbtree_base_compare &) {}
};

template <typename Compare> struct rbtree_base_compare<Compare, false> {
      protected:
        Compare _compare;

        rbtree_base_compare() : _compare() {}
        rbtree_base_compare(const Compare &other) : _compare(other) {}

        inline Compare &get_compare() { return _compare; }
        inline const Compare &get_compare() const { return _compare; }

        template <typename T> bool compare(const T &lhs, const T &rhs) {
                return _compare(lhs, rhs);
        }

        template <typename T> bool compare(const T &lhs, const T &rhs) const {
                return _compare(lhs, rhs);
        }

        void swap(rbtree_base_compare &other) {
                std::swap(_compare, other._compare);
        }
};

template <typename Allocator, bool Empty = __is_empty(Allocator)>
struct rbtree_base_alloc : public Allocator {
      protected:
        typedef typename Allocator::const_reference const_reference;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::size_type size_type;

        rbtree_base_alloc() : Allocator() {}
        rbtree_base_alloc(const Allocator &other) : Allocator(other) {}

        Allocator &get_allocator() { return *this; }

        pointer allocate(size_type n, const void *hint = 0) {
                return Allocator::allocate(n, hint);
        }

        void deallocate(pointer p, size_type n) {
                Allocator::deallocate(p, n);
        }

        void construct(pointer p, const_reference val) {
                Allocator::construct(p, val);
        }

        void destroy(pointer p) { Allocator::destroy(p); }

        FORCE_INLINE void swap(rbtree_base_alloc &) {}
};

template <typename Allocator> struct rbtree_base_alloc<Allocator, false> {
      protected:
        typedef typename Allocator::const_reference const_reference;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::size_type size_type;

        Allocator _allocator;

        rbtree_base_alloc() : _allocator() {}
        rbtree_base_alloc(const Allocator &other) : _allocator(other) {}

        Allocator &get_allocator() { return _allocator; }

        pointer allocate(size_type n, const void *hint = 0) {
                return _allocator.allocate(n, hint);
        }

        void deallocate(pointer p, size_type n) {
                _allocator.deallocate(p, n);
        }

        void construct(pointer p, const_reference val) {
                _allocator.construct(p, val);
        }

        void destroy(pointer p) { _allocator.destroy(p); }

        void swap(rbtree_base_alloc &other) {
                std::swap(_allocator, other._allocator);
        }
};

template <typename KeyExtract, bool Empty = __is_empty(KeyExtract)>
struct rbtree_base_extract : public KeyExtract {
      protected:
        typedef typename KeyExtract::argument_type argument_type;
        typedef typename KeyExtract::result_type result_type;

        rbtree_base_extract() : KeyExtract() {}
        rbtree_base_extract(const KeyExtract &other) : KeyExtract(other) {}

        KeyExtract &get_key_extract() { return *this; }
        const KeyExtract &get_key_extract() const { return *this; }

        FORCE_INLINE void swap(rbtree_base_extract &) {}
};

template <typename KeyExtract> struct rbtree_base_extract<KeyExtract, false> {
      protected:
        typedef typename KeyExtract::argument_type argument_type;
        typedef typename KeyExtract::result_type result_type;

        KeyExtract _key_extract;

        rbtree_base_extract() : _key_extract() {}
        rbtree_base_extract(const KeyExtract &other) : _key_extract(other) {}

        KeyExtract &get_key_extract() { return &_key_extract; }
        const KeyExtract &get_key_extract() const { return &_key_extract; }

        void swap(rbtree_base_extract &other) {
                std::swap(_key_extract, other._key_extract);
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

        rbtree_iterator(const iterator &other) : _current(other._current) {}
        rbtree_iterator(const node_type *current)
            : _current(const_cast<node_type *>(current)) {}

        rbtree_iterator &operator=(const iterator &other) {
                if (this != &other) {
                        _current = other._current;
                }
                return *this;
        }

        inline node_type *node() { return _current; }
        inline const node_type *node() const { return _current; }

        reference operator*() const { return _current->value; }
        pointer operator->() const { return &(this->operator*()); }

        rbtree_iterator &operator++() {
                _current = static_cast<node_type *>(_current->next(RB_RIGHT));
                return *this;
        }

        rbtree_iterator operator++(int) {
                const rbtree_iterator tmp(*this);
                _current = static_cast<node_type *>(_current->next(RB_RIGHT));
                return tmp;
        }

        rbtree_iterator &operator--() {
                _current = static_cast<node_type *>(_current->next(RB_LEFT));
                return *this;
        }

        rbtree_iterator operator--(int) {
                const rbtree_iterator tmp(*this);
                _current = static_cast<node_type *>(_current->next(RB_LEFT));
                return tmp;
        }
};

template <typename Type, typename PointerA, typename ReferenceA,
          typename PointerB, typename ReferenceB>
inline bool
operator==(const rbtree_iterator<Type, PointerA, ReferenceA> &lhs,
           const rbtree_iterator<Type, PointerB, ReferenceB> &rhs) {
        return lhs._current == rhs._current;
}

template <typename Type, typename PointerA, typename ReferenceA,
          typename PointerB, typename ReferenceB>
inline bool
operator!=(const rbtree_iterator<Type, PointerA, ReferenceA> &lhs,
           const rbtree_iterator<Type, PointerB, ReferenceB> &rhs) {
        return !(lhs == rhs);
}

template <typename KeyType, typename ValueType, typename KeyExtract,
          typename Compare, typename Allocator>
struct rbtree_base : public rbtree_base_extract<KeyExtract>,
                     public rbtree_base_compare<Compare>,
                     public rbtree_base_alloc<Allocator> {
        typedef rbtree_base_extract<KeyExtract> extract_base;
        typedef rbtree_base_compare<Compare> compare_base;
        typedef rbtree_base_alloc<Allocator> alloc_base;
        typedef KeyType key_type;
        typedef ValueType value_type;
        typedef rbnode<value_type> node_type;
        typedef Compare compare_type;
        typedef Allocator allocator_type;
        typedef rbtree_iterator<value_type, value_type *, value_type &>
            iterator;
        typedef rbtree_iterator<value_type, const value_type *,
                                const value_type &>
            const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

      protected:
        rbnode_base _anchor;

        rbtree_base(const compare_type &comp = compare_type(),
                    const allocator_type &alloc = allocator_type())
            : extract_base(), compare_base(comp), alloc_base(alloc),
              _anchor(RB_BLACK, &_anchor, &_anchor, NULL) {}
        rbtree_base(const rbtree_base &other)
            : extract_base(), compare_base(other), alloc_base(other),
              _anchor(RB_BLACK, &_anchor, &_anchor, NULL) {}

        ~rbtree_base() { destroy_tree(static_cast<node_type *>(root())); }

        using alloc_base::get_allocator;

        rbnode_base *&root() { return _anchor.parent; }
        const rbnode_base *root() const { return _anchor.parent; }
        rbnode_base *anchor() { return &_anchor; }
        const rbnode_base *anchor() const { return &_anchor; }
        iterator begin() {
                return iterator(static_cast<node_type *>(anchor()->right));
        }
        iterator end() { return iterator(static_cast<node_type *>(anchor())); }
        const_iterator begin() const {
                return iterator(
                    static_cast<const node_type *>(anchor()->right));
        }
        const_iterator end() const {
                return iterator(static_cast<const node_type *>(anchor()));
        }
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rbegin() const {
                return const_reverse_iterator(end());
        }
        const_reverse_iterator rend() const {
                return const_reverse_iterator(begin());
        }

        void destroy_node(node_type *node) {
                get_allocator().destroy(node);
                get_allocator().deallocate(node, 1);
        }

        void destroy_tree(node_type *node) {
                if (node != NULL) {
                        destroy_tree(static_cast<node_type *>(node->left));
                        destroy_tree(static_cast<node_type *>(node->right));
                        destroy_node(node);
                }
        }

        void swap(rbtree_base &other) {
                _anchor.swap(other._anchor);
		if (root() != NULL) {
			root()->parent = anchor();
		}
		if (other.root() != NULL) {
			other.root()->parent = other.anchor();
		}
                compare_base::swap(other);
                alloc_base::swap(other);
		extract_base::swap(other);
        }

        node_type *create_node(const value_type &value) {
                node_type *const node = get_allocator().allocate(1);
                try {
                        get_allocator().construct(
                            node,
                            node_type(RB_BLACK, NULL, NULL, NULL, value));
                } catch (...) {
                        get_allocator().deallocate(node, 1);
                        throw;
                }
                return node;
        }
};

template <typename KeyType, typename ValueType, typename KeyExtract,
          typename Compare, typename Allocator>
struct rbtree
    : public rbtree_base<KeyType, ValueType, KeyExtract, Compare, Allocator> {
        typedef rbtree_base<KeyType, ValueType, KeyExtract, Compare, Allocator>
            base;
        using typename base::const_iterator;
        using typename base::const_reverse_iterator;
        using typename base::iterator;
        using typename base::key_type;
        using typename base::node_type;
        using typename base::reverse_iterator;
        using typename base::value_type;
	using typename base::compare_type;
	using typename base::allocator_type;
        typedef std::size_t size_type;

      protected:
        using base::_anchor;
        size_type _size;

      public:
        rbtree() : base(), _size(0) {}
        explicit rbtree(const compare_type &comp,
                        const allocator_type &alloc = allocator_type())
            : base(comp, alloc), _size(0) {}
        template <class InputIt>
        rbtree(InputIt first, InputIt last,
               const compare_type &comp = compare_type(),
               const allocator_type &alloc = allocator_type())
            : base(comp, alloc), _size(0) {
                insert(first, last);
        }
        rbtree(const rbtree &other) : base(other), _size(0) {
                insert(other.begin(), other.end());
        }

        using base::anchor;
        using base::begin;
        using base::end;
        using base::get_allocator;
        using base::rbegin;
        using base::rend;
        using base::root;

        inline bool empty() const { return size() == 0; }
        inline size_type size() const { return _size; }
        inline size_type max_size() const {
                return std::numeric_limits<size_type>::max()
                       / sizeof(node_type);
        }

        void clear() {
                base::destroy_tree(static_cast<node_type *>(root()));
                _size = 0;
                anchor()->parent = NULL;
                anchor()->right = anchor();
                anchor()->left = anchor();
        }

        ft::pair<iterator, bool> insert(const value_type &value) {
                return insert_aux(static_cast<node_type *>(root()), value);
        }

        ft::pair<iterator, bool> insert(iterator hint,
                                        const value_type &value) {
                if (hint != begin()) {
                        --hint;
                }
                return insert_aux(hint.node(), value);
        }

        template <class InputIt> void insert(InputIt first, InputIt last) {
                for (; first != last; ++first) {
                        insert(*first);
                }
        }

        iterator erase(iterator pos) {
                _size -= 1;
                return delete_node(pos._current);
        }

        void erase(iterator first, iterator last) {
                while (first != last) {
                        first = erase(first);
                }
        }

        bool erase(const key_type &key) {
                iterator pos = find(key);
                if (pos == end()) {
                        return false;
                }
                erase(pos);
                return true;
        }

	void swap(rbtree &other) {
		base::swap(other);
		std::swap(_size, other._size);
	}
	
	size_type count(const key_type &key) const {
		if (find(key) == end()) {
			return 0;
		}
		return 1;
	}

        const_iterator find(const key_type &key) const {
                const node_type *current
                    = static_cast<const node_type *>(root());

                while (current != NULL) {
                        if (comp(key, current->value)) {
                                current = static_cast<const node_type *>(
                                    current->left);
                        } else if (comp(current->value, key)) {
                                current = static_cast<const node_type *>(
                                    current->right);
                        } else {
                                return const_iterator(current);
                        }
                }
                return end();
        }

        iterator find(const key_type &key) {
                return iterator(
                    const_cast<const rbtree *>(this)->find(key)._current);
        }

	ft::pair<const_iterator, const_iterator> equal_range(const key_type &key) const {
		return ft::make_pair(lower_bound(key), upper_bound(key));
	}

	ft::pair<iterator, iterator> equal_range(const key_type &key) {
		return ft::make_pair(lower_bound(key), upper_bound(key));
	}

	const_iterator lower_bound(const key_type &key) const {
                const node_type *current
                    = static_cast<const node_type *>(root());
		const node_type *bound_end = end().node();

                while (current != NULL) {
                        if (!comp(current->value, key)) {
				bound_end = current;
                                current = static_cast<const node_type *>(
                                    current->left);
                        } else {
                                current = static_cast<const node_type *>(
                                    current->right);
			}
                }
                return const_iterator(bound_end);
	}

	iterator lower_bound(const key_type &key) {
                return iterator(
                    const_cast<const rbtree *>(this)->lower_bound(key).node());
        }

        const_iterator upper_bound(const key_type &key) const {
                const node_type *current
                    = static_cast<const node_type *>(root());
                const node_type *bound_end = end().node();

                while (current != NULL) {
			if (comp(key, current->value)) {
                                bound_end = current;
                                current = static_cast<const node_type *>(
                                    current->left);
			} else {
                                current = static_cast<const node_type *>(
                                    current->right);
			}
                }
                return const_iterator(bound_end);
        }

        iterator upper_bound(const key_type &key) {
                return iterator(
                    const_cast<const rbtree *>(this)->upper_bound(key).node());
        }

        void assert_correct() const {
                assert_correct(static_cast<const node_type *>(root()));
        }

      protected:
        using base::get_compare;
        using base::get_key_extract;
        inline bool comp(const value_type &a, const value_type &b) const {
                return get_compare()(get_key_extract()(a),
                                     get_key_extract()(b));
        }

        rbnode_base *rotate(rbnode_base *const node, const rbside side) {
#ifdef FT_DEBUG
                assert(node != NULL && "cannot rotate on a NULL node");
                assert(node->get_side(!side) != NULL
                       && "cannot rotate further");
#endif
                rbnode_base *const new_root = node->get_side(!side);

                node->set_side(!side, new_root->get_side(side));
                if (new_root->get_side(side) != NULL) {
                        new_root->get_side(side)->parent = node;
                }
                new_root->parent = node->parent;
                if (node->parent == anchor()) {
                        root() = new_root;
                } else if (node == node->parent->get_side(side)) {
                        node->parent->set_side(side, new_root);
                } else {
                        node->parent->set_side(!side, new_root);
                }
                new_root->set_side(side, node);
                node->parent = new_root;
                return new_root;
        }

        rbnode_base *transplant(rbnode_base *const to,
                                rbnode_base *const from) {
#ifdef FT_DEBUG
                assert(to != NULL && "cannot transplant to a NULL node");
#endif
                if (to->parent == anchor()) {
                        root() = static_cast<node_type *>(from);
                } else if (to->parent->left == to) {
                        to->parent->left = from;
                } else {
                        to->parent->right = from;
                }
                if (from != NULL) {
                        from->parent = to->parent;
                }
                return to->parent;
        }

        iterator delete_node(node_type *const node) {
                rbcolor old_color = node->color;
                rbnode_base *moved_node = NULL;
                rbnode_base *parent = NULL;

                // todo do the cast to node_type* in the iterator class to
                // reduce code duplication?
                const iterator next
                    = iterator(static_cast<node_type *>(node->next(RB_RIGHT)));
                if (node->left == NULL) {
                        moved_node = node->right;
                        parent = transplant(node, node->right);
                } else if (node->right == NULL) {
                        moved_node = node->left;
                        parent = transplant(node, node->left);
                } else {
                        rbnode_base *min = node->right->minimum();
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

                delete_fix_iterators(node);

                base::destroy_node(node);
                if (old_color == RB_BLACK)
                        delete_fix_balance(moved_node, parent);
                return next;
        }

        void delete_fix_iterators(node_type *const node) {
                if (node == anchor()->left) {
                        anchor()->left = node->predecessor();
			if (anchor()->left == NULL) {
				anchor()->left = anchor();
			}
                }
                if (node == anchor()->right) {
                        anchor()->right = node->successor();
			if (anchor()->right == NULL) {
				anchor()->right = anchor();
			}
                }
        }

        void delete_fix_balance(rbnode_base *node, rbnode_base *parent) {
                while (node != root()
                       && rbnode_base::get_color(node) == RB_BLACK) {
                        const rbside side
                            = node != NULL ? node->side()
                                           : (parent->left == NULL ? RB_LEFT
                                                                   : RB_RIGHT);
                        rbnode_base *sibling = parent->get_side(!side);
                        if (rbnode_base::get_color(sibling) == RB_RED) {
                                sibling->color = RB_BLACK;
                                parent->color = RB_RED;
                                rotate(parent, side);
                                sibling = parent->get_side(!side);
                        }
                        if (rbnode_base::get_color(sibling->get_side(side))
                                == RB_BLACK
                            && rbnode_base::get_color(sibling->get_side(!side))
                                   == RB_BLACK) {
                                sibling->color = RB_RED;
                                node = parent;
                                parent = parent->parent;
                        } else {
                                if (rbnode_base::get_color(
                                        sibling->get_side(!side))
                                    == RB_BLACK) {
                                        sibling->get_side(side)->color
                                            = RB_BLACK;
                                        sibling->color = RB_RED;
                                        rotate(sibling, !side);
                                        sibling = parent->get_side(!side);
                                }
                                sibling->color = parent->color;
                                parent->color = RB_BLACK;
                                sibling->get_side(!side)->color = RB_BLACK;
                                rotate(parent, side);
                                node = root();
                        }
                }
                if (node != NULL) {
                        node->color = RB_BLACK;
                }
        }

        void insert_fix_iterators() {
                if (anchor()->left == anchor()) {
                        anchor()->left = root();
                }
                if (anchor()->right == anchor()) {
                        anchor()->right = root();
                }
                if (anchor()->left->right != NULL) {
                        anchor()->left = anchor()->left->right;
                }
                if (anchor()->right->left != NULL) {
                        anchor()->right = anchor()->right->left;
                }
        }

        void insert_fix_balance(rbnode_base *node) {
                while (rbnode_base::get_color(node->parent) == RB_RED) {
                        const rbside parent_side = node->parent->side();
                        rbnode_base *const uncle
                            = node->parent->parent->get_side(!parent_side);
                        if (rbnode_base::get_color(uncle) == RB_RED) {
                                node->parent->color = RB_BLACK;
                                uncle->color = RB_BLACK;
                                node->parent->parent->color = RB_RED;
                                node = node->parent->parent;
                        } else {
                                if (node
                                    == node->parent->get_side(!parent_side)) {
                                        node = node->parent;
                                        rotate(node, parent_side);
                                }
                                node->parent->color = RB_BLACK;
                                node->parent->parent->color = RB_RED;
                                rotate(node->parent->parent, !parent_side);
                        }
                }
                root()->color = RB_BLACK;
        }

        ft::pair<iterator, bool> insert_aux(node_type *const search_start,
                                            const value_type &value) {
                node_type *insert_node = search_start;
                node_type *parent_node = NULL;

                if (insert_node != anchor()) {
                        while (insert_node != NULL) {
                                parent_node = insert_node;
                                if (comp(value, parent_node->value)) {
                                        insert_node = static_cast<node_type *>(
                                            parent_node->left);
                                } else if (comp(parent_node->value, value)) {
                                        insert_node = static_cast<node_type *>(
                                            parent_node->right);
                                } else {
                                        return ft::make_pair(
                                            iterator(parent_node), false);
                                }
                        }
                }

                node_type *const node = base::create_node(value);

                node->parent = parent_node;
                if (parent_node == NULL) {
                        node->parent = anchor();
                        anchor()->parent = node;
                } else if (comp(node->value, parent_node->value)) {
                        parent_node->left = node;
                } else {
                        parent_node->right = node;
                }

                node->color = RB_RED;
                insert_fix_iterators();
                insert_fix_balance(node);
                _size += 1;
                return ft::make_pair(iterator(node), true);
        }

#ifdef FT_DEBUG
        static std::size_t assert_correct(const node_type *const node) {
                if (node == NULL) {
                        return 1;
                }

                const node_type *const left
                    = static_cast<const node_type *>(node->left);
                const node_type *const right
                    = static_cast<const node_type *>(node->right);

                if (rbnode_base::get_color(node) == RB_RED
                    && (rbnode_base::get_color(left) == RB_RED
                        || rbnode_base::get_color(right) == RB_RED)) {
                        assert(0 && "red violation");
                }

                const std::size_t left_height = assert_correct(left);
                const std::size_t right_height = assert_correct(right);
                assert(left_height == right_height && "black violation");

                assert((left == NULL || Compare()(left->value, node->value))
                       && "bst violation left side");
                assert((right == NULL || !Compare()(right->value, node->value))
                       && "bst violation right side");

                return left_height
                       + (rbnode_base::get_color(node) == RB_BLACK ? 1 : 0);
        }
#else
        static void assert_correct(const node_type *const) {}
#endif
};

template <typename KeyType, typename ValueType, typename KeyExtract,
          typename Compare, typename Allocator>
bool operator==(const rbtree<KeyType, ValueType, KeyExtract, Compare, Allocator> &lhs,
		const rbtree<KeyType, ValueType, KeyExtract, Compare, Allocator> &rhs) {
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename KeyType, typename ValueType, typename KeyExtract,
          typename Compare, typename Allocator>
bool operator!=(const rbtree<KeyType, ValueType, KeyExtract, Compare, Allocator> &lhs,
		const rbtree<KeyType, ValueType, KeyExtract, Compare, Allocator> &rhs) {
	return !(lhs == rhs);
}

}
}

#endif /* RED_BLACK_TREE_HPP */
