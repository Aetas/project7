#ifndef MOVIETREE_H
#define MOVIETREE_H

#include<string>
#include<json-c/json.h>

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

	void addRawNode(int&, std::string&, int&, int&);
	void insert(MovieNode*);				//adds a new node
	void insert(MovieNode*, MovieNode*);	//adds a new node to a specified sub tree

	void inorder_walk();					//external call to root
	MovieNode* search(std::string&);		//finds node with the passed key
	MovieNode* iterative_search(std::string&);	//while version of search, non-recursive
	MovieNode* minimum();					//find min (up for debate wether or not these should be private)
	MovieNode* maximum();					//find max (^*************************************************^)

	void initJson();
	json_object* getJsonObject();


private:

	int operations;
	MovieNode *root;
	json_object* Assignment6Output;

	int nodeCount();

	void inorder_walk(MovieNode*);			//internal reccursive call
	MovieNode* search(MovieNode*, std::string&);//recursive, and sub-tree version of search
	MovieNode* minimum(MovieNode*);			//find min of specified sub-tree
	MovieNode* maximum(MovieNode*);			//find max of specified sub-node
	MovieNode* successor(MovieNode*);		//next incriment
	MovieNode* predecessor(MovieNode*);		//next smaller
	void transplant(MovieNode*, MovieNode*);//switches dangling trees on a parent
	void delete_node(MovieNode*);			//removes a node
	void delete_tree(MovieNode*);			//delete whole tree. Not purely in ~MovieTree() because it was easier to debugg.

};

#endif // MOVIETREE_H
