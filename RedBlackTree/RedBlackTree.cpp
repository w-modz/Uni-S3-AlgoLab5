#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <list>
#include <algorithm>
#include <sstream>

// TODO: 
// Test insert() for crashing in edgecases
// Benchmark insert()

template<typename T>
struct Node
{
	T data;
	Node* parent;
	Node* left;
	Node* right;
	bool is_black;

	Node(const T& data, Node* parent, Node* left, Node* right, bool is_black)
		: data(data), parent(parent), left(left), right(right), is_black(is_black)
	{}

	Node(const T& data)
		: data(data), parent(nullptr), left(nullptr), right(nullptr), is_black(true)
	{}

	~Node()
	{
		if (parent != nullptr)
		{
			parent = nullptr;
		}
		if (left != nullptr)
		{
			delete left;
			left = nullptr;
		}
		if (right != nullptr)
		{
			delete right;
			right = nullptr;
		}
	}
};

template<typename T>
class RedBlackTree
{
private:
	uint32_t size;
	Node<T>* root;
public:
	RedBlackTree() noexcept
		: root(nullptr), size(0)
	{}

	~RedBlackTree()
	{
		clear();
	}

	uint32_t getSize() const noexcept
	{
		return size;
	}

	Node<T>* getRoot() const noexcept
	{
		return root;
	}
	template <typename Comp>
	void insert(T new_data, Comp greater)
	{
		// No root edgecase
		if (root == nullptr)
		{
			root = new Node<T>(new_data);
			root->is_black = true;
			size++;
			return;
		}
		else
		{
			Node<T>* new_node = new Node<T>(new_data);
			bool inserted = false;
			Node<T>* previous_node = nullptr;
			Node<T>* current_node = root;
			bool is_less;
			// while() loop for binary search insertion
			while (!inserted)
			{
				if (current_node == nullptr)
				{
					new_node->parent = previous_node;
					if (is_less)
					{
						previous_node->left = new_node;
					}
					else
					{
						previous_node->right = new_node;
					}
					inserted = true;
				}
				else if (!greater(new_node->data,current_node->data) && !greater(current_node->data, new_node->data)) return;
				else if (greater(current_node->data, new_node->data))
				{
					previous_node = current_node;
					current_node = current_node->left;
					is_less = true;
				}
				else if (greater(new_node->data,current_node->data))
				{
					previous_node = current_node;
					current_node = current_node->right;
					is_less = false;
				}
			}
			new_node->is_black = false;
			// Check for violation of RedBlackTree properties after insertion
			if (new_node->parent->is_black)
			{
				size++;
				return;
			}
			else
			{
				validate(new_node);
			}
		}
		size++;
	}

	// Function for fixing violations of RedBlackTree properties after an insertion operation
	void validate(Node<T>* new_node)
	{
		// Calling of function implies new_node is red
		if (new_node->parent->is_black)
		{
			return;
		}

		if (!isUncleBlack(new_node))
		{
			// Recoloring and moving violation upward in the tree
			recolor(new_node);
			if (getGrandparent(new_node) != nullptr)
			{
				if (!getGrandparent(new_node)->is_black && !getGrandparent(new_node)->parent->is_black)
				{
					validate(getGrandparent(new_node));
				}
			}
		}
		else
		{
			int rotation;
			if (new_node->parent == getGrandparent(new_node)->left && new_node == new_node->parent->left)
			{
				rotation = 1;
			}
			else if (new_node->parent == getGrandparent(new_node)->left && new_node == new_node->parent->right)
			{
				rotation = 2;
			}
			else if (new_node->parent == getGrandparent(new_node)->right && new_node == new_node->parent->right)
			{
				rotation = 3;
			}
			// no need to check for 4th case; assume RL
			else
			{
				rotation = 4;
			}

			switch (rotation)
			{
			case 1:
				leftLeftRotation(getGrandparent(new_node), new_node->parent);
				break;
			case 2:
				leftRightRotation(getGrandparent(new_node), new_node->parent, new_node);
				break;
			case 3:
				rightRightRotation(getGrandparent(new_node), new_node->parent);
				break;
			case 4:
				rightLeftRotation(getGrandparent(new_node), new_node->parent, new_node);
				break;
			default:
				break;
			}
		}
		// Making sure the proprery two is preserved after validation
		root->is_black = true;
	}
	// Function for recoloring tree if current_node and its parent are red
	void recolor(Node<T>* current_node)
	{
		if (current_node == root || getGrandparent(current_node) == nullptr)
		{
			return;
		}
		current_node->parent->is_black = true;
		getUncle(current_node)->is_black = true;
		if (getGrandparent(current_node) != root)
		{
			getGrandparent(current_node)->is_black = false;
		}
	}
	// Function to avoid out-of-scope errors and simplify validation algorithm
	Node<T>* getUncle(Node<T>* current_node)
	{
		if (!current_node->parent)
		{
			return nullptr;
		}
		else if (!getGrandparent(current_node))
		{
			return nullptr;
		}
		if (current_node->parent == getGrandparent(current_node)->left)
		{
			if (!getGrandparent(current_node)->right)
			{
				return nullptr;
			}
			return getGrandparent(current_node)->right;
		}
		else
		{
			if (!getGrandparent(current_node)->left)
			{
				return nullptr;
			}
			return getGrandparent(current_node)->left;
		}
	}

