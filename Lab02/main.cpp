#include <QApplication>
#include "mainwindow.h"
int main(int argc,char **argv){
    QApplication app(argc,argv);
    MainWindow window(64);
    window.show();
    return app.exec();
}
