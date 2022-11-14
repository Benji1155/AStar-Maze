/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : A* Algorithm Mazr
Description : Main file which includes the A* Maze.
Author : Maxwell Presley
Mail : MaxwellPresley@mds.ac.nz
**************************************************************************/
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

//just once for text colour
HANDLE tc = GetStdHandle(STD_OUTPUT_HANDLE);

string maze[10][10] =
{
{ "A10", "B10", "C10", "D10", "E10", "F10", "G10", "H10", "I10", "J10" },
{ "A9", "B9", "C9", "D9", "E9", "F9", "G9", "H9", "I9", "J9" },
{ "A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8", "I8", "J8" },
{ "A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7", "I7", "J7" },
{ "A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6", "I6", "J6" },
{ "A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5", "I5", "J5" },
{ "A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4", "I4", "J4" },
{ "A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3", "I3", "J3" },
{ "A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2", "I2", "J2" },
{ "A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1", "I1", "J1" },
};

signed char maze_char[10][10] =
{
{254,254,254,254,254,254,254,254,254,254},
{254,79,79,79,79,79,254,254,254,254},
{254,79,254,254,254,79,79,254,254,254},
{254,79,79,254,254,79,79,254,254,254},
{254,254,254,254,254,79,79,254,254,254},
{79,79,79,79,79,79,79,79,79,254},
{254,254,254,254,254,254,79,254,254,254},
{254,254,254,254,254,254,79,254,254,254},
{254,254,254,254,79,79,79,254,254,254},
{254,254,254,254,254,254,254,254,254,254},
};

//Create new class for the double linked list
class OpenList
{
public:
	string key;
	float distance;
	// Pointer to next node in DLL
	OpenList* next;
	// Pointer to previous node in DLL
	OpenList* previous;
	string parent;

	//Contrustor
	OpenList()
	{
		key;
		distance = 0.0f;
		next = NULL;
		previous = NULL;
	}
	OpenList(string k, float d, string t)
	{
		key = k;
		distance = d;
		parent = t;
	}
};

class OpenLinkedList
{
public:
	OpenList* head;

	OpenLinkedList()
	{
		head = NULL;
	}
	OpenLinkedList(OpenList* n)
	{
		head = n;
	}

	//Check if Node Exists

	OpenList* CheckIfNodeExists(string k)
	{
		OpenList* temp = NULL;
		OpenList* ptr = head;
		//while the doesnt ptr points to a node
		while (ptr != NULL)
		{
			if (ptr->key == k)
			{
				temp = ptr;
			}
			ptr = ptr->next;
		}
		return temp;
	}

	string ReturnParent(string k)
	{
		string temp_string;
		OpenList* temp = NULL;
		OpenList* ptr = head;
		//while the doesnt ptr points to a node
		while (ptr != NULL)
		{
			if (ptr->key == k)
			{
				temp = ptr;
				temp_string = temp->parent;
			}
			ptr = ptr->next;
		}
		return temp_string;
	}

	//Append a Node
	void AppendNode(OpenList* n)
	{
		//Checks if a node exists with that key
		if (CheckIfNodeExists(n->key) != NULL)
		{
			cout << "Node Already exists :" << n->key << ". Append another node with a different key value" << endl;
		}
		//if the key doesnt exists then start creating a new node
		else
		{
			//set node as head
			if (head == NULL)
			{
				head = n;
				cout << "Node Appended as Head Node" << endl;
			}
			else
			{
				OpenList* ptr = head;
				while (ptr->next != NULL)
				{
					ptr = ptr->next;
				}
				ptr->next = n;
				n->previous = ptr;
				cout << "Node Appended" << endl;
			}
		}
	}

	//Prepend Node
	void PrependNode(OpenList* n)
	{
		if (CheckIfNodeExists(n->key) != NULL)
		{
			cout << "Node Already exists :" << n->key << ". Append another node with a different key value" << endl;
		}
		else
		{
			if (head == NULL)
			{
				head = n;
				cout << "Node Prepended as Head Node" << endl;
			}
			else
			{
				head->previous = n;
				n->next = head;

				head = n;
				cout << "Node Prepended" << endl;
			}
		}
	}

