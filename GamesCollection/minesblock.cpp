#include "minesblock.h"

MinesBlock::MinesBlock(Point p,QWidget *parent) : QLabel(parent)
{
    pos=p;
    allowPress=true;
    isMine=false;//初始化为非0 逻辑中只需设雷
    isFlag=false;
    isShow=false;
    isQuestion=false;
    //默认未翻开的图片
    setPix(QString(":/first/picture/mines/blank.png"));
    resize(MINESUNIT,MINESUNIT);//设置Label大小
}


void MinesBlock::setPix(QString pix)
{
    QPixmap pixmap(pix);
    QPixmap facePix = pixmap.scaled(MINESUNIT,MINESUNIT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(facePix);
}

void MinesBlock::mousePressEvent(QMouseEvent *e)
{
    if(!allowPress)
        return;
    if(e->button()==Qt::LeftButton&&!this->isShow){
        emit leftClick();
    }
    else if(e->button()==Qt::RightButton){
        emit rightClick();
    }

    return QLabel ::mousePressEvent(e);
}

void MinesBlock::enterEvent(QEvent *e)
{
    //鼠标进入方块时的效果展示
    if(!this->isShow&&!this->isFlag&&!this->isQuestion&&this->allowPress){
        //调用自定义函数 同时设定图片大小
        this->setPix(":/first/picture/mines/0.png");
    }
    return QLabel::enterEvent(e);
}

void MinesBlock::leaveEvent(QEvent *e)
{
    //鼠标离开方块时的效果展示
    if(!this->isShow&&!this->isFlag&&!this->isQuestion&&this->allowPress){
        //调用自定义函数 同时设定图片大小
        this->setPix(":/first/picture/mines/blank.png");
    }
    return QLabel::leaveEvent(e);
}




