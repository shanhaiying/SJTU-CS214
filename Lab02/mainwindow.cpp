#include "mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(int n):n(n)
{
    resize(1200,900);
    deltaY=800/(2*n);
    startX=new int [n*2+1];
    for(int i=0;i<n*2+1;i++) startX[i]=deltaX;
    scene=new QGraphicsScene(this);
    view=new QGraphicsView(scene,this);
    view->resize(1200,900);
    mergesort(1,1,n);
    int X=findstart(1,2*n);
    for(int i=1;i<=2*n;i++) scene->addLine(START,START+i*startY,START+X+lenunit,START+i*startY);
    int newX=X>600?X:600;
    resize(newX,900);
    view->resize(newX,900);
    qDebug()<<"draw finish\n";
}

int MainWindow::findstart(int startRank, int endRank){
    int X=startX[startRank];
    for(int i=startRank;i<=endRank;i++)
        if(X<startX[i]) X=startX[i];
    for(int i=startRank;i<=endRank;i++) startX[i]=X;
    return X;
}

void MainWindow::combine(int startRank,int step,int n){
    int startpoint;
    int X=findstart(startRank,startRank+(n-1)*step);
    for(int i=1;i<=n-1;i++){
        startpoint=startRank+2*i*step;
        int Y1,Y2;
        scene->addLine(START+X,Y1=START+(startpoint-step)*startY,START+X,Y2=START+startpoint*startY);
        scene->addEllipse(START+X-R,Y1-R,R*2,R*2,QPen(Qt::black),QBrush(Qt::black));
        scene->addEllipse(START+X-R,Y2-R,R*2,R*2,QPen(Qt::black),QBrush(Qt::black));
        for(int i=startpoint;i>=startpoint-step;i--) startX[i]=X+lenunit;
        qDebug()<<"combine:"<<startpoint-step<<"\t"<<startpoint<<START+X;
    }
}

void MainWindow::merge(int startRank,int step,int n){
    if(n==1) {
        int X=findstart(startRank,startRank+step);
        int Y1,Y2;
        scene->addLine(START+X,Y1=START+startY*startRank,START+X,Y2=START+startY*(startRank+step));
        scene->addEllipse(START+X-R,Y1-R,R*2,R*2,QPen(Qt::black),QBrush(Qt::black));
        scene->addEllipse(START+X-R,Y2-R,R*2,R*2,QPen(Qt::black),QBrush(Qt::black));
        qDebug()<<"merge:"<<startRank<<"\t"<<startRank+step<<START+X;
        for(int i=startRank;i<=startRank+step;i++)
            startX[i]=X+lenunit;
        return;
    }
    merge(startRank,step*2,n/2);
    merge(startRank+step,step*2,n/2);
    combine(startRank,step,n);
}

void MainWindow::mergesort(int startRank, int step, int n){//mergesort 2(s,s+step,...s+(n-1)step)
    if(n==1) {
        int X=findstart(startRank,startRank+step);
        int Y1,Y2;
        scene->addLine(START+X,Y1=START+startRank*startY,START+X,Y2=START+startY*(startRank+step));
        scene->addEllipse(START+X-R,Y1-R,R*2,R*2,QPen(Qt::black),QBrush(Qt::black));
        scene->addEllipse(START+X-R,Y2-R,R*2,R*2,QPen(Qt::black),QBrush(Qt::black));
        for(int i=startRank;i<=startRank+step;i++) startX[i]=X+lenunit;
        qDebug()<<"mergesort:"<<startRank<<"\t"<<startRank+step<<"\t"<<START+X;
        return;
    }
    mergesort(startRank,step,n/2);
    mergesort(startRank+(step*n),step,n/2);
    merge(startRank,step,n);
}
