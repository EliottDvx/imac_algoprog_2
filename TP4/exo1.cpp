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
    while(i>0 && (*this)[i] > (*this)[(i-1)/2]){
        swap( (*this)[i], (*this)[(i-1)/2] );
        i = (i-1)/2;
    }
}

void Heap::heapify(int heapSize, int nodeIndex)
{
	// use (*this)[i] or this->get(i) to get a value at index i
	int i_max = nodeIndex;
}

void Heap::buildHeap(Array& numbers)
{

}

void Heap::heapSort()
{

}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    MainWindow::instruction_duration = 50;
    w = new HeapWindow();
	w->show();

	return a.exec();
}