	void leftLeftRotation(Node<T>* current_parent, Node<T>* lchild)
	{
		rotateRight(current_parent, lchild);
		bool temp = current_parent->is_black;
		if (current_parent != root)
		{
			current_parent->is_black = lchild->is_black;
		}
		if (lchild != root)
		{
			lchild->is_black = temp;
		}
	}

	void leftRightRotation(Node<T>* current_parent, Node<T>* lchild, Node<T>* x)
	{
		rotateLeft(lchild,x);
		leftLeftRotation(current_parent,x);
	}

	void rightRightRotation(Node<T>* current_parent, Node<T>* rchild)
	{
		rotateLeft(current_parent, rchild);
		bool temp = current_parent->is_black;

		if (current_parent != root)
		{
			current_parent->is_black = rchild->is_black;
		}
		if (rchild != root)
		{
			rchild->is_black = temp;
		}
	}

	void rightLeftRotation(Node<T>* current_parent, Node<T>* rchild, Node<T>* x)
	{
		rotateRight(rchild,x);
		rightRightRotation(current_parent,x);
	}

	Node<T>* getGrandparent(Node<T>* current_node)
	{
		if (!current_node->parent)
		{
			return nullptr;
		}
		else if (!current_node->parent->parent)
		{
			return nullptr;
		}
		else
		{
			return current_node->parent->parent;
		}
	}
	bool isUncleBlack(Node<T>* current_node)
	{
		if (getUncle(current_node) == nullptr)
		{
			return true;
		}
		return getUncle(current_node)->is_black;
	}
	void rotateLeft(Node<T>* current_parent, Node<T>* rchild)
	{
		Node <T>* temp = rchild->left;
		if (current_parent == root)
		{
			root = rchild;
			rchild->parent = nullptr;
		}
		else
		{
			if (current_parent->parent->left == current_parent)
			{
				current_parent->parent->left = rchild;
				rchild->parent = current_parent->parent;
			}
			else
			{
				current_parent->parent->right = rchild;
				rchild->parent = current_parent->parent;
			}
		}
		current_parent->parent = rchild;
		rchild->left = current_parent;
		current_parent->right = temp;
		if (temp != nullptr)
		{
			temp->parent = current_parent;
		}
	}

	void rotateRight(Node<T>* current_parent, Node<T>* lchild)
	{
		Node<T>* temp = lchild->right;
		if (current_parent == root)
		{
			root = lchild;
			lchild->parent = nullptr;
		}
		else
		{
			if (current_parent->parent->left == current_parent)
			{
				current_parent->parent->left = lchild;
				lchild->parent = current_parent->parent;
			}
			else
			{
				current_parent->parent->right = lchild;
				lchild->parent = current_parent->parent;
			}
		}
		current_parent->parent = lchild;
		lchild->right = current_parent;
		current_parent->left = temp;
		if (temp != nullptr)
		{
			temp->parent = current_parent;
		}
	}

	// Function that visits the root, traverses the left subtree, then the right 
	void preorder(Node<T>* root, std::list<T>* list)
	{
		if (root == nullptr)
		{
			return;
		}
		list->push_back(root->data);
		preorder(root->left, list);
		preorder(root->right, list);
	}
	// Function that traverses the left subtree, visits the root and traverses the right subtree
	void inorder(Node<T>* root, std::list<T>* list)
	{
		if (root == nullptr)
		{
			return;
		}
		inorder(root->left, list);
		list->push_back(root->data);
		inorder(root->right, list);
	}

