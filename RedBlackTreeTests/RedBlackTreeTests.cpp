#include "pch.h"
#include "CppUnitTest.h"
#include "../RedBlackTree/RedBlackTree.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RedBlackTreeTests
{
	TEST_CLASS(RedBlackTreeTests)
	{
	public:
		
		TEST_METHOD(InsertTest1)
		{
			RBT<int>* tree = new RBT<int>;
			tree->insert(8);
			Assert::IsTrue(tree->getRoot()->is_black);
			Assert::AreEqual(8, tree->getRoot()->data);
		}
		TEST_METHOD(InsertTest2)
		{
			RBT<int>* tree = new RBT<int>;
			tree->insert(8);
			tree->insert(18);
			Assert::IsTrue(tree->getRoot()->is_black);
			Assert::AreEqual(8, tree->getRoot()->data);
			Assert::IsFalse(tree->getRoot()->right->is_black);
			Assert::AreEqual(18, tree->getRoot()->right->data);
		}
		TEST_METHOD(InsertTest3)
		{
			RBT<int>* tree = new RBT<int>;
			tree->insert(8);
			tree->insert(18);
			tree->insert(5);
			Assert::IsTrue(tree->getRoot()->is_black);
			Assert::AreEqual(8, tree->getRoot()->data);
			Assert::IsFalse(tree->getRoot()->left->is_black);
			Assert::AreEqual(5, tree->getRoot()->left->data);
			Assert::IsFalse(tree->getRoot()->right->is_black);
			Assert::AreEqual(18, tree->getRoot()->right->data);
		}
		TEST_METHOD(InsertTest4)
		{
			RBT<int>* tree = new RBT<int>;
			tree->insert(8);
			tree->insert(18);
			tree->insert(5);
			tree->insert(15);
			Assert::IsTrue(tree->getRoot()->is_black);
			Assert::AreEqual(8, tree->getRoot()->data);
			Assert::IsTrue(tree->getRoot()->left->is_black);
			Assert::AreEqual(5, tree->getRoot()->left->data);
			Assert::IsTrue(tree->getRoot()->right->is_black);
			Assert::AreEqual(18, tree->getRoot()->right->data);
			Assert::IsFalse(tree->getRoot()->right->left->is_black);
			Assert::AreEqual(15, tree->getRoot()->right->left->data);
		}
		TEST_METHOD(InsertTest5)
		{
			RBT<int>* tree = new RBT<int>;
			tree->insert(8);
			tree->insert(18);
			tree->insert(5);
			tree->insert(15);
			tree->insert(17);
			Assert::IsTrue(tree->getRoot()->is_black);
			Assert::AreEqual(8, tree->getRoot()->data);

			Assert::IsTrue(tree->getRoot()->left->is_black);
			Assert::AreEqual(5, tree->getRoot()->left->data);

			Assert::IsTrue(tree->getRoot()->right->is_black);
			Assert::AreEqual(17, tree->getRoot()->right->data);

			Assert::IsFalse(tree->getRoot()->right->left->is_black);
			Assert::AreEqual(15, tree->getRoot()->right->left->data);

			Assert::IsFalse(tree->getRoot()->right->right->is_black);
			Assert::AreEqual(18, tree->getRoot()->right->right->data);
		}

		TEST_METHOD(InsertTest6)
		{
			RBT<int>* tree = new RBT<int>;
			tree->insert(8);
			tree->insert(18);
			tree->insert(5);
			tree->insert(15);
			tree->insert(17);
			tree->insert(25);
			Assert::IsTrue(tree->getRoot()->is_black);
			Assert::AreEqual(8, tree->getRoot()->data);

			Assert::IsTrue(tree->getRoot()->left->is_black);
			Assert::AreEqual(5, tree->getRoot()->left->data);

			Assert::IsFalse(tree->getRoot()->right->is_black);
			Assert::AreEqual(17, tree->getRoot()->right->data);

			Assert::IsTrue(tree->getRoot()->right->left->is_black);
			Assert::AreEqual(15, tree->getRoot()->right->left->data);

			Assert::IsTrue(tree->getRoot()->right->right->is_black);
			Assert::AreEqual(18, tree->getRoot()->right->right->data);

			Assert::IsFalse(tree->getRoot()->right->right->right->is_black);
			Assert::AreEqual(25, tree->getRoot()->right->right->right->data);
		}

		TEST_METHOD(InsertTest7)
		{
			RBT<int>* tree = new RBT<int>;
			tree->insert(8);
			tree->insert(18);
			tree->insert(5);
			tree->insert(15);
			tree->insert(17);
			tree->insert(25);
			tree->insert(40);
			Assert::IsTrue(tree->getRoot()->is_black);
			Assert::AreEqual(8, tree->getRoot()->data);

			Assert::IsTrue(tree->getRoot()->left->is_black);
			Assert::AreEqual(5, tree->getRoot()->left->data);

			Assert::IsFalse(tree->getRoot()->right->is_black);
			Assert::AreEqual(17, tree->getRoot()->right->data);

			Assert::IsTrue(tree->getRoot()->right->left->is_black);
			Assert::AreEqual(15, tree->getRoot()->right->left->data);

			Assert::IsTrue(tree->getRoot()->right->right->is_black);
			Assert::AreEqual(25, tree->getRoot()->right->right->data);

			Assert::IsFalse(tree->getRoot()->right->right->left->is_black);
			Assert::AreEqual(18, tree->getRoot()->right->right->left->data);

			Assert::IsFalse(tree->getRoot()->right->right->right->is_black);
			Assert::AreEqual(40, tree->getRoot()->right->right->right->data);
		}

		TEST_METHOD(InsertTest8)
		{
			RBT<int>* tree = new RBT<int>;
			tree->insert(8);
			tree->insert(18);
			tree->insert(5);
			tree->insert(15);
			tree->insert(17);
			tree->insert(25);
			tree->insert(40);
			tree->insert(80);
			Assert::IsTrue(tree->getRoot()->is_black);
			Assert::AreEqual(17, tree->getRoot()->data);

			Assert::IsFalse(tree->getRoot()->left->is_black);
			Assert::AreEqual(8, tree->getRoot()->left->data);

			Assert::IsTrue(tree->getRoot()->left->left->is_black);
			Assert::AreEqual(5, tree->getRoot()->left->left->data);

			Assert::IsTrue(tree->getRoot()->left->right->is_black);
			Assert::AreEqual(15, tree->getRoot()->left->right->data);

			Assert::IsFalse(tree->getRoot()->right->is_black);
			Assert::AreEqual(25, tree->getRoot()->right->data);

			Assert::IsTrue(tree->getRoot()->right->left->is_black);
			Assert::AreEqual(18, tree->getRoot()->right->left->data);

			Assert::IsTrue(tree->getRoot()->right->right->is_black);
			Assert::AreEqual(40, tree->getRoot()->right->right->data);

			Assert::IsFalse(tree->getRoot()->right->right->right->is_black);
			Assert::AreEqual(80, tree->getRoot()->right->right->right->data);
		}
	};
}
