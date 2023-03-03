#include <QApplication>
#include <time.h>

#include "tp2.h"


MainWindow* w=nullptr;

void recursivQuickSort(Array& toSort, int size)
{
	// stop statement = condition + return (return stop the function even if it does not return anything)
    if(size == 0){
        return;
    }
	
	Array& lowerArray = w->newArray(size);
	Array& greaterArray= w->newArray(size);
    int lowerSize = 0, greaterSize = 0; // effectives sizes

    int pivot = toSort[0];

    for(uint i = 1; i < size; i++){
        if(toSort[i] < toSort[0]){
            lowerArray[lowerSize] = toSort[i];
            lowerSize++;
        }
        else{
            greaterArray[greaterSize] = toSort[i];
            greaterSize++;
        }
    }

    recursivQuickSort(lowerArray, lowerSize);
    recursivQuickSort(greaterArray, greaterSize);

    for(uint i = 0; i < size; i++){
        if(i < lowerSize){
            toSort[i] = lowerArray[i];
        }
        else if(i == lowerSize){
            toSort[i] = pivot;
        }
        else{
            toSort[i] = greaterArray[i-lowerSize-1];
        }
    }
}

void quickSort(Array& toSort){
	recursivQuickSort(toSort, toSort.size());
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	uint elementCount=20;
	MainWindow::instruction_duration = 50;
    w = new TestMainWindow(quickSort);
	w->show();

	return a.exec();
}