	//Insert Node after
	void InsertNodeAfter(string k, OpenList* n) {
		OpenList* ptr = CheckIfNodeExists(k);
		if (ptr == NULL) {
			cout << "No node exists with key value: " << k << endl;
		}
		else {
			if (CheckIfNodeExists(n->key) != NULL) {
				cout << "Node Already exists with key value : " << n->key << ". Append another node with different Key value" << endl;
			}
			else {
				OpenList* nextNode = ptr->next;
				// inserting at the end
				if (nextNode == NULL) {
					ptr->next = n;
					n->previous = ptr;
					cout << "Node Inserted at the END" << endl;
				}

				//inserting in between
				else {
					n->next = nextNode;
					nextNode->previous = n;
					n->previous = ptr;
					ptr->next = n;

					cout << "Node Inserted in Between" << endl;
				}
			}
		}
	}
	//Unlink a node
	void DeleteNodeByKey(string k)
	{
		OpenList* ptr = CheckIfNodeExists(k);
		if (ptr == NULL)
		{
			cout << "No Node Exists with key value: " << k << endl;
		}
		else
		{
			if (head == NULL)
			{
				cout << "Linked List already empty. Can't delete" << endl;
			}
			else if (head != NULL)
			{
				if (head->key == k)
				{
					head = head->next;
					cout << k << "Node Unlinked with key value of OpenList: " << k << endl;
				}
				else
				{
					//Deleting at end
					OpenList* NextNode = ptr->next;
					OpenList* PreviousNode = ptr->previous;

					if (NextNode == NULL)
					{
						PreviousNode->next = NULL;
						cout << k << "Node Deleted at the End of OpenList" << endl;
					}
					else
					{
						//Deleting at the between
						PreviousNode->next = NextNode;
						NextNode->previous = PreviousNode;
						cout << k << "Node Deleted in Between of OpenList" << endl;
					}
				}
			}
		}
	}

	void UpdateNodeByKey(string k, float d, int q, string na, string t)
	{
		OpenList* ptr = CheckIfNodeExists(k);
		if (ptr != NULL)
		{
			ptr->distance = d;
			ptr->parent = t;
			cout << "Node Data Updated Successfully!" << endl;
		}
		else
		{
			cout << "Node Doesn't exist with key value: " << k << endl;
		}
	}

	//Prints list of items
	void PrintList()
	{
		if (head == NULL)
		{
			cout << "No Nodes in List" << endl;
		}
		else
		{
			cout << endl << "List Printed!" << endl;
			OpenList* temp = head;

			//cycle thru each node
			while (temp != NULL)
			{
				cout << "Key: " << temp->key << endl;
				cout << "parent: " << temp->parent << endl;
				cout << "Fitness: " << temp->distance << endl;
				cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;

				temp = temp->next;
			}
			cout << endl;
		}
	}

	//Search List for smallest f rating
	string FindSmallestFitness()
	{
		float temp_float = 0.0f;
		string temp_string;
		int iteration = 1;
		if (head == NULL)
		{
			cout << "No Nodes in List" << endl;
			return "empty";
		}
		else
		{
			cout << endl << "Finding best fitness..." << endl;
			OpenList* temp = head;

			//cycle thru each node
			while (temp != NULL)
			{
				if (iteration == 1)
				{
					temp_float = temp->distance;
					temp_string = temp->key;
					iteration++;
				}
				else
				{
					if (temp_float > temp->distance)
					{
						temp_float = temp->distance;
						temp_string = temp->key;
					}
				}
				temp = temp->next;
			}
			cout << "Smallest is: " << temp_string << " with a fitness of: " << temp_float;
			cout << endl;
			return temp_string;
		}
	}
	//export the list to txt
	void ExportList(string location)
	{
		fstream myFile;
		if (head == NULL)
		{
			cout << "No Nodes in List" << endl;
		}
		else
		{
			cout << endl << "List Values: ";
			OpenList* temp = head;
			//Open the file
			myFile.open(location, ios::out); //write
			//Write the first line once
			myFile << "NAME // parent // PRICE // QUANTITY\n";
			//Cycle thru each node and print in the coccect format
			while (temp != NULL)
			{
				if (myFile.is_open())
				{
					myFile << " // " << temp->parent << " // " << temp->distance << " // " << "\n";
				}
				temp = temp->next;
			}
			cout << endl;
		}
		//close file when done
		myFile.close();
	}