	std::string printTraversal(std::string str)
	{
		std::ostringstream output_stream;
		std::list<int>* list = new std::list<int>;
		if (str == "preorder")
		{
			preorder(root, list);
		}
		else if (str == "inorder")
		{
			inorder(root, list);
		}
		else
		{
			throw std::invalid_argument("invalid function argument");
		}

		for (std::list<int>::iterator i = list->begin(); i != list->end(); ++i)
		{
			output_stream << *i << " ";
		}
		output_stream << "\n";
		return output_stream.str();
	}
	// Function that return the height of the given Node's subtree
	uint32_t findHeight(Node<T>* root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		uint32_t left_height = findHeight(root->left);
		uint32_t right_height = findHeight(root->right);
		return std::max(left_height, right_height) + 1;
	}

	std::string toString(Node<T>* root)
	{
		std::ostringstream output_stream;
		output_stream << "---RBT Structure---\nNotation: (data,color,parent data)\n";
		int height = findHeight(root);
		if (height > 5)
		{
			output_stream << "(Only the top 5 levels of the tree have been shown)\n";
			height = 5;
		}
		for (int i = 1; i <= height; i++)
		{
			output_stream << "Level " << i << ": ";
			output_stream << getLevel(root, i);
			output_stream << "\n";
		}
		return output_stream.str();
	}
	// Returns the ith level of rbt as string
	std::string getLevel(Node<T>* root, int level)
	{
		std::ostringstream output_stream;
		if (root == nullptr)
		{
			return "( )";
		}
		if (level == 1)
		{
			if (root->parent != nullptr)
			{
				if (root->is_black)
				{
					output_stream << "(" << root->data << ",B," << root->parent->data << ")";
				}
				else
				{
					output_stream << "(" << root->data << ",R," << root->parent->data << ")";
				}
			}
			else
			{
				if (root->is_black)
				{
					output_stream << "(" << root->data << "," << "B," << "NULL" << ")";
				}
				else
				{
					output_stream << "(" << root->data << "," << "R," << "NULL" << ")";
				}
			}
		}
		else if (level > 1)
		{
			output_stream << getLevel(root->left, level - 1);
			output_stream << getLevel(root->right, level - 1);
		}
		return output_stream.str();
	}
	template <typename Comp>
	Node<T>* getNode(T element,Comp greater)
	{
		Node<T>* current_node = root;
		while (true)
		{
			if (current_node == nullptr)
			{
				return nullptr;
			}
			else if (!greater(current_node->data, element) && !greater(element,current_node->data))
			{
				return current_node;
			}
			else if (greater(current_node->data, element))
			{
				current_node = current_node->left;
			}
			else
			{
				current_node = current_node->right;
			}
		}
	}

	// Function that looks for the smallest value in the right subtree of a given Node
	Node<T>* inorderSuccessor(Node<T>* root)
	{
		if (root == nullptr || root->right == nullptr)
		{
			return nullptr;
		}
		Node<T>* current_node = root->right;
		while (current_node->left != nullptr)
		{
			current_node = current_node->left;
		}
		return current_node;
	}

	T getMinNodeData()
	{
		if (root == nullptr)
		{
			return NULL;
		}
		Node<T>* current_node = root;
		while (current_node->left != nullptr)
		{
			current_node = current_node->left;
		}
		return current_node->data;
	}

	void clear()
	{
		// clear() function makes use of the Node's recursive deconstructors
		delete root;
		size = 0;
		root = nullptr;
	}
};
template<typename T>
bool greater(const T data1, const T data2)
{
	return data1 > data2;
}

#include <map>
#include <vector>
#include <numeric>
#include <algorithm>
void test()
{
	std::vector<int> v(8);
	std::iota(v.begin(), v.end(), 0);
	std::map<int, int> heights, root_data;
	do
	{
		RedBlackTree<int> t;
		for (int i : v)
			t.insert(i, greater<int>);
		++heights[t.findHeight(t.getRoot())];
		++root_data[t.getRoot()->data];
	} while (std::next_permutation(v.begin(), v.end()));
	for (auto [height, cnt] : heights)
		std::cout << height << ": " << cnt << std::endl;
	std::cout << "***" << std::endl;
	for (auto [data, cnt] : root_data)
		std::cout << data << ": " << cnt << std::endl;
}

int main()
{
	RedBlackTree<int>* tree = new RedBlackTree<int>;
	tree->insert(8, greater<int>);
	tree->insert(18, greater<int>);
	tree->insert(5, greater<int>);
	tree->insert(15, greater<int>);
	tree->insert(17, greater<int>);
	tree->insert(25, greater<int>);
	tree->insert(40, greater<int>);
	tree->insert(80, greater<int>);
	tree->printTraversal("inorder");
	std::cout << tree->toString(tree->getRoot());
	std::cout << tree->findHeight(tree->getRoot());
	std::cout << "\n" << tree->getSize();
	test();
}