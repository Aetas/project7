/*
 * Derek Prince
 * Assignment 5
 * CU - Boulder
 * CSCI 2270 - Algorithms and Datastructures - Rhonda Hoenigman
 * Binary Search Tree
*/

#include<iostream>
#include<fstream>
#include<string>
#include"MovieTree.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;



int main(int argc, char* argv[])
{
	MovieTree* database = new MovieTree();
	std::ifstream in_file;
	//if(argc >= 1)
	//	in_file.open(argv[1]);

	if (in_file.is_open())
	{
		int rating, year, quantity;
		string title, buffer;
		while (!in_file.eof())
		{
			getline(in_file, buffer, ',');
			rating = stoi(buffer);
			getline(in_file, buffer, ',');
			title = buffer;
			getline(in_file, buffer, ',');
			year = stoi(buffer);
			getline(in_file, buffer);
			quantity = stoi(buffer);
			database->addRawNode(rating, title, year, quantity);
		}
	}
	else
	{
		cout << argv[1] << "----File was not found. Check local directory for" << argv[1] << "----" << endl;
		return 0;
		//could also -> while(!in_file.is_open()) {...requent new input... open()}
	}
	in_file.close();

	int select = -1;
	MovieNode* temp = nullptr;
	while (select != 4)
	{
		string title = "";
		cout << "======Main Menu=====" << endl
			<< "1. Find a movie" << endl
			<< "2. Rent a movie" << endl
			<< "3. Print the inventory" << endl
			<< "4. Quit" << endl;
		cin >> select;
		switch (select)
		{
		case 1:	//find a movie
			cout << "Enter title:";
			cin >> title;
			temp = database->search(title);
			if (temp == NULL)
			{
				cout << "Movie not found." << endl;
				break;
			}
			cout << "Movie Info:" << endl
				<< "===========" << endl
				<< "Ranking:" << temp->ranking << endl
				<< "Title:" << temp->title << endl
				<< "Year:" << temp->year << endl
				<< "Quantity:" << temp->quantity << endl;
			break;
		case 2:	//rent a movie
			cout << "Enter title:";
			cin >> title;
			temp = database->search(title);
			if (temp == NULL)
			{
				cout << "Movie not found." << endl;
				break;
			}
			if (temp->quantity == 0)
			{
				cout << "Movie out of stock." << endl;
				break;
			}
			//database->rentMovie(title);
			temp->quantity--;
			cout << "Movie has been rented." << endl
				<< "Movie Info:" << endl
				<< "===========" << endl
				<< "Ranking:" << temp->ranking << endl
				<< "Title:" << temp->title << endl
				<< "Year:" << temp->year << endl
				<< "Quantity:" << temp->quantity << endl;
			break;
		case 3:	//print inventory
			database->inorder_walk();
			break;
		case 4:
			cout << "Goodbye!" << endl;
			break;
		default://not an option
			cout << "That was not an option" << endl;
			break;
		}
	}
	if (temp != nullptr)
		delete temp;
	delete database;
	return 0;
}
