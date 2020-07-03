#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>


static int deltaX=20;//Please modify it when changing input size.
#define R 2
#define START (-300)
#define startY deltaY
class MainWindow:public QMainWindow
{
    Q_OBJECT
    private:
        int n;
        int *startX;
        int deltaY;
        const int lenunit=5;
        QGraphicsScene *scene;
        QGraphicsView *view;
    protected:
    void mergesort(int startRank,int step,int n);
    void merge(int startRank,int step,int n);
    void combine(int startRank,int step,int n);
    int findstart(int startRank,int endRank);
    public:
        MainWindow(int n);
        ~MainWindow(){}

};

#endif // MAINWINDOW_H
