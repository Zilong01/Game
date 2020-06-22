#include "minesdiffset.h"
#include "ui_minesdiffset.h"
#include<QHBoxLayout>
#include<QLabel>
#include<QDebug>
MinesDiffSet::MinesDiffSet(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MinesDiffSet)
{
    ui->setupUi(this);

    this->setFixedSize(230,300);

    //////////////////////////提示信息////////////////
    QLabel *tips=new QLabel("选择您喜欢的难度哟~",this);
    //放大字体
    QFont ft;
    ft.setPointSize(10);
    ft.setWeight(QFont::Black);
    tips->setFont(ft);

    //设置字体颜色
    QPalette pa;
    tips->resize(200,30);
    //居中
    tips->move((this->width()-tips->width())*0.5,0);
    tips->show();



    ///////////////////主要部件////////////////////
    colChooseWidget=new NumWidget(this);
    rowChooseWidget=new NumWidget(this);
    minesChooseWidget=new NumWidget(this);


    /////移动
    QLabel* colL=new QLabel("列数",this);
    colL->resize(30,colChooseWidget->height()+tips->height());
    QLabel* rowL=new QLabel("行数",this);
    rowL->resize(30,colChooseWidget->height()+tips->height());
    QLabel* minesL=new QLabel("雷数",this);
    minesL->resize(30,colChooseWidget->height()+tips->height());

    colL->move(0,0);
    colChooseWidget->move(colL->width(),0+tips->height());
    colChooseWidget->setMinNum(9);
    colChooseWidget->setMaxNum(30);

    rowL->move(0,colL->height());
    rowChooseWidget->move(colL->width(),colL->height()+tips->height());
    rowChooseWidget->setMinNum(9);
    rowChooseWidget->setMaxNum(16);

    minesL->move(0,colL->height()*2);
    minesChooseWidget->move(colL->width(),colL->height()*2+tips->height());
    minesChooseWidget->setMinNum(10);
    minesChooseWidget->setMaxNum(99);

    btn_q=new QPushButton("确定",this);
    btn_q->move(this->width()-btn_q->width()-10,this->height()-btn_q->height()-5);

    //更改值
    connect(rowChooseWidget,&NumWidget::getNumChange,this,[=](int num){
        this->URow=num;
        emit setRow(URow);
    });

    connect(colChooseWidget,&NumWidget::getNumChange,this,[=](int num){
        this->UCol=num;
        emit setCol(UCol);
    });
    connect(minesChooseWidget,&NumWidget::getNumChange,this,[=](int num){
        this->UMines=num;
        emit setMines(UMines);
        //emit test();
    });


//    connect(btn_q,&QPushButton::clicked,[=](){
//        //emit this->setNum(UCol,URow,UMines);

//        this->hide();
//        qDebug()<<UCol<<URow<<UMines;

//        //this->deleteLater();
//    });


}

MinesDiffSet::~MinesDiffSet()
{
    delete ui;
}

