#ifndef __HUFFMAN_CODER_CPP
#define __HUFFMAN_CODER_CPP

#include "HuffmanCoder.h"

#include <cassert>

HuffmanCoder::HuffmanCoder() {};

HuffmanCoder& HuffmanCoder::get() {
	static HuffmanCoder instance;
	return instance;
}

void HuffmanCoder::setInputFileName(const std::string& fileName) {
	inputFileName = fileName;
}

void HuffmanCoder::setOutputFileName(const std::string& fileName) {
	outputFileName = fileName;
}

void HuffmanCoder::createFrequencyTableFromFile(std::list<HuffmanTree*>& ft, std::ifstream& inputFile) {
	char currentChar;
	inputFile.clear();
	while (inputFile.get(currentChar)) {
		std::list<HuffmanTree*>::iterator symbolIter;
		symbolIter = std::find_if(ft.begin(), ft.end(), [=](HuffmanTree* p) -> bool { return p->getRootChar() == currentChar; });

		if (symbolIter != ft.end()) {
			(*symbolIter)->rootCountIncrement();
		}
		else {
			HuffmanTree* temp = new HuffmanTree(std::make_pair(currentChar, 1));
			ft.push_back(temp);
		}
	}

	ft.sort([](HuffmanTree* p, HuffmanTree* q) -> bool { return p->getRootCount() < q->getRootCount(); });
	inputFile.clear();

	return;
}

void HuffmanCoder::createHuffmanTree(HuffmanTree*& huffmanTree, std::list<HuffmanTree*>& frequencyTable) {
	std::list<HuffmanTree*>::iterator it, prev;

	while (frequencyTable.size() > 1) {
		it = frequencyTable.begin();
		prev = it;
		HuffmanTree* left = *it;
		++it;
		HuffmanTree* right = *it;

		PAIR newData = std::make_pair('\0', left->getRootCount() + right->getRootCount());
		huffmanTree = new HuffmanTree(newData, *left, *right);
		left = nullptr;
		right = nullptr;
		frequencyTable.erase(prev);
		frequencyTable.erase(it);
		it = frequencyTable.begin();

		while (it != frequencyTable.end() && newData.second > (*it)->getRootCount()) {
			++it;
		}
		frequencyTable.insert(it, huffmanTree);
	}

	it = frequencyTable.begin();
	return;
}

void HuffmanCoder::createHuffmanAlphabet(std::map<char, std::string>& huffmanAlphabet, HTNode* huffmanTree, std::string code) {
	if (huffmanTree->data.first == '\0') {
		std::string tempCode = code;
		createHuffmanAlphabet(huffmanAlphabet, huffmanTree->left, code += '0');
		createHuffmanAlphabet(huffmanAlphabet, huffmanTree->right, tempCode += '1');
	}
	else {
		huffmanAlphabet[huffmanTree->data.first] = code;
	}
	return;
}

std::string HuffmanCoder::encode(const std::string& text, std::map<char, std::string>& huffmanAlphabet) {
	std::string encoded;

	size_t length = text.length();
	for (size_t i = 0; i < length; i++) {
		encoded += huffmanAlphabet[text[i]];
	}

	return encoded;
}

void HuffmanCoder::compress() {
	std::string inputFileName = get().inputFileName;
	std::string encodedFileName = get().outputFileName;

	std::ifstream inputFile(inputFileName, std::ios::in | std::ios::beg);
	std::ofstream outputFile(encodedFileName, std::ios::out | std::ios::beg | std::ios::trunc);
	// ASSERT
	assert(inputFile && outputFile);

	std::list<HuffmanTree*> frequencyTable;
	get().createFrequencyTableFromFile(frequencyTable, inputFile);
	inputFile.seekg(std::ios::beg);
	HuffmanTree* huffmanTree = nullptr;
	get().createHuffmanTree(huffmanTree, frequencyTable);
	std::map<char, std::string> huffmanAlphabet;
	get().createHuffmanAlphabet(huffmanAlphabet, huffmanTree->getRoot(), "");

	std::string inputLine;

	while (std::getline(inputFile, inputLine)) {
		//inputLine += '\n';
		if (!inputFile.eof()) {
			inputLine += '\n';
		}
		outputFile << get().encode(inputLine, huffmanAlphabet);
	}
	
	outputFile << std::endl << "tree:\n";
	huffmanTree->save(outputFile);
	delete huffmanTree;

	inputFile.close();
	outputFile.close();

	return;
}

void HuffmanCoder::decompress() {
	std::string inputFileName = get().inputFileName;
	std::string outputFileName = get().outputFileName;

	std::ifstream inputFile(inputFileName, std::ios::in | std::ios::beg);
	// ASSERT
	assert(inputFile);
	std::string text, inputLine;

	std::getline(inputFile, text);
	std::getline(inputFile, inputLine);

	HuffmanTree huffmanTree;
	huffmanTree.load(inputFile);

	std::ofstream outputFile(outputFileName, std::ios::out | std::ios::beg | std::ios::trunc);
	// ASSERT
	assert(outputFile);
	
	HTNode* htptr = huffmanTree.getRoot();
	size_t length = text.length();
	for (size_t i = 0; i <= length; i++) {
		if (htptr->data.first != '\0') {
			outputFile << htptr->data.first;
			htptr = huffmanTree.getRoot();
			i--;
		}
		else if (text[i] == '0') {
			htptr = htptr->left;
		}
		else {
			htptr = htptr->right;
		}
	}

	inputFile.close();
	outputFile.close();
	return;
}

void HuffmanCoder::debug() {
	std::string inputFileName = get().inputFileName;
	std::ifstream inputFile(inputFileName, std::ios::in | std::ios::beg);
	// ASSERT
	assert(inputFile);

	std::list<HuffmanTree*> frequencyTable;
	get().createFrequencyTableFromFile(frequencyTable, inputFile);
	inputFile.seekg(std::ios::beg);
	HuffmanTree* huffmanTree = nullptr;
	get().createHuffmanTree(huffmanTree, frequencyTable);
	std::map<char, std::string> huffmanAlphabet;
	get().createHuffmanAlphabet(huffmanAlphabet, huffmanTree->getRoot(), "");
	
	std::string inputLine, encodedText;

	size_t precompressionSize = 0;
	while (std::getline(inputFile, inputLine)) {
		if (!inputFile.eof()) {
			inputLine += '\n';
		}
		precompressionSize += inputLine.length();
		encodedText += get().encode(inputLine, huffmanAlphabet);
	}
	inputFile.close();
	double compressionDegree = (double)encodedText.length() / (double)(precompressionSize * 8);

	size_t length = encodedText.length(), bitBlockSize = 8;
	size_t additionalZeroes = 8 - length % 8;
	for (size_t i = 0; i < additionalZeroes; i++) {
		encodedText += '0';
		length++;
	}

	for (size_t i = 0; i < length; i++) {
		int decNumber = 0;
		for (int j = bitBlockSize - 1; j >= 0; j--) {
			decNumber += (encodedText[i] - '0') * std::pow(2, j);
			i++;
		}
		i--;
		std::cout << decNumber << " ";
	}
	std::cout << std::endl << "Compression degree: " << compressionDegree << std::endl;
	return;
}

#endif // !__HUFFMAN_CODER_CPP