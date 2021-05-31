
#include "DataDefine.h"

#include <stdio.h>
#include <limits.h>
//#include <cmath>

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
	printf("please input graph vertexNum ArcNum IncInfo=0 \n");
	scanf_s("%d,%d,%d", &G.vexnum, &G.arcnum, &IncInfo);
	//printf("please input graph vertexNum ArcNum IncInfo=0 \n");
	for (int i = 0; i < G.vexnum; i++) {
		scanf_s("%d", &G.vexs[i]);//构造顶点向量
	}
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; ++j) {
			//init graph
			G.arcs[i][j] = { INFINITY,NULL };
		}
	}
		
	for (int k = 0; k < G.vexnum; k++) {
		VertexType v1, v2; VRType w;

		scanf_s("%d %d %d", &v1, &v2, &w);

		int i = LocateVex(G, v1); int j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;
		if (IncInfo) {
			scanf("%s", G.arcs[i][j].info);
		}
		G.arcs[i][j] = G.arcs[j][i];
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
	scanf("%d", &G.kind);
	switch (G.kind)
	{
	case DG:return CreateDG(G);
	case DN:return CreateDN(G);
	case UDG:return CreateUDG(G);
	case UDN:return CreateUDN(G);
	default:return ERROR;

	}
}


int main()
{
	MGraph graph;
	CreateGraph(graph);
	return OK;
}

