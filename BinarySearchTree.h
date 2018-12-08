#ifndef ALGORITHMDEMO_BINARYSEARCHTREE_H
#define ALGORITHMDEMO_BINARYSEARCHTREE_H

template<typename KeyType, typename ValueType>
class BinarySearchTree
{
private:
    struct Node
    {
        KeyType key;
        ValueType value;
        Node* left;
        Node* right;
        Node(KeyType k, ValueType v) : key(k), value(v), left(NULL), right(NULL) {}
    };
    Node *root;
    int count;
public:
    BinarySearchTree()
    {
        count = 0;
        root = NULL;
    }
    ~BinarySearchTree()
    {
        releaseNode(root);
    }
    bool empty()
    {
        return (count == NULL);
    }
    int size()
    {
        return count;
    }
    void insert(KeyType k, ValueType v)
    {
        Node** nodePtr = &root;
        while(*nodePtr != NULL)
        {
            if(k > (*nodePtr)->key) nodePtr = &(*nodePtr)->right;
            else if(k < (*nodePtr)->key) nodePtr = &(*nodePtr)->left;
            else 
            {
                (*nodePtr)->value = v;
                return;
            }
        }
        *nodePtr = new Node(k, v);
        count++;
    }

    bool contain(KeyType k)
    {
        return (NULL != getNode(k));
    }

    ValueType getValue(KeyType k)
    {
        Node* node = getNode(k);
        assert(NULL != node);
        return node->value;
    }

    void inOrder()
    {
        cout << "InOrder:" << endl;
        inOrder(root);
        cout << "Done!" << endl;
    }

    KeyType min()
    {
        assert(!empty());
        return min(root)->key;
    }

    KeyType max()
    {
        assert(!empty());
        return max(root)->key;
    }

    void delKey(KeyType k)
    {
        delKey(root, k);
    }

    void delMin()
    {
        if(root)
            root = delMin(root);
    }

    void delMax()
    {
        if(root)
            root = delMax(root);
    }

    KeyType* ceil(KeyType k)
    {
        if(NULL == root)
            return NULL;
        Node* node = ceil(root, k);
        if(NULL == node)
            return NULL;
        else return &node->key;
    }

    KeyType* floor(KeyType k)
    {
        if(NULL == root)
            return NULL;
        Node* node = floor(root, k);
        if(NULL == node)
            return NULL;
        else return &node->key;
    }
private:
    void releaseNode(Node* node)
    {
        if(node != NULL)
        {
            releaseNode(node->left);
            releaseNode(node->right);
            delete node;
            count--;
        }
    }

    void inOrder(Node* node)
    {
        if(node != NULL)
        {
            inOrder(node->left);
            cout << node->key << " ";
            inOrder(node->right);
        }
    }

    Node *getNode(KeyType k)
    {
        Node* node = root;
        while(node != NULL)
        {
            if(k < node->key)
                node = node->left;
            else if(k > node->key)
                node = node->right;
            else return node;
        }
        return NULL;
    }

    Node* delMin(Node* node)
    {
        if(NULL != node->left)
        {
            node->left = delMin(node->left);
            return node;
        }
        Node *rightNode = node->right;
        delete node;
        count--;
        return rightNode;
    }

    Node* delMax(Node* node)
    {
        if(NULL != node->right)
        {
            node->right = delMax(node->right);
            return node;
        }
        Node *leftNode = node->left;
        delete node;
        count--;
        return leftNode;
    }

    Node* min(Node* node)
    {
        if(NULL == node->left)
            return node;

        return min(node->left);
    }

    Node* max(Node* node)
    {
        if(NULL == node->right)
            return node;

        return max(node->right);
    }

    Node* delKey(Node* node, KeyType k)
    {
        if(node == NULL) return node;

        Node* nextNode = node;
        if(k > node->key)
        {
            node->right = delKey(node->right, k);
        }
        else if(k < node->key)
        {
            node->left = delKey(node->left, k);
        }
        else
        {
            if(NULL == node->left)
            {
                nextNode = node->right;
                delete node;
                count--;
            }
            else if(NULL == node->right)
            {
                nextNode = node->left;
                delete node;
                count--;
            }
            else
            {
                Node* minNode = min(node->right);
                nextNode->key = minNode->key;
                nextNode->value = minNode->value;
                node->right = delMin(node->right);
            }
        }
        return nextNode;
    }

    Node* ceil(Node *node, KeyType k)
    {
        Node* ceilNode = NULL;
        if(NULL == node)
            return NULL;

        if(node->key < k)
            return ceil(node->right, k);
        else if(node->key > k)
        {
            ceilNode = node;

            Node* tmpNode = ceil(node->left, k);
            if(NULL == tmpNode)
                return ceilNode;
            else
                return tmpNode;
        }
        else return node;
    }

    Node* floor(Node *node, KeyType k)
    {
        Node* ceilNode = NULL;
        if(NULL == node)
            return NULL;

        if(node->key > k)
            return floor(node->left, k);
        else if(node->key < k)
        {
            ceilNode = node;

            Node* tmpNode = floor(node->right, k);
            if(NULL == tmpNode)
                return ceilNode;
            else
                return tmpNode;
        }
        else return node;
    }
};

#endif
