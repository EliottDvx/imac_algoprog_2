#include "tp1.h"
#include <QApplication>
#include <time.h>

int isMandelbrot(Point z, int n, Point point){
    // recursiv Mandelbrot
    // check n
    if(n == 0){
        return 0;
    }
    // check length of z
    float module = sqrt(z.x * z.x + z.y * z.y);

    // if Mandelbrot, return 1 or n (check the difference)
    if(module > 2){
        return n;
    }else{
        // otherwise, process the square of z and recall
        // isMandebrot
        z.x = (z.x * z.x - z.y * z.y) + point.x;
        z.y = (2 * z.x * z.y) + point.y;

        return isMandelbrot(z, n-1, point);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MandelbrotWindow(isMandelbrot);
    w->show();

    a.exec();
}



