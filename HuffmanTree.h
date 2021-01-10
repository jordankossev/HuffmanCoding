#ifndef __HUFFMAN_TREE_H
#define __HUFFMAN_TREE_H

#include <iostream>
#include <fstream>
#include <stack>
#include <string>

using PAIR = std::pair<char, size_t>;

struct HTNode {
	PAIR data;
	HTNode* left, * right;
};

class HuffmanTree {
private:
	HTNode* root;

	void deleteFrom(HTNode*);
	void saveTree(std::ofstream&, HTNode*);
	HuffmanTree* loadTree(std::ifstream&);
public:
	HuffmanTree();
	HuffmanTree(PAIR);
	HuffmanTree(PAIR, HuffmanTree&, HuffmanTree&);
	~HuffmanTree();

	char getRootChar() const;
	size_t getRootCount() const;

	void rootCountIncrement();

	HTNode* getRoot() const;
	void setRoot(HTNode*);

	void save(std::ofstream&);
	void load(std::ifstream&);
};

#endif // !__HUFFMAN_TREE_H