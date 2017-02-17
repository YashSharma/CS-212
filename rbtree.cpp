#include <iostream>
using namespace std;

#define RED 1
#define BLACK 2

struct node
{
	int val;
	node *left, *right, *p;
	int color;
};

struct node NIL;
node *tnil = &NIL;

void leftrotate(node **root, node *x)
{
	node *y = x->right;
	x->right = y->left;
	if(y->left != tnil)
		y->left->p = x;
	y->p = x->p;
	if(x->p == tnil)
		*root = y;
	else if(x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;
}

void rightrotate(node **root, node	*y)
{
	node *x = y->left;
	y->left = x->right;
	if(x->right != tnil)
		x->right->p = y;
	x->p = y->p;
	if(y->p == tnil)
		*root = x;
	else if(y == y->p->left)
		y->p->left = x;
	else
		y->p->right = x;
	x->right = y;
	y->p = x;
}

void rbinsertfixup(node **root, node *z)
{
	while(z->p->color == RED)
	{
		if(z->p==z->p->p->left)
		{
			node* y = z->p->p->right;
			if(y->color == RED)
			{
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}else {
			if(z==z->p->right)
			{
				z = z->p;
				leftrotate(root, z);
			}
			z->p->color = BLACK;
			z->p->p->color = RED;
			rightrotate(root, z->p->p);
			}
		}else
		{
			node* y = z->p->p->left;
			if(y->color == RED)
			{
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}else 
			{
				if(z == z->p->left)
				{
					z = z->p;
					rightrotate(root,z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				leftrotate(root,z->p->p);
			}
		}
	}
	(*root)->color = BLACK;
}

void rbinsert(node **root, int item)
{
	node *z = new node;
	z->val = item;
	node *y = tnil;
	node *x = *root;
	while(x!=tnil)
	{
		y = x;
		if(z->val<x->val)
			x = x->left;
		else
			x = x->right;
	}
	z->p = y;
	if(y==tnil)
	{
		*root = z;
	}else if(z->val<y->val)
		y->left = z;
	else
		y->right = z;
	z->left = tnil;
	z->right = tnil;
	z->color = RED;
	rbinsertfixup(root,z);
}

void rbtransplant(node **root, node *u, node *v)
{
	if(u->p == tnil)
		*root = v;
	else if(u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	v->p = u->p;
}

node* search(node *root, int item)
{
	if(root == tnil)
		return tnil;
	else if(root->val==item)
		return root;
	else if(root->val<item)
		return search(root->right, item);
	else
		return search(root->left, item);
}

node* minimum(node *root)
{
	while(root->left!=tnil)
		root = root->left;
	return root;
}

void rbdeletefixup(node **root, node *x)
{
	while(x != *root && x->color == BLACK)
	{
		if(x == x->p->left)
		{
			node *w = x->p->right;
			if(w->color == RED)
			{
				w->color = BLACK;
				x->p->color = RED;
				leftrotate(root, x->p);
				w = x->p->right;
			}
			if(w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->p;
			}else
			{
				if(w->right->color == BLACK)
				{
					w->left->color = BLACK;
					w->color = RED;
					rightrotate(root, w);
					w = x->p->right;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->right->color = BLACK;
				leftrotate(root, x->p);
				x = *root;
			}
		}else
		{
			node *w = x->p->left;
			if(w->color == RED)
			{
				w->color = BLACK;
				x->p->color = RED;
				rightrotate(root, x->p);
				w = x->p->left;
			}
			if(w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->p;
			}else
			{
				if(w->left->color == BLACK)
				{
					w->right->color = BLACK;
					w->color = RED;
					leftrotate(root, w);
					w = x->p->left;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				rightrotate(root, x->p);
				x = *root;
			}


		}
	}
	x->color = BLACK;
}


void rbdelete(node **root, int item)
{
	node *z = search(*root,item);
	if(z == tnil)
	{
		cout<<"Value not in Tree"<<endl;
		return;
	}

	node *y = z;
	node *x;
	int y_original_color = y->color;
	if(z->left == tnil)
	{
		x = z->right;
		rbtransplant(root, z, z->right);
	}
	else if(z->right == tnil)
	{
		x = z->left;
		rbtransplant(root, z, z->left);
	}
	else
	{
		y = minimum(z->right);
		y_original_color = y->color;
		x = y->right;
		if(y->p == z)
		{
			x->p = y;
		}else
		{
			rbtransplant(root, y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		rbtransplant(root, z, y);
		y->left = z->left;
		y->left->p = y;
		y->color = z->color;
	}
	if(y_original_color == BLACK)
		rbdeletefixup(root, x);
}

void inorder(node* root)
{
    if (root == tnil) return; 
    inorder(root->left);
 
    cout<<root->val<<endl;
 
    inorder(root->right);
}


int main()
{
	NIL.left = NIL.right = NIL.p = tnil;
	NIL.color = BLACK;
	node *tree = tnil;

	int arr[5] = {1,2,3,4,5};

	for(int i = 0;i<5;i++)
	{
		rbinsert(&tree, arr[i]);
	}

	rbdelete(&tree, 10);

	inorder(tree);
	return 0; 
}



