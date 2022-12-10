#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#ifdef FT_DEBUG
#include <cassert>
#include <cstddef>
#endif
#include <algorithm>
#include <functional>
#include <iterator>
#include <iterator.hpp>

//TODO add option to disable attributes
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

	//TODO move implementation to cpp file
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

        inline rbnode_base *bound(const rbside side) {
		rbnode_base *node = this;
                while (node->get_side(side) != NULL) {
                        node = node->get_side(side);
                }
                return node;
        }

	//TODO move to cpp file
        rbnode_base *next(const rbside side) {
                rbnode_base *node = this;
                if (node->get_side(side) != NULL) {
                        node = node->get_side(side)->bound(!side);
                } else {
                        rbnode_base *node_parent = node->parent;
                        while (node_parent != NULL
                               && node == node_parent->get_side(side)) {
                                node = node_parent;
                                node_parent = node_parent->parent;
                        }
                        node = node_parent;
                }
                return node;
        }

        inline rbnode_base *predecessor() { return next(RB_LEFT); }
        inline rbnode_base *successor() { return next(RB_RIGHT); }

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

        FORCE_INLINE bool swap(rbtree_base_compare &) {}
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

template <typename KeyExtract>
struct rbtree_base_extract<KeyExtract, false> {
      protected:
        typedef typename KeyExtract::argument_type argument_type;
        typedef typename KeyExtract::result_type result_type;

	KeyExtract _key_extract;

        rbtree_base_extract() : _key_extract() {}
        rbtree_base_extract(const KeyExtract &other) : _key_extract(other) {}

        KeyExtract &get_key_extract() { return &_key_extract; }
        const KeyExtract &get_key_extract() const { return &_key_extract; }
};

template <typename T, typename Pointer, typename Reference>
struct rbtree_iterator {
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef std::ptrdiff_t difference_type;
	typedef Pointer pointer;
	typedef Reference reference;
	typedef rbnode<T> node_type;
	typedef rbtree_iterator<T, T*, T&> iterator;

        node_type *_current;

	rbtree_iterator(const iterator &other) : _current(other._current) {}
	rbtree_iterator(const node_type *current) : _current(const_cast<node_type*>(current)) {}

	rbtree_iterator &operator=(const iterator &other) {
		if (this != &other) {
			_current = other._current;
		}
		return *this;
	}

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
	typedef rbtree_iterator<value_type, value_type *, value_type &> iterator;
	typedef rbtree_iterator<value_type, const value_type *, const value_type &> const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

      protected:
        rbnode_base _anchor;

        rbtree_base(const compare_type &comp = compare_type(),
                    const allocator_type &alloc = allocator_type())
            : extract_base(), compare_base(comp), alloc_base(alloc),
              _anchor(RB_BLACK, NULL, NULL, NULL) {}

        ~rbtree_base() { destroy_tree(static_cast<node_type *>(root())); }

        using alloc_base::get_allocator;

        rbnode_base *&root() { return _anchor.parent; }
        const rbnode_base *root() const { return _anchor.parent; }
	rbnode_base *anchor() { return &_anchor; }
	const rbnode_base *anchor() const { return &_anchor; }
	iterator begin() { return iterator(static_cast<node_type *>(anchor()->right)); }
	iterator end() { return iterator(static_cast<node_type *>(anchor())); }
	const_iterator begin() const { return iterator(static_cast<const node_type *>(anchor()->right)); }
	const_iterator end() const { return iterator(static_cast<const node_type *>(anchor())); }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

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
                compare_base::swap(other);
                alloc_base::swap(other);
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
        using typename base::key_type;
        using typename base::node_type;
        using typename base::value_type;

      protected:
        using base::_anchor;

      public:
        rbtree() : base() {}

	using base::root;
	using base::anchor;
	using base::begin;
	using base::end;
	using base::rbegin;
	using base::rend;
	
        bool insert(const value_type &value) {
                node_type *insert_node = static_cast<node_type *>(root());
                node_type *parent_node = NULL;

                while (insert_node != NULL) {
                        parent_node = insert_node;
                        if (comp(value, parent_node->value)) {
                                insert_node = static_cast<node_type *>(
                                    parent_node->left);
                        } else if (comp(parent_node->value, value)) {
                                insert_node = static_cast<node_type *>(
                                    parent_node->right);
                        } else {
                                return false;
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
                return true;
        }

        void assert_correct() const {
                assert_correct(static_cast<const node_type *>(root()));
        }

      protected:
	using base::get_compare;
	using base::get_key_extract;
	inline bool comp(const value_type &a, const value_type &b) const {
		return get_compare()(get_key_extract()(a), get_key_extract()(b));
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

        void insert_fix_iterators() {
                if (anchor()->left == NULL) {
                        anchor()->left = root();
                        anchor()->right = root();
                } else if (anchor()->left->right != NULL) {
                        anchor()->left = anchor()->left->right;
                } else if (anchor()->right->left != NULL) {
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
                                if (node == node->parent->get_side(!parent_side)) {
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
}
}

#endif /* RED_BLACK_TREE_HPP */
