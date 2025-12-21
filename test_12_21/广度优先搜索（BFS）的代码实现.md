# 广度优先搜索（BFS）的代码实现

## 引言:

刚开始我对BFS的理解就是广的话，肯定是横向开是优先搜索，找最邻近的点。但是中间的顺序呢？针对邻接矩阵是从小到大，但是邻接表好像又不一样了！我们学了解一个基础 BFS 代码。

### 关键部分：

- `visited`数组：作用是标记顶点是否已访问（避免重复遍历）；
- 队列的使用：BFS 的 “分层遍历” 依赖队列缓存待访问顶点（入队 / 出队操作是核心）；
- 邻接顶点的遍历：`FirstNeighbor`/`NextNeighbor`的逻辑 ；
- BFS 的流程：“ 访问初始顶点→标记→入队→出队遍历邻接顶点→未访问则重复标记 / 入队” 的循环逻辑

```c
bool visited[MAX_VERTEX_NUM]; //访问标记数组
//广度优先遍历
void BFS(Graph G,int v){  //从顶点v出发,广度优先遍历图G
    visit(v);             //访问初始顶点v
    visited[v]=TRUE;      //对v做已访问标记
    EnQueue(Q,v);         //顶点v入队列Q
    
    while(!isEmpty(Q)){   //队列非空
        DeQueue(Q,v);     //顶点v出队列
        //检测所有邻接点
        for(w=FirstNeighbor(G,v);w>=0;w=NextNeighbor(G,v,w)){
            if(!visited[w]){ //w为v的尚未访问的邻接顶点
                visit(w);     //访问顶点w
                visited[w]=TRUE;//对w做已访问标记
                EnQueue(Q,w); //顶点w入队列
            }
        }
    }
}
```

#### 一、代码的基础元素

1. **访问标记数组 `visited`**

   ```c
   bool visited[MAX_VERTEX_NUM]; // 访问标记数组
   ```

   - 作用：标记每个顶点是否被访问过，**初始值全为 `false`**（表示所有顶点都未访问）。
   - 用途：避免顶点被重复遍历，记录就是为了不重复访问。

2. **BFS 函数的定义**

   ```c
   void BFS(Graph G, int v) { // 从顶点v出发，广度优先遍历图G
   ```

   - 参数 `Graph G`：图的存储结构
   - 参数 `int v`：**起始顶点的索引**

#### 二、代码逐行解读（结合左侧图）

以**起始顶点为 1**为例的遍历过程：

##### 1. 初始化起始顶点

```c
visit(v);               // 访问初始顶点v（比如打印“1”）
visited[v] = TRUE;      // 标记顶点v为“已访问”（此时visited[1]=true）
EnQueue(Q, v);          // 把顶点v加入队列Q（队列初始化为：[1]）
```

- 这一步是 BFS 的 “起点”：先处理起始顶点（顶点我们假设为1），再把它加入队列，记录下次遇到就不访问。

##### 2. 队列循环处理（核心逻辑）

```c
while(!isEmpty(Q)) {    // 只要队列不为空，就持续处理
```

队列是 BFS 的核心：**队列里存的是 “已访问、但邻接顶点还没处理完的顶点”**。

##### （1）取出队头顶点

```c
DeQueue(Q, v);          // 顶点v出队（从队列头拿一个顶点）
```

- 第一次循环：队列是`[1]`，出队后`v=1`。

##### （2）遍历当前顶点的所有邻接顶点

```c
for(w=FirstNeighbor(G,v); w>=0; w=NextNeighbor(G,v,w))
```

- `FirstNeighbor(G,v)`：找顶点`v`的**第一个邻接顶点**（比如 v=1 时，第一个邻接顶点是 2）。
- `NextNeighbor(G,v,w)`：找顶点`v`在`w`之后的**下一个邻接顶点**（比如 v=1 时，w=2 之后的下一个邻接顶点是 5）。
- 循环条件`w>=0`：表示还有未遍历的邻接顶点。

##### （3）处理未访问的邻接顶点

```c
if(!visited[w]) {       // 若w是v的“未访问”邻接顶点
    visit(w);           // 访问顶点w（比如打印w的值）
    visited[w] = TRUE;  // 标记w为“已访问”
    EnQueue(Q, w);      // 把w加入队列（后续处理w的邻接顶点）
}
```

就是处理为访问的，遇到访问的跳过，没遇到就把TRUE填进去，表示已经访问 。

##### 这个图就好分析：

![image-20251221165428364](C:\Users\Rory\AppData\Roaming\Typora\typora-user-images\image-20251221165428364.png)

## 引言二：

如果说从中参杂了非联通数呢？读完8不久已经结束了!对这个时候我们的`visited`数组就起到作用了，我们需要在遍历一遍，这样才能找到false，继续遍历！！

### 添加一个for循环：

```c
// 访问标记数组（全局/外部定义）
bool visited[MAX_VERTEX_NUM];
// 对图G进行广度优先遍历（处理非连通图）
void BFSTraverse(Graph G) { 
    // 初始化访问标记数组为“未访问”
    for (int i=0; i<G.vexnum; ++i) 
        visited[i] = FALSE;
    // 初始化辅助队列
    InitQueue(Q);
    // 遍历所有顶点，处理每个连通分量
    for (int i=0; i<G.vexnum; ++i) {
        // 若顶点i未被访问（属于新的连通分量）
        if (!visited[i]) { 
            // 从顶点i出发，遍历该连通分量
            BFS(G, i); 
        }
    }
}
// 从顶点v出发，广度优先遍历图G（单个连通分量）
void BFS(Graph G, int v) { 
    // 访问初始顶点v
    visit(v);
    // 标记顶点v为已访问
    visited[v] = TRUE;
    // 顶点v入队列
    EnQueue(Q, v); 
    // 队列非空时持续处理
    while (!isEmpty(Q)) { 
        // 顶点v出队列
        DeQueue(Q, v); 
        // 遍历v的所有邻接顶点
        for (w=FirstNeighbor(G, v); w>=0; w=NextNeighbor(G, v, w)) { 
            // 若w是v的未访问邻接顶点
            if (!visited[w]) { 
                // 访问顶点w
                visit(w); 
                // 标记w为已访问
                visited[w] = TRUE; 
                // 顶点w入队列
                EnQueue(Q, w); 
            }
        }
    }
}
```

ps：这里总结一个规律就是调用BFS的函数次数=连通分量数

### 引言：

那这里就会问了矩阵和表有啥区别对它的影响了，这里针对广度优先生成树就有影响了，邻接矩阵和邻接表的生成树不一样！位置不同可能会！相反的森林也就是我们刚刚遇到的非联通图产生的影响了！