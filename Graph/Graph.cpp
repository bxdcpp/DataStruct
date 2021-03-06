
//参考://原文链接：https ://blog.csdn.net/Africa_South/article/details/88553068
#include "DataDefine.h"

#include <iostream>
#include <queue>
//#include <limits.h>
//#include <cmath>
#define MAX 1024

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
	//无向图
	int IncInfo; //IncInfo为0表示各个边不存储信息
	std::cin >> G.vexnum >> G.arcnum >> IncInfo;
	int i, j;
	for (i = 0; i < G.vexnum; i++) 
		std::cin >> G.vexs[i]; //输入各个顶点的数据
	for (i = 0; i < G.vexnum; i++) {
		for (j = 0; j < G.vexnum; j++) 
			G.arcs[i][j] = { MAX,NULL };
		//初始化邻接矩阵，一般是初始化为0，
		//但是这里我与前面UDN一致是为了通用一些查找函数
	}
	// 输入邻接的点来构造邻接边
	for (i = 0; i < G.arcnum; i++) {
		VertexType v1, v2;
		std::cin >> v1 >> v2;
		int index1 = LocateVex(G, v1);
		int index2 = LocateVex(G, v2);
		G.arcs[index1][index2].adj = 1; // 1表示邻接
		if (IncInfo) std::cin >> *G.arcs[index1][index2].info;
		G.arcs[index2][index1] = G.arcs[index1][index2];  // 无向图对称构造
	}
	return OK;
}

status CreateUDN(MGraph& G)
{
	//无向网（无向带权图）
	int IncInfo;//IncInfo=0,则弧不含有信息
	std::cout << ("please input graph vertexNum ArcNum IncInfo=0 \n");
	std::cin >> G.vexnum >> G.arcnum >> IncInfo;
	//printf("please input graph vertexNum ArcNum IncInfo=0 \n");
	for (int i = 0; i < G.vexnum; i++) {
		std::cin >> G.vexs[i];//构造顶点向量
	}
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; ++j) {
			//init graph
			G.arcs[i][j] = { MAX,NULL };
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
		std::cout << "G.arcs[" << i << "][" << j << "]" << "," << G.arcs[i][j].adj << std::endl;
	}
	return OK;
}

status CreateGraph(MGraph& G)
{
	//采用数组(邻接矩阵)表示法
	G.kind = UDN;
	switch (G.kind)
	{
	case DG:return CreateDG(G);
	case DN:return CreateDN(G);
	case UDG:return CreateUDG(G);//无向图
	case UDN:return CreateUDN(G);//无向网（无向带权图）
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
		if (G.arcs[index][i].adj != MAX)
			break;
		i++;
	}
	if (i == G.vexnum) return -1;

	return i;
}

