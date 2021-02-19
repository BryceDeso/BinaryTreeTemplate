#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"

BinaryTree::~BinaryTree()
{
}

void BinaryTree::insert(int value)
{
	//If the tree is empty, set the root to be a new node with the given value.

	//Create a TreeNode pointer that will act as an iterator pointing to the current node and set it to the root.
	//Create a TreeNode pointer that will act as an iterator pointing to the parent 
	//of the current node and set it to the root.

	//Loop until the the current node iterator reaches a nullptr.
		//Check if the value we want to add to the tree is less than the value at the current node.
			//Set the parent node to be the current node before the current node moves positions.
			//Change the current node to be the child to its left and continue.

		//Check if the value we want to add to the tree is greater than the value at the current node.
			//Set the parent node to be the current node before the current node moves positions.
			//Change the current node to be the child to its right and continue.

		//If the value is the same as a value already in the list return 

	//end loop

	//If the value we want to add is less than the value of the parent node, insert the value to the left.
	//Otherwise, insert the value to the right.

	if (m_root == nullptr)
	{
		m_root = new TreeNode(value);
	}

	TreeNode* currentIter = m_root;
	TreeNode* parentIter = m_root;
	TreeNode* insertNode = new TreeNode(value);

	while (currentIter != nullptr)
	{
		if (value < currentIter->getData())
		{
			parentIter = currentIter;
			currentIter->setLeft(insertNode);
		}
		else if (value > currentIter->getData())
		{
			parentIter = currentIter;
			currentIter->setRight(insertNode);
		}

		if (findNode(value, currentIter, parentIter))
		{
			return;
		}
	}
	
	if (value < parentIter->getData())
	{
		currentIter->setData(value);
		parentIter->setLeft(currentIter);
	}
	else
	{
		currentIter->setData(value);
		parentIter->setRight(currentIter);
	}
}

void BinaryTree::remove(int value)
{
	//Create two TreeNode pointers: one to hold a reference to the node we want to remove
	//and another to hold a reference to its parent.

	//Try to find the node that matches the value given and its parent in the tree.
	//If the node cannot be found return.


	//Check to see if the node has a right

		//Initialize two iterators to find the node whose data will be copied and its parent.

		//Set the first iterator to point to the right child of the node we want to remove.

		//Loop while the first iterator has a value to its left

			//Set the second iterator to be the value of the first iterator.
			//Set the first iterator to be the value to the left of it

		//end loop

		//Once the smallest value has been found, copy the data in first iterator to the node we want to remove.

		//Check if the second iterator has a left child.
			//Check if the left child stores the same data as the node we wanted to remove.
				//Set the second iterators left child to be the first iterators right child.

		//Check if the second iterator has a right child.
			//Check if the right child contains the same data as the node we want to remove.
				//Set the right child of the second iterator to be the right child of the first iterator.

		//Delete the first iterator

	//Otherwise, if the node doesn't have a right child

		//check if the parent of the node to remove has a left child.
			//Check if the data that the left child holds is the same as the data the node to remove holds.
				//Set the left child of the parent node to be the left child of the node to remove.

		//Check if the parent of the node to remove has a right child.
			//Check if the data the right child holds is the same as the data the node to remove holds.
				//Set the right child of the parent node to be the left child of the node to remove.

		//Check if the node we want to remove is the root.
			//Set the root to be its left child.

		//Delete the pointer that points to the node to remove.

	TreeNode* currentNode;
	TreeNode* parentNode;

	findNode(value, currentNode, parentNode);

	if (currentNode->hasRight())
	{
		currentNode = m_root;
		parentNode = m_root;

		currentNode = currentNode->getRight();

		while (currentNode->hasLeft())
		{
			parentNode->setData(currentNode->getData());
			currentNode->setData(currentNode->getLeft()->getData());
		}

		if (currentNode->hasLeft())
		{
			if (currentNode->getLeft()->getData() == value)
			{
				parentNode->setRight(currentNode->getLeft());
			}
		}

		if (currentNode->hasRight())
		{
			if (currentNode->getRight()->getData() == value)
			{
				parentNode->setRight(currentNode->getRight());
			}
		}

		*currentNode;
	}

	if (!currentNode->hasRight())
	{
		if (parentNode->hasLeft())
		{
			if (parentNode->getRight()->getData() == currentNode->getData())
			{
				currentNode->setLeft(parentNode->getLeft());
			}
		}

		if (parentNode->hasRight())
		{
			if (parentNode->getLeft()->getData() == currentNode->getData())
			{
				currentNode->setRight(parentNode->getLeft());
			}
		}

		if (currentNode == m_root)
		{
			currentNode->setLeft(m_root);
		}

		*currentNode;
	}
}

