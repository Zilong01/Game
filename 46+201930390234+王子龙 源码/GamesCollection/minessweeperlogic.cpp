#include "minessweeperlogic.h"
#include<QDebug>

MinesSweeperLogic::MinesSweeperLogic(int row_, int col_, int numOfMines_, QWidget *parent)
{
    row=row_;
    col=col_;
    numOfMines=numOfMines_;
    firstClick=true;


}

void MinesSweeperLogic::newMap()
{
    //清除上把信息
    map.clear();
    firstClick=true;

    for(int j=0;j<col;j++){
        qDebug()<<"newmap()中当前col"<<col<<row;
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
                if(!map[j][i]->isFlag){
                    showBlock({j,i});//不是旗子

                }
                //else
                    //是旗子
            });

            //监听右键信号
            connect(map[j][i],&MinesBlock::rightClick,[=](){
                    changeFlag(j,i);//必须封装

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
    qDebug()<<col-1<<row-1;
    //map[29][15];
    if(p.x<0||p.x>col-1||p.y>row-1||p.y<0)
        return;//越界

    if(map[p.x][p.y]->isMine&&firstClick){//第一次点击就踩雷
        newMap();
        return;
    }

    if(!map[p.x][p.y]->isMine&&firstClick){//第一次点击
        emit firstClickSignal();
    }

    if(map[p.x][p.y]->isShow){
        return;//避免再次递归 造成程序崩溃
    }

    firstClick=false;
    //踩雷
    if(map[p.x][p.y]->isMine&&map[p.x][p.y]->clicking){
        //map[p.x][p.y]->setPixmap(QString(":/first/picture/mines/boom.png"));
        map[p.x][p.y]->setPix(QString(":/first/picture/mines/boom.png"));//重设图片及大小
        map[p.x][p.y]->isShow=true;

        for(int i=0;i<col;i++){
            for(int j=0;j<row;j++){

                map[i][j]->allowPress=false;//禁止点击

                if(p.x==i&&p.y==j)
                    continue;//跳过本雷
                else{
                    if(map[i][j]->isMine){
                        //显示所有雷
                        if(map[i][j]->isFlag)
                            map[i][j]->setPix(QString(":/first/picture/mines/clear.png"));
                        else
                            map[i][j]->setPix(QString(":/first/picture/mines/mine.png"));
                        map[i][j]->isShow=true;
                    }
                }
            }
        }


        emit gameOver();
        return;
    }




    else if(map[p.x][p.y]){

        int tempNum=0;

        //计算雷数
        for(int i=-1;i<2;i++){
            for(int j=-1;j<2;j++){
                if(i==0&&j==0)
                    continue;
                /*if(p.x-i<0||p.y-j<0||p.x+i>=row||p.y+j>=col)*//////6.20修复
                if(p.x+i<0||p.y+j<0||p.x+i>=col||p.y+j>=row){///////////////6.21修复
                    //越界
                    //return;
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
            if(map[p.x][p.y]->isFlag)
            {
               map[p.x][p.y]->isFlag=false;//收回旗帜
               numOfFlag--;
            }

        }

        else{
            //没有雷
            map[p.x][p.y]->setPix(QString(":/first/picture/mines/0.png"));
            map[p.x][p.y]->isShow=true;
            if(map[p.x][p.y]->isFlag)//收回旗帜
            {
               map[p.x][p.y]->isFlag=false;
               numOfFlag--;
            }
            //继续递归
            for(int i=-1;i<2;i++){
                for(int j=-1;j<2;j++){
                    if(i==0&&j==0)
                        continue;
                    Point temp;
                    temp.x=p.x+i;temp.y=p.y+j;

                    if(temp.x<0||temp.y<0||temp.x>col-1||temp.y>row-1){
                        qDebug()<<"temp.x"<<temp.x<<temp.y;
                        return;
                    }
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

void MinesSweeperLogic::resetMapSize(int row_, int col_, int numOfMines_)
{
    row=row_;
    col=col_;
    numOfMines=numOfMines_;
}

void MinesSweeperLogic::changeFlag(int x,int y)
{

    if(!map[x][y]->isFlag&&!map[x][y]->isQuestion){
    map[x][y]->isFlag=true;
    numOfFlag++;
    emit flagChangeSignal();
    map[x][y]->setPix(QString(":/first/picture/mines/flag.png"));
    }
    else if(map[x][y]->isFlag&&!map[x][y]->isQuestion){
        map[x][y]->isFlag=false;
        numOfFlag--;
        emit flagChangeSignal();
        map[x][y]->isQuestion=true;
        map[x][y]->setPix(QString(":/first/picture/mines/question.png"));
    }
    else if(map[x][y]->isQuestion){
        map[x][y]->isQuestion=false;
        map[x][y]->setPix(QString(":/first/picture/mines/blank.png"));
    }
}

void MinesSweeperLogic::checkWin()
{
    for(int i=0;i<col;i++){
        for(int j=0;j<row;j++){
            if(!map[i][j]->isMine){//不是雷
                if(!map[i][j]->isShow)//有任何一个没点开
                    return;
            }
        }
    }//end for
    //不是雷且全部点开
    emit gameWin();
}


