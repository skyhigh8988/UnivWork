#include <iostream>
#include <fstream>
#include <queue>
#include <string>

using namespace std;

/*Node class*/
class twoThreeNode
{
	friend class twoThreeTree;

public:
	twoThreeNode();
	twoThreeNode(int);
	~twoThreeNode();

private:
	int keyLeft, keyRight, keyTemp;
	twoThreeNode *childLeft, *childMiddle, *childRight, *childTemp, *parent;
};

/*Tree class*/
class twoThreeTree
{
public:
	twoThreeTree();
	~twoThreeTree();

	void traversal();
	void readTree();
	void readQuery();

	void insert(int);
	void remove(int);
	
private:
	twoThreeNode *root;

	twoThreeNode* search(int);
	void split(twoThreeNode*);
	twoThreeNode* locate(int);
	twoThreeNode* swap(twoThreeNode*, int);
	void fix(twoThreeNode*);
};

int main (void)
{
	twoThreeTree *tree = new twoThreeTree;
	tree->readTree();
	tree->readQuery();

	return 0;
}

/*Constructor of node*/
twoThreeNode::twoThreeNode()
{
	/*Initial value*/
	keyLeft = keyLeft = keyTemp = -2147483647;
	childLeft = childMiddle = childRight = childTemp = parent = NULL;

	return;
}

/*Constructor of node with key*/
twoThreeNode::twoThreeNode(int key)
{
	/*Set key*/
	keyLeft = key;

	/*Initial other value*/
	keyRight = keyTemp = -2147483647;
	childLeft = childMiddle = childRight = childTemp = parent = NULL;

	return;
}

/*destructor of node*/
twoThreeNode::~twoThreeNode()
{
	childLeft = childMiddle = childRight = childTemp = parent = NULL;
	return;
}

/*Constructor of tree*/
twoThreeTree::twoThreeTree()
{
	/*Initial file*/
	fstream fileOutput;
	fileOutput.open("F74976120_ans.out", ios::out | ios::binary);
	fileOutput.close();

	/*Initial value*/
	root = NULL;

	return;
}

/*Read "tree.in"*/
void twoThreeTree::readTree()
{
	int key;
	
	fstream fileInput;
	fileInput.open("tree.in", ios::in | ios::binary);

	/*File dosen't eixit*/
	if (fileInput.fail()) return;

	/*Read key and insert to tree*/
	while (!fileInput.eof())
	{
		fileInput >> key;
		insert(key);
	}

	fileInput.close();
	return;
}

/*Read "Query.in"*/
void twoThreeTree::readQuery()
{
	int key;
	string operation;
	
	fstream fileInput;
	fileInput.open("query.in", ios::in | ios::binary);

	/*File dosen't eixit*/
	if (fileInput.fail()) return;
	
	while (!fileInput.eof())
	{
		/*Read operation and key*/
		fileInput >> operation;
		fileInput >> key;

		/*Do operation and output tree*/
		if (!operation.compare("insert")) insert(key);
		else if (!operation.compare("delete")) remove(key);
		traversal();
	}

	fileInput.close();
	return;
}

/*Output tree*/
void twoThreeTree::traversal()
{
	twoThreeNode *currentNode = root;

	fstream fileOutput;
	fileOutput.open("F74976120_ans.out", ios::out | ios::app | ios::binary);

	/*Check empty or not*/
	if (currentNode != NULL)
	{
		queue<twoThreeNode*> traversalQuene;
	
		while (1) {
			/*Print node to file & Push children to queue*/
			fileOutput << '(' << currentNode->keyLeft;
			if (currentNode->keyRight != -2147483647) fileOutput << ',' << currentNode->keyRight;
			fileOutput << ')';
			if (currentNode->childLeft != NULL)
			{
				traversalQuene.push(currentNode->childLeft);
				fileOutput << "-(" << currentNode->childLeft->keyLeft;
				if (currentNode->childLeft->keyRight != -2147483647) fileOutput << ',' << currentNode->childLeft->keyRight;
				fileOutput << ')';

				if (currentNode->childMiddle != NULL)
				{
					traversalQuene.push(currentNode->childMiddle);
					fileOutput << '(' << currentNode->childMiddle->keyLeft;
					if (currentNode->childMiddle->keyRight != -2147483647) fileOutput << ',' << currentNode->childMiddle->keyRight;
					fileOutput << ')';

					if (currentNode->childRight != NULL)
					{
						traversalQuene.push(currentNode->childRight);
						fileOutput << '(' << currentNode->childRight->keyLeft;
						if (currentNode->childRight->keyRight != -2147483647) fileOutput << ',' << currentNode->childRight->keyRight;
						fileOutput << ')';
					}
				}
			}
			fileOutput << '\n';

			/*Pop next node from queue*/
			if (traversalQuene.empty()) break;
			else
			{
				currentNode = traversalQuene.front();
				traversalQuene.pop();
			}
		}
	}

	fileOutput << '\n';
	fileOutput.close();

	return;
}

