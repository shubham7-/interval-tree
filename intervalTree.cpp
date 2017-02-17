#include<bits/stdc++.h>
using namespace std;
struct node
{
    int low,high,maxi;
    struct node *left, *right;
};
// A function to create a new BST node
struct node *newnode(int low, int high)
{
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->low = low;
    temp->high = high;
    temp->maxi=high;
    temp->left = temp->right = NULL;
    return temp;
}
struct node * minvaluenode(struct node* node)
{
    struct node* current = node;
 
    /* loop to find the left-most leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
 
/* function to insert a new node with a given key in BST */
struct node* insert(struct node* node, int low, int high)
{
    if (node == NULL) return newnode(low,high);
    if (low < node->low)
        node->left  = insert(node->left, low, high);
    else
        node->right = insert(node->right,low, high);
	node->maxi=max(node->high,max((node->left==NULL)?0:node->left->maxi,
			   					  (node->right==NULL)?0:node->right->maxi));
    return node;
}
 
/* Given a bst and a key, function deletes the key and returns new root */
struct node* deletenode(struct node* node, int low, int high)
{
    
    if (node == NULL) return node;
 
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (low < node->low)
        node->left = deletenode(node->left, low, high);
 
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (low > node->low)
        node->right = deletenode(node->right,low,high);
 
    // if key is same as root's key, then This is the node
    // to be deleted
    else if(low==node->low&&high==node->high)
    {
        // node with only one child or no child
        if (node->left == NULL)
        {
            struct node *temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL)
        {
            struct node *temp = node->left;
            free(node);
            return temp;
        }
 
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct node* temp = minvaluenode(node->right);
 
        // Copy the inorder successor's content to this node
        node->low = temp->low;
        node->high=temp->high;
        node->maxi=temp->maxi;
 
        // Delete the inorder successor
        node->right = deletenode(node->right, temp->low,temp->high);
    }
    node->maxi=max(node->high,max((node->left==NULL)?0:node->left->maxi,
			   					  (node->right==NULL)?0:node->right->maxi));
    return node;
}
void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout<<root->low<<":"<<root->high<<":"<<root->maxi<<" ";
        inorder(root->right);
    }
}
// A utility function to check if given two intervals overlap
bool overlap(int low1, int high1, int low2, int high2)
{
    if (low1 <= high2 && low2 <= high1)
        return true;
    return false;
}
 
// The main function that searches a given interval i in a given Interval Tree.
void find(struct node* node, int low, int high)
{
    // Base Case, tree is empty
    if (node == NULL) return;
 
    // If given interval overlaps with root
    if (overlap(node->low,node->high,low,high)){
    	cout<<node->low<<":"<<node->high<<endl;
    	return;
	}
        
 
    // If left child of root is present and max of left child is
    // greater than or equal to given interval, then i may
    // overlap with an interval is left subtree
    if (node->left != NULL && node->left->maxi >= low)
        find(node->left,low,high);
    find(node->right,low,high);
}

int main()
{
	int ch,low,high;
	struct node *root = NULL;
	while(true){
		cin>>ch>>low>>high;
		if(ch==1){
			root = insert(root,low,high);
			inorder(root);
		}
		else if(ch==2){
			root = deletenode(root,low,high);
			inorder(root);
		}
		else if(ch==3){
			find(root,low,high);
		}
		else{
			break;
		}
		cout<<endl;
	}
	return 0;
}

