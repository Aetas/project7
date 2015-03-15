#include<iostream>
#include<string>
#include<json/json.h>
#include "MovieTree.h"

//******************
//-FREEEEEBIRD-
//******************

std::ostream& operator<<(std::ostream& os, MovieNode* n)
{
	os << "Movie:" << n->title << std::endl;
	return os;
}

//******************
//-MOVIE_NODE-
//******************
//default construct, never really used
MovieNode::MovieNode()
{
	parent = nullptr;
	title = "nil";
	year = -1;
	quantity = -1;
	ranking = -1;
	left = nullptr;
	right = nullptr;
	isRed = false;
}
//proper argument construct
MovieNode::MovieNode(int& rating, std::string& ttl, int& yr, int& qtty)
{
	parent = nullptr;
	title = ttl;
	year = yr;
	quantity = qtty;
	ranking = rating;
	left = nullptr;
	right = nullptr;
	isRed = true;
}

//destructor
MovieNode::~MovieNode()
{

}
//******************
//-END MOVIE_NODE-
//******************


//******************
//-MOVIE_TREE
//******************

//default construct
MovieTree::MovieTree()
{
	Assignment6Output = json_object_new_object();
	operations = 1;
	nil = new MovieNode();
	nil->parent = nil;
	nil->left = nil;
	nil->right = nil;
	nil->isRed = false;
    root = nil;
    root->parent = nil;
}

//default destructs
MovieTree::~MovieTree()
{
	void delete_tree(MovieNode* root);
	delete nil;
}

//used to pass raw data from main() into the MovieTree's domain, eliminating creation of objects in main. Keeps it tidy (to me)
void MovieTree::addRawNode(int& rank, std::string& ttl, int& yr, int& qtty, json_object* traverseLog)
{
	MovieNode* n = new MovieNode(rank, ttl, yr, qtty);	//creates real node
	//n->right = nil;
	//n->left = nil;
	n->parent = nil;
	insert(n, traverseLog);	//finds the position it belongs in
}

//search for a movie by title (external)
MovieNode* MovieTree::search(std::string& ttl, json_object* traverseLog)
{
	MovieNode* n = root;	//start at root, this is the external call

	json_object* jMovie = json_object_new_string(n->title.c_str());
    json_object_array_add(traverseLog, jMovie);

	if (n == nil || n->title == ttl)	//basically, if the tree does not exist
		return n;
	if (ttl.compare(n->title) < 0)			//choose which branch ot go into and call self again to repeat
		return search(n->left, ttl, traverseLog);
	else
		return search(n->right, ttl, traverseLog);
}

//same as above but internal
MovieNode* MovieTree::search(MovieNode* n, std::string& ttl, json_object* traverseLog)
{
    json_object* jMovie = json_object_new_string(n->title.c_str());
    json_object_array_add(traverseLog, jMovie);

	if (n == nil || n->title == ttl)
		return n;
	if (ttl.compare(n->title) < 0)
		return search(n->left, ttl, traverseLog);
	else
		return search(n->right, ttl, traverseLog);
}

//a function a wrote for fun as prompted by the book. "This method is faster on most modern computers"
MovieNode* MovieTree::iterative_search(std::string& ttl, json_object* traverseLog)
{

	MovieNode* n = root;
	while (n != nil && ttl != n->title)	//instead of recursion calls, just while() it until it is found
	{
	    json_object* jMovie = json_object_new_string(n->title.c_str());
        json_object_array_add(traverseLog, jMovie);
		if (ttl.compare(n->title) < 0)
			n = n->left;
		else
			n = n->right;
	}
	return n;
}

//external call to print entire tree
void MovieTree::inorder_walk(json_object* traverseLog)
{
	MovieNode* n = root;	//start at root
	if (n != nil)	//if there is still room to dive
	{
		inorder_walk(n->left, traverseLog);	//start small
		json_object* jMovie = json_object_new_string(n->title.c_str());
        json_object_array_add(traverseLog, jMovie);
		std::cout << n;			//custom ostream
		inorder_walk(n->right, traverseLog);	//then step down the large
	}
}

void MovieTree::inorder_walk(MovieNode* n, json_object* traverseLog)
{
	if (n != nil)	//if there is still room to dive
	{
		inorder_walk(n->left, traverseLog);	//start small
		json_object* jMovie = json_object_new_string(n->title.c_str());
        json_object_array_add(traverseLog, jMovie);
		std::cout << n;			//custom ostream
		inorder_walk(n->right, traverseLog);	//then step down the large
	}
}

