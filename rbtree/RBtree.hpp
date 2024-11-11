#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <queue>

namespace RBT{

enum Color {RED, BLACK, NONE};

template <typename T>
struct Node
{
    Node *parent_;
    Node *left_;
    Node *right_;
    Color color_;
    T key_;

    Node(T key, Node<T> *parent = nullptr, Node<T> *left = nullptr, Node<T> *right = nullptr, Color color = BLACK) :
        color_{color}, key_{key}, parent_{parent}, left_{left}, right_{right} {}
    ~Node() = default;
};

template <typename T>
class Tree
{
private:
    Node<T> *nil_;
    Node<T> *root_;

    //          x                   y
    //        /  \                /  \
    //       A    y    ----->    x    C
    //           / \            / \
    //          B   C          A   B
    void left_rotate(Node<T> *x)
    {
        Node<T> *y = x->right_;
        x->right_ = y->left_;
        if(y->left_ != nil_) {y->left_->parent_ = x;}
        y->parent_ = x->parent_;

        //x is the root
        if(x->parent_ == nil_) {root_ = y;}
        else if(x->parent_->left_ == x) {x->parent_->left_ = y;}
        else{x->parent_->right_ = y;}

        y->left_ = x;
        x->parent_ = y;
    }

    //          x                   y
    //        /  \                /  \
    //       y    A    ----->    C    x
    //      / \                      / \
    //     C   B                    B   A
    void right_rotate(Node<T> *x)
    {
        Node<T> *y = x->left_;
        x->left_ = y->right_;
        if(y->right_ != nil_) {y->right_->parent_ = x;}
        y->parent_ = x->parent_;

        //x is the root
        if(x->parent_ == nil_) {root_ = y;}
        else if(x->parent_->left_ == x) {x->parent_->left_ = y;}
        else if(x->parent_->right_ == x) {x->parent_->right_ = y;}

        y->right_ = x;
        x->parent_ = y;
    }

    void insert_fixup(Node<T> *x)
    {
        while(x->parent_->color_ == RED)
        {
            if(x->parent_->parent_->left_ == x->parent_)
            {
                Node<T> *uncle = x->parent_->parent_->right_;

                //if uncle color is red -> change colors and do recursively for grandparant
                if(uncle->color_ == RED)
                {
                    x->parent_->color_ = BLACK;
                    uncle->color_ = BLACK;
                    uncle->parent_->color_ = RED;
                    x = uncle->parent_;
                }
                else
                {
                    if(x->parent_->right_ == x)
                    {
                        x = x->parent_;
                        left_rotate(x);
                    }
                    x->parent_->color_ = BLACK;
                    x->parent_->parent_->color_ = RED;
                    right_rotate(x->parent_->parent_);
                }
            }
            else
            {
                Node<T> *uncle = x->parent_->parent_->left_;

                //if uncle color is red -> change colors and do recursively for grandparant
                if(uncle->color_ == RED)
                {
                    x->parent_->color_ = BLACK;
                    uncle->color_ = BLACK;
                    uncle->parent_->color_ = RED;
                    x = uncle->parent_;
                }
                else
                {
                    if(x->parent_->left_ == x)
                    {
                        x = x->parent_;
                        right_rotate(x);
                    }
                    x->parent_->color_ = BLACK;
                    x->parent_->parent_->color_ = RED;
                    left_rotate(x->parent_->parent_);
                }
            }
        }
        root_->color_ = BLACK;
    }

    //change the subtree to_replace with a subtree replacement
    void transplant(Node<T> *to_replace, Node<T> *replacement)
    {
        //root case
        if(to_replace->parent_ == nil_) {root_ = replacement;}
        //left child
        else if(to_replace == to_replace->parent_->left_) {to_replace->parent_->left_ = replacement;}
        //right child
        else {to_replace->parent_->right_ = replacement;}
        replacement->parent_ = to_replace->parent_;
    }

