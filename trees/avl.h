#ifndef _AVL_H
#define _AVL_H value

#include <functional>
#include <iostream>  // DEL
#include <memory> 

template <class T>
class TreeNode {
   public:
    T val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const T& value, TreeNode* l = nullptr, TreeNode* r = nullptr) {
        val = value;
        left = l;
        right = r;
    }
};

template <class T, class Compare = std::less<T>>
class Avl {
   public:
    // unary operator to apply to each nodevalue
    typedef std::function<void(const T&)> Applicator;
    // unary operator to apply to each node with its id
    typedef std::function<void(int id, const TreeNode<T>&)> NodeApplicator;
    enum traverse_type { DIRECT, REVERSED, MINMAX, MAXMIN, LEVELS };

   private:
    size_t _size;
    TreeNode<T>* _root;
    Compare _cmp;

    void _clean_tree(TreeNode<T>* node) {
        if (node) {
            _clean_tree(node->left);
            _clean_tree(node->right);
            delete node;
        }
    }

    void _insert(TreeNode<T>* node, const T& val) {
        // place to insert value
        TreeNode<T>** place;
        if (_cmp(val, node->val)) {
            place = &node->left;
        } else if (_cmp(node->val, val)) {
            place = &node->right;
        } else {
            node->val = val;
            return;
        }

        if (*place)
            return _insert(*place, val);
        else
            *place = new TreeNode<T>(val);
    }

    TreeNode<T>** _find(TreeNode<T>** nodePtr, const T& val) {
        TreeNode<T>* node = *nodePtr;
        if (!node) return nullptr;

        if (_cmp(val, node->val)) {
            return _find(&((*nodePtr)->left), val);
        } else if (_cmp(node->val, val)) {
            return _find(&((*nodePtr)->right), val);
        } else {
            return nodePtr;
        }
    }

    TreeNode<T>** _find_min(TreeNode<T>** nodePtr) {
        if ((*nodePtr)->left) {
            return _find_min(&((*nodePtr)->left));
        } else {
            return nodePtr;
        }
    }

    TreeNode<T>** _find_max(TreeNode<T>** nodePtr) {
        if ((*nodePtr)->right) {
            return _find_max(&((*nodePtr)->right));
        } else {
            return nodePtr;
        }
    }

    void _traverse_direct(TreeNode<T>* node, int id, const NodeApplicator& f) {
        if (node) {
            f(id, *node);
            _traverse_direct(node->left, id*2, f);
            _traverse_direct(node->right, id*2+1, f);
        }
    }

    void _traverse_reversed(TreeNode<T>* node, int id, const NodeApplicator& f) {
        if (node) {
            _traverse_direct(node->left, id*2, f);
            _traverse_direct(node->right, id*2+1, f);
            f(id, *node);
        }
    }

    void _traverse_minmax(TreeNode<T>* node, int id, const NodeApplicator& f) {
        if (node) {
            _traverse_direct(node->left, id*2, f);
            f(id, *node);
            _traverse_direct(node->right, id*2+1, f);
        }
    }

    void _traverse_maxmin(TreeNode<T>* node, int id, const NodeApplicator& f) {
        if (node) {
            _traverse_direct(node->right, id*2+1, f);
            f(id, *node);
            _traverse_direct(node->left, id*2, f);
        }
    }

    void _remove(TreeNode<T>** nodePtr) {
        TreeNode<T>* node = *nodePtr;
        if (!node->left && !node->right) {
            *nodePtr = nullptr;
            delete node;
        } else if (!node->right) {
            TreeNode<T>** max_left = _find_max(&(node->left));
            std::swap(node->val, (*max_left)->val);
            _remove(max_left);
        } else {
            TreeNode<T>** min_right = _find_min(&(node->right));
            std::swap(node->val, (*min_right)->val);
            _remove(min_right);
        } 
    }

   public:
    Avl() {
        _size = 0;
        _root = nullptr;
    }

    virtual ~Avl() { _clean_tree(_root); }

    int size() { return _size; }

    bool empty() { return _root; }

    void insert(const T& val) {
        if (_root)
            _insert(_root, val);
        else
            _root = new TreeNode<T>(val);
        _size++;
    }

    bool remove(const T& val) {
        if (empty()) return false;

        TreeNode<T>** nodePtr = _find(&_root, val);
        if (!nodePtr) return false;

        _remove(nodePtr);
        _size--;
        return true;
    }

    T pop_min() {
        if(empty()) return false;

        TreeNode<T>** min = _find_min(&_root);
        T val = (*min)->val;

        _remove(min);

        return val;
    }

    T pop_max() {
        if(empty()) return false;

        TreeNode<T>** max = _find_max(&_root);
        T val = (*max)->val;

        _remove(max);

        return val;
    }

    void traverse(traverse_type ttype, Applicator func) {
        NodeApplicator f = [&](int id, const TreeNode<T>& node) {
            func(node.val);
        };
        switch (ttype) {
            case DIRECT:
                _traverse_direct(_root, 1, f);
                break;
            case REVERSED:
                _traverse_reversed(_root, 1, f);
                break;
            case MINMAX:
                _traverse_minmax(_root, 1, f);
                break;
            case MAXMIN:
                _traverse_maxmin(_root, 1, f);
                break;
            default:
                break;
        }
    }

    void gen_dotfile(std::ostream& out) {
        out << "digraph g { \n";
        out << "node [shape=circle];\n";

        auto add_node = [&](int id, const TreeNode<T>& node) {
            out << "node" << id << "[label=" << node.val << "];\n";
            if (node.left) {
                out << "node" << id << " -> node" << id*2 << ";\n";
            } else  {
                out << "nil" << id*2 << "[label=nil color=\"red\"];\n";
                out << "node" << id << " -> nil" << id*2 << ";\n";
            }

            if (node.right) {
                out << "node" << id << " -> node" << id*2+1 << ";\n";
            } else {
                out << "nil" << id*2+1 << "[label=nil color=\"red\"];\n";
                out << "node" << id << " -> nil" << id*2+1 << ";\n";
            }
        };
        _traverse_direct(_root, 1, add_node);

        out << "}";
    }
};
#endif /* ifndef _AVL_H */