TreeNode* BinaryTree::find(int value)
{
	//Initialize an iterator starting at the root.

	//Loop through the tree while the iterator isn't nullptr.
		//Check if the node has the data we want
			//Return the iterator
		//If the node doesn't have the data we want, check to see if it's higher in value.
			//Set the iterator to be its current right child.
		//If the node doesn't have the data we want, check to see if it's lower in value.
			//Set the iterator to be its current left child.
	//end loop

	//Return nullptr

	TreeNode* currentIter = m_root;

	while (currentIter != nullptr)
	{
		if (currentIter->getData() == value)
		{
			return currentIter;
		}
		else if (currentIter->getData() < value)
		{
			currentIter->setRight(currentIter);
		}
		else if (currentIter->getData() > value)
		{
			currentIter->setLeft(currentIter);
		}
	}

	return nullptr;
}

void BinaryTree::draw(TreeNode* selected)
{
	draw(m_root, 400, 40, 400, selected);
}

bool BinaryTree::findNode(int searchValue, TreeNode*& nodeFound, TreeNode*& nodeParent)
{
	//Create two iterators: one that will point to the current node to compare the search value to,
	//and the other to hold a reference to the parent.

	//Loop while the current node iterator isn't nullptr/
		//Check if the search value is the same as the current nodes data.
			//Set the node found argument to be the current node and the parent node to be the parent node iterator.
			//Return true.
		//Check if the search value is greater than the value at the current node.
			//Set the parent node to be the current node.
			//Set the current node to be the child to the right of the current node.
		//Check if the search value is less than the value at the current node.
			//Set the parent node to be the current node.
			//Set the current node to be its left child.
	//end loop

	TreeNode* currentNodeIter = m_root;
	TreeNode* parentNodeIter = m_root;
	TreeNode* insertNode = new TreeNode(searchValue);
	

	while (currentNodeIter != nullptr)
	{
		if (searchValue == currentNodeIter->getData())
		{
			nodeFound = currentNodeIter;
			nodeParent = parentNodeIter;
			return true;
		}
		else if (searchValue > currentNodeIter->getData())
		{
			nodeParent = currentNodeIter;
			nodeParent->setRight(insertNode);
		}
		else if (searchValue < currentNodeIter->getData())
		{
			nodeParent = currentNodeIter;
			nodeParent->setLeft(insertNode);
		}
	}

	return false;
}

void BinaryTree::draw(TreeNode* currentNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{
	//Decrease the horizontal space as the nodes draw.
	horizontalSpacing /= 2;

	if (currentNode)
	{
		//Checks to see if the current node has a left.
		if (currentNode->hasLeft())
		{
			//Draws a line between the left child and the currrent node.
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			//Draws the left child..
			draw(currentNode->getLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}
		//Checks to see if the current node has a right.
		if (currentNode->hasRight())
		{
			//Draws a line between this child and the current node.
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);
			//Draws the right child.
			draw(currentNode->getRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}
		//Draws the current node.
		currentNode->draw(x, y, selected == currentNode);
	}
}