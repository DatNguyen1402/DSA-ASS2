#ifndef INVENTORY_COMPRESSOR_H
#define INVENTORY_COMPRESSOR_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <utility>
#include "inventory.h"
#include "hash/xMap.h"
#include "heap/Heap.h"
#include "list/XArrayList.h"

// File: src/test/tc_compressor.cpp

// std::string pairToString(std::pair<char, int>& p) {
//     return "(" + std::string(1, p.first) + ", " + std::to_string(p.second) + ")";
// }


template<int treeOrder>
class HuffmanTree {
public:
    struct HuffmanNode {
        char symbol;
        int freq;
        int id;
        XArrayList<HuffmanNode*> children;

        HuffmanNode(char s, int f, int id) : symbol(s), freq(f), id(id){}; //Leaf node
        HuffmanNode(int f, const  XArrayList<HuffmanNode*>& childs, int id) : symbol(0), freq(f), id(id) {
            children = childs; //copy constructor
        }; //Internal node
    };

    HuffmanTree();
    ~HuffmanTree();

    void build(XArrayList<pair<char, int>>& symbolsFreqs);
    void generateCodes(xMap<char, std::string>& table);
    std::string decode(const std::string& huffmanCode);

    
    

private:
    HuffmanNode* root;

    //helper
    void generateCodes(xMap<char, std::string>& table, HuffmanNode* root, std::string code);
};



template<int treeOrder>
class InventoryCompressor {
public:
    InventoryCompressor(InventoryManager* manager);
    ~InventoryCompressor();

    void buildHuffman();
    void printHuffmanTable();
    std::string productToString(const List1D<InventoryAttribute>& attributes, const std::string& name);
    std::string encodeHuffman(const List1D<InventoryAttribute>& attributes, const std::string& name);
    std::string decodeHuffman(const std::string& huffmanCode, List1D<InventoryAttribute>& attributesOutput, std::string& nameOutput);

private:
    xMap<char, std::string>* huffmanTable;
    InventoryManager* invManager;
    HuffmanTree<treeOrder>* tree;
};


#endif // INVENTORY_COMPRESSOR_H

template <int treeOrder>
HuffmanTree<treeOrder>::HuffmanTree()
{
}

template <int treeOrder>
HuffmanTree<treeOrder>::~HuffmanTree()
{
    //TODO
}

template <typename NodePtr>
int minHeapComparator(NodePtr& lhs, NodePtr& rhs) {
    if (lhs->freq < rhs->freq) return -1;
    else if (lhs->freq > rhs->freq) return 1;
    else if (lhs->id < rhs->id) return -1;
    else if (lhs->id > rhs->id) return 1;
    else return 0;
}



template <int treeOrder>
void HuffmanTree<treeOrder>::build(XArrayList<pair<char, int>>& symbolsFreqs)
{
    //TODO
    Heap<HuffmanNode*> heap(&minHeapComparator);

    int L = symbolsFreqs.size();
    int idx = 0;

    
    for (int i = 0; i < symbolsFreqs.size(); i++) {
        HuffmanNode* node = new HuffmanNode(symbolsFreqs.get(i).first, symbolsFreqs.get(i).second, idx++);
        heap.push(node);
    }
    
    while ((L - 1) % (treeOrder-1) != 0)
    {
        HuffmanNode* dummyNode = new HuffmanNode('\0', 0, idx++); 
        heap.push(dummyNode);
        L++;
    }
     

    while(heap.size() > 1){
        XArrayList<HuffmanNode*> minNodes;
        int sumFreq = 0;
    
        for (int i = 0; i < treeOrder && heap.size() > 0; i++) {
            HuffmanNode* node = heap.pop();
            minNodes.add(node);
            sumFreq += node->freq;
        }
    
        HuffmanNode* parent = new HuffmanNode(sumFreq, minNodes, idx++);
        heap.push(parent);  
    }
    root = heap.pop(); 
}


template <int treeOrder>
void HuffmanTree<treeOrder>::generateCodes(xMap<char, std::string> &table, HuffmanNode* root, std::string code)
{
    //TODO
    if (root->children.empty()) {
        table.put(root->symbol, code);  
        return;
    }

    for (int i = 0; i < root->children.size(); i++) {
        HuffmanNode* child = root->children.get(i);
        generateCodes(table, child, code + std::to_string(i)); 
    }
}


template <int treeOrder>
void HuffmanTree<treeOrder>::generateCodes(xMap<char, std::string> &table){
    std::string code = "";
    generateCodes(table, root, code);
}

