#include <iostream>
#include <cstdlib>
#include <vector>

const int Hash_size = 12;
struct HashTable
{
    int *elem;
    int count;
};
int m = 0;

void init_hash(HashTable** hash)
{
    int i;
    m = Hash_size;
    (*hash)->count = m;
    (*hash)->elem = new int[m * sizeof(int)];
    for(i = 0; i < m; i++)
    {
        (*hash)->elem[i] = -1;
    }
}

int Hash(int key)
{
    /* 除留余数法 */
    return key % m;
}

void Insert_hash(HashTable** hash, int key)
{
    int addr = Hash(key);
    while((*hash)->elem[addr] != -1)
    {
        addr = Hash(addr + 1) % m;
    }

    (*hash)->elem[addr] = key;
}

bool Search_hash(HashTable* hash, int key)
{
    int addr = Hash(key);
    while(hash->elem[addr] != key)
    {
        addr = Hash(addr + 1) % m;
        if(hash->elem[addr] == -1 || addr == Hash(key))
        {
            std::cout << "search unsuccess" << std::endl;
            return false;
        }
    }

    std::cout << "key: " << key << " addr = " << addr << std::endl;
    return true;
}

void show(HashTable* hash)
{
    for(int i = 0; i < m; i++)
    {
        std::cout << "index: " << i << " i.key = " << hash->elem[i] << std::endl;
    }
}

int main(int argc, char** argv)
{
    HashTable *hash;

    init_hash(&hash);
    std::vector<int> a = {12, 44, 39, 52, 48, 20, 19, 33, 82, 91, 66};
    int as = a.size();
    for(int i = 0; i < as; i++)
    {
        Insert_hash(&hash, a[i]);
    }

    show(hash);

    Search_hash(hash, 44);

    return 0;
}
