#include <QApplication>
#include <time.h>

#include "tp2.h"

MainWindow* w=nullptr;

void insertionSort(Array& toSort){
	Array& sorted=w->newArray(toSort.size());

    sorted[0] = toSort[0];

    int min = 0;
    for(uint i=1; i < toSort.size(); i++){
        min = i;
        for(uint j=0; j < sorted.size(); j++){
            if(sorted[j] > toSort[i]){
                min = j;
                break;
            }
        }
        sorted.insert(min, toSort[i]);
    }
	
	toSort=sorted; // update the original array
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    uint elementCount=15; // number of elements to sort
    MainWindow::instruction_duration = 100; // delay between each array access (set, get, insert, ...)
    w = new TestMainWindow(insertionSort); // window which display the behavior of the sort algorithm
	w->show();

	return a.exec();
}