/*Find a leaf to insert the key*/
twoThreeNode* twoThreeTree::search(int key)
{
	/*Target is root*/
	if (root == NULL) return NULL;
	
	/*Find the acceptable node*/
	twoThreeNode *currentNode = root;
	while (1)
	{
		if (key < currentNode->keyLeft)
		{
			if (currentNode->childLeft == NULL) return currentNode;
			currentNode = currentNode->childLeft;
		}
		else if (currentNode->keyRight != -2147483647 && key > currentNode->keyRight)
		{
			if (currentNode->childRight == NULL) return currentNode;
			currentNode = currentNode->childRight;
		}
		else {
			if (currentNode->childMiddle == NULL) return currentNode;
			currentNode = currentNode->childMiddle;
		}
	}

	/*Never run here*/
	return NULL;
}

/*Find a node contain the key*/
twoThreeNode* twoThreeTree::locate(int key)
{
	/*Empty tree*/
	if (root == NULL) return NULL;
	
	/*Find the target node*/
	twoThreeNode *currentNode = root;
	while (1)
	{
		/*Find key in current node*/
		if (key == currentNode->keyLeft || key == currentNode->keyRight) return currentNode;

		/*Check if there is an acceptable child to find or key doesn't eixit*/
		else if (key < currentNode->keyLeft)
		{
			if (currentNode->childLeft == NULL) return NULL;
			currentNode = currentNode->childLeft;
		}
		else if (currentNode->keyRight != -2147483647 && key > currentNode->keyRight)
		{
			if (currentNode->childRight == NULL) return NULL;
			currentNode = currentNode->childRight;
		}
		else {
			if (currentNode->childMiddle == NULL) return NULL;
			currentNode = currentNode->childMiddle;
		}
	}

	/*Never run here*/
	return NULL;
}

/*Insert a key to the tree*/
void twoThreeTree::insert(int key)
{
	twoThreeNode *targetNode = search(key);

	/*Empty tree, creat a node for root*/
	if (targetNode == NULL) root = new twoThreeNode(key);

	/*Case:2 node*/
	else if (targetNode->keyRight == -2147483647)
	{
		/*Insert key and adjust location by bigness*/
		if (targetNode->keyLeft > key)
		{
			targetNode->keyRight = targetNode->keyLeft;
			targetNode->keyLeft = key;
		}
		else targetNode->keyRight = key;
	}

	/*Case:3 node, need split*/
	else
	{
		/*Insert key and adjust location by bigness*/
		if (targetNode->keyLeft > key)
		{
			targetNode->keyTemp = targetNode->keyRight;
			targetNode->keyRight = targetNode->keyLeft;
			targetNode->keyLeft = key;
		}
		else if (targetNode->keyRight < key)
		{
			targetNode->keyTemp = key;
		}
		else
		{
			targetNode->keyTemp = targetNode->keyRight;
			targetNode->keyRight = key;
		}

		/*Split the node*/
		split(targetNode);
	}
	
	return;
}

