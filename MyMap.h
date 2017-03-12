// MyMap.h

// Skeleton for the MyMap class template.  You must implement the first six
// member functions.
template<typename KeyType, typename ValueType>
class MyMap
{
public:
    MyMap();
    ~MyMap();
    
    void clear();
    
    int size() const;
    void associate(const KeyType& key, const ValueType& value);
	  // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;
    
	  // for a modifiable map, return a pointer to modifiable ValueType
	ValueType* find(const KeyType& key)
	{
		return const_cast<ValueType*>(const_cast<const MyMap*>(this)->find(key));
	}

	  // C++11 syntax for preventing copying and assignment
	MyMap(const MyMap&) = delete;
	MyMap& operator=(const MyMap&) = delete;

private:
    
    /*
     * Basic struct used in the BST
     */
    struct Node{
        KeyType key;
        ValueType value;
        Node *left, *right;
        
        Node(KeyType k, ValueType v){
            key = k;
            value = v;
            left = right = nullptr;
        }
    };
    
    Node *m_root;
    int m_size;

    /*
     * Uses the binary search function below
     * to obtain correct insertion position (either new, or override)
     * otherwise boundary conditions (set as m_root)
     */
    void insert(KeyType key, ValueType value);
    
    /*
     * All-purpose binary search
     * if found,
     * returns true, and will populate found with Node of found
     * if not found,
     * return false, and will populate found with Node just before 
     * and also populates right, so that we know where to insert
     */
    bool search(KeyType key, Node *cur, Node *&found, bool &right) const;
    
    /*
     * post-order traversal
     * to access child Nodes before parents
     */
    void clearTree(Node *cur);
    
};

template<typename KeyType, typename ValueType>
MyMap<KeyType,ValueType>::MyMap()
{
    m_root = nullptr;
    m_size = 0;
}

template<typename KeyType, typename ValueType>
MyMap<KeyType, ValueType>::~MyMap()
{
    clear();
}

template<typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::clear()
{
    clearTree(m_root);
}


template<typename KeyType, typename ValueType>
int MyMap<KeyType, ValueType>::size() const
{
    return m_size;
}

template<typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
    insert(key, value);
}

template<typename KeyType, typename ValueType>
const ValueType* MyMap<KeyType, ValueType>::find(const KeyType& key) const
{
    Node *found;
    bool isRightNode;
    if(search(key, m_root, found, isRightNode))
    {
        return &found->value;
    }
    
    return nullptr;
}


//******************** Private BST implementations ************************************

/*
 * Uses the binary search function below
 * to obtain correct insertion position (either new, or override)
 * otherwise boundary conditions (set as m_root)
 */
template<typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::insert(KeyType key, ValueType value)
{
    Node *found;
    bool isRightNode;
    if(search(key, m_root, found, isRightNode)) //if currently exists
    {
        found->value = value;   //override
        return;
    }
    
    //can insert
    m_size++;
    
    if(m_root == nullptr)
    {
        m_root = new Node(key, value);
        return;
    }
    
    if(isRightNode){
        found->right = new Node(key, value);
    }
    else{
        found->left = new Node(key, value);
    }
    
}

/*
 * All-purpose binary search
 * if found,
 * returns true, and will populate found with Node of found
 * if not found,
 * return false, and will populate found with Node just before
 * and also populates right, so that we know where to insert
 */
template<typename KeyType, typename ValueType>
bool MyMap<KeyType, ValueType>::search(KeyType key, Node *cur, Node *&found, bool &right) const
{
    if(cur == nullptr)
        return false;
    
    else if(key == cur->key){
        found = cur;
        return true;
    }
    else if (key < cur->key){
        
        if(cur->left != nullptr)
            return search(key, cur->left, found, right);
        else
        {
            found = cur;
            right = false;
            return false;
        }
    }
    else if (key > cur->key){
        
        if(cur->right != nullptr)
            return search(key, cur->right, found, right);
        else{
            found = cur;
            right = true;
            return false;
        }
        
    }
    
    return false;
    
}

/*
 * post-order traversal
 * to access child Nodes before parents
 */
template<typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::clearTree(Node *cur)
{
    if(cur == nullptr)
        return;
    
    clearTree(cur->left);
    clearTree(cur->right);
    
    delete cur;
}

















