#define MAXVERT 1005
#define INF 0x3f3ff3f3f
#define undirected 1
//图结构
typedef struct{
    int vexnum,arcnum;//顶点数和边数
    int arc[MAXV][MAXV];//邻接矩阵边的权值
}MGraph;
//初始化
Void InitMGraph(MGraph *G, int n)
{
   G->vexnum=n;//顶点数
   for(int i=0;i<n;i++)
   {
      for(int j=0;j<n;j++)
      {
         G->arc[i][j]=INF;
      }
   }
}

Void addedge(MGraph *G,int u,int v,int w)//G指向图结构的指针；u,v;边的左右两个端点,w为边的权值
{
    G->arc[u][v]=w;
    if(undirected)//无向图
    G->arc[v][u]=w;
}





