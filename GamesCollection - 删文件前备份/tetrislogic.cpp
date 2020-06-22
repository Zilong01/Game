#include "tetrislogic.h"
#include<QRandomGenerator>
#include"tetrisscene.h"
#include<QTimer>
#include<QDebug>
#include<QSound>
vector<vector<bool>>TetrisLogic:: map;//地图初始化在游戏场景中
int TetrisLogic::xNum=10;
int TetrisLogic::yNum=20;
int TetrisLogic:: changeTimes=5;
int TetrisLogic:: score=0;
bool TetrisLogic::gameOver=false;
//bool TetrisLogic::lineClear=false;

TetrisLogic::Difficulty TetrisLogic::difficulty=NORMAL;

Point TetrisLogic::shape[7][4][4]={

    {//O型  四种形态都一样
     {{0,0}, {1,0}, {0,1}, {1,1}},
     {{0,0}, {1,0}, {0,1}, {1,1}},
     {{0,0}, {1,0}, {0,1}, {1,1}},
     {{0,0}, {1,0}, {0,1}, {1,1}}
    },

    {// I 只有两种形态
     {{1,0}, {1,1}, {1,2}, {1,3}},
     {{0,1}, {1,1}, {2,1}, {3,1}},
     {{1,0}, {1,1}, {1,2}, {1,3}},
     {{0,1}, {1,1}, {2,1}, {3,1}}
    },

    {//S型2种
     {{0,1}, {1,1}, {1,0}, {2,0}},
     {{0,0}, {0,1}, {1,1}, {1,2}},
     {{0,1}, {1,1}, {1,0}, {2,0}},
     {{0,0}, {0,1}, {1,1}, {1,2}}
    },

    {//Z型 2种
     {{0,1},{1,1},{1,2},{2,2}},
     {{1,0},{1,1},{0,1},{0,2}},
     {{0,1},{1,1},{1,2},{2,2}},
     {{1,0},{1,1},{0,1},{0,2}},
    },

    {//L型
     {{0,0},{0,1},{0,2},{1,2}},
     {{0,1},{1,1},{2,1},{2,0}},
     {{0,0},{1,0},{1,1},{1,2}},
     {{0,0},{1,0},{2,0},{0,1}}
    },

    {//J型 4种
     {{1,0}, {1,1}, {0,2}, {1,2}},
     {{0,1}, {1,1}, {2,1}, {2,2}},
     {{1,0}, {2,0}, {1,1}, {1,2}},
     {{0,0}, {0,1}, {1,1}, {2,1}}
    },

    {//T型 4种
     {{0,0}, {1,0}, {2,0}, {1,1}},
     {{0,0}, {0,1}, {0,2}, {1,1}},
     {{0,2}, {1,2}, {2,2}, {1,1}},
     {{2,0}, {2,1}, {2,2}, {1,1}}
    }


};

TetrisLogic::TetrisLogic()
{
    //初始化x y curent值
    newBlock();
}
void TetrisLogic::newBlock(){

        //下落初始位置
        x=4;
        y=0;

        //重置清行判断
        //lineClear=false;

        //重置可旋转次数
        if(TetrisLogic::difficulty==TetrisLogic::NORMAL)
            TetrisLogic::changeTimes=15;
        else if(TetrisLogic::difficulty==TetrisLogic::DIFFICULT)
            TetrisLogic::changeTimes=5;
        else if(TetrisLogic::difficulty==TetrisLogic::EPIC){
            TetrisLogic::changeTimes=4;
        }

        //设置随机下落的俄罗斯方块的形状与状态
        srand(static_cast<int>(time(0)));
        currentShape=rand()%7;
        currentState=rand()%4;
}
bool TetrisLogic::checkChange(int moveX, int moveY, bool isChangeState)
{
    for(int i=0;i<4;i++){ //若是切换状态的检查 则对状态进行检测 （此时不更新
        int tempX=x+shape[currentShape][(currentState+isChangeState)%4][i].x+moveX;
        int tempY=y+shape[currentShape][(currentState+isChangeState)%4][i].y+moveY;

        if(tempX<0||tempX>9||tempY<0||tempY>19||map[tempX][tempY]){
            return false;//不允许转化/移动
        }
    }
   return true;
}
void TetrisLogic::move(moveDirection direction)
{

    clearPrevious();//清除当前位置的砖块
    switch (direction) {
    case CHANGE:
        if(checkChange(0,0,1)){
            currentState=(currentState+1)%4;
        }
        updateMap();
        break;

    case LEFT:
        if(checkChange(-1,0)){
            x--;
        }
        updateMap();
        break;

    case RIGHT:
        if(checkChange(1,0)){
            x++;
        }
        updateMap();
        break;
    case DOWN:
        if(checkChange()){
            y++;
        }
        else{//下落受限
            updateMap();//删除的图像重新显示-》使得底部方块状态保存
            clearLine();//检测能否消去
            //////////////////////////此处出入
            qDebug()<<"move(DOwn)受限";
            newBlock();//重置砖块| 位置坐标指向新方块
        }
        updateMap();
        break;
    default:
        updateMap();
        break;
    }

}
void TetrisLogic::clearPrevious(){
//在改变坐标之前清楚当前位置map上的值
    for(int i=0;i<4;i++){
        int tempX=x+shape[currentShape][currentState][i].x;
        int tempY=y+shape[currentShape][currentState][i].y;
        map[tempX][tempY]=false;
    }
}
void TetrisLogic::updateMap(){

    for(int i=0;i<4;i++){
        //////注意 map的单位是1 不是unit
        int tempX=x+shape[currentShape][currentState][i].x;
        int tempY=y+shape[currentShape][currentState][i].y;
        if(map[tempX][tempY]){//当前位置已有方块
            gameOver=true;
            //emit die();
            qDebug()<<"逻辑模块updateMap：游戏结束(当前位置已有"<<tempX<<tempY;
        }
        else map[tempX][tempY]=true;
    }
    //qDebug()<<"updateMap()调用";
}
void TetrisLogic::clearLine(){
    int i,j;
    for(j=0;j<map[0].size();j++){ //y坐标的数量-》行数
        int flag1=true;
        for(i=0;i<map.size();i++){// map.size()是列数x坐标数量
            if(map[i][j]==0)//检测这一行是否有空格 若有返回false
                flag1=false;
        }
        if(flag1){
            for(int k=0;k<map.size();k++){/////每一列都删除第j行的元素（循环列数次）
                qDebug()<<"clearLine调用";
                map[k].erase(map[k].begin()+j);//清除k列j行
                map[k].insert(map[k].begin(),0); //增加k列第一（0）行0 ->前后行数不变
            }
            score+=10;//得分增加
//            lineClear=true;
            //emit  lineClear1();
        }
    }
}