int MovieTree::getTreeSize()
{

    MovieNode* n = root;
    if(n == nil)
    { //This node doesn't exist. Therefore there are no nodes in this 'subtree'
        return 0;
    }
    else
    { //Add the size of the left and right trees, then add 1 (which is the current node)
        return getTreeSize(n->left) + getTreeSize(n->right) + 1;
    }
}

int MovieTree::getTreeSize(MovieNode* n)
{
    if(n == nil)
    { //This node doesn't exist. Therefore there are no nodes in this 'subtree'
        return 0;
    }
    else
    { //Add the size of the left and right trees, then add 1 (which is the current node)
        return getTreeSize(n->left) + getTreeSize(n->right) + 1;
    }
}

int MovieTree::getMaxHeight()
{
    MovieNode* n = root;
    if(n == nil)
        return 0;

    int lheight = -1;
    int rheight = -1;

    lheight = getMaxHeight(n->left, lheight, rheight);
    rheight = getMaxHeight(n->right, lheight, rheight);

    if(lheight > rheight)
        return lheight+1;
    return rheight+1;
}

int MovieTree::getMaxHeight(MovieNode* n, int& lheight, int& rheight)
{
    if(n == nil)
        return 0;

    lheight = getMaxHeight(n->left, lheight, rheight);
    rheight = getMaxHeight(n->right, lheight, rheight);

    if(lheight > rheight)
        return lheight+1;
    return rheight+1;
}

// Returns 0 if the tree is invalid, otherwise returns the black node height.
int MovieTree::rbValid(MovieNode * node)
{
    int lh = 0;
    int rh = 0;

    // If we are at a nil node just return 1
    if (node == nil)
        return 1;
    else
    {
        // First check for consecutive red links.
        if (node->isRed)
        {
            if(node->left->isRed || node->right->isRed)
            {
                std::cout << "This tree contains a red violation" << std::endl;
                return 0;
            }
        }
        // Check for valid binary search tree.
        if ((node->left != nil && node->left->title.compare(node->title) > 0) || (node->right != nil && node->right->title.compare(node->title) < 0))
        {
            std::cout << "This tree contains a binary tree violation" << std::endl;
            return 0;
        }
        // Deteremine the height of let and right children.
        lh = rbValid(node->left);
        rh = rbValid(node->right);

        // black height mismatch
        if (lh != 0 && rh != 0 && lh != rh)
        {
            std::cout << "This tree contains a black height violation" << std::endl;
            return 0;
        }
        // If neither height is zero, incrament if it if black.
        if (lh != 0 && rh != 0)
        {
                if (node->isRed)
                    return lh;
                else
                    return lh+1;
        }
        else
            return 0;
    }
}
MovieNode* MovieTree::getNil()
{
    return nil;
}

//minimum from root (whole tree)
MovieNode* MovieTree::minimum()
{
	MovieNode* n = root;
	while (n->left != nil)	//I don't think NULL is actually needed
		n = n->left;					//basically, just go left until you cant. That's the smallest
	return n;
}

//minimum for specified tree (sub-tree). same as above. Made for delete, really.
MovieNode* MovieTree::minimum(MovieNode* n)
{
	while (n->left != nil)
		n = n->left;
	return n;
}

//max from root (whole tree)
MovieNode* MovieTree::maximum()
{
	MovieNode* n = root;		//mirror of minimum, as is the nature of binary
	while (n->right != nil)
		n = n->right;
	return n;
}

//max from specified tree (sub-tree). same as above. made for delete
MovieNode* MovieTree::maximum(MovieNode* n)
{
	while (n->right != nil)
		n = n->right;
	return n;
}

//find next largest in the tree
MovieNode* MovieTree::successor(MovieNode* n)
{
	if (n->right != nil)
		return minimum(n);			//if the right child is not empty, that is the successor
	MovieNode* trail = n->parent;	//trailing pointer
	while (trail != nil && n == trail->right)	//so long as trail is pointing at something and ascending the tree, n will be larger so long as it is on the right
	{
		n = trail;
		trail = trail->parent;	//could just as easily have been "trail = n->parent;"
	}
	return trail;
}

// find next smallest in tree
MovieNode* MovieTree::predecessor(MovieNode* n)
{
	if (n->left != nil)
		return maximum(n);			//if the left child exists, that is the predecessor
	MovieNode* trail = n->parent;	//trailing pointer
	while (trail != nil && n == trail->left)		//same as successor, but looking at the other side of the tree for mirrored result
	{
		n = trail;
		trail = trail->parent;	//could just as easily have been "trail = n->parent;"
	}
	return trail;
}