	bool CheckIfNIsClosed(string k1)
	{
		bool does_exist;
		if (head == NULL)
		{
			cout << "No Nodes in List" << endl;
		}
		else
		{
			OpenList* temp = head;

			//cycle thru each node
			while (temp != NULL)
			{
				if (k1 == temp->key)
				{
					does_exist = 1;
					break;
				}
				else
				{
					does_exist = 0;
				}
				temp = temp->next;
			}
		}
		cout << does_exist;
		return does_exist;
	}
};

class ClosedList
{
public:
	string key;
	float distance;
	int quantity;
	// Pointer to next node in DLL
	ClosedList* next;
	// Pointer to previous node in DLL
	ClosedList* previous;
	string name;
	string parent;

	//Contrustor
	ClosedList()
	{
		key;
		distance = 0.0f;
		quantity = 0;
		next = NULL;
		previous = NULL;
	}
	ClosedList(string k, float d, int q, string na, string t)
	{
		key = k;
		distance = d;
		quantity = q;
		name = na;
		parent = t;
	}
};

class ClosedLinkedList
{
public:
	ClosedList* head;

	ClosedLinkedList()
	{
		head = NULL;
	}
	ClosedLinkedList(ClosedList* n)
	{
		head = n;
	}

	//Check if Node Exists

	ClosedList* CheckIfNodeExists(string k)
	{
		ClosedList* temp = NULL;
		ClosedList* ptr = head;
		//while the doesnt ptr points to a node
		while (ptr != NULL)
		{
			if (ptr->key == k)
			{
				temp = ptr;
			}
			ptr = ptr->next;
		}
		return temp;
	}

	//Append a Node
	void AppendNode(ClosedList* n)
	{
		//Checks if a node exists with that key
		if (CheckIfNodeExists(n->key) != NULL)
		{
			cout << "Node Already exists :" << n->key << ". Append another node with a different key value" << endl;
		}
		//if the key doesnt exists then start creating a new node
		else
		{
			//set node as head
			if (head == NULL)
			{
				head = n;
				cout << "Node Appended as Head Node" << endl;
			}
			else
			{
				ClosedList* ptr = head;
				while (ptr->next != NULL)
				{
					ptr = ptr->next;
				}
				ptr->next = n;
				cout << "Node Appended" << endl;
			}
		}
	}

	//Prepend Node
	void PrependNode(ClosedList* n)
	{
		if (CheckIfNodeExists(n->key) != NULL)
		{
			cout << "Node Already exists :" << n->key << ". Append another node with a different key value" << endl;
		}
		else
		{
			if (head == NULL)
			{
				head = n;
				cout << "Node Prepended as Head Node" << endl;
			}
			else
			{
				head->previous = n;
				n->next = head;

				head = n;
				cout << "Node Prepended" << endl;
			}
		}
	}

	//Unlink a node
	void DeleteNodeByKey(string k)
	{
		ClosedList* ptr = CheckIfNodeExists(k);
		if (ptr == NULL)
		{
			cout << "No Node Exists with key value: " << k << endl;
		}
		else
		{
			if (head == NULL)
			{
				cout << "Doubly Linked List already empty. Can't delete" << endl;
			}
			else if (head != NULL)
			{
				if (head->key == k)
				{
					head = head->next;
					cout << "Node Unlinked with key value: " << k << endl;
				}
				else
				{
					//Deleting at end
					ClosedList* NextNode = ptr->next;

					if (NextNode == NULL)
					{
						cout << "Node Deleted at the End" << endl;
					}
					else
					{
						//Deleting at the between
						cout << "Node Deleted in Between" << endl;
					}
				}
			}
		}
	}

