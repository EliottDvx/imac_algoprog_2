#include "tp3.h"
#include <QApplication>
#include <time.h>

MainWindow* w = nullptr;
using std::size_t;

/**
 * @brief define indexMin and indexMax as the first and the last index of toSearch
 * @param array array of int to process
 * @param toSearch value to find
 * @param indexMin first index of the value to find
 * @param indexMax last index of the value to find
 */

int binarySearchMin(Array& array, int toSearch, uint start = 0){
    int n = array.size();
    uint end = n;
    uint mid;
    int indexMin = -1;

    while(start < end){
        mid = (start+end)/2;

        if(toSearch > array[mid]){
            start = mid+1;
        }
        else if(toSearch < array[mid]){
            end = mid;
        }
        else{
            indexMin = mid;
            end = mid;
        }
    }

    return indexMin;
}

int binarySearchMax(Array& array, int toSearch, uint start = 0){
    int n = array.size();
    uint end = n;
    uint mid;
    int indexMax = -1;

    while(start < end){
        mid = (start+end)/2;

        if(toSearch > array[mid]){
            start = mid+1;
        }
        else if(toSearch < array[mid]){
            end = mid;
        }
        else{
            indexMax = mid;
            start = mid + 1;
        }
    }

    return indexMax;
}

void binarySearchAll(Array& array, int toSearch, int& indexMin, int& indexMax)
{
    indexMin = indexMax = -1;

    indexMin = binarySearchMin(array, toSearch);
    indexMax = binarySearchMax(array, toSearch, indexMin);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 500;
	w = new BinarySearchAllWindow(binarySearchAll);
	w->show();

	return a.exec();
}