/*Split the node*/
void twoThreeTree::split(twoThreeNode *splitNode)
{
	twoThreeNode *parentNode, *leftNode, *rightNode;
	int minKey, midKey, maxKey;

	minKey = splitNode->keyLeft;
	midKey = splitNode->keyRight;
	maxKey = splitNode->keyTemp;

	/*Creat two node for split*/
	leftNode = new twoThreeNode(minKey);
	rightNode = new twoThreeNode(maxKey);

	/*Deal with parent node, root*/
	if (splitNode == root)
	{
		/*Creat node and set key and child*/
		parentNode = new twoThreeNode(midKey);
		parentNode->childLeft = leftNode;
		parentNode->childMiddle = rightNode;
		root = parentNode;
	}

	/*Deal with parent node, other case*/
	else
	{
		parentNode = splitNode->parent;

		/*Key should put at keyLeft*/
		if (midKey < parentNode->keyLeft)
		{
			/*Adjust and insert key*/
			parentNode->keyTemp = parentNode->keyRight;
			parentNode->keyRight = parentNode->keyLeft;
			parentNode->keyLeft = midKey;

			/*Adjust and insert child*/
			parentNode->childTemp = parentNode->childRight;
			parentNode->childRight = parentNode->childMiddle;
			parentNode->childMiddle = rightNode;
			parentNode->childLeft = leftNode;
		}

		/*Key should put at keyTemp*/
		else if (parentNode->keyRight != -2147483647 && midKey > parentNode->keyRight)
		{
			/*Adjust and insert key*/
			parentNode->keyTemp = midKey;

			/*Adjust and insert child*/
			parentNode->childTemp = rightNode;
			parentNode->childRight = leftNode;
		}

		/*Key should put at keyRight*/
		else
		{
			/*Adjust and insert key*/
			parentNode->keyTemp = parentNode->keyRight;
			parentNode->keyRight = midKey;
			
			/*Adjust and insert child*/
			parentNode->childTemp = parentNode->childRight;
			parentNode->childRight = rightNode;
			parentNode->childMiddle = leftNode;
		}
	}
	leftNode->parent = rightNode->parent = parentNode;

	/*Fix child if not a leaf*/
	if (splitNode->childLeft != NULL)
	{
		leftNode->childLeft = splitNode->childLeft;
		leftNode->childMiddle = splitNode->childMiddle;
		leftNode->childLeft->parent = leftNode->childMiddle->parent = leftNode;

		rightNode->childLeft = splitNode->childRight;
		rightNode->childMiddle = splitNode->childTemp;
		rightNode->childLeft->parent = rightNode->childMiddle->parent = rightNode;
	}

	delete splitNode;

	/*Split parent if need*/
	if (parentNode->keyTemp != -2147483647) split(parentNode);

	return;
}

/*Swap target node with a leaf*/
twoThreeNode* twoThreeTree::swap(twoThreeNode *targetNode, int key)
{
	twoThreeNode *currentNode;
	
	/*Detetmine child to find*/
	if (targetNode->keyLeft == key) currentNode = targetNode->childMiddle;
	else currentNode = targetNode->childRight;

	/*Down to leaf*/
	while (currentNode->childLeft != NULL) currentNode = currentNode->childLeft;

	/*Swap key*/
	if (targetNode->keyLeft == key) targetNode->keyLeft = currentNode->keyLeft;
	else targetNode->keyRight = currentNode->keyLeft;

	return currentNode;
}

/*Delete a key from tree*/
void twoThreeTree::remove(int key)
{
	twoThreeNode *targetNode = locate(key);

	/*Key dosen't eixit*/
	if (targetNode == NULL) return;

	/*Fix if target not a leaf, then delete key*/
	if (targetNode->childLeft != NULL)
	{
		/*Swap with acceptable leaf*/
		targetNode = swap(targetNode, key);

		targetNode->keyLeft = targetNode->keyRight;
		targetNode->keyRight = -2147483647;
	}
	else
	{
		if (targetNode->keyLeft == key) targetNode->keyLeft = targetNode->keyRight;
		targetNode->keyRight = -2147483647;
	}

	/*Fix if there is an empty node*/
	if (targetNode->keyLeft == -2147483647) fix(targetNode);

	return;
}

