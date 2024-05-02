#pragma once
typedef struct tagVertex
{
	int row;
	int	col;
	int info;  //���
}Vertex;

#define BLANK -1
#define MAX_ROW  10        //��Ϸ��ͼ����
#define	MAX_COL  16			//��Ϸ��ͼ����
#define MAX_VERTEX_NUM 160	//������
#define	MAX_PIC_NUM	16		//������
#define REPEAT_NUM 10		//ÿ��ͼƬ����
#define	MAP_TOP 50			//��Ϸ��ͼ���Ͻ�������
#define MAP_LEFT 20			//��Ϸ��ͼ���ϽǺ�����
#define PIC_WIDTH 40		//��ϷͼƬ���
#define PIC_HEIGHT 40		//��ϷͼƬ�߶�
#define PLAY_TIMER_ID 1
#define GAME_LOSE -1			//��Ϸʧ��
#define GAME_SUCCESS 0			//��Ϸ�ɹ�
#define GAME_PLAY 1			//��Ϸ���ڽ���
#define GAME_PAUSE 2        //��Ϸ��ͣ

#define GAME_MAIN_FRAME 0  //������
#define GAME_MODEL_BASE 1 //����ģʽ
#define GAME_MODEL_EASY 2 //����ģʽ
#define GAME_MODEL_LEVEL 3 //�ؿ�ģʽ