    void erase_fixup(Node<T> *x)
    {
        Node<T> *sibling = nil_;
        while(x != root_ && x->color_ == BLACK)
        {
            if(x == x->parent_->left_)
            {
                sibling = x->parent_->right_;
                if(sibling->color_ == RED)
                {
                    sibling->color_ = BLACK;
                    x->parent_->color_ = RED;
                    left_rotate(x->parent_);
                    sibling = x->parent_->right_;
                }
                if(sibling->left_->color_ == BLACK && sibling->right_->color_ == BLACK)
                {
                    sibling->color_ = RED;
                    x = x->parent_;
                }
                else
                {
                    if(sibling->right_->color_ == BLACK)
                    {
                        sibling->left_->color_ = BLACK;
                        sibling->color_ = RED;
                        right_rotate(sibling);
                        sibling = x->parent_->right_;
                    }
                    sibling->color_ = x->parent_->color_;
                    x->parent_->color_ = BLACK;
                    sibling->right_->color_ = BLACK;
                    left_rotate(x->parent_);
                    x = root_;
                }
            }
            else
            {
                sibling = x->parent_->left_;
                if(sibling->color_ == RED)
                {
                    sibling->color_ = BLACK;
                    x->parent_->color_ = RED;
                    right_rotate(x->parent_);
                    sibling = x->parent_->left_;
                }
                if(sibling->right_->color_ == BLACK && sibling->left_->color_ == BLACK)
                {
                    sibling->color_ = RED;
                    x = x->parent_;
                }
                else
                {
                    if(sibling->left_->color_ == BLACK)
                    {
                        sibling->right_->color_ = BLACK;
                        sibling->color_ = RED;
                        left_rotate(sibling);
                        sibling = x->parent_->left_;
                    }
                    sibling->color_ = x->parent_->color_;
                    x->parent_->color_ = BLACK;
                    sibling->left_->color_ = BLACK;
                    right_rotate(x->parent_);
                    x = root_;
                }
            }
        }
        x->color_ = BLACK;
    }

public:
    Tree() {nil_ = new Node<T>{0}, root_ = nil_;}
    Tree(T key) {nil_ = new Node<T> {0}, root_ = new Node<T>{key, nil_, nil_, nil_};}
    Tree(Node<T> *nil, Node<T> *root) : nil_(nil), root_{root} {}
    ~Tree()
    {
        if (root_ == nil_) {delete nil_; return;}

        std::queue<Node<T> *> dlt_q;
        dlt_q.push(root_);

        while(!dlt_q.empty())
        {
            Node<T> *cur_node = dlt_q.front();
            dlt_q.pop();

            if(cur_node->left_ != nil_) {dlt_q.push(cur_node->left_);}
            if(cur_node->right_ != nil_) {dlt_q.push(cur_node->right_);}

            delete cur_node;
        }
        delete nil_;
    }
    Tree(const Tree<T> &) = delete;

    int count(T key)
    {
        if(find(key) == nil_) {return 0;}
        else {return 1;}
    }

    int count(T begin, T end)
    {
        int res = 0;

        std::queue<Node<T> *> q;
        q.push(root_);

        while(!q.empty())
        {
            Node<T> *cur_node = q.front();
            q.pop();

            if(cur_node != nil_)
            {
                if(cur_node->key_ <= end && cur_node->key_ >= begin)
                {
                    ++res;
                    q.push(cur_node->left_);
                    q.push(cur_node->right_);
                }
                else if(cur_node->key_ < begin)
                {
                    q.push(cur_node->right_);
                }
                else
                {
                    q.push(cur_node->left_);
                }
            }
        }
        return res;
    }

    Node<T> *get_nil() const {return nil_;}

    Node<T> *get_max(Node<T> *subtree) const
    {
        while(subtree->right_ != nil_)
        {
            subtree = subtree->right_;
        }
        return subtree;
    }

    Node<T> *get_min(Node<T> *subtree) const
    {
        while(subtree->left_ != nil_)
        {
            subtree = subtree->left_;
        }
        return subtree;
    }

    // returns nil_ if key was not found and ptr on Node if was
    Node<T> *find(T key)
    {
        Node<T> *search_elem = root_;

        while(search_elem != nil_ && search_elem->key_ != key)
        {
            if(key < search_elem->key_)
            {
                search_elem = search_elem->left_;
            }
            else {search_elem = search_elem->right_;}
        }
        return search_elem;
    }

    void insert(T key)
    {
        if(find(key) != nil_) {return;}
        Node<T> *new_node = new Node<T> {key, nil_, nil_, nil_};
        insert(new_node);
    }

    void insert(Node<T> *x)
    {
        if(find(x->key_) != nil_) {return;}

        Node<T> *compare = root_;
        Node<T> *parent = nil_;

        while(compare != nil_)
        {
            parent = compare;
            if(x->key_ < compare->key_)
            {
                compare = compare->left_;
            }
            else {compare = compare->right_;}
        }
        x->parent_ = parent;

        //empty tree
        if(parent == nil_)
        {
            root_ = x;
        }
        else if(x->key_ < parent->key_) {parent->left_ = x;}
        else {parent->right_ = x;}

        x->left_ = nil_;
        x->right_ = nil_;
        x->color_ = RED;

        //fix properties
        insert_fixup(x);
    }

    //deletion of Node from memory is up to user
    void erase(T key)
    {
        Node<T> *delete_node = find(key);
        if(delete_node == nil_) {return;}
        erase(delete_node);
    }

    void erase(Node<T> *x)
    {
        if(find(x->key_) == nil_) {return;}

        Node<T> *subtree = nil_;
        Color original_color = x->color_;
        // 1 or 0 child
        if(x->left_ == nil_)
        {
            subtree = x->right_;
            transplant(x, subtree);
        }
        else if(x->right_ == nil_)
        {
            subtree = x->left_;
            transplant(x, subtree);
        }
        // 2 children
        else
        {
            Node<T> *successor = get_min(x->right_);
            original_color = successor->color_;

            Node<T> *subtree = successor->right_;
            if(successor != x->right_)
            {
                transplant(successor, subtree);
                successor->right_ = x->right_;
                successor->right_->parent_ = successor;
            }
            else {subtree->parent_ = successor;} //need if subtree is nil_ in fixup algorithm
            transplant(x, successor);
            successor->left_ = x->left_;
            successor->left_->parent_ = successor;
            successor->color_ = x->color_;
        }

        //if hight of black changed
        if(original_color == BLACK) {erase_fixup(subtree);}
        delete x;
    }
};

}

#endif

