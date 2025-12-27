// 逆拓扑排序核心函数：参数G是邻接表存储的有向图，返回值表示是否排序成功（无环则成功）
bool ReverseTopologicalSort(Graph G) {
    // 1. 初始化栈：用于存储“出度为0”的顶点（逆拓扑的起点）
    InitStack(S);  
    // 2. 定义出度数组：outdegree[i]表示第i个顶点的出度（有多少条边从该顶点出发）
    int outdegree[G.vexnums];  
    
    // 3. 遍历所有顶点，统计每个顶点的出度，并将出度为0的顶点入栈
    for (int i = 0; i < G.vexnums; i++) {
        // 3.1 初始化当前顶点的出度为0
        int out = 0;
        // 3.2 指向当前顶点的第一条边（遍历该顶点的所有出边）
        //定义一个指向 “边节点” 的指针 p，并让这个指针指向图 G 中第 i 个顶点的第一条出边节点
        ArcNode *p = G.vertices[i].firstarc;
        // 3.3 遍历该顶点的所有出边，统计出度
        while (p) {
            out++;          // 每找到一条出边，出度+1
            p = p->nextarc; // 指向下一条出边
        }
        // 3.4 将统计好的出度存入数组
        outdegree[i] = out;
        // 3.5 若当前顶点出度为0（没有任何出边，是逆拓扑的“终点/起点”），入栈
        if (outdegree[i] == 0) {  
            Push(S, i);
        }
    }

    // 4. 定义计数器：记录已输出的顶点数，用于最后判断是否有环
    int count = 0;  
    // 5. 主循环：栈不为空时，持续处理出度为0的顶点
    while (!IsEmpty(S)) {
        // 5.1 定义变量i，接收出栈的顶点索引
        int i;
        // 5.2 出栈：取出一个出度为0的顶点
        //Pop（中文常译作 “出栈”）是栈（Stack）这种数据结构的核心操作函数
        Pop(S, &i);  
        // 5.3 存储该顶点到结果数组（这是逆拓扑序列的一个元素）
        print[count++] = i;  

        // 6. 关键步骤：找到当前顶点i的所有“前驱顶点”（即哪些顶点有边指向i），并更新其出度
        // 6.1 遍历所有顶点，找指向i的顶点（j是候选前驱）
        for (int j = 0; j < G.vexnums; j++) {
            // 6.2 指向j的第一条出边
            ArcNode *p = G.vertices[j].firstarc;
            // 6.3 遍历j的所有出边，判断是否指向i
            while (p) {
                // 6.4 若j的这条边指向i → j是i的前驱顶点
                if (p->adjvex == i) {  
                    // 6.5 j的出度减1（因为i已被处理，j指向i的这条边可以移除）
                    outdegree[j]--;    
                    // 6.6 若j的出度变为0（j没有剩余出边），入栈等待处理
                    if (outdegree[j] == 0) {  
                        Push(S, j);
                    }
                    // 6.7 找到j指向i的边后，无需继续遍历j的其他边，跳出循环
                    break;  
                }
                // 6.8 继续遍历j的下一条出边
                p = p->nextarc;
            }
        }
    }

    // 7. 判断是否有环：若输出的顶点数 < 总顶点数 → 存在环，逆拓扑排序失败
    if (count < G.vexnums) {
        return false;  
    } else {
        // 8. 无环，排序成功
        return true;   
    }
}