//global insert from root
void MovieTree::insert(MovieNode* newNode, json_object* traverseLog)
{
	MovieNode* y = nil;
	MovieNode* x = root;
	while (x != nil)
	{
	    y = x;
	    json_object* jMovie = json_object_new_string(y->title.c_str());
	    json_object_array_add(traverseLog, jMovie);
	    if(newNode->title.compare(x->title) < 0)
            x = x->left;
        else
            x = x->right;
	}
    newNode->parent = y;
	if (y == nil)
        root = newNode;
    else if (newNode->title.compare(y->title) < 0)
        y->left = newNode;
    else
        y->right = newNode;
    newNode->left = nil;
    newNode->right = nil;

    //addFixup(newNode);
    fix_violation(newNode);
}

//insert that starts in a specified sub tree. Same as above. Used pretty much only for delete and transplant f()'s
void MovieTree::insert(MovieNode* start, MovieNode* newNode, json_object* traverseLog)
{
	MovieNode* y = nil;
	MovieNode* x = start;
	while (x != nil)
	{
	    y = x;
	    json_object* jMovie = json_object_new_string(y->title.c_str());
	    json_object_array_add(traverseLog, jMovie);
	    if(newNode->title.compare(x->title) < 0)
            x = x->left;
        else
            x = x->right;
	}
    newNode->parent = y;
	if (y == nil)
        root = newNode;
    else if (newNode->title.compare(y->title) < 0)
        y->left = newNode;
    else
        y->right = newNode;
    newNode->left = nil;
    newNode->right = nil;

    //addFixup(newNode);
    fix_violation(newNode);
}

