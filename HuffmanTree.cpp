#ifndef __HUFFMAN_TREE_CPP
#define __HUFFMAN_TREE_CPP

#include "HuffmanTree.h"

void HuffmanTree::deleteFrom(HTNode* node) {
	if (node) {
		deleteFrom(node->left);
		deleteFrom(node->right);
		delete node;
	}
}

void HuffmanTree::saveTree(std::ofstream& file, HTNode* tree) {
	if (tree == nullptr) {
		file << "null" << std::endl;
		return;
	}

	saveTree(file, tree->left);
	saveTree(file, tree->right);
	file << (int)tree->data.first << " " << tree->data.second << std::endl;
}

HuffmanTree* HuffmanTree::loadTree(std::ifstream& file) {
	std::stack<HuffmanTree*> stack;
	std::string input;

	while (file >> input) {
		if (input == "null") {
			stack.push(nullptr);
		}
		else {
			char first = (char)std::stoi(input);
			file >> input;
			size_t second = std::stoi(input);
			PAIR tempPair = std::make_pair(first, second);

			HuffmanTree* right = stack.top();
			stack.top() = nullptr;
			stack.pop();
			HuffmanTree* left = stack.top();
			stack.top() = nullptr;
			stack.pop();
			stack.push(new HuffmanTree(tempPair, *left, *right));
		}
	}

	return stack.top();
}

// PUBLIC:

HuffmanTree::HuffmanTree() {
	root = nullptr;
}

HuffmanTree::HuffmanTree(PAIR pair) {
	root = new HTNode({ pair, nullptr, nullptr });
}

HuffmanTree::HuffmanTree(PAIR pair, HuffmanTree& leftTree, HuffmanTree& rightTree) {
	root = new HTNode({ pair, leftTree.getRoot(), rightTree.getRoot() });

	leftTree.setRoot(nullptr);
	rightTree.setRoot(nullptr);
}

HuffmanTree::~HuffmanTree() {
	deleteFrom(root);
}

char HuffmanTree::getRootChar() const {
	return root->data.first;
}

size_t HuffmanTree::getRootCount() const {
	return root->data.second;
}

void HuffmanTree::rootCountIncrement() {
	root->data.second++;
}

HTNode* HuffmanTree::getRoot() const {
	if (this) {
		return root;
	}

	return nullptr;
}

void HuffmanTree::setRoot(HTNode* ptr) {
	if (this) {
		root = ptr;
	}
}

void HuffmanTree::save(std::ofstream& outputFile) {
	saveTree(outputFile, root);
}

void HuffmanTree::load(std::ifstream& file) {
	root = loadTree(file)->getRoot();
	return;
}

#endif // !__HUFFMAN_TREE_CPP