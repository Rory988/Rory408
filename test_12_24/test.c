// 图的邻接表存储（图片隐含的图结构）
typedef struct {
    VNode adjlist[];                // 顶点数组
    int n, e;                       // 顶点数、边数
} Graph;
// 图片核心函数：BFS求顶点u到其他顶点的最短路径
void BFS_MIN_Distance(Graph G, int u) {
    // 初始化三个核心数组
    for (int i = 0; i < G.n; i++) {
        visited[i] = false;         // 访问标记：未访问
        d[i] = ∞;                   // 路径长度：初始无穷大
        path[i] = -1;               // 前驱顶点：初始无前驱
    }
         visited[u] = true;         // 标记起点u已访问
         d[u] = 0;                  // 起点到自身路径长度为0
         EnQueue(Q, u);             // 起点入队
         // BFS核心遍历
    while (!IsEmpty(Q)) {           // 队列非空
        DeQueue(Q, w);              // 出队顶点w
                                    // 遍历w的所有邻接顶点v
        for (w的每个邻接顶点v) {
            if (!visited[v]) {      // v未被访问
                visited[v] = true;  // 标记v已访问
                d[v] = d[w] + 1;    // v的路径长度 = w的长度+1
                path[v] = w;        // v的前驱顶点是w
                EnQueue(Q, v);      // v入队
            }
        }
    }
}