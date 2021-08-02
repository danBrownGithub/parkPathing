#include <typeinfo>
#include <string>
#include <iostream>


template <typename uniKey, typename data> 
class UnorderedMap
{

    public:
    class Bucket
    {
        public:
        bool filled;
        uniKey key;
        data value;
    };

    UnorderedMap();
    float critLoad;
    float loadFactor;
    int numBucket;
    int numFilled;

    
    void insert(uniKey _key, data _value);
    data* search(uniKey _key);
    int hash(int _key);
    int hash (std::string _key);
    void refactor();
    void size();
    data* operator[](uniKey _key);

    Bucket* table;
};

template <typename uniKey, typename data> 
UnorderedMap<uniKey,data>::UnorderedMap()
{
    table = new Bucket[2];
    numBucket=2;
    numFilled=0;
    loadFactor=0.0;
    critLoad=0.5;
    
}


template <typename uniKey, typename data> 
void UnorderedMap<uniKey,data>::size()
{
    std::cout<<numBucket<<std::endl;
    
}

template <typename uniKey, typename data> 
void UnorderedMap<uniKey,data>::insert(uniKey _key, data _value)
{

    auto insertIndex = hash(_key)%numBucket;
    std::cout<<insertIndex<<std::endl;
    if (table[insertIndex].filled==false)
    {
        table[insertIndex].key=_key;
        table[insertIndex].value=_value;
        table[insertIndex].filled=true;
        numFilled++;
    }
    else 
    {
        while(table[insertIndex].filled==true)
        {
            insertIndex++;
        }
        table[insertIndex].key=_key;
        table[insertIndex].value=_value;
        table[insertIndex].filled=true;
        numFilled++;
    }


    if ((float)numFilled/(float)numBucket>critLoad)
    {
        refactor();
    }

}

template <typename uniKey, typename data> 
int UnorderedMap<uniKey,data>::hash(int _key)
{
    return _key%numBucket;
}


template <typename uniKey, typename data> 
int UnorderedMap<uniKey,data>::hash(std::string _key)
{
    int hashedKey=0;
    for (int i =0;i<4;i++)
    {
        hashedKey+=_key[i]^13;
    }
    
    return hashedKey;
}

template <typename uniKey, typename data> 
void UnorderedMap<uniKey,data>::refactor()
{
    auto factor = 1/critLoad;
    Bucket* temp = new Bucket[(int)(numBucket*factor)];

    for (int i =0;i<numBucket;i++)
    {
        
        if (table[i].filled==true)
        {
            auto insertIndex = hash(table[i].key)%((int)(numBucket*factor));
            if (temp[insertIndex].filled==false)
            {
                temp[insertIndex].key=table[i].key;
                temp[insertIndex].value=table[i].value;
                temp[insertIndex].filled=true;

            }    
            else 
            {
                while(temp[insertIndex].filled==true)
                {
                    insertIndex++;
                }
                temp[insertIndex].key=table[i].key;
                temp[insertIndex].value=table[i].value;
                temp[insertIndex].filled=true;
                
            }
        } 
    }
    numBucket=numBucket*factor;
    delete[] table;
    table=temp;
}

template <typename uniKey, typename data> 
data* UnorderedMap<uniKey,data>::search(uniKey _key)
{
    auto insertIndex = hash(_key)%numBucket;
    if (table[insertIndex].key==_key)
    {
        return &table[insertIndex].value;
    }
    else if (table[insertIndex].key!=_key)
    {
        
        while (table[insertIndex].key!=_key)
        {
            insertIndex++;
            
            if ((insertIndex==numBucket))
            {
                std::cout<<"not found"<<std::endl;
                return nullptr;
            }

        }
        if (table[insertIndex].key==_key)
        {
            return &table[insertIndex].value;
        }
    }
    return nullptr;
    
}

template <typename uniKey, typename data> 
data* UnorderedMap<uniKey,data>::operator[](uniKey _key)
{
    return search(_key);
};

