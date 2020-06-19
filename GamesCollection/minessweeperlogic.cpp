#include "minessweeperlogic.h"
#include<QDebug>

MinesSweeperLogic::MinesSweeperLogic(int row_, int col_, int numOfMines_, QWidget *parent)
{
    row=row_;
    col=col_;
    numOfMines=numOfMines_;


}

void MinesSweeperLogic::newMap()
{
    for(int j=0;j<col;j++){
        vector<MinesBlock*> temp;
        for(int i=0;i<row;i++){
            MinesBlock* block=new MinesBlock({j,i},this);
            map.push_back(temp);
            map[j].push_back(block);
            map[j][i]->pos=Point({j,i});
            map[j][i]->move(j*MINESUNIT,i*MINESUNIT);
            map[j][i]->show();
            map[j][i]->isShow=false;


            //监听block中的点击信号
            connect(map[j][i],&MinesBlock::leftClick,[=](){
                if(!map[j][i]->isFlag)
                    showBlock({j,i});//不是旗子
                //else
                    //不是旗子
            });
        }
    }

    srand(static_cast<int>(time(0)));

    //初始化雷
    for(int i=0;i<numOfMines;i++){
        bool ok=false;
        while(!ok){
            int x=rand()%col;
            int y=rand()%row;
            if(!map[x][y]->isMine){
                map[x][y]->isMine=true;
                ok=true;
            }
        }
    }

    //计算数字->删去 感觉不需要计算每一个格子 仅在点击时计算
}

void MinesSweeperLogic::showBlock(Point p)
{
    if(p.x<0||p.x>col-1||p.y>row-1||p.y<0)
        return;//越界

    if(map[p.x][p.y]->isMine&&firstClick){//第一次点击就踩雷
        newMap();
        return;
    }

    if(map[p.x][p.y]->isShow){
        return;//避免再次递归
    }

    firstClick=false;
    //踩雷
    if(map[p.x][p.y]->isMine){
        //map[p.x][p.y]->setPixmap(QString(":/first/picture/mines/boom.png"));
        map[p.x][p.y]->setPix(QString(":/first/picture/mines/boom.png"));//重设图片及大小
        emit gameOver();
        map[p.x][p.y]->isShow=true;
    }

    else if(map[p.x][p.y]){
        int tempNum=0;

        //计算雷数
        for(int i=-1;i<2;i++){
            for(int j=-1;j<2;j++){
                if(i==0&&j==0)
                    continue;
                /*if(p.x-i<0||p.y-j<0||p.x+i>=row||p.y+j>=col)*/
                if(p.x+i<0||p.y+j<0||p.x+i>=row||p.y+j>=col){
                    //越界
                    continue;
                }
                else if(map[p.x+i][p.y+j]->isMine)
                    tempNum++;
            }
        }


        //周围有雷
        if(tempNum){
            map[p.x][p.y]->setPix(QString(":/first/picture/mines/%1.png").arg(tempNum));
            tempNum=0;
            map[p.x][p.y]->isShow=true;

        }
        else{
            //没有雷
            map[p.x][p.y]->setPix(QString(":/first/picture/mines/0.png"));
            map[p.x][p.y]->isShow=true;
            //继续递归
            //////////////////////////////此处有BUG///////////////////////
            //            Point temp;
            //            temp.x=p.x-1;temp.y=p.y-1;
            //            showBlock(temp);
            //            return;
            //            temp.x=p.x+1;temp.y=p.y+1;
            //            showBlock(temp);
            for(int i=-1;i<2;i++){
                for(int j=-1;j<2;j++){
                    if(i==0&&j==0)
                        continue;
                    Point temp;
                    temp.x=p.x+i;temp.y=p.y+j;

                    //                    if((temp.x==0&&temp.y==0)||(temp.x==col-1&&temp.y==row-1))//到达边界终止递归
                    //                    {

                    //                        return;
                    //                    }
                    if(temp.x<0||temp.y<0||temp.x>col-1||temp.y>row-1)
                        return;
                    else {//不是边界继续递归
                        qDebug()<<"递归"<<temp.x<<temp.y;
                        showBlock(temp);
                    }
                }
            }
          return;
        }
    }
    return;
}

