#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Tree;
class Node
{
friend class Tree;
private:
    int value;
    Node *left, *right;
    int height;
public:
    Node(int v) : value(v), left(NULL), right(NULL) {}
    ~Node() {}
};
class Tree
{
private:
    Node *root;
public:
    Tree() : root(NULL) {}
    void init()
    {
        int num;
        cin >> num;
        for (int i = 0; i < num; i++)
        {
            int temp;
            cin >> temp;
            root = insert(root, temp);
            cout << root->value << ": " << getHeight(root->left) << " " << getHeight(root->right) << endl;
        }
        for (int i = 0; i < num; i++)
        {
            int temp;
            cin >> temp;
            root = remove(root, temp);
            cout << root->value << ": " << getHeight(root->left) << " " << getHeight(root->right) << endl;                       
        }
    }
    int getHeight(Node *current)
    {
        if (current == NULL)
        {
            return 0;
        }
        return max(getHeight(current->left), getHeight(current->right)) + 1;
    }
    Node *leftRotate(Node *current)
    {
        Node *temp = current->left;
        current->left = temp->right;
        temp->right = current;      
        return temp;
    }
    Node *rightRotate(Node *current)
    {
        Node *temp = current->right;
        current->right = temp->left;
        temp->left = current;
        return temp;
    }
    Node *leftLeftRotate(Node *current)
    {
        cout << current->value << ": " << "left left" << endl;
        return leftRotate(current);
    }
    Node *rightRightRotate(Node *current)
    {
        cout << current->value << ": " << "right right" << endl;        
        return rightRotate(current);
    }
    Node *leftRightRotate(Node *current)
    {
        cout << current->value << ": " << "left right" << endl;        
        current->left = rightRotate(current->left);
        return leftRotate(current);
    }
    Node *rightLeftRotate(Node *current)
    {
        cout << current->value << ": " << "right left" << endl;        
        current->right = leftRotate(current->right);
        return rightRotate(current);
    }
    Node *insert(Node *node, int v)
    {
        if (node == NULL)
        {
            node = new Node(v);
            return node;
        }
        else
        {
            if (v < node->value)
            {
                node->left = insert(node->left, v);
            }
            else
            {
                node->right = insert(node->right, v);
            }
            if ((getHeight(node->left) - getHeight(node->right)) >= 2)
            {
                if (getHeight(node->left->left) > getHeight(node->left->right))
                {
                    return leftLeftRotate(node);
                }
                else
                {
                    return leftRightRotate(node);
                }
            }
            else if ((getHeight(node->left) - getHeight(node->right)) <= -2)
            {
                if (getHeight(node->right->left) > getHeight(node->right->right))
                {
                    return rightLeftRotate(node);
                }
                else
                {
                    return rightRightRotate(node);
                }
            }
            else
            {
                return node;
            }
        }
    }
    Node *remove(Node *node, int v)
    {
        if (node == NULL)
        {
            return NULL;
        }
        if (v == node->value)
        {
            if (node->left == NULL || node->right == NULL)
            {
                Node *temp;
                if (node->left != NULL)
                {
                    temp = node->left;
                }
                else
                {
                    temp = node->right;
                }
                delete node;
                return temp;
            }
            else
            {
                if (getHeight(node->left) > getHeight(node->right))
                {
                    Node *nodetemp = node->left;
                    while (nodetemp->right)
                        nodetemp = nodetemp->right;
                    node->value = nodetemp->value;
                    node->left = remove(node->left, node->value);
                }
                else
                {
                    Node *nodetemp = node->right;
                    while (nodetemp->left)
                        nodetemp = nodetemp->left;
                    node->value = nodetemp->value;
                    node->right = remove(node->right, node->value);
                }
                return node;
            }
        }
        else if (v < node->value)
        {
            node->left = remove(node->left, v);
        }
        else
        {
            node->right = remove(node->right, v);
        }
        
        if ((getHeight(node->left) - getHeight(node->right)) <= -2)
        {
            if (getHeight(node->right->left) > getHeight(node->right->right))
            {
                return rightLeftRotate(node);
            }
            else
            {
                return rightRightRotate(node);
            }
        }
        else if ((getHeight(node->left) - getHeight(node->right)) >= 2)
        {
            if (getHeight(node->left->left) < getHeight(node->left->right))
            {
                return leftRightRotate(node);
            }
            else
            {
                return leftLeftRotate(node);
            }
        }
        else
        {
            return node;
        }
    }
    void print()
    {
        cout << root->value << endl;
    }
};
int main(void)
{
    Tree t;
    t.init();
    //t.print();
    return 0;
}