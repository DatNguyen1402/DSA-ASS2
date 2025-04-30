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
    if (root->children.size() == 0) {
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
    return std::string();
}

template <int treeOrder>
InventoryCompressor<treeOrder>::InventoryCompressor(InventoryManager *manager)
{
    //TODO
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
    return std::string();
}

template <int treeOrder>
std::string InventoryCompressor<treeOrder>::encodeHuffman(const List1D<InventoryAttribute> &attributes, const std::string &name)
{
    //TODO
    return std::string();
}

template <int treeOrder>
std::string InventoryCompressor<treeOrder>::decodeHuffman(const std::string &huffmanCode, List1D<InventoryAttribute> &attributesOutput, std::string &nameOutput)
{
    //TODO
    return std::string();
}
