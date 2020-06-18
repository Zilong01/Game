#include "choosegamescene.h"
#include "ui_choosegamescene.h"
#include<QPainter>
#include<QDebug>
#include<QLabel>
#include<QTimer>
#include<QSound>
ChooseGameScene::ChooseGameScene(QWidget *parent) :
    MyWindow(parent)//,
   // ui(new Ui::ChooseGameScene)
{

    setBackGroundPic(":/first/picture/beiJing3.jpg");
    //ui->setupUi(this);
    //connect(ui->quitAction,&QAction::triggered,[=](){close();});
    MyWindow::setWindow(this);

    this->setWindowTitle(QString("选择你要玩的游戏"));


    //选择游戏按钮
            //通过修改num值增加游戏项目
    const int num=3;
    MyPushButton * btn_chooseGame[num];
    QString name[num]={"贪吃蛇","俄罗斯方块","还没想好"};
    QLabel *gameName[num];
    for(int i=0;i<num;i++){ //创建按钮的边框图片   并以QLabel形式 在其上显示游戏名称
        btn_chooseGame[i]=new MyPushButton(":/first/picture/game1.png");
        btn_chooseGame[i]->reSizeBtn(400,80);
        btn_chooseGame[i]->setParent(this);
        btn_chooseGame[i]->move(0.5*(this->width()-btn_chooseGame[i]->width()),370+50*i);
     //下面是游戏名称的显示
        gameName[i]=new QLabel(name[i],this);
        gameName[i]->setFixedSize(btn_chooseGame[i]->width(),btn_chooseGame[i]->height());
        gameName[i]->move(0.5*(this->width()-btn_chooseGame[i]->width()),370+50*i);//移动到相同位置
//        //设置label上的文字对齐方式均居中
        gameName[i]->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        //放大字体
        QFont ft;
        ft.setPointSize(20);
        ft.setWeight(QFont::Black);
        gameName[i]->setFont(ft);

        //设置字体颜色
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::white);
        gameName[i]->setPalette(pa);

        //设置鼠标穿透
        gameName[i]->setAttribute(Qt::WA_TransparentForMouseEvents);//51号

    }

    connect(btn_chooseGame[0],&QPushButton::clicked,[=](){
        gameSnake=new SnakeScene(this);
        btn_chooseGame[0]->btnShow();//动画
        btn_chooseGame[0]->btnMusic(":/first/music/Click.wav");
        //设置游戏场景的初始位置
        gameSnake->setGeometry(this->geometry());
       // QTimer::singleShot(600,this,[=](){
            this->hide();
            gameSnake->show();

        //});

        //背景音乐->改在了场景中 方便控制

        //监听返回选择游戏界面的信号
        connect(gameSnake,&SnakeScene::backChooseScene,[=](){
            //playSound->stop();
            //playSound->deleteLater();
            this->setGeometry(gameSnake->geometry());
            //gameSnake->close();
    //////delete崩溃 应改用deleteLater() 在所有事件处理好之后再清除内存
            //delete gameSnake;
            gameSnake->deleteLater();
            gameSnake=nullptr;
            this->show();
        });
    });

    //俄罗斯方块
    connect(btn_chooseGame[1],&QPushButton::clicked,[=](){
        gameTetris=new TetrisScene(this);
        btn_chooseGame[1]->btnShow();//动画
        btn_chooseGame[1]->btnMusic(":/first/music/Click.wav");
        //设置游戏场景的初始位置
        gameTetris->setGeometry(this->geometry());
       // QTimer::singleShot(600,this,[=](){
            this->hide();
            gameTetris->show();
        //});

        //监听返回选择游戏界面的信号
        connect(gameTetris,&TetrisScene::backChooseScene,[=](){
           this->setGeometry(gameTetris->geometry());
           gameTetris->deleteLater();
            gameTetris=nullptr;
            this->show();
            qDebug()<<"连接";
        });
    });




}

ChooseGameScene::~ChooseGameScene()
{
    //delete ui;
}

void ChooseGameScene::paintEvent(QPaintEvent *e)
{
    MyWindow::paintEvent(e);
    QPainter painter(this);

    //绘制应用图标于窗口内
    QPixmap pix2;
    pix2.load(":/first/picture/appPix.png");
    painter.drawPixmap(0,this->height()*0.20,pix2.width()*0.3,pix2.height()*0.3,pix2);
}


