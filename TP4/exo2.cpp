#include <time.h>
#include <stdio.h>

#include <QApplication>
#include <QDebug>

#include "tp3.h"
#include "tp4.h"
#include "tp4_exo2.h"
#include "HuffmanNode.h"

_TestMainWindow* w1 = nullptr;
using std::size_t;
using std::string;

void processCharFrequences(string data, Array& frequences);
void buildHuffmanHeap(const Array& frequences, HuffmanHeap& priorityMinHeap, int& heapSize);
HuffmanNode* makeHuffmanSubTree(HuffmanNode* rightNode, HuffmanNode* leftNode);
HuffmanNode* buildHuffmanTree(HuffmanHeap& priorityMinHeap, int heapSize);

string huffmanEncode(const string& toEncode, HuffmanNode* huffmanTree);
string huffmanDecode(const string& toDecode, const HuffmanNode& huffmanTreeRoot);


void main_function(HuffmanNode*& huffmanTree)
{
    string data = "Ouesh, bien ou bien ? Ceci est une chaine de caracteres sans grand interet";

    // this array store each caracter frequences indexed by their ascii code
    Array characterFrequences(256);
    characterFrequences.fill(0);
    // this array store each caracter code indexed by their ascii code
    string characterCodes[256];
    HuffmanHeap priorityMinHeap;
    int heapSize = 0;

    processCharFrequences(data, characterFrequences);
    displayCharacterFrequences(characterFrequences);
    buildHuffmanHeap(characterFrequences, priorityMinHeap, heapSize);
    qDebug() << priorityMinHeap.toString().toStdString().c_str();

    huffmanTree = buildHuffmanTree(priorityMinHeap, heapSize);
    huffmanTree->processCodes("");
    string encoded = huffmanEncode(data, huffmanTree);
    string decoded = huffmanDecode(encoded, *huffmanTree);

    qDebug("Encoded: %s\n", encoded.c_str());
    qDebug("Decoded: %s\n", decoded.c_str());
}


void processCharFrequences(string data, Array& frequences)
{
    frequences.fill(0);
    for(int i=0; i < data.size(); i++){
        frequences[data[i]]++;
    }
}

void HuffmanHeap::insertHeapNode(int heapSize, HuffmanNode* newNode)
{
    int i = heapSize;
    (*this)[i] = newNode;
    while(i>0 && this->get(i)->frequences > this->get((i-1)/2)->frequences){
        this->swap(i, (i-1)/2);
        i = (i-1)/2;
    }

}

void buildHuffmanHeap(const Array& frequences, HuffmanHeap& priorityMinHeap, int& heapSize)
{
    heapSize = 0;

    for(int i=0; i < frequences.size(); i++){
        if(frequences[i] != 0){
            priorityMinHeap.insertHeapNode(heapSize, new HuffmanNode(i, frequences[i]));
            heapSize++;
        }
    }

}

void HuffmanHeap::heapify(int heapSize, int nodeIndex)
{
    int i_min = nodeIndex;
    int leftChildIndex = nodeIndex*2 + 1;
    int rightChildIndex = nodeIndex*2 + 2;

    if(leftChildIndex < heapSize && this->get(nodeIndex)->frequences > this->get(leftChildIndex)->frequences){
        i_min = leftChildIndex;
    }
    if(rightChildIndex < heapSize && this->get(i_min)->frequences > this->get(rightChildIndex)->frequences){
        i_min = rightChildIndex;
    }

    if(i_min != nodeIndex){
        this->swap(nodeIndex, i_min);
        this->heapify(heapSize, i_min);
    }
}


HuffmanNode* HuffmanHeap::extractMinNode(int heapSize)
{
    this->swap(0, heapSize-1);
    this->heapify(heapSize-1, 0);
    return this->get(heapSize-1);
}

HuffmanNode* makeHuffmanSubTree(HuffmanNode* rightNode, HuffmanNode* leftNode)
{
    HuffmanNode* newNode = new HuffmanNode('\0');
    newNode->frequences = leftNode->frequences + rightNode->frequences;
    newNode->left = leftNode;
    newNode->right = rightNode;
    return newNode;
}

HuffmanNode* buildHuffmanTree(HuffmanHeap& priorityMinHeap, int heapSize)
{
    while(heapSize > 1){
        HuffmanNode* left = priorityMinHeap.extractMinNode(heapSize);
        heapSize--;

        HuffmanNode* right = priorityMinHeap.extractMinNode(heapSize);
        heapSize--;

        HuffmanNode* newNode = makeHuffmanSubTree(left, right);
        priorityMinHeap.insertHeapNode(heapSize, newNode);
        heapSize++;
    }

    return priorityMinHeap.extractMinNode(heapSize);
}

void HuffmanNode::processCodes(const std::string& baseCode)
{
    if(!this->isLeaf()){
        if(this->left){
            this->left->processCodes(baseCode + "0");
        }
        if(this->right){
            this->right->processCodes(baseCode + "1");
        }
    }else{
        this->code = baseCode;
    }
}

void HuffmanNode::fillCharactersArray(std::string charactersCodes[])
{
    /**
      * Fill the string array with all nodes codes of the tree
      * It store a node into the cell corresponding to its ascii code
      * For example: the node describing 'O' should be at index 79
     **/
    if (!this->left && !this->right)
        charactersCodes[this->character] = this->code;
    else {
        if (this->left)
            this->left->fillCharactersArray(charactersCodes);
        if (this->right)
            this->right->fillCharactersArray(charactersCodes);
    }
}

string huffmanEncode(const string& toEncode, HuffmanNode* huffmanTree)
{

    std::string charactersCodes[256]; // array of 256 huffman codes for each character
    huffmanTree->fillCharactersArray(charactersCodes);
    string encoded = "";

    for(int i=0; i < toEncode.size(); i++){
        encoded += charactersCodes[toEncode[i]];
    }

    return encoded;
}


string huffmanDecode(const string& toDecode, const HuffmanNode& huffmanTreeRoot)
{
    string decoded = "";

    const HuffmanNode* currentNode = &huffmanTreeRoot;

    for(int i = 0; i < toDecode.size(); i++){
        if(toDecode[i] == '0'){
            currentNode = currentNode->left;
        }

        if(toDecode[i] == '1'){
            currentNode = currentNode->right;
        }

        if(currentNode->isLeaf()){
            decoded += currentNode->character;
            currentNode = &huffmanTreeRoot;
        }
    }

    return decoded;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Array::wait_for_operations = false;
    w1 = new HuffmanMainWindow(main_function);
    w1->show();
    return a.exec();
}
