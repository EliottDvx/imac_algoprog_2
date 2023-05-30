#include "tp4.h"
#include "mainwindow.h"

#include <QApplication>
#include <time.h>
#include <stdio.h>

MainWindow* w = nullptr;
using std::size_t;
using std::string;

int Heap::leftChildIndex(int nodeIndex)
{
    return nodeIndex*2 + 1;
}

int Heap::rightChildIndex(int nodeIndex)
{
    return nodeIndex*2 +2;
}

void Heap::insertHeapNode(int heapSize, int value)
{
	int i = heapSize;
    (*this)[i] = value;
    while(i>0 && (*this)[i] > (*this)[(i-1)/2]){
        swap(i, (i-1)/2);
        i = (i-1)/2;
    }
}

void Heap::heapify(int heapSize, int nodeIndex)
{
    int i_max = nodeIndex;

    if(leftChildIndex(nodeIndex) < heapSize && (*this)[nodeIndex] < (*this)[leftChildIndex(nodeIndex)]){
        i_max = leftChildIndex(nodeIndex);
    }
    if(rightChildIndex(nodeIndex) < heapSize && (*this)[i_max] < (*this)[rightChildIndex(nodeIndex)]){
        i_max = rightChildIndex(nodeIndex);
    }

    if(i_max != nodeIndex){
        swap(nodeIndex, i_max);
        heapify(heapSize, i_max);
    }
}

void Heap::buildHeap(Array& numbers)
{
    for(int i=0; i < numbers.size(); i++){
        this->insertHeapNode(i, numbers[i]);
    }
}

void Heap::heapSort()
{
    for(int i = (*this).size()-1; i > 0; i--){
        swap(0, i);
        heapify(i, 0);
    }
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    MainWindow::instruction_duration = 50;
    w = new HeapWindow();
	w->show();

	return a.exec();
}