	void UpdateNodeByKey(string k, float d, int q, string na, string t)
	{
		ClosedList* ptr = CheckIfNodeExists(k);
		if (ptr != NULL)
		{
			ptr->distance = d;
			cout << "Node Data Updated Successfully!" << endl;
		}
		else
		{
			cout << "Node Doesn't exist with key value: " << k << endl;
		}
	}

	//Prints list of items
	void PrintList()
	{
		if (head == NULL)
		{
			cout << "No Nodes in List" << endl;
		}
		else
		{
			cout << endl << "List Printed!" << endl;
			ClosedList* temp = head;

			//cycle thru each node
			while (temp != NULL)
			{
				cout << "Key: " << temp->key << endl;
				cout << "parent: " << temp->parent << endl;
				cout << "Fitness: " << temp->distance << endl;
				cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;

				temp = temp->next;
			}
			cout << endl;
		}
	}

	//Prints list of items
	void PrintOrder(string start_node)
	{
		int max_width = 10;
		int max_length = 10;

		string path;
		int count = 0;
		cout << "Most Optimal Path is: " << endl;
		if (head == NULL)
		{
			cout << "No Nodes in List" << endl;
		}
		else
		{
			ClosedList* temp = head;

			//cycle thru each node
			while (temp != NULL)
			{
				if (count == 0)
				{
					path = temp->parent;
					cout << temp->key << " - ";
					cout << path << "" << endl;
					for (int i = 0; i < max_width; i++) {
						for (int j = 0; j < max_length; j++) {
							if (path == maze[i][j])
							{
								maze_char[i][j] = 61;
							}
						}
					}
				}
				else
				{
					if (path == temp->key)
					{
						cout << temp->key << " - ";
						path = temp->parent;
						cout << path << endl;
						if (path != start_node)
						{
							for (int i = 0; i < max_width; i++) {
								for (int j = 0; j < max_length; j++) {
									if (path == maze[i][j])
									{
										maze_char[i][j] = 61;
									}
								}
							}
						}
					}
					else
					{
					}
				}

				count++;
				temp = temp->next;
			}
			cout << endl;
		}
	}

	bool CheckIfNIsClosed(string neighbor)
	{
		bool does_exist;
		if (head == NULL)
		{
			cout << "No Nodes in List" << endl;
		}
		else
		{
			ClosedList* temp = head;

			//cycle thru each node
			while (temp != NULL)
			{
				if (neighbor == temp->key)
				{
					does_exist = 1;
					cout << "IT EXISTSSSSSSSSSSSSSS";
					break;
				}
				else
				{
					does_exist = 0;
				}
				temp = temp->next;
			}
		}
		cout << does_exist;
		return does_exist;
	}
};

//initalising functions
void Upper();
void Lower();
bool MenuAnswer(string input);
void PrintMaze();
void SetStart();
void SetEnd();
float CalcDistance(int current_x, int current_y, string neighbor);
void SetObst();

string start_node;
string goal_node;
string current_node;

float f;

