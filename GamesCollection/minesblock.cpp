#include "minesblock.h"

MinesBlock::MinesBlock(Point p,QWidget *parent) : QLabel(parent)
{
    pos=p;

    isMine=false;//初始化为非0 逻辑中只需设雷
    isFlag=false;
    isShow=false;
    //默认未翻开的图片
    setPixmap(QString(":/first/pictrue/mines/blank.gif"));
    resize(MINESUNIT,MINESUNIT);
}
