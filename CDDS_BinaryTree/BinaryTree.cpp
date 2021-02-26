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
	TreeNode* tempNode = new TreeNode(value);

	//Loop until the the current node iterator reaches a nullptr.
	while (currentIter != nullptr)
	{
		//Check if the value we want to add to the tree is less than the value at the current node.
		if (value < currentIter->getData())
		{
			//Set the parent node to be the current node before the current node moves positions.
			//Change the current node to be the child to its left and continue.
			parentIter = currentIter;
			//If currentIter doesn't have a Left, set currentIter's left to tempNode.
			if (!currentIter->hasLeft())
			{
				currentIter->setLeft(tempNode);
			}
			currentIter = currentIter->getLeft();
		}
		//Check if the value we want to add to the tree is greater than the value at the current node.
		else if (value > currentIter->getData())
		{
			//Set the parent node to be the current node before the current node moves positions.
			//Change the current node to be the child to its right and continue.
			parentIter = currentIter;
			//If currentIter doesn't have a right, set currentIter's right to tempNode.
			if (!currentIter->hasRight())
			{
				currentIter->setRight(tempNode);
			}
			currentIter = currentIter->getRight();
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
	TreeNode* currentNode = m_root;
	TreeNode* parentNode = m_root;

	//Try to find the node that matches the value given and its parent in the tree.
	//If the node cannot be found return.
	findNode(value, currentNode, parentNode);

	//Check to see if the node has a right
	if (currentNode->hasRight())
	{
		//Initialize two iterators to find the node whose data will be copied and its parent.
		TreeNode* firstIter = currentNode;
		TreeNode* secondIter = parentNode;

		//Set the first iterator to point to the right child of the node we want to remove.
		firstIter = firstIter->getRight();

		//Loop while the first iterator has a value to its left
		while (firstIter->hasLeft())
		{
			//Set the second iterator to be the value of the first iterator.
			//Set the first iterator to be the value to the left of it
			secondIter = firstIter;
			firstIter = firstIter->getLeft();
		}
		//end loop

		//Once the smallest value has been found, copy the data in first iterator to the node we want to remove.
		currentNode->setData(firstIter->getData());

		//Check if the second iterator has a left child.
		if (secondIter->hasLeft())
		{
			//Check if the left child stores the same data as the node we wanted to remove.
			if (secondIter->getLeft()->getData() == value)
			{
				//Set the second iterators left child to be the first iterators right child.
				secondIter->setLeft(firstIter->getRight());
			}
		}

		//Check if the second iterator has a right child.
		if (secondIter->hasRight())
		{
			//Check if the right child contains the same data as the node we want to remove.
			if (secondIter->getRight()->getData() == value)
			{
				//Set the right child of the second iterator to be the right child of the first iterator.
				secondIter->setRight(firstIter->getRight());
			}
		}
		//Delete the first iterator
	}

	//Otherwise, if the node doesn't have a right child
	if (!currentNode->hasRight())
	{
		//check if the parent of the node to remove has a left child.
		if (parentNode->hasLeft())
		{
			//Check if the data that the left child holds is the same as the data the node to remove holds.
			if (parentNode->getLeft()->getData() == value)
			{
				//Set the left child of the parent node to be the left child of the node to remove.
				parentNode->setLeft(currentNode->getLeft());
			}
		}

		//Check if the parent of the node to remove has a right child.
		if (parentNode->hasRight())
		{
			//Check if the data the right child holds is the same as the data the node to remove holds.
			if (parentNode->getRight()->getData() == value)
			{
				//Set the right child of the parent node to be the left child of the node to remove.
				parentNode->setRight(currentNode->getLeft());
			}
		}

		//Check if the node we want to remove is the root.
		if (currentNode == m_root)
		{
			//Set the root to be its left child.
			currentNode->setLeft(m_root);
		}

		//Delete the pointer that points to the node to remove.
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
			currentIter = currentIter->getRight();
		}
		//If the node doesn't have the data we want, check to see if it's lower in value.
		else if (currentIter->getData() > value)
		{
			//Set the iterator to be its current left child.
			currentIter = currentIter->getLeft();
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
	TreeNode* currentNodeIter = nodeFound;
	TreeNode* parentNodeIter = nodeParent;

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
			currentNodeIter = currentNodeIter->getRight();
		}
		//Check if the search value is less than the value at the current node.
		else if (searchValue < currentNodeIter->getData())
		{
			//Set the parent node to be the current node.
			//Set the current node to be its left child.
			nodeParent = currentNodeIter;
			currentNodeIter = currentNodeIter->getLeft();
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
