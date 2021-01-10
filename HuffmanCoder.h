#ifndef __HUFFMAN_CODER_H
#define __HUFFMAN_CODER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <list>
#include <fstream>
#include <stack>

#include "HuffmanTree.h"

class HuffmanCoder {
private:
	HuffmanCoder();

	void createFrequencyTableFromFile(std::list<HuffmanTree*>&, std::ifstream&);
	void createHuffmanTree(HuffmanTree*&, std::list<HuffmanTree*>&);
	void createHuffmanAlphabet(std::map<char, std::string>&, HTNode*, std::string);
	std::string encode(const std::string&, std::map<char, std::string>&);

	std::string inputFileName;
	std::string outputFileName;

public:
	HuffmanCoder(const HuffmanCoder&) = delete;
	HuffmanCoder& operator=(const HuffmanCoder&) = delete;
	
	static HuffmanCoder& get();
	void setInputFileName(const std::string&);
	void setOutputFileName(const std::string&);

	static void compress();
	static void decompress();
	static void debug();
};


#endif // !__HUFFMAN_CODER_H