void MovieTree::fix_violation(MovieNode *&pt) {
	MovieNode *parent_pt = nullptr;
	MovieNode *grand_parent_pt = nullptr;

	while ((pt != root) && (pt->isRed) && (pt->parent->isRed))
	{

		parent_pt = pt->parent;
		grand_parent_pt = pt->parent->parent;

		/**
		* Case : A
		* Parent of pt is left child of Grand-parent of pt
		**/

		if (parent_pt == grand_parent_pt->left) {

			MovieNode *uncle_pt = grand_parent_pt->right;

			/**
			* Case : 1
			* The uncle of pt is also red
			* Only Recoloring required
			**/

			if (uncle_pt != nullptr && uncle_pt->isRed) {
				grand_parent_pt->isRed = true;
				parent_pt->isRed = false;
				uncle_pt->isRed = false;
				pt = grand_parent_pt;
			}

			else {

				/**
				* Case : 2
				* pt is right child of its parent
				* Left-rotation required
				**/

				if (pt == parent_pt->right) {
					leftRotate(parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/**
				* Case : 3
				* pt is left child of its parent
				* Right-rotation required
				**/

				rightRotate(grand_parent_pt);
				std::swap(parent_pt->isRed, grand_parent_pt->isRed);
				pt = parent_pt;
			}
		}

		/**
		* Case : B
		* Parent of pt is right child of Grand-parent of pt
		**/

		else {
			MovieNode *uncle_pt = grand_parent_pt->left;

			/**
			* Case : 1
			* The uncle of pt is also red
			* Only Recoloring required
			**/

			if ((uncle_pt != nullptr) && (uncle_pt->isRed)) {
				grand_parent_pt->isRed = true;
				parent_pt->isRed = false;
				uncle_pt->isRed = false;
				pt = grand_parent_pt;
			}

			else {

				/**
				* Case : 2
				* pt is left child of its parent
				* Right-rotation required
				**/

				if (pt == parent_pt->left) {
					rightRotate(parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				/**
				* Case : 3
				* pt is right child of its parent
				* Left-rotation required
				**/

				leftRotate(grand_parent_pt);
				std::swap(parent_pt->isRed, grand_parent_pt->isRed);
				pt = parent_pt;
			}
		}
	}

	root->isRed = false;
}

//add rebalance
void MovieTree::addFixup(MovieNode* offender)
{
    MovieNode* y = nil;
    if (offender == root)
        offender->isRed = false;
    else if (offender->parent == root)
    {
        //well done, nothing to do here.
    }
    else while (offender->isRed)
	{
		if (offender->parent == offender->parent->parent->left && offender->parent)
		{
			y = offender->parent->parent->right;
			if (y->isRed)
			{
				offender->parent->isRed = false;
				y->isRed = false;
				offender->parent->parent->isRed = true;
				offender = offender->parent->parent;
			}
			else if (offender == offender->parent->right)
			{
				offender = offender->parent;
				leftRotate(offender);
			}
			offender->parent->isRed = false;
			offender->parent->parent->isRed = true;
			rightRotate(offender);
		}
		else //(offender->parent == offender->parent->parent->right)
		{
			y = offender->parent->parent->left;
			if (y->isRed)
			{
				offender->parent->isRed = false;
				y->isRed = false;
				offender->parent->parent->isRed = true;
				offender = offender->parent->parent;
			}
			else if (offender == offender->parent->left)
			{
				offender = offender->parent;
				rightRotate(offender);
			}
			offender->parent->isRed = false;
			offender->parent->parent->isRed = true;
			leftRotate(offender);
		}
    }
}

//right rotation
void MovieTree::rightRotate(MovieNode* x)
{
    MovieNode* y = x->left;
    x->left = y->right;
    if (y->right != nil)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nil)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;

}

//left rotation
void MovieTree::leftRotate(MovieNode* x)
{
    MovieNode* y = x->right;
    x->right = y->left;
    if (y->left != nil)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nil)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;

}

//delete rebalance
void MovieTree::deleteFixup(MovieNode* x)
{
    while (x != root && !x->isRed)
    {
        if (x == x->parent->left)
        {
            MovieNode* w = x->parent->right;
            if (w->isRed)
            {
                w->isRed = false;
                x->parent->isRed = true;
                leftRotate(x->parent);
                w = x->parent;
            }
            if (!w->left->isRed && !w->right->isRed)
            {
                w->isRed = true;
                x = x->parent;
            }
            else if (!w->right->isRed)
            {
                w->left->isRed = false;
                w->isRed = true;
                rightRotate(w);
                w = x->parent->right;
            }
            w->isRed = x->parent->isRed;
            x->parent->isRed = false;
            w->right->isRed = false;
            leftRotate(x->parent);
            x = root;
        }
        else //it is the right child
        {
            MovieNode* w = x->parent->left;
            if (w->isRed)
            {
                w->isRed = false;
                x->parent->isRed = true;
                rightRotate(x->parent);
                w = x->parent;
            }
            if (!w->right->isRed && !w->left->isRed)
            {
                w->isRed = true;
                x = x->parent;
            }
            else if (!w->left->isRed)
            {
                w->right->isRed = false;
                w->isRed = true;
                leftRotate(w);
                w = x->parent->left;
            }
            w->isRed = x->parent->isRed;
            x->parent->isRed = false;
            w->left->isRed = false;
            rightRotate(x->parent);
            x = root;
        }
    }
    x->isRed = false;
}
/*
* ['5', '3', 'Inception', '3', 'Interstellar', '3', "It's a Wonderful Life", '3', 'Leon: The Professional', '3', 'Life Is Beautiful', '3', 'Memento', '5', '6', '']
*/

//lets the delete() magic happen
void MovieTree::transplant(MovieNode* u, MovieNode* v)	//swaps u with v
{
	if (u->parent == nil)	//if u was root, make v new root
		root = v;
	else if (u == u->parent->left)	//if u is smaller than it's parent
		u->parent->left = v;		//set v to the left child of parent of u. Swap them at left, really
	else
		u->parent->right = v;		//otherwise swap them at right
	v->parent = u->parent;
}

//maddening delete function
void MovieTree::delete_node(MovieNode* del_node)	//holy buttshit, Batman
{
    MovieNode* x = nil;
    MovieNode* y = del_node;
    bool originalColor = y->isRed;

	if (del_node->left == nil)					    //if there is no left child
	{
	    x = del_node->right;
		transplant(del_node, del_node->right);		//swap left to right
	}
	else if (del_node->right == nil)                //if there is no right child
	{
        x = del_node->left;
		transplant(del_node, del_node->left);		//swap right to left
	}
	else
	{
		y = minimum(del_node->right);	//make temp the smallest node on the large branch of del_node
		originalColor = y->isRed;
		x = y->right;
		if (y->parent == del_node)
            x->parent = y;
        else
        {
			transplant(y, y->right);			//swap temp and it's right branch
			y->right = del_node->right;			//set right branch to del's right branch
			y->parent->right = y;				//set temp to the right child in it's tree
		}
		transplant(del_node, y);				//now that it's always in the same form, transplant
		y->left = del_node->left;				//aquire del_nodes left branch
		y->left->parent = y;					//replace del_node as the heir to the throne
		y->isRed = del_node->isRed;
	}
	if (originalColor == FALSE)
        //deleteFixup(x);
        fix_violation(x);
}

//deletes the whole tree network made in the movietree object. Independant from ~mov() to debug and use again
void MovieTree::delete_tree(MovieNode* rt)
{
	if (rt->left != NULL || rt->left != nullptr)		//find the extrema and work backwards from there
		delete_tree(rt->left);
	if (rt->right != NULL || rt->right != nullptr)
		delete_tree(rt->right);
	delete rt;
}

json_object* MovieTree::getJsonObject()
{
    return Assignment6Output;
}
//******************
//-END MOVIE_TREE
//******************
