//求从顶点u出发到其他顶点的最短路径
void BFS_MIN_Distance(Graph G,int u){
    for(int i=0;i<G.vexnum;++i){
        d[i]=-1;    //初始化路径长度
        path[i]=-1; //初始化路径（从哪个顶点过来）
    }
    d[u]=0;         //u到自身的距离为0
    visited[u]=TRUE;
    EnQueue(Q,u);
    
    while(!isEmpty(Q)){ //BFS算法主过程
        DeQueue(Q,u);   //队头元素出队并置为u
        //依次检查u的所有邻接点w
        for(w=FirstNeighbor(G,u);w>=0;w=NextNeighbor(G,u,w)){
            if(!visited[w]){ //w为u的尚未访问的邻接顶点
                d[w]=d[u]+1; //路径长度加1
                path[w]=u;   //最短路径应从u到w
                visited[w]=TRUE; //对w做已访问标记
                EnQueue(Q,w); //顶点w入队
            }
        }
    }
}