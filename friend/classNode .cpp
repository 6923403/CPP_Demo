class Node 
{
    friend class BinaryTree; // class BinaryTree can now access data directly
    private: 
       int data;
       int key;
       // ...
 
    
};

**BinaryTree就可以直接访问Node中的private的成员**

class BinaryTree
{
    private:
       Node *root;
 
    int find(int key);
};

int BinaryTree::find(int key)
{
    // check root for NULL...
    if(root->key == key)
    {
        // no need to go through an accessor function
        return root->data;
    }
    // perform rest of find
}
