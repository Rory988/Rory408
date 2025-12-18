//邻接矩阵存储表示法
#define  MaxVertexNum 100
typedef struct{
    char Vex[MaxVertexNum];               //顶点表
    int Edges[MaxVertexNum][MaxVertexNum];//边表
    int vexnum, arcnum;                   //邻接矩阵
}MGraph;  图的当前定点数和边数/弧数