int main(OpenList* node, OpenList* head, OpenList* temp) {
	bool does_exist = 0;
	float f;
	int max_width = 10;
	int max_length = 10;
	OpenLinkedList obj_open;
	ClosedLinkedList obj_closed;
	string k1;
	string neighbor;
	int count = 1;
	string next_node;

	SetStart();
	SetEnd();
	SetObst();
	PrintMaze();

	current_node = start_node;

	count = 0;
	while (count != 1)
	{
		OpenList* n1 = new OpenList();
		n1->key = current_node;
		n1->distance = 0;
		obj_open.PrependNode(n1);
		count++;
		//obj_open.PrintList();
	}

	count = 0;
	while (count != 1)
	{
		OpenList* n2 = new OpenList();
		k1 = current_node;
		obj_open.DeleteNodeByKey(k1);
		count++;
	}

	count = 0;
	while (count != 1)
	{
		ClosedList* n2 = new ClosedList();
		n2->key = current_node;
		obj_closed.PrependNode(n2);
		count++;
	}

	while (current_node != goal_node)
	{
		obj_closed.PrintList();
		for (int i = 0; i < max_width; i++) {
			for (int j = 0; j < max_length; j++) {
				if (current_node == maze[i][j])
				{
					int current_x = i;
					int current_y = j;
					cout << "Found" << endl;

					cout << "Getting Neighbours..." << endl;

					if (current_x == 0 or current_y == 0)
					{
					}
					else
					{
						current_x--;
						current_y--;

						cout << maze[current_x][current_y] << " ";
						neighbor = maze[current_x][current_y];

						does_exist = obj_closed.CheckIfNIsClosed(neighbor);
						cout << "1 ";
						f = CalcDistance(current_x, current_y, neighbor);
						count = 0;
						if (maze_char[current_x][current_y] == 79)
						{
						}
						else
						{
							if (does_exist != 1)
							{
								while (count != 1)
								{
									if (current_x > 9 or current_y > 9)
									{
									}
									else
									{
										if (current_x < 0 or current_y < 0)
										{
										}
										else
										{
											OpenList* n1 = new OpenList();
											n1->key = neighbor;
											n1->distance = f;
											n1->parent = current_node;
											obj_open.PrependNode(n1);
										}
									}
									count++;
								}
							}
						}
						current_x++;
						current_y++;
					}

					if (current_y == 0)
					{
					}
					else
					{
						current_y--;

						cout << maze[current_x][current_y] << " ";
						neighbor = maze[current_x][current_y];

						does_exist = obj_closed.CheckIfNIsClosed(neighbor);
						cout << "2 ";
						f = CalcDistance(current_x, current_y, neighbor);
						count = 0;

						if (maze_char[current_x][current_y] == 79)
						{
						}
						else
						{
							if (does_exist != 1)
							{
								while (count != 1)
								{
									if (current_x > 9 or current_y > 9)
									{
									}
									else
									{
										if (current_x < 0 or current_y < 0)
										{
										}
										else
										{
											OpenList* n1 = new OpenList();
											n1->key = neighbor;
											n1->distance = f;
											n1->parent = current_node;
											obj_open.PrependNode(n1);
										}
									}
									count++;
								}
							}
						}
						current_y++;
					}

					if (current_y == 0 or current_x == 9)
					{
					}
					else
					{
						current_y--;
						current_x++;

						cout << maze[current_x][current_y] << " ";
						neighbor = maze[current_x][current_y];

						does_exist = obj_closed.CheckIfNIsClosed(neighbor);
						cout << "3 ";
						f = CalcDistance(current_x, current_y, neighbor);
						count = 0;
						if (maze_char[current_x][current_y] == 79)
						{
						}
						else
						{
							if (does_exist != 1)
							{
								while (count != 1)
								{
									if (current_x > 9 or current_y > 9)
									{
									}
									else
									{
										if (current_x < 0 or current_y < 0)
										{
										}
										else
										{
											OpenList* n1 = new OpenList();
											n1->key = neighbor;
											n1->distance = f;
											n1->parent = current_node;
											obj_open.PrependNode(n1);
										}
									}
									count++;
								}
							}
						}
						current_y++;
						current_x--;
					}

					//Middle Row
					if (current_x == 0)
					{
					}
					else
					{
						current_x--;
						cout << maze[current_x][current_y] << " ";
						neighbor = maze[current_x][current_y];

						does_exist = obj_closed.CheckIfNIsClosed(neighbor);
						cout << "4";
						f = CalcDistance(current_x, current_y, neighbor);
						count = 0;
						if (maze_char[current_x][current_y] == 79)
						{
						}
						else
						{
							if (does_exist != 1)
							{
								while (count != 1)
								{
									if (current_x > 9 or current_y > 9)
									{
									}
									else
									{
										if (current_x < 0 or current_y < 0)
										{
										}
										else
										{
											OpenList* n1 = new OpenList();
											n1->key = neighbor;
											n1->distance = f;
											n1->parent = current_node;
											obj_open.PrependNode(n1);
										}
									}
									count++;
								}
							}
						}
						current_x++;
					}

					cout << current_node << " ";

					if (current_x == 9)
					{
					}
					else
					{
						current_x++;

						cout << maze[current_x][current_y] << " ";
						neighbor = maze[current_x][current_y];

						does_exist = obj_closed.CheckIfNIsClosed(neighbor);
						cout << does_exist;
						cout << "5555 ";
						f = CalcDistance(current_x, current_y, neighbor);
						count = 0;
						if (maze_char[current_x][current_y] == 79)
						{
						}
						else
						{
							if (does_exist != 1)
							{
								while (count != 1)
								{
									if (current_x > 9 or current_y > 9)
									{
									}
									else
									{
										if (current_x < 0 or current_y < 0)
										{
										}
										else
										{
											OpenList* n1 = new OpenList();
											n1->key = neighbor;
											n1->distance = f;
											n1->parent = current_node;
											obj_open.PrependNode(n1);
										}
									}
									count++;
								}
							}
						}
						current_x--;
					}

					//Bottom Row
					if (current_x == 0 or current_y == 9)
					{
					}
					else
					{
						current_x--;
						current_y++;

						cout << maze[current_x][current_y] << " ";
						neighbor = maze[current_x][current_y];

						does_exist = obj_closed.CheckIfNIsClosed(neighbor);
						cout << "6 ";
						f = CalcDistance(current_x, current_y, neighbor);
						count = 0;
						if (maze_char[current_x][current_y] == 79)
						{
						}
						else
						{
							if (does_exist != 1)
							{
								while (count != 1)
								{
									if (current_x > 9 or current_y > 9)
									{
									}
									else
									{
										if (current_x < 0 or current_y < 0)
										{
										}
										else
										{
											OpenList* n1 = new OpenList();
											n1->key = neighbor;
											n1->distance = f;
											n1->parent = current_node;
											obj_open.PrependNode(n1);
										}
									}
									count++;
								}
							}
						}
						current_x++;
						current_y--;
					}

					if (current_y == 9)
					{
					}
					else
					{
						current_y++;

						cout << maze[current_x][current_y] << " ";
						neighbor = maze[current_x][current_y];

						does_exist = obj_closed.CheckIfNIsClosed(neighbor);
						cout << "7 ";
						f = CalcDistance(current_x, current_y, neighbor);
						count = 0;
						if (maze_char[current_x][current_y] == 79)
						{
						}
						else
						{
							if (does_exist != 1)
							{
								while (count != 1)
								{
									if (current_x > 9 or current_y > 9)
									{
									}
									else
									{
										if (current_x < 0 or current_y < 0)
										{
										}
										else
										{
											OpenList* n1 = new OpenList();
											n1->key = neighbor;
											n1->distance = f;
											n1->parent = current_node;
											obj_open.PrependNode(n1);
										}
									}
									count++;
								}
							}
						}
						current_y--;
					}

					if (current_y == 9 or current_x == 9)
					{
					}
					else
					{
						current_y++;
						current_x++;

						cout << maze[current_x][current_y] << " ";
						neighbor = maze[current_x][current_y];

						does_exist = obj_closed.CheckIfNIsClosed(neighbor);
						cout << "8 ";
						f = CalcDistance(current_x, current_y, neighbor);
						count = 0;
						if (maze_char[current_x][current_y] == 79)
						{
						}
						else
						{
							if (does_exist != 1)
							{
								while (count != 1)
								{
									if (current_x > 9 or current_y > 9)
									{
									}
									else
									{
										if (current_x < 0 or current_y < 0)
										{
										}
										else
										{
											OpenList* n1 = new OpenList();
											n1->key = neighbor;
											n1->distance = f;
											n1->parent = current_node;
											obj_open.PrependNode(n1);
										}
									}
									count++;
								}
							}
						}
						current_y--;
						current_x--;
					}
				}
			}
		}
		string parent;

		//system("CLS");
		obj_open.PrintList();
		k1 = goal_node;
		does_exist = obj_open.CheckIfNodeExists(k1);
		cout << does_exist;
		if (does_exist == true)
		{
			current_node = goal_node;
			cout << "Moving to " << current_node << endl;

			k1 = current_node;
			parent = obj_open.ReturnParent(k1);

			count = 0;
			while (count != 1)
			{
				ClosedList* n2 = new ClosedList();
				n2->key = current_node;
				n2->parent = parent;
				obj_closed.PrependNode(n2);
				count++;
			}
		}
		else
		{
			next_node = obj_open.FindSmallestFitness();
			if (next_node == "empty")
			{
				break;
			}
			else
			{
				current_node = next_node;
				cout << "Moving to " << current_node << endl;

				for (int i = 0; i < max_width; i++) {
					for (int j = 0; j < max_length; j++) {
						if (current_node == maze[i][j])
						{
							maze_char[i][j] = 88;
						}
					}
				}
				k1 = current_node;
				parent = obj_open.ReturnParent(k1);

				k1 = current_node;
				obj_open.DeleteNodeByKey(k1);
				count = 0;
				while (count != 1)
				{
					ClosedList* n2 = new ClosedList();
					n2->key = current_node;
					n2->parent = parent;
					obj_closed.PrependNode(n2);
					count++;
				}
				//obj_closed.PrintList();
			}
		}
	}
	if (next_node == "empty")
	{
		system("cls");
		cout << "No route possible" << endl;
	}
	else
	{
		//system("CLS");
		obj_closed.PrintOrder(start_node);
		PrintMaze();
	}
	obj_closed.PrintList();
}

