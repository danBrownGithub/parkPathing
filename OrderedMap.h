#include <typeinfo>
#include <string>

template <typename uniKey, typename data> 
class OrderedMap
{
    public:

    class Datum
    {
        public:
        Datum(uniKey _key, data _value);
        uniKey key;
        data value;
        Datum* left;
        Datum* right;
    };

    OrderedMap();
    void emplace(uniKey _key,data _value);
    void emplacePrim(Datum* root, uniKey _key,data _value);
    void emplaceNonPrim(Datum* root, uniKey _key,data _value);

    data* search(uniKey _key);
    data* searchPrim(uniKey key,Datum* _root);
    data* searchNonPrim(uniKey _key,Datum* _root);

    int operator<(std::string str);
    int operator>(std::string str);
    data* operator[](uniKey _key);
    

    Datum* root;
    
};

template <typename uniKey, typename data> 
OrderedMap<uniKey,data>::OrderedMap()
{
    root=nullptr;
}

template <typename uniKey, typename data> 
OrderedMap<uniKey,data>::Datum::Datum(uniKey _key, data _value)
{
    
        key=_key;
        value=_value;
        left=nullptr;
        right=nullptr;
    
}

template <typename uniKey, typename data> 
void OrderedMap<uniKey,data>::emplace(uniKey _key,data _value)
{
    std::string str;
    int z;
    if (root==nullptr)
    {
        root = new Datum(_key,_value);
        return;
    }
    /*
    if (typeid(_key)==typeid(str))
    {
        //emplaceNonPrim(root,_key,_value);
    }
    else if (typeid(_key)==typeid(z))
    {
        emplacePrim(root,_key,_value);
    }
    */
    emplacePrim(root,_key,_value);
}

template <typename uniKey, typename data> 
void OrderedMap<uniKey,data>::emplacePrim(Datum* _root, uniKey _key,data _value)
{
        if(_key<_root->key)
        {
            if (_root->left==nullptr)
            {
                _root->left=new Datum(_key,_value);
                return;
            }
            else 
            {
                emplacePrim(_root->left,_key,_value);
                return;
            }
        }
        else if (_key>_root->key)
        {
            if (_root->right==nullptr)
            {
                _root->right=new Datum(_key,_value);
                return;
            }
            else 
            {
                emplacePrim(_root->right,_key,_value);
                return;
            }
        }
        else
        {
            _root->value=_value;
        }
    
}

template <typename uniKey, typename data> 
void OrderedMap<uniKey,data>::emplaceNonPrim(Datum* _root, uniKey _key,data _value)
{
        if(_key.compare(_root->key)<0)
        {
            if (_root->left==nullptr)
            {
                _root->left=new Datum(_key,_value);
                return;
            }
            else 
            {
                emplaceNonPrim(_root->left,_key,_value);
                return;
            }
        }
        else if (_key.compare(_root->key)>0)
        {
            if (_root->right==nullptr)
            {
                _root->right=new Datum(_key,_value);
                return;
            }
            else 
            {
                emplaceNonPrim(_root->right,_key,_value);
                return;
            }
        }
        else
        {
            _root->value=_value;
        }
} 


template <typename uniKey, typename data> 
data* OrderedMap<uniKey,data>::search(uniKey _key)
{
    if (root==nullptr)
        {
            return nullptr;
        }

    int z;
    std::string str;
    /*
    if (typeid(_key)==typeid(z))
    {
        return searchPrim(_key,root);
    }
    else if (typeid(_key)==typeid(str))
    {
        //return searchNonPrim(_key,root);
        
    }
    */
    return searchPrim(_key,root);
    
}

template <typename uniKey, typename data> 
data* OrderedMap<uniKey,data>::searchPrim(uniKey _key,Datum* _root)
{
    
        if (_root->key==_key)
        {
            return& _root->value;
        }
        else if (_key<_root->key&&_root->left!=nullptr)
        {
            return searchPrim(_key,_root->left);
        }
        else if (_key>_root->key&&_root->right!=nullptr)
        {
            return searchPrim(_key,_root->right);
        }
        
    
    
}

template <typename uniKey, typename data> 
data* OrderedMap<uniKey,data>::searchNonPrim(uniKey _key,Datum* _root)
{
        if (_key.compare(_root->key)==0)
        {
            return& _root->value;
        }
        else if (_key.compare(_root->key)<0&&_root->left!=nullptr)
        {
            return searchNonPrim(_key,root->left);
        }
        else if (_key.compare(_root->key)>0&&root->left!=nullptr)
        {
            return searchNonPrim(_key,root->right);
        }
        return nullptr;
}

template <typename uniKey, typename data> 
int OrderedMap<uniKey,data>::operator>(std::string str)
{
    return this->compare(str);
}

template <typename uniKey, typename data> 
int OrderedMap<uniKey,data>::operator<(std::string str)
{
    return this->compare(str);
}


template <typename uniKey, typename data> 
data* OrderedMap<uniKey,data>::operator[](uniKey _key)
{
    return search(_key);
};

