#include <QApplication>
#include <time.h>
#include "tp2.h"

MainWindow* w=nullptr;

void merge(Array& first, Array& second, Array& result);

void splitAndMerge(Array& origin)
{
	// stop statement = condition + return (return stop the function even if it does not return anything)
    if(origin.size() == 1){
        return;
    }

	// initialisation
	Array& first = w->newArray(origin.size()/2);
	Array& second = w->newArray(origin.size()-first.size());
	
    for(uint i = 0; i < origin.size(); i++){
        if(i < first.size()){
            first[i] = origin[i];
        }
        else{
            second[i-first.size()] = origin[i];
        }
    }


    splitAndMerge(first);
    splitAndMerge(second);

    merge(first, second, origin);
}

void merge(Array& first, Array& second, Array& result)
{
    if(first[0] < second[0]){
        for(uint i = 0; i < result.size(); i++){
            if(i < first.size()){
                result[i] = first[i];
            }
            else{
                result[i] = second[i-first.size()];
            }
        }
    }
    else{
        for(uint i = 0; i < result.size(); i++){
            if(i < second.size()){
                result[i] = second[i];
            }
            else{
                result[i] = first[i-second.size()];
            }
        }
    }
}

void mergeSort(Array& toSort)
{
    splitAndMerge(toSort);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 50;
    w = new TestMainWindow(mergeSort);
	w->show();

	return a.exec();
}
