#include "MyMap.h"
#include "Dictionary.h"
#include "TreeNode.h"

void get_identity(std::string my_id[])
{
    my_id[0] = "avsrcm";
    my_id[1] = "12449123";
}

template <typename K, typename V>
MyMap<K, V>::MyMap()
{
	root = nullptr;
}

template <typename K, typename V>
MyMap<K, V>::~MyMap()
{
    clear_helper(root);
}

template <typename K, typename V>
MyMap<K,V>::MyMap(const MyMap<K, V> &source)
{
    if(root == nullptr)
	{
	    root = nullptr;
	}
	else
    {
        clear_helper(root);
        clone(source.root);
	}
}

template <typename K, typename V>
MyMap<K, V> & MyMap<K, V>::operator=(const MyMap<K, V> &source)
{
    if(source.root == nullptr)
    {
        root = nullptr;
    }
    else
    {
        clear_helper(root);
        root = clone(source.root);
    }
    return *this;
}

template <typename K, typename V>
V & MyMap<K, V>::at(const K &key)
{
    if(root == nullptr)
    {
        throw std::out_of_range("MyMap::at");
    }
    return at_helper(root, key);
}

template <typename K, typename V>
V & MyMap<K, V>::operator[](const K &key)
{
   if(find(key) != nullptr)
   {
       return at_helper(root, key);
   }
   else
   {
       MyPair<K,V> temp(key);
       insert_helper(root,temp);
       return at_helper(root, key);
   }
}

template <typename K, typename V>
bool MyMap<K, V>::empty() const
{
    if(root->right == root && root->left == root)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename K, typename V>
int MyMap<K, V>::size() const
{
  return size_helper(root);
}

template <typename K, typename V>
void MyMap<K, V>::clear()
{
    clear_helper(root);
    root = nullptr;
}

template <typename K, typename V>
void MyMap<K, V>::insert(const MyPair<K, V> &init_pair)
{
    insert_helper(root, init_pair);
}

template <typename K, typename V>
void MyMap<K, V>::erase(const K &key)
{
    erase_helper(root, key);
}

template <typename K, typename V>
MyPair<K, V> * MyMap<K, V>::find(const K &key) const
{
    return find_helper(root, key);
}

template <typename K, typename V>
void MyMap<K, V>::print() const
{
    print_helper(root, "");
}

template <typename K, typename V>
int MyMap<K, V>::count(const K &key) const
{
    return count_helper(root, key);
}

/*
***********************************************************
          *            private                 *
***********************************************************
*/
template <typename K, typename V>
V & MyMap<K, V>::at_helper(TreeNode<MyPair<K, V>> *&rt, const K &key)
{
    MyPair<K,V> atNode(key);

    if(rt == nullptr)
    {
        rt = new TreeNode<MyPair<K,V>>(atNode, nullptr, nullptr);
        return rt->data.second;
    }
    else if(rt->data.first == key)
    {
        return rt->data.second;
    }
    else if(rt->data.first > key)
    {
        return at_helper(rt->left, atNode.first);
    }
    else
    {
        return at_helper(rt->right, atNode.first);
    }
}

template <typename K, typename V>
int MyMap<K, V>::size_helper(TreeNode<MyPair<K, V>> *rt) const
{
    if(rt == nullptr)
        return 0;

    return (1 + size_helper(rt->left) + size_helper(rt->right));
}

template <typename K, typename V>
void MyMap<K, V>::clear_helper(TreeNode<MyPair<K, V>> *&rt)
{
    if(rt == nullptr)
        return;
    else
    {
        clear_helper(rt->left);
        clear_helper(rt->right);
        delete rt;
    }
}

template <typename K, typename V>
void MyMap<K, V>::insert_helper(TreeNode<MyPair<K, V>> *&rt, const MyPair<K, V> &init_pair)
{
    if(rt == nullptr)
    {
        rt = new TreeNode<MyPair<K, V>>(init_pair, nullptr, nullptr);
    }
    else if(init_pair.first < rt->data.first)
    {
        insert_helper(rt->left, init_pair);
    }
    else
    {
        insert_helper(rt->right, init_pair);
    }
}

template <typename K, typename V>
TreeNode<MyPair<K, V>> * MyMap<K,V>::get_min(TreeNode<MyPair<K, V>> *rt)
{
    if(rt->left == nullptr)
        return rt;
    else
        return get_min(rt->left);
}

template <typename K, typename V>
void MyMap<K, V>::erase_helper(TreeNode<MyPair<K, V>> *&rt, const K &key)
{
    if(rt == nullptr)
    {
        rt = nullptr;
    }
    else if(key < rt->data.first)
    {
        erase_helper(rt->left, key);
    }

    else if(key > rt->data.first)
    {
        erase_helper(rt->right, key);
    }
    else
    {
        TreeNode<MyPair<K,V>> *temp = rt;
        if(rt->left == nullptr)
        {
            rt = rt->right;
            delete temp;
        }
        else if(rt->right == nullptr)
        {
            rt = rt->left;
            delete temp;
        }
        else
        {
            TreeNode<MyPair<K,V>> *temp = get_min(rt->right);
            rt->data.first = temp->data.first;
            rt->data.second = temp->data.second;
            delete temp;
        }
    }
}

template <typename K, typename V>
MyPair<K, V> * MyMap<K,V>::find_helper(TreeNode<MyPair<K, V>> *rt, const K &key) const
{
    if(rt == nullptr)
        return nullptr;

    if(key < rt->data.first)
    {
        return find_helper(rt->left, key);
    }
    else if(key > rt->data.first)
    {
        return find_helper(rt->right, key);
    }
    else
        return &rt->data;
}

template <typename K, typename V>
void MyMap<K, V>::print_helper(TreeNode<MyPair<K, V>> *rt, std::string indent) const
{
    if(rt == nullptr)
    {
        cout << indent << "   empty" << endl;
        return;
    }
    print_helper(rt->right, indent += "   ");
    cout << indent << " " << rt->data.first;
    cout << " " << rt->data.second << endl;
    print_helper(rt->left, indent += "");
}

template <typename K, typename V>
int MyMap<K, V>::count_helper(TreeNode<MyPair<K, V>> *rt, const K &key) const
{
    int count = 0;

    if(rt == nullptr)
        return 0;
    if(rt->right = NULL)
    {
        count += count_helper(rt->right, key);
    }
    else if(rt->left = NULL)
    {
        count += count_helper(rt->left, key);
    }
    return count;
}

template <typename K, typename V>
TreeNode<MyPair<K, V>> * MyMap<K, V>::clone(const TreeNode<MyPair<K, V>> *rt)
{
    if (rt == nullptr)
        return nullptr;
    else
    {
        TreeNode<MyPair<K, V>> *tempTree = new TreeNode<MyPair<K, V>>(rt->data, clone(rt->left), clone(rt->right));
        return tempTree;
    }
}
