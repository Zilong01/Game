#include "infowindow.h"
#include "ui_infowindow.h"
#include<QFile>
#include<QTextStream>
#include<QDateTime>
#include<QDebug>
#include<QLabel>
#include<QMessageBox>
#include<QFileDialog>
InfoWindow::InfoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InfoWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("小游戏历史记录,点击历史记录按钮可切换游戏");
    ///读取游戏记录
    QFile MinesRecord("D:\\2020_train\\Game\\GamesCollection\\minesInformation.txt");

    if(MinesRecord.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream date(&MinesRecord);//数据流对象并与文件关联
        QGridLayout *layout=new QGridLayout();//网格布局
        for(int i=0;i<15;i++){
            QString temp=date.readLine();
            QLabel *tempLabel=new QLabel();//用label保存信息
            tempLabel->setText(temp);
            layout->addWidget(tempLabel);//把信息放入布局中
        }
        ui->scrollAreaMines->widget()->setLayout(layout);//把布局放入

    }
    else qDebug()<<"读取扫雷记录文件打开失败";


    //贪吃蛇文件记录
    QFile snakeRecord("D:\\2020_train\\Game\\GamesCollection\\snakeInformation.txt");

    if(snakeRecord.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream date(&snakeRecord);//数据流对象并与文件关联
        QGridLayout *layout=new QGridLayout();//网格布局
        for(int i=0;i<15;i++){
            QString temp=date.readLine();
            QLabel *tempLabel=new QLabel();//用label保存信息
            tempLabel->setText(temp);
            layout->addWidget(tempLabel);//把信息放入布局中
        }
        ui->scrollAreaSnake->widget()->setLayout(layout);//把布局放入
        snakeRecord.close();
    }
    else qDebug()<<"读取扫雷记录文件打开失败";

    //俄罗斯方块文件记录
    QFile tetrisRecord("D:\\2020_train\\Game\\GamesCollection\\tetrisInformation.txt");

    if(tetrisRecord.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream date(&tetrisRecord);//数据流对象并与文件关联
        QGridLayout *layout=new QGridLayout();//网格布局
        for(int i=0;i<15;i++){
            QString temp=date.readLine();
            QLabel *tempLabel=new QLabel();//用label保存信息
            tempLabel->setText(temp);
            layout->addWidget(tempLabel);//把信息放入布局中
        }
        ui->scrollAreaTetris->widget()->setLayout(layout);//把布局放入
        tetrisRecord.close();
    }
    else qDebug()<<"读取俄罗斯记录文件打开失败";

    //点击按钮可切换
    connect(ui->snakeBtn,&QPushButton::clicked,[=](){
        qDebug()<<"点击";
        ui->stackedWidget->setCurrentIndex(1);
    });

    connect(ui->tetrisBtn,&QPushButton::clicked,[=](){
        qDebug()<<"点击";
        ui->stackedWidget->setCurrentIndex(2);
    });

    connect(ui->minesBtn,&QPushButton::clicked,[=](){
        qDebug()<<"点击";
        ui->stackedWidget->setCurrentIndex(0);
    });



    QAction * saveAction = ui->meneFile->addAction("保存");
    connect(saveAction,&QAction::triggered,[=](){
        QDateTime time=QDateTime::currentDateTime();
        QString fileName=time.toString("MM dd hh mm")+"游戏数据"+".txt";
        QString filePath=QFileDialog::getExistingDirectory(this)+"\\"+fileName;
        if(!filePath.isEmpty()){
            QString tempInfo;
            QFile snakeRecord("D:\\2020_train\\Game\\GamesCollection\\snakeInformation.txt");
            if(snakeRecord.open(QIODevice::ReadOnly|QIODevice::Text)){
                QTextStream date(&snakeRecord);//数据流对象并与文件关联
                tempInfo+="贪吃蛇数据\n";
                tempInfo+=date.readAll();
                snakeRecord.close();
            }

            QFile tetrisRecord("D:\\2020_train\\Game\\GamesCollection\\tetrisInformation.txt");
            if(tetrisRecord.open(QIODevice::ReadOnly|QIODevice::Text)){
                QTextStream date(&tetrisRecord);//数据流对象并与文件关联
                tempInfo+="俄罗斯方块数据\n";
                tempInfo+=date.readAll();
                tetrisRecord.close();
            }

            QFile minesRecord("D:\\2020_train\\Game\\GamesCollection\\minesInformation.txt");
            if(minesRecord.open(QIODevice::ReadOnly|QIODevice::Text)){
                QTextStream date(&minesRecord);//数据流对象并与文件关联
                tempInfo+="俄罗斯方块数据\n";
                tempInfo+=date.readAll();
                minesRecord.close();
            }

            QFile file(filePath);
            if(file.exists()){
                QMessageBox::warning(this,"保存","文件已经存在");
            }
            else if(file.open(QIODevice::ReadWrite| QIODevice::Text)){
                QTextStream date(&file);//数据流对象并与文件关联
                QByteArray str=tempInfo.toUtf8();
                file.write(str);
                file.close();
                QMessageBox::information(this,"保存","保存成功!");
            }
            else QMessageBox::warning(this,"保存","保存失败!");
        }

    });
    QAction * deleteAction = ui->meneFile->addAction("删除");
    connect(deleteAction,&QAction::triggered,[=](){
        //弹出警告
        int choice;
        choice=QMessageBox::warning(this,"删除文件","删除后历史记录不可恢复\n删除后仍会显示 误删请及时截屏保存！",QString("我再想想"),QString("删除！"));
        if(choice==1){
            QFile snakeRecord("D:\\2020_train\\Game\\GamesCollection\\snakeInformation.txt");
            if(snakeRecord.open(QIODevice::WriteOnly|QIODevice::Truncate)){
                snakeRecord.close();
            }

            QFile tetrisRecord("D:\\2020_train\\Game\\GamesCollection\\tetrisInformation.txt");
            if(tetrisRecord.open(QIODevice::WriteOnly|QIODevice::Truncate)){
                tetrisRecord.close();
            }

            QFile minesRecord("D:\\2020_train\\Game\\GamesCollection\\minesInformation.txt");
            if(minesRecord.open(QIODevice::WriteOnly|QIODevice::Truncate)){
                minesRecord.close();
            }
        }

    });
}

InfoWindow::~InfoWindow()
{
    delete ui;
}

void InfoWindow::changePage(int page)
{
    if(page>2||page<0)
        return;
    ui->stackedWidget->setCurrentIndex(page);
}
