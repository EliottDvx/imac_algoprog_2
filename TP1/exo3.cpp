#include "tp1.h"
#include <QApplication>
#include <time.h>

#define return_and_display(result) return _.store(result);


int search(int value, Array& toSort, int size)
{
    Context _("search", value, size); // do not care about this, it allow the display of call stack

    size--;

    if(size < 0){
        return_and_display(-1);
    }

    if(toSort[size] != value){
        return_and_display(search(value, toSort, size));
    }

    return_and_display(size);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  // create a window manager
    MainWindow::instruction_duration = 400;  // make a pause between instruction display
    MainWindow* w = new SearchWindow(search); // create a window for this exercice
    w->show(); // show exercice

    return a.exec(); // main loop while window is opened
}




