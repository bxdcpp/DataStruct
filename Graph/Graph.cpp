
//参考://原文链接：https ://blog.csdn.net/Africa_South/article/details/88553068
#include "DataDefine.h"

#include <iostream>
#include <queue>
//#include <limits.h>
//#include <cmath>

void showMatrix(MGraph G)
{
	for (int i = 0; i < G.vexnum; i++)
	{
		for (int j = 0; j < G.vexnum; j++) 
			std::cout << G.arcs[i][j].adj << " ";

		std::cout << std::endl;
	}
}

status LocateVex(MGraph G, VertexType u)
{
	int pos;
	for (pos = 0; pos < G.vexnum && G.vexs[pos] != u; pos++);

	return pos;
}

status CreateDG(MGraph& G)
{
	return OK;
}

status CreateDN(MGraph& G)
{
	return OK;
}

status CreateUDG(MGraph& G)
{
	//无向网（无向带权图）
	int IncInfo;//IncInfo=0,则弧不含有信息
	std::cout<<("please input graph vertexNum ArcNum IncInfo=0 \n");
	std::cin >> G.vexnum >> G.arcnum >> IncInfo;
	//printf("please input graph vertexNum ArcNum IncInfo=0 \n");
	for (int i = 0; i < G.vexnum; i++) {
		std::cin >>G.vexs[i];//构造顶点向量
	}
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; ++j) {
			//init graph
			G.arcs[i][j] = { INT_MAX,NULL };
		}
	}
		
	for (int k = 0; k < G.arcnum; k++) {
		VertexType v1, v2; VRType w;

		std::cin >> v1 >> v2 >> w;

		int i = LocateVex(G, v1); int j = LocateVex(G, v2);
		std::cout << "index i=" << i << "," << "j=" << j << std::endl;
		G.arcs[i][j].adj = w;
		if (IncInfo) {
			std::cin >> *G.arcs[i][j].info;
		}
		G.arcs[j][i] = G.arcs[i][j];
		std::cout << "G.arcs["<<i<<"]["<<j<<"]"<< "," << G.arcs[i][j].adj  << std::endl;
	}


	return OK;
}

status CreateUDN(MGraph& G)
{
	return OK;
}

status CreateGraph(MGraph& G)
{
	//采用数组(邻接矩阵)表示法
	G.kind = UDG;
	switch (G.kind)
	{
	case DG:return CreateDG(G);
	case DN:return CreateDN(G);
	case UDG:return CreateUDG(G);
	case UDN:return CreateUDN(G);
	default:return ERROR;

	}
}

//返回图G中U的第一个临接节点
status FirstAdjVex(MGraph G, VertexType v)
{
	int index = LocateVex(G, v);
	int i = 0;
	while (i < G.vexnum)
	{
		if (G.arcs[index][i].adj != INT_MAX)
			break;
	}
	if (i == G.vexnum) return -1;

	return i;
}

int NextAdjVex(MGraph G, VertexType v, VertexType u) {
	int indexV = LocateVex(G, v);
	int indexU = LocateVex(G, u);
	int index;
	for (index = indexU + 1; index < G.vexnum && G.arcs[indexV][index].adj == -1; index++);
	if (index == G.vexnum) return -1;
	else return index;
}

VertexType GetVex(MGraph G, VertexType V)
{
	return 0;
}

void PutVex(MGraph& G, VertexType V)
{
}

void InsertVex(MGraph& G, VertexType v) 
{
}

void DeleteVex(MGraph& G, VertexType V)
{
}

void InsertArc(MGraph& G, VertexType v, VRType w)
{
}

void DeleteArc(MGraph& G, VertexType v, VRType w)
{
}

void BFSTraverse(MGraph G) {
	// 按照广度优先非递归遍历图G，使用辅助队列Q和访问标志数组visited。
	int* visited = new int[G.vexnum];
	std::queue<int> Q;
	int i;
	for (i = 0; i < G.vexnum; i++) visited[i] = 0;

	for (i = 0; i < G.vexnum; i++) {
		if (!visited[i]) { //访问顶点i
			visited[i] = 1;
			std::cout << G.vexs[i] << " ";
			Q.push(i);
			while (!Q.empty()) {
				int u = Q.front();
				Q.pop(); //取出对头顶点
				for (int w = FirstAdjVex(G, G.vexs[u]); w >= 0; w = NextAdjVex(G, G.vexs[u], G.vexs[w])) {
					if (!visited[w]) {  // w为u的尚未访问的邻接顶点
						visited[w] = 1;
						std::cout << G.vexs[w] << " ";
						Q.push(w);
					}
				}
			}
		}
	}
}

int main()
{
	/*无向网
		6 10 0
		A B C D E F
		A B 5
		A C 8
		A D 7
		A F 3
		B C 4
		C D 5
		C F 9
		D E 5
		D F 6
		E F 1

		无向图
		8 9 0
		V1 V2 V3 V4 V5 V6 V7 V8
		V1 V2
		V1 V3
		V2 V4
		V2 V5
		V3 V6
		V3 V7
		V4 V8
		V5 V8
		V6 V7*/
	MGraph graph;
	CreateGraph(graph);
	showMatrix(graph);
	return OK;
}

