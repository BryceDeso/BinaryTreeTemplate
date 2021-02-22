#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"

BinaryTree::~BinaryTree()
{
}

void BinaryTree::insert(int value)
{
	//If the tree is empty, set the root to be a new node with the given value.
	if (m_root == nullptr)
	{
		m_root = new TreeNode(value);
	}

	//Create a TreeNode pointer that will act as an iterator pointing to the current node and set it to the root.
	//Create a TreeNode pointer that will act as an iterator pointing to the parent 
	//of the current node and set it to the root.
	TreeNode* currentIter = m_root;
	TreeNode* parentIter = m_root;
	TreeNode* insertNode = new TreeNode(value);

	//Loop until the the current node iterator reaches a nullptr.
	while (currentIter != nullptr)
	{
		//Check if the value we want to add to the tree is less than the value at the current node.
		if (value < currentIter->getData())
		{
			//Set the parent node to be the current node before the current node moves positions.
			//Change the current node to be the child to its left and continue.
			parentIter = currentIter;
			currentIter->setLeft(insertNode);
		}
		//Check if the value we want to add to the tree is greater than the value at the current node.
		else if (value > currentIter->getData())
		{
			//Set the parent node to be the current node before the current node moves positions.
			//Change the current node to be the child to its right and continue.
			parentIter = currentIter;
			currentIter->setRight(insertNode);
		}

		//If the value is the same as a value already in the list return 
		if (findNode(value, currentIter, parentIter))
		{
			return;
		}
		//end loop
	}
	
	//If the value we want to add is less than the value of the parent node, insert the value to the left.
	//Otherwise, insert the value to the right.
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
	TreeNode* currentNode;
	TreeNode* parentNode;

	//Try to find the node that matches the value given and its parent in the tree.
	//If the node cannot be found return.
	findNode(value, currentNode, parentNode);

	//Check to see if the node has a right
	if (currentNode->hasRight())
	{
		//Initialize two iterators to find the node whose data will be copied and its parent.
		currentNode = m_root;
		parentNode = m_root;

		//Set the first iterator to point to the right child of the node we want to remove.
		currentNode = currentNode->getRight();

		//Loop while the first iterator has a value to its left
		while (currentNode->hasLeft())
		{
			//Set the second iterator to be the value of the first iterator.
			//Set the first iterator to be the value to the left of it
			parentNode->setData(currentNode->getData());
			currentNode->setData(currentNode->getLeft()->getData());
		}
		//end loop

		//Once the smallest value has been found, copy the data in first iterator to the node we want to remove.

		//Check if the second iterator has a left child.
		if (currentNode->hasLeft())
		{
			//Check if the left child stores the same data as the node we wanted to remove.
			if (currentNode->getLeft()->getData() == value)
			{
				//Set the second iterators left child to be the first iterators right child.
				parentNode->setRight(currentNode->getLeft());
			}
		}

		//Check if the second iterator has a right child.
		if (currentNode->hasRight())
		{
			//Check if the right child contains the same data as the node we want to remove.
			if (currentNode->getRight()->getData() == value)
			{
				//Set the right child of the second iterator to be the right child of the first iterator.
				parentNode->setRight(currentNode->getRight());
			}
		}
		//Delete the first iterator
		*currentNode;
	}

	//Otherwise, if the node doesn't have a right child
	if (!currentNode->hasRight())
	{
		//check if the parent of the node to remove has a left child.
		if (parentNode->hasLeft())
		{
			//Check if the data that the left child holds is the same as the data the node to remove holds.
			if (parentNode->getRight()->getData() == currentNode->getData())
			{
				//Set the left child of the parent node to be the left child of the node to remove.
				currentNode->setLeft(parentNode->getLeft());
			}
		}

		//Check if the parent of the node to remove has a right child.
		if (parentNode->hasRight())
		{
			//Check if the data the right child holds is the same as the data the node to remove holds.
			if (parentNode->getLeft()->getData() == currentNode->getData())
			{
				//Set the right child of the parent node to be the left child of the node to remove.
				currentNode->setRight(parentNode->getLeft());
			}
		}

		//Check if the node we want to remove is the root.
		if (currentNode == m_root)
		{
			//Set the root to be its left child.
			currentNode->setLeft(m_root);
		}

		//Delete the pointer that points to the node to remove.
		*currentNode;
	}
}

TreeNode* BinaryTree::find(int value)
{
	//Initialize an iterator starting at the root.
	TreeNode* currentIter = m_root;

	//Loop through the tree while the iterator isn't nullptr.
	while (currentIter != nullptr)
	{
		//Check if the node has the data we want
		if (currentIter->getData() == value)
		{
			//Return the iterator
			return currentIter;
		}
		//If the node doesn't have the data we want, check to see if it's higher in value.
		else if (currentIter->getData() < value)
		{
			//Set the iterator to be its current right child.
			currentIter->setRight(currentIter);
		}
		//If the node doesn't have the data we want, check to see if it's lower in value.
		else if (currentIter->getData() > value)
		{
			//Set the iterator to be its current left child.
			currentIter->setLeft(currentIter);
		}
		//end loop
	}
	//Return nullptr
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
	TreeNode* currentNodeIter = m_root;
	TreeNode* parentNodeIter = m_root;
	TreeNode* insertNode = new TreeNode(searchValue);
	
	//Loop while the current node iterator isn't nullptr/
	while (currentNodeIter != nullptr)
	{
		//Check if the search value is the same as the current nodes data.
		if (searchValue == currentNodeIter->getData())
		{
			//Set the node found argument to be the current node and the parent node to be the parent node iterator.
			//Return true.
			nodeFound = currentNodeIter;
			nodeParent = parentNodeIter;
			return true;
		}
		//Check if the search value is greater than the value at the current node.
		else if (searchValue > currentNodeIter->getData())
		{
			//Set the parent node to be the current node.
			//Set the current node to be the child to the right of the current node.
			nodeParent = currentNodeIter;
			nodeParent->setRight(insertNode);
		}
		//Check if the search value is less than the value at the current node.
		else if (searchValue < currentNodeIter->getData())
		{
			//Set the parent node to be the current node.
			//Set the current node to be its left child.
			nodeParent = currentNodeIter;
			nodeParent->setLeft(insertNode);
		}
		//end loop
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
