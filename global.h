#pragma once
typedef struct tagVertex
{
	int row;
	int	col;
	int info;  //编号
}Vertex;

#define BLANK -1
#define MAX_ROW  10        //游戏地图行数
#define	MAX_COL  16			//游戏地图列数
#define MAX_VERTEX_NUM 160	//顶点数
#define	MAX_PIC_NUM	16		//种类数
#define REPEAT_NUM 10		//每种图片个数
#define	MAP_TOP 50			//游戏地图左上角纵坐标
#define MAP_LEFT 20			//游戏地图左上角横坐标
#define PIC_WIDTH 40		//游戏图片宽度
#define PIC_HEIGHT 40		//游戏图片高度
#define PLAY_TIMER_ID 1
#define GAME_LOSE -1			//游戏失败
#define GAME_SUCCESS 0			//游戏成功
#define GAME_PLAY 1			//游戏正在进行
#define GAME_PAUSE 2        //游戏暂停

#define GAME_MAIN_FRAME 0  //主界面
#define GAME_MODEL_BASE 1 //基本模式
#define GAME_MODEL_EASY 2 //休闲模式
#define GAME_MODEL_LEVEL 3 //关卡模式