bool MenuAnswer(string input) {
	if ((input.find_first_not_of("0123456789") == string::npos) == true) {//if the input is a number
		return false;
	}
	else {//if input is not a number example 1a, a1, a, 1.1 & @#*
		system("CLS");
		Sleep(300);
		Upper();
		cout << " The value " << input << " is not a valid integer. Try again. " << endl; //tells user its not a valid int
		Sleep(300);
		Lower();
		return true;
	}
}

void Upper()
{
	SetConsoleTextAttribute(tc, 2);
	for (int i = 0; i < 63; i++) {
		cout << char(205);
	}
	cout << endl;
}

void Lower()
{
	cout << endl;
	for (int i = 0; i < 63; i++) {
		cout << char(205);
	}
	SetConsoleTextAttribute(tc, 15);
	cout << endl;
}

void PrintMaze()
{
	char square = 254;
	bool is_there = false;
	cout << endl;
	//setting the max size of length and height
	const int m = 10, n = 10;
	int start_num = 11;
	for (int i = 0; i < m; i++) {
		start_num--;
		if (start_num == 10)
		{
			cout << start_num << " ";
		}
		else
		{
			cout << start_num << "  ";
		}
		for (int j = 0; j < n; j++) {
			is_there = false;
			if (maze[i][j] != start_node and maze[i][j] != goal_node)
			{
				if (maze_char[i][j] == 79)
				{
					SetConsoleTextAttribute(tc, 4);
					cout << square << " ";
					SetConsoleTextAttribute(tc, 7);
				}
				else if (maze_char[i][j] == 61)
				{
					SetConsoleTextAttribute(tc, 2);
					cout << square << " ";
					SetConsoleTextAttribute(tc, 7);
				}
				else if (maze_char[i][j] == 88)
				{
					SetConsoleTextAttribute(tc, 6);
					cout << square << " ";
					SetConsoleTextAttribute(tc, 7);
				}
				else
				{
					SetConsoleTextAttribute(tc, 7);
					cout << square << " ";
					SetConsoleTextAttribute(tc, 7);
				}
			}
			else if (maze[i][j] == start_node)
			{
				SetConsoleTextAttribute(tc, 3);
				cout << square << " ";
				SetConsoleTextAttribute(tc, 7);
			}
			else if (maze[i][j] == goal_node)
			{
				SetConsoleTextAttribute(tc, 3);
				cout << square << " ";
				SetConsoleTextAttribute(tc, 7);
			}
		}
		cout << endl;
	}
	cout << "   A B C D E F G H I J" << endl;
}

