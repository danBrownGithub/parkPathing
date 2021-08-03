#include <typeinfo>
#include <string>
#include <iostream>
#include <stdio.h>

template <typename uniKey, typename data> 
class UnorderedMap
{

    public:
    struct Bucket
    {
        
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
    Bucket* search(uniKey _key);
    int hash(int _key);
    int hash (std::string _key);
    void refactor();
    void size();
    Bucket* operator[](uniKey _key);

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
    //std::cout<<insertIndex<<std::endl;
   
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
    int powerOf=10;
    int val=0;
    int valToReturn=0;
    while (_key/powerOf>1)
    {
        val=_key%powerOf;
        powerOf*=10;
        valToReturn=val*powerOf;

    }
    
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
    auto tempBucket=(int)(numBucket*factor);
    Bucket* temp = new Bucket[tempBucket];

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
    numBucket=tempBucket;
    
    delete[] table;
    
    table=temp;
    
}

template <typename uniKey, typename data> 
typename UnorderedMap<uniKey,data>::Bucket* UnorderedMap<uniKey,data>::search(uniKey _key)
{
    auto insertIndex = hash(_key)%numBucket;
    auto stopper = insertIndex;
    if (table[insertIndex].key==_key)
    {   
        return &table[insertIndex];
    }
    else if (table[insertIndex].key!=_key)
    {
        
        while (table[insertIndex].key!=_key)
        {
            insertIndex++;
            
            if ((insertIndex==numBucket))
            {
                insertIndex=0;
                //std::cout<<"not found"<<std::endl;
                
            }
            if (insertIndex==stopper)
            {
                return nullptr;
            }

        }
        if (table[insertIndex].key==_key)
        {
            return &table[insertIndex];
        }
    }
    return nullptr;
    
}

template <typename uniKey, typename data> 
typename UnorderedMap<uniKey,data>::Bucket* UnorderedMap<uniKey,data>::operator[](uniKey _key)
{
    if (search(_key)==nullptr)
    {
        data temp;
        insert(_key,temp);
        return search(_key);
    }
    else
    {
        return search(_key);
    }
};