/*Fix the empty node*/
void twoThreeTree::fix(twoThreeNode *targetNode)
{
	twoThreeNode *parentNode;

	/*Empty tree*/
	if (targetNode == root)
	{
		if (targetNode->childLeft != NULL) root = targetNode->childLeft;
		else root = NULL;
		delete targetNode;
	}

	/*Other case*/
	else
	{
		parentNode = targetNode->parent;

		/*Case: left child*/
		if (parentNode->childLeft == targetNode)
		{
			/*Check if is able to distribute from right subling*/
			if (parentNode->childMiddle->keyRight != -2147483647)
			{
				/*Move key*/
				targetNode->keyLeft = parentNode->keyLeft;
				parentNode->keyLeft = parentNode->childMiddle->keyLeft;
				parentNode->childMiddle->keyLeft = parentNode->childMiddle->keyRight;
				parentNode->childMiddle->keyRight = -2147483647;

				/*Move child if need*/
				if (parentNode->childMiddle->childLeft != NULL)
				{
					targetNode->childMiddle = parentNode->childMiddle->childLeft;
					targetNode->childMiddle->parent = targetNode;
					parentNode->childMiddle->childLeft = parentNode->childMiddle->childMiddle;
					parentNode->childMiddle->childMiddle = parentNode->childMiddle->childRight;
					parentNode->childMiddle->childRight = NULL;
				}
				return;
			}

			/*Merge with right subling*/
			targetNode->keyLeft = parentNode->keyLeft;
			targetNode->keyRight = parentNode->childMiddle->keyLeft;
			parentNode->keyLeft = parentNode->keyRight;
			parentNode->keyRight = -2147483647;

			/*Move child if need*/
			if (parentNode->childMiddle->childLeft != NULL)
			{
				targetNode->childMiddle = parentNode->childMiddle->childLeft;
				targetNode->childMiddle->parent = targetNode;
				targetNode->childRight = parentNode->childMiddle->childMiddle;
				targetNode->childRight->parent = targetNode;
			}

			/*Adjust children*/
			delete parentNode->childMiddle;
			parentNode->childMiddle = parentNode->childRight;
			parentNode->childRight = NULL;

		}
		/*Case: middle child*/
		else if (parentNode->childMiddle == targetNode)
		{
			/*Check if is able to distribute from right subling*/
			if (parentNode->childRight != NULL && parentNode->childRight->keyRight != -2147483647)
			{
				/*Move key*/
				targetNode->keyLeft = parentNode->keyRight;
				parentNode->keyRight = parentNode->childRight->keyLeft;
				parentNode->childRight->keyLeft = parentNode->childRight->keyRight;
				parentNode->childRight->keyRight = -2147483647;

				/*Move child if need*/
				if (parentNode->childRight->childLeft != NULL)
				{
					targetNode->childMiddle = parentNode->childRight->childLeft;
					targetNode->childMiddle->parent = targetNode;
					parentNode->childRight->childLeft = parentNode->childRight->childMiddle;
					parentNode->childRight->childMiddle = parentNode->childRight->childRight;
					parentNode->childRight->childRight = NULL;
				}
				return;
			}

			/*Check if is able to distribute from left subling*/
			else if (parentNode->childLeft->keyRight != -2147483647)
			{
				/*Move key*/
				targetNode->keyLeft = parentNode->keyLeft;
				parentNode->keyLeft = parentNode->childLeft->keyRight;
				parentNode->childLeft->keyRight = -2147483647;
				
				/*Move child if need*/
				if (parentNode->childLeft->childRight != NULL)
				{
					targetNode->childRight = targetNode->childLeft;
					targetNode->childLeft = parentNode->childLeft->childRight;
					targetNode->childLeft->parent = targetNode;
					parentNode->childLeft->childRight = NULL;
				}
				return;
			}

			/*Merge with left subling*/
			parentNode->childLeft->keyRight = parentNode->keyLeft;
			parentNode->keyLeft = parentNode->keyRight;
			parentNode->keyRight = -2147483647;

			/*Move child if need*/
			if (targetNode->childLeft != NULL)
			{
				parentNode->childLeft->childRight = targetNode->childLeft;
				parentNode->childLeft->childRight->parent = parentNode->childLeft;
			}
			
			/*Adjust children*/
			delete targetNode;
			parentNode->childMiddle = parentNode->childRight;
			parentNode->childRight = NULL;
		}
		/*Case: right child*/
		else
		{
			/*Check if is able to distribute from left subling*/
			if (parentNode->childMiddle->keyRight != -2147483647)
			{
				/*Move key*/
				targetNode->keyLeft = parentNode->keyRight;
				parentNode->keyRight = parentNode->childMiddle->keyRight;
				parentNode->childMiddle->keyRight = -2147483647;
				
				/*Move child if need*/
				if (parentNode->childMiddle->childRight != NULL)
				{
					targetNode->childMiddle = targetNode->childLeft;
					targetNode->childLeft = parentNode->childMiddle->childRight;
					targetNode->childLeft->parent = targetNode;
					parentNode->childMiddle->childRight = NULL;
				}
				return;
			}

			/*Merge with left subling*/
			parentNode->childMiddle->keyRight = parentNode->keyRight;
			parentNode->keyRight = -2147483647;

			/*Move child if need*/
			if (targetNode->childLeft != NULL)
			{
				parentNode->childMiddle->childRight = targetNode->childLeft;
				parentNode->childMiddle->childRight->parent = parentNode->childMiddle;
			}

			/*Adjust children*/
			delete targetNode;
			parentNode->childRight = NULL;
		}

		/*Fix if there is an empty node*/
		if (parentNode->keyLeft == -2147483647) fix(parentNode);
	}

	return;
}