void SetStart()
{
	int m = 10;
	int n = 10;
	string start;
	bool exists = false;
	while (exists == false)
	{
		system("CLS");
		PrintMaze();
		cout << "Please select where you want to begin (example A4): ";
		cin >> start;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (start == maze[i][j])
				{
					if (maze_char[i][j] == 79)
					{
						cout << "Start Node cannot place on obstacle" << endl;
						Sleep(600);
					}
					else
					{
						cout << "Start Node placed" << endl;
						exists = true;
						Sleep(600);
					}
				}
			}
		}
	}
	start_node = start;
}

void SetEnd()
{
	int m = 10;
	int n = 10;
	string end;
	bool exists = false;
	while (exists == false)
	{
		system("CLS");
		PrintMaze();
		cout << "Please select where you want to end (example G10): ";
		cin >> end;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (end == maze[i][j])
				{
					if (maze_char[i][j] == 79)
					{
						cout << "End Node cannot place on obstacle" << endl;
						Sleep(600);
					}
					else
					{
						cout << "End Node placed" << endl;
						exists = true;
						Sleep(600);
					}
				}
			}
		}
	}
	goal_node = end;
}

void SetObst()
{
	int m = 10;
	int n = 10;
	string obst;
	bool exists = false;
	while (obst != "0" or obst != "0")
	{
		system("CLS");
		PrintMaze();
		cout << "Please select where you want your obsticles to be, enter 0 when you want to continue: ";
		cin >> obst;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (obst == maze[i][j])
				{
					if (maze_char[i][j] == 79)
					{
						cout << "Node no londer an obstacle" << endl;
						maze_char[i][j] = 254;
						Sleep(600);
					}
					else
					{
						if (obst == goal_node or obst == start_node)
						{
							cout << "Node cannot be start or end node!" << endl;
							Sleep(600);
						}
						else
						{
							maze_char[i][j] = 79;
							exists = true;
							cout << "Node set as obstacle!" << endl;
							Sleep(600);
						}
					}
				}
			}
		}
	}
}