template <int treeOrder>
std::string HuffmanTree<treeOrder>::decode(const std::string &huffmanCode)
{
    //TODO
    std::string result = "";
    HuffmanNode* current = root;

    for (char c : huffmanCode)
    {
        int index = c - '0'; 

        if (index < 0 || index >= treeOrder)
            throw std::runtime_error("Invalid Huffman code");

        current = current->children.get(index);

        if (current->children.empty())
        {
            result += current->symbol;
            current = root; 
        }
    }

    if (current != root)
        throw std::runtime_error("Incomplete Huffman code"); 

    return result;
    
}
int defautHashFunc(char& key, int tablesize) {
    return (int)key % tablesize;
}
template <int treeOrder>
InventoryCompressor<treeOrder>::InventoryCompressor(InventoryManager *manager)
{
    //TODO
    this->invManager = manager;
    this->tree = new HuffmanTree<treeOrder>();
    this->huffmanTable = new xMap<char, std::string>(&defautHashFunc);

}

template <int treeOrder>
InventoryCompressor<treeOrder>::~InventoryCompressor()
{
    //TODO

}

template <int treeOrder>
void InventoryCompressor<treeOrder>::buildHuffman()
{
    //TODO
    int charFreq[256] = {0}; 
    XArrayList<pair<char, int>> symbolsFreqs = XArrayList<pair<char, int>>();

    for (int i = 0; i < invManager->size(); i++) {
        
        std::string attributesString = productToString(invManager->getProductAttributes(i), invManager->getProductName(i));
        // cout << "attributesString: " << attributesString << std::endl;

        for(int j = 0; j < attributesString.size(); j++){
            unsigned char c = attributesString[j];
            charFreq[c]+=1;

        }
    }

    
    for (int i = 0; i < 256; i++) {
        if (charFreq[i] > 0) { 

            symbolsFreqs.add(std::make_pair((char)i, charFreq[i]));
        }
    }

    // for (int i = 0; i < symbolsFreqs.size(); i++) {
    //     std::cout << symbolsFreqs.get(i).first << ": " << symbolsFreqs.get(i).second << std::endl;
    // }

    


    tree->build(symbolsFreqs);
    tree->generateCodes(*huffmanTable); 

    // void HuffmanTree<treeOrder>::build(XArrayList<pair<char, int>>& symbolsFreqs)


}

template <int treeOrder>
void InventoryCompressor<treeOrder>::printHuffmanTable() {
    DLinkedList<char> keys = huffmanTable->keys();
    for (char ch : keys) {
        std::cout << "'" << ch << "' : " << huffmanTable->get(ch) << std::endl;
    }
}

template <int treeOrder>
std::string InventoryCompressor<treeOrder>::productToString(const List1D<InventoryAttribute> &attributes, const std::string &name)
{
    //TODO
    std::ostringstream oss;
    oss << name << ":";
    for (int i = 0; i < attributes.size(); i++) {
        const InventoryAttribute& attr = attributes.get(i);
        oss << "(" << attr.toString() << ")";
        if (i < attributes.size() - 1) {
            oss << ", ";
        }
    }
    return oss.str();
}

template <int treeOrder>
std::string InventoryCompressor<treeOrder>::encodeHuffman(const List1D<InventoryAttribute> &attributes, const std::string &name)
{
    //TODO
    std::string defautCode = productToString(attributes, name);
    std::string huffmanCode = "";
    for (char ch : defautCode) {
        if (huffmanTable->containsKey(ch)) {
            huffmanCode += huffmanTable->get(ch);
        } else {
            throw std::runtime_error("Character not found in Huffman table");
        }
    }
    return huffmanCode;
}

template <int treeOrder>
std::string InventoryCompressor<treeOrder>::decodeHuffman(const std::string &huffmanCode, List1D<InventoryAttribute> &attributesOutput, std::string &nameOutput)
{
    //TODO
    std::string decodeString = tree->decode(huffmanCode);
    attributesOutput = List1D<InventoryAttribute>();
    std::istringstream iss(decodeString);
    std::string token;
    std::getline(iss, nameOutput, ':'); // Extract name
    while (std::getline(iss, token, ',')) {
        if (!token.empty() && token.front() == ' ') {
            token.erase(0, 2);
        }
        // Xoá dấu ')' ở cuối nếu có
        if (!token.empty() && token.back() == ')') {
            token.pop_back();
        }
    
        size_t sep = token.find(':');
        if (sep == std::string::npos) {
            std::cerr << "Invalid attribute token: " << token << std::endl;
            continue;
        }
    
        std::string attrName = token.substr(0, sep);
        std::string valueStr = token.substr(sep + 1);
    
        try {
            double attrValue = std::stod(valueStr);
            attributesOutput.add(InventoryAttribute(attrName, attrValue));
        } catch (const std::exception& e) {
            std::cerr << "Error converting value in token '" << token << "': " << e.what() << std::endl;
        }
    }
    
    return decodeString;
}