// 返回G中顶点v相对于u的下一邻接点
int NextAdjVex(MGraph G, VertexType v, VertexType u) {
	int indexV = LocateVex(G, v);
	int indexU = LocateVex(G, u);
	int index;
	for (index = indexU + 1; index < G.vexnum && G.arcs[indexV][index].adj == MAX; index++);
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

// 从图中第v个顶点开始进行深度优先遍历
void DFS(MGraph G, int v, int* visited) {
	visited[v] = 1; //先访问顶点v
	std::cout << G.vexs[v] << " ";
	for (int w = FirstAdjVex(G, G.vexs[v]); w >= 0; w = NextAdjVex(G, G.vexs[v], G.vexs[w])) {
		if (!visited[w])
			DFS(G, w, visited); // 对v的尚未访问的邻接顶点w递归调用DFS
	}
}

// 图的深度优先遍历
void DFSTraverse(MGraph G) {
	int* visited = new int[G.vexnum]; // 访问标志数组
	for (int i = 0; i < G.vexnum; i++) visited[i] = 0; // 初始化未被访问
	for (int i = 0; i < G.vexnum; i++) {
		if (!visited[i])
			DFS(G, i, visited); // 对尚未访问的顶点i调用DFS，
											 // 因为图G可能不是连通图
	}
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

//普里姆算法
struct {
	VertexType adjvex;
	VRType lowcost;
}closedge[MAX_VERTEX_NUM];

int minmum(MGraph G) 
{

	int min = MAX;
	int index = -1;
	for (int i = 0; i < G.vexnum; ++i) {
		//最小值大于 该边的权值 且 该边的权值不为 0
		if (min > closedge[i].lowcost && closedge[i].lowcost != 0) {
			min = closedge[i].lowcost;
			index = i;
		}
	}
	return index;
}


//思想：（贪心算法） 时间复杂度：O(n*n)
//使用辅助数组closedge{顶点，权值}
//从当前节点写入到各个顶点的信息，已经访问过的lowcost = 0;
//不断的求得当前到达下一个节点的最小边

void MiniSpanTree_PRIM(MGraph G, VertexType u) 
{
	//书本P174表格
	int k = LocateVex(G, u);//该顶点位置      k=0

	for (int j = 0; j < G.vexnum; ++j)//辅助数组初始化
		if (j != k)//相当于u顶点 边的信息
			closedge[j] = { u,G.arcs[k][j].adj };//{adjvex,lowcost}

	closedge[k].lowcost = 0;//初始，U={u}，把u并入集合

	for (int i = 1; i < G.vexnum; ++i) 
	{//选择其余G.vexnum-1个顶点
		k = minmum(G);    //求出T的下一个结点，第k顶点
		printf("%c-->%c\n", closedge[k].adjvex, G.vexs[k]);//输出 生成树边
		closedge[k].lowcost = 0;//第k顶点并入U集

		for (int j = 0; j < G.vexnum; ++j)
			if (G.arcs[k][j].adj < closedge[j].lowcost)
				//新顶点并入U后重新选择最小边
				closedge[j] = { G.vexs[k],G.arcs[k][j].adj };
	}
}


//最短路径，迪杰斯特拉算法
typedef int Patharc[MAX_VERTEX_NUM];//用于存储最短路径下标的数组
typedef int ShortPathTable[MAX_VERTEX_NUM];//用于存储到各点最短路径的权值和

void ShortestPath_DIJ(MGraph G, int V0, Patharc& P, ShortPathTable& D) {
	int v, w, min, k = NULL;
	int final[MAX_VERTEX_NUM];  //final[w]=1 表示已经求得顶点V0到Vw的最短路径

	//初始化数据
	for (v = 0; v < G.vexnum; v++) {
		final[v] = 0;             //全部顶点初始化为未找到最短路径
		D[v] = G.arcs[V0][v].adj; //将与V0点有连线的顶点加上权值
		P[v] = 0;                 //初始化路径数组P为0
	}

	D[V0] = 0;    //V0至V0路径为0
	final[V0] = 1;//V0至V0不需要求路径

	//开始主循环，每次求得V0到某个v顶点的最短路径
	for (v = 1; v < G.vexnum; v++) {
		min = MAX;
		//循环后得到一个已知最短路径的顶点，作为发散修正的顶点
		for (w = 0; w < G.vexnum; w++)
			if (!final[w] && D[w] < min) {
				k = w;
				min = D[w];
			}
		final[k] = 1; //将目前找到的最近的顶点置1
		//修正当前最短路径 及距离
		//从该顶点发散出去的各个顶点距离修正
		for (w = 0; w < G.vexnum; w++)
			//如果经过v顶点的路径比现在这条路径的长度短的话，更新
			if (!final[w] && (min + G.arcs[k][w].adj < D[w])) {
				D[w] = min + G.arcs[k][w].adj;//修改当前路径长度
				P[w] = k;     //存放前驱顶点
			}

	}
}


//最短路径，佛洛依德算法
//本质就是动态规划
//时间复杂度 n*n*n
typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int DistancMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

void ShortestPath_FLOYD(MGraph G, PathMatrix& P, DistancMatrix& D) 
{
	int v, w, k;
	//初始化D和P
	for (v = 0; v < G.vexnum; v++)
		for (w = 0; w < G.vexnum; w++)
		{
			D[v][w] = G.arcs[v][w].adj;
			P[v][w] = -1;
		}

	//算法核心
	for (k = 0; k < G.vexnum; k++)
		for (v = 0; v < G.vexnum; v++)
			for (w = 0; w < G.vexnum; w++)
				if (D[v][w] > D[v][k] + D[k][w])
				{
					D[v][w] = D[v][k] + D[k][w];
					P[v][w] = P[v][k];
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
		V6 V7

		8 9 0
		A B C D E F G H
		A B
		A C
		A D
		B D
		B E
		C F
		C G
		D H
		E H
		F G
		
		*/


	MGraph graph;
	CreateGraph(graph);
	showMatrix(graph);
	std::cout << "\nBFS：\n";
	BFSTraverse(graph);
	std::cout << "\nDFS："<<std::endl;
	DFSTraverse(graph);
	std::cout << std::endl;
	std::cout << "prim：" << std::endl;
	MiniSpanTree_PRIM(graph, 'A');

	Patharc p; ShortPathTable dis;
	std::cout << "ShortestPath_DIJ：" << std::endl;
	ShortestPath_DIJ(graph, 0, p, dis);

	for (int i = 0; i < graph.vexnum; i++)
	{
		std::cout << dis[i] <<" "<<std::endl;
	}

	return OK;
}

