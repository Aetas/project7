#ifndef MOVIETREE_H
#define MOVIETREE_H

#include<string>
#include<json/json.h>

struct MovieNode
{
	MovieNode();
	MovieNode(int& rank, std::string& ttl, int& yr, int& qtty);
	virtual ~MovieNode();
	friend std::ostream& operator<<(std::ostream& os, MovieNode* n);

	MovieNode* parent;
	MovieNode* left;
	MovieNode* right;
    int ranking;
    std::string title;
    int year;
    int quantity;
    bool isRed;
};


class MovieTree
{
public:
	MovieTree();
	virtual ~MovieTree();

	inline void test()
	{
		delete_tree(root);
	}

	void addRawNode(int&, std::string&, int&, int&, json_object*);
	void insert(MovieNode*, json_object*);	//adds a new node
	void insert(MovieNode*, MovieNode*, json_object*);	//adds a new node to a specified sub tree
	void delete_node(MovieNode*);			//removes a node

	void inorder_walk(json_object*);					//external call to root
	MovieNode* search(std::string&, json_object*);		//finds node with the passed key
	MovieNode* iterative_search(std::string&, json_object*);	//while version of search, non-recursive
	MovieNode* minimum();					//find min (up for debate wether or not these should be private)
	MovieNode* maximum();					//find max (^*************************************************^)

	int getTreeSize();
	int getMaxHeight();

	void initJson();
	json_object* getJsonObject();
	int operations;


private:

	MovieNode* root;
	MovieNode* nil;
	json_object* Assignment6Output;

	//int nodeCount();
	int countLongestPath();
	int getTreeSize(MovieNode*);
    int rbValid(MovieNode*);
    int getMaxHeight(MovieNode*, int&, int&);

	void inorder_walk(MovieNode*, json_object*);			//internal reccursive call
	MovieNode* search(MovieNode*, std::string&, json_object*);//recursive, and sub-tree version of search
	MovieNode* minimum(MovieNode*);			//find min of specified sub-tree
	MovieNode* maximum(MovieNode*);			//find max of specified sub-node
	MovieNode* successor(MovieNode*);		//next incriment
	MovieNode* predecessor(MovieNode*);		//next smaller
	void rightRotate(MovieNode*);
	void leftRotate(MovieNode*);
	void transplant(MovieNode*, MovieNode*);//switches dangling trees on a parent
	void addFixup(MovieNode*);
	void deleteFixup(MovieNode*);
	void delete_tree(MovieNode*);			//delete whole tree. Not purely in ~MovieTree() because it was easier to debugg.

};

#endif // MOVIETREE_H
