#define MaxVertexNum 100  //图中顶点数目的最大值

//边表结点
typedef struct ArcNode {
    int adjvex;             //该弧所指向的顶点的位置
    struct ArcNode *nextarc;//指向下一条弧的指针
    //InfoType info;        //网的边权值（若为无向图可注释）
}ArcNode;

//顶点表结点
typedef struct VNode {
    VertexType data;        //顶点信息
    ArcNode *firstarc;      //指向第一条依附该顶点的弧的指针
}VNode, AdjList[MaxVertexNum];

//图的邻接表存储类型
typedef struct {
    AdjList vertices;       //邻接表
    int vexnum, arcnum;     //图的顶点数和弧数
}Graph;


bool TopologicalSort(Graph G){
    InitStack(S);           //初始化栈，存储入度为0的顶点
    for(int i=0; i<G.vexnum; i++)
        if(indegree[i]==0)
            Push(S,i);      //将所有入度为0的顶点进栈
    
    int count=0;            //计数，记录当前已经输出的顶点数
    while(!IsEmpty(S)){     //栈不空，则存在入度为0的顶点
        Pop(S,i);           //栈顶元素出栈
        print[count++]=i;   //输出顶点i
        for(p=G.vertices[i].firstarc; p; p=p->nextarc){
            //将p所指向的顶点的入度减1，并且将入度减为0的顶点压入栈
            v = p->adjvex;
            if(!(--indegree[v]))
                Push(S,v);  //入度为0，则入栈
        }
    }//while

    if(count<G.vexnum)
        return false;       //排序失败，有向图中有回路
    else
        return true;        //拓扑排序成功
}