#include <QApplication>
#include <time.h>

#include "tp2.h"

MainWindow* w = nullptr;

void selectionSort(Array& toSort){
    int min = 0;
    for(uint i=0; i < toSort.size(); i++){
        min = i;
        for(uint j=i; j < toSort.size(); j++){
            if(toSort[min] > toSort[j]){
                min = j;
            }
        }
        toSort.swap(i, min);
    }
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    uint elementCount=15; // number of elements to sort
    MainWindow::instruction_duration = 100; // delay between each array access (set, get, insert, ...)
    w = new TestMainWindow(selectionSort); // window which display the behavior of the sort algorithm
    w->show();

	return a.exec();
}