float CalcDistance(int current_x, int current_y, string neighbor)
{
	//Calculate f for n, where f = g + h
	//Calculating h manhattan distance - |x1 - x2| + |y1 - y2| =
	int goal_x;
	int goal_y;
	int start_x;
	int start_y;

	//manhattan distacne - h
	//Euclidean distance - g
	//Firness distance - f
	float h;
	float g;

	//Temp varibles for calculations
	int temp1;
	int temp2;

	int neighbor_x;
	int neighbor_y;

	//Find the x,y coords of the goal

	int m = 10;
	int n = 10;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (goal_node == maze[i][j])
			{
				goal_x = i;
				goal_y = j;
			}
		}
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (neighbor == maze[i][j])
			{
				neighbor_x = i;
				neighbor_y = j;
			}
		}
	}

	//Find the x,y coords of the goal
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (start_node == maze[i][j])
			{
				start_x = i;
				start_y = j;
			}
		}
	}

	//If statement for y and x that sorts the x and y so that negitives dont occure
	if (goal_x < current_x)
	{
		temp1 = current_x - goal_x;
	}
	else
	{
		temp1 = goal_x - current_x;
	}

	if (goal_y < current_y)
	{
		temp2 = current_y - goal_y;
	}
	else
	{
		temp2 = goal_y - current_y;
	}

	h = temp1 + temp2;

	//If statement for y and x that sorts the x and y so that negitives dont occure
	//Distance from (current node to neibhour n) + (current g distance from start to current)

	if (start_x < current_x)
	{
		temp1 = current_x - start_x;
	}
	else
	{
		temp1 = start_x - current_x;
	}

	if (start_y < current_y)
	{
		temp2 = current_y - start_y;
	}
	else
	{
		temp2 = start_y - current_y;
	}

	//Euclidean distance formula
	temp1 = temp1 * temp1;
	temp2 = temp2 * temp2;
	temp1 = temp1 + temp2;
	g = sqrt(temp1);

	//Calculate f for n, where f = g + h
	f = g + h;
	//cout << "Fitness of " << maze[current_x][current_y] << " is: " << f << endl;
	return f;
}