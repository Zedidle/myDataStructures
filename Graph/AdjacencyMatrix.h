#include "iostream"
using namespace std;
#include "vector"



#define MAXVEX 100
#define INFINITY 65535
typedef int VertexType;
typedef int EdgeType;

namespace AdjacencyMatrix {
	
	// 邻接矩阵
	void Test() {
		cout << "无向图：" << endl;
		// 无向图
		vector<vector<int>> matrix_nodir = {
			{0, 1, 1, 1},
			{1, 0, 1, 0},
			{1, 1, 0, 1},
			{1, 0, 1, 0}
		};
		for (int i = 0; i < matrix_nodir.size(); i++) {
			int num = 0;
			for (auto n : matrix_nodir[i]) {
				if(n) num++;
			}
			cout << i << "的度：" << num << endl;
		}
		cout << endl;


		cout << "有向图：" << endl; 
		// 有向图
		vector<vector<int>> matrix_dir = {
			{0, 0, 0, 1},
			{1, 0, 1, 0},
			{1, 1, 0, 0},
			{0, 0, 0, 0}
		};
		int n = matrix_dir.size();
		for (int i = 0; i < n; i++) {
			int num_out=0, num_in=0;
			for (int j = 0; j < n; j++) {
				if (matrix_dir[i][j]) num_out++;
				if (matrix_dir[j][i]) num_in++;
			}
			cout << i << "的出度, 入度：" << num_out << ", " << num_in << endl;
		}
		cout << endl;

		cout << "网图：" << endl;
		vector<vector<int>> matrix_power = {
			{0, -1, -1, -1, 6},
			{9, 0, 3, -1, -1},
			{2, -1, 0, 5, -1},
			{-1, -1, -1, 0, 1},
			{-1, -1, -1, -1, 0},
		};
	}


	// 无向图建立邻接表
	void Test1() {
		struct EdgeNode {  // 边表结点
			int adjvex; 
			EdgeType weight; // 对于网图有需要weight
			EdgeNode* next = nullptr;
		};

		typedef struct{	 // 顶点表结点
			VertexType data;
			EdgeNode *firstedge;
		} VertexNode, AdjList[MAXVEX];

		struct GraphAdjList {
			AdjList adjList;
			int numVertexes, numEdges;

			void Show() {
				for (int i = 0; i < numVertexes; i++) {
					EdgeNode* n = adjList[i].firstedge;
					while (n != nullptr) {
						cout << "边："<< i << "-" << n->adjvex << endl;
						n = n->next;
					}
				}
			}
		};

		GraphAdjList* G = new GraphAdjList;
		int i, j, k, weight;
		EdgeNode* e;
		cout << "输入顶点数和边数：" << endl;
		cin >> G->numVertexes >> G->numEdges;
		cout << "顶点数: " << G->numVertexes << "  边数: " << G->numEdges << endl;
		cout << "输入顶点信息：" << endl;
		for (i = 0; i < G->numVertexes; i++) {
			cin >> G->adjList[i].data;
			G->adjList[i].firstedge = NULL;
		}
		cout << endl << "头插法 建立边表：" << endl;
		for (k = 0; k < G->numEdges; k++) {
			cout << "输入边（vi, vj) 上的顶点序号：" << endl;
			cin >>i>>j;
			//cin >>i>>j>>weight; // 对于网图有需要weight
			e = (EdgeNode*) malloc(sizeof(EdgeNode));
			e->adjvex = j;
			e->next = G->adjList[i].firstedge;
			G->adjList[i].firstedge = e;
			

			// 对于有向图，则不需要下面这部分了
			e = (EdgeNode*) malloc(sizeof(EdgeNode));
			e->adjvex = i;
			e->next = G->adjList[j].firstedge;
			G->adjList[j].firstedge = e;
		}

		G->Show();
	}



	// (有向图) 十字链表的创建
	void Test2() {
		cout << "(有向图) 十字链表的创建 : " << endl;


		struct EdgeNode {  // 边表结点
			int tailvex;
			int headvex;
			EdgeNode* headlink = nullptr;
			EdgeNode* taillink = nullptr;
		};

		typedef struct{	 // 顶点表结点
			VertexType data;
			EdgeNode* firstin = nullptr;
			EdgeNode* firstout = nullptr;
		} VertexNode, AdjList[MAXVEX];

		struct GraphAdjList {
			AdjList adjList;
			int numVertexes, numEdges;

			void Show() {
				EdgeNode* n = nullptr;
				for (int i = 0; i < numVertexes; i++) {
					cout << endl << "i:" << i << endl;
					n = adjList[i].firstout;
					cout << "Out: " << endl;
					while (n != nullptr) {
						cout << "tail - head：" << n->tailvex << "-" << n->headvex << endl;
						n = n->taillink;
					}
					n = adjList[i].firstin;
					cout << "In: " << endl;
					while (n != nullptr) {
						cout << "tail - head：" << n->tailvex << "-" << n->headvex << endl;
						n = n->headlink;
					}
				}
				n = NULL;
				delete n;
			}
		};

		GraphAdjList* G = new GraphAdjList;
		int i, j, k;
		EdgeNode* e;
		cout << "输入顶点数和边数：" << endl;
		//cin >> G->numVertexes >> G->numEdges;
		G->numVertexes = 4; G->numEdges = 5;
		cout << "顶点数: " << G->numVertexes << "  边数: " << G->numEdges << endl;

		cout << "输入顶点信息：" << endl;
		for (i = 0; i < G->numVertexes; i++) {
			//cin >> G->adjList[i].data;
			G->adjList[i].data = i;
		}

		cout << endl << "头插法 建立边表：" << endl;
		vector<pair<int, int>> Edges = {{0, 3}, {1, 0}, {1, 2}, {2, 1}, {2, 0}};
		for (k = 0; k < G->numEdges; k++) {
			//cout << "输入弧（vi, vj) 尾-头 的顶点序号：" << endl;
			//cin >> i >> j;
			i = Edges[k].first;
			j = Edges[k].second;
			e = (EdgeNode*)malloc(sizeof(EdgeNode));
			e->tailvex = i;
			e->headvex = j;

			// 关键在于同时建立一个顶点的入度与出度边
			// 入度链表 与 出度链表 互不干扰

			// 出度边
			e->taillink = G->adjList[i].firstout;
			G->adjList[i].firstout = e;

			// 入度边
			e->headlink = G->adjList[j].firstin;
			G->adjList[j].firstin = e;
		}

		G->Show();
	}



	// (无向图)邻接多重表
	void Test3() {
		
		struct EdgeNode {  // 边表结点
			EdgeNode(int i, int j): ivex(i), jvex(j){}
			int ivex = -1;
			EdgeNode* ilink = nullptr;
			int jvex = -1;
			EdgeNode* jlink = nullptr;
		};

		typedef struct {	 // 顶点表结点
			VertexType data;
			EdgeNode* firstedge = nullptr;
		} VertexNode, AdjList[MAXVEX];

		struct AdjacencyMultiTable {
			AdjList adjList;
			vector<EdgeNode*> eNodes;
			int numVertexes, numEdges;

			void Show() {
				for (int i = 0; i < numVertexes; i++) {
					cout << endl<<"i:" << i << endl;
					EdgeNode* n = adjList[i].firstedge;
					while (n) {
						cout << "p - p:" << n->ivex << "-" << n->jvex << endl;
						if (i == n->ivex) {
							n = n->ilink;
						}else if (i == n->jvex) {
							n = n->jlink;
						}
					}
				}
			}

			void MakeLinks() {
				vector<bool> marks(numEdges, false);
				EdgeNode** e = nullptr;
				for (int i = 0; i < numVertexes; i++) {
					marks = vector<bool>(numEdges, false);
					int value = adjList[i].data; // 测试的话 value = i;
					// 双重指针真的太帅了
					e = &(adjList[i].firstedge); // 将 adjList[i].firstedge 指针的地址给到 e;
					for(int j=0;j<numEdges;j++){
						if (eNodes[j]->ivex == value) {
							*e = eNodes[j]; // 改变 adjList[i].firstedge 指向的地址为 eNodes[j] 的地址;
							e = &(eNodes[j]->ilink); // 将 eNodes[j]->ilink 的地址给到 e;
							marks[j] = true;
						}else if (eNodes[j]->jvex == value) { // else if 是因为前者为真时，后者绝对不会触发，所以加上else 用作提醒，当跑通前者时，可以少看一个判断
							*e = eNodes[j];
							e = &(eNodes[j]->jlink);
							marks[j] = true;
						}
					}
				}
				e = nullptr;
				delete e;
			}
		};
		AdjacencyMultiTable* G = new AdjacencyMultiTable;
		G->numVertexes = 4, G->numEdges = 5;
		int i, j, k;
		EdgeNode* e;

		for (int i = 0; i < G->numVertexes; i++) {
			G->adjList[i].data = i;
		}


		// 由于是无向图，方向顺序都无所谓
		//vector<pair<int, int>> Edges = { {0, 1}, {1, 2}, {2, 3}, {3, 0}, {0, 2} };
		//vector<pair<int, int>> Edges = { {0, 1}, {0, 2}, {1, 2}, {2, 3}, {3, 0} };
		vector<pair<int, int>> Edges = { {0, 1}, {0, 2}, {0, 3}, {1, 2}, {2, 3} };

		for (int i = 0; i < G->numEdges; i++) {
			//cout << Edges[i].first << ", " << Edges[i].second << endl;
			G->eNodes.push_back(new EdgeNode(Edges[i].first, Edges[i].second));
		}
	
		G->MakeLinks();
		G->Show();
	}



	// ============================================================
	// 普利姆算法
	void Test4() {
		vector<vector<int>> G = {
			{0, 10, -1, -1, -1, 11, -1, -1, -1},
			{10, 0, 18, -1, -1, -1, 16, -1, 12},
			{-1, 18, 0, 22, -1, -1, -1, -1, 8},
			{-1, -1, 22, 0, 20, -1, -1, 16, 21},
			{-1, -1, -1, 20, 0, 26, -1, 7, -1},
			{11, -1, -1, -1, 26, 0, 17, -1, -1},
			{-1, 16, -1, -1, -1, 17, 0, 19, -1},
			{-1, -1, -1, 16, 7, -1, 19, 0, -1},
			{-1, 12, 8, 21, -1, -1, -1, -1, 0}
		};
		
		struct EdgeNode {
			EdgeNode(int i, int j, int power): i(i), j(j), power(power){}
			int i;
			int j;
			int power;
		};

		int n = G.size();
		vector<EdgeNode*> edges;
		vector<EdgeNode*> ans;
		vector<bool> record(n, false);

		int i = 0, j;
		while(true){
			// 以第0个点开始作为扩充
			for (j = 0; j < n; j++) {
				if (G[i][j] > 0) {
					edges.push_back(new EdgeNode(i, j, G[i][j]));
				}
			}
			sort(edges.begin(), edges.end(), [](EdgeNode* a, EdgeNode* b){
				return a->power < b->power;
			});

			EdgeNode* e = nullptr;
			while (edges.size()) {
				e = edges.front();
				edges.erase(edges.begin(), edges.begin() + 1);
				if (!record[e->j]) {  // 第 e->j 位置的点并没有加入结果集
					ans.push_back(e);
					record[e->i] = record[e->j] = true;  // 将处于 e->i 和 e->j 位置的点加入结果集
					i = e->j; // 将链接的下一个点，作为扩充点
					break;
				}
			}

			e = nullptr;
			delete e;
			if (ans.size() == n-1) break;
		}

		int totalpower = 0;
		for (auto e : ans) {
			cout << e->i << ", " << e->j << ", power:" << e->power <<endl;
			totalpower += e->power;
		}
		cout << totalpower << endl;
	}


	// ============================================================
	// 克鲁斯卡尔算法
	int FindParent(const vector<int>& parent, int f) {
		while (parent[f] > 0) {
			f = parent[f];
		}
		return f;
	}
	void Test5() {
		vector<vector<int>> G = {
			{0, 10, -1, -1, -1, 11, -1, -1, -1},
			{10, 0, 18, -1, -1, -1, 16, -1, 12},
			{-1, 18, 0, 22, -1, -1, -1, -1, 8},
			{-1, -1, 22, 0, 20, -1, -1, 16, 21},
			{-1, -1, -1, 20, 0, 26, -1, 7, -1},
			{11, -1, -1, -1, 26, 0, 17, -1, -1},
			{-1, 16, -1, -1, -1, 17, 0, 19, -1},
			{-1, -1, -1, 16, 7, -1, 19, 0, -1},
			{-1, 12, 8, 21, -1, -1, -1, -1, 0}
		};
		struct EdgeNode {
			EdgeNode(int i, int j, int power) : begin(i), end(j), power(power) {}
			EdgeNode* parent;
			int begin;
			int end;
			int power;
		};
		vector<EdgeNode*> edges;
		vector<EdgeNode*> ans;
		vector<int> parent(MAXVEX);

		int len = G.size();
		for (int i = 0; i < len; i++) {
			// 以第0个点开始作为扩充
			for (int j = i+1; j < len; j++) {
				if (G[i][j] > 0) {
					edges.push_back(new EdgeNode(i, j, G[i][j]));
				}
			}
		}
		sort(edges.begin(), edges.end(), [](EdgeNode* a, EdgeNode* b){
			return a->power < b->power;
		});

		int numEdges = edges.size();
		cout << "numEdges: " << numEdges << endl;

		for (int i = 0; i < len; i++) {
			parent[i] = 0;
		}

		// beautiful
		int n, m;
		int total = 0;
		for (int i = 0; i < numEdges; i++) {
			n = FindParent(parent, edges[i]->begin);
			m = FindParent(parent, edges[i]->end);
			if (n != m) {
				parent[n] = m;
				printf("(%d, %d) %d ", edges[i]->begin, edges[i]->end, edges[i]->power);
				total += edges[i]->power;
			}
		}
		cout << "total: " << total << endl;
	}



	// ============================================
	// 最短路径

	vector<vector<int>> Gra = {
		{0, 1, 5, -1, -1, -1, -1, -1, -1},
		{1, 0, 3, 7, 5, -1, -1, -1, -1},
		{5, 3, 0, -1, 1, 7, -1, -1, -1},
		{-1, 7, -1, 0, 2, -1, 3, -1, -1},
		{-1, 5, 1, 2, 0, 3, 6, 9, -1},
		{-1, -1, 7, -1, 3, 0, -1, 5, -1},
		{-1, -1, -1, 3, 6, -1, 0, 2, 7},
		{-1, -1, -1, -1, 9, 5, 2, 0, 4},
		{-1, -1, -1, -1, -1, -1, 7, 4, 0}
	};

	// 迪杰斯特拉算法
	typedef vector<int> Pathmatrix, ShortPathTable;
	#define MAXVEX 9
	struct MGraph {
		MGraph(const vector<vector<int>> &Gra){
			numVertexes = Gra.size();
			matirx = Gra;
			for (auto &g : matirx) {
				for (int& i : g) {
					if(i == -1) i = INFINITY;
				}
			}
		}
		int numVertexes;
		vector<vector<int>> matirx;
	};

	void My_Dijkstra(MGraph G, int v0, Pathmatrix& P, ShortPathTable& D) {
		vector<vector<int>> Gra = G.matirx;
		int len = Gra.size();
		vector<bool> F(len, false);
		int v, k, w, m;
		// 初始化
		for (v = 0; v < len; v++) {
			D[v] = Gra[v0][v];
			P[v] = v0;
		}
		F[v0] = true;


		// 大循环
		for (v = 1; v < len; v++) {
			// 小循环1：确定当前最短边及其下标
			m = INFINITY;
			for (w = 0; w < len; w++) {
				if (!F[w] && D[w] < m) {
					m = D[w];
					k = w;
				}
			}
			F[k] = true;
			// 小循环2：刷新起点到所有点的最短距离及前驱
			for (w = 0; w < len; w++) {
				if (!F[w] && (m + Gra[k][w] < D[w])) {
					D[w] = m+Gra[k][w];
					P[w] = k;
				}
			}
		}
	}


	void Test6() {


		MGraph G(Gra);
		Pathmatrix P(MAXVEX);
		ShortPathTable D(MAXVEX);
		int end = 8, start = 0;
		My_Dijkstra(G, start, P, D);
		cout << endl;
		cout << endl;
		cout << "到达 i位置的前一个位置：" << endl;
		for (int i = 0; i < P.size(); i++) {
			cout << i << ":" << P[i] << "  ";
		}
		string ans = "";
		int cur = end;
		while (cur!=start) {
			ans = "->" + to_string(cur) + ans;
			cur = P[cur];
		}
		cout << endl << "ans: " << to_string(start) + ans <<endl;

		cout << endl;
		cout << "起点到每个点的最短距离：" << endl;
		for (int i = 0; i < D.size(); i++) {
			cout << D[i] << " ";
		}
		cout << endl;
	}



	typedef vector<vector<int>> Pathmatrix2, ShortPathTable2;

	void My_Floyd(MGraph G) {
		int v, w, k;
		Pathmatrix2 D = G.matirx;
		vector<int> p(D.size());
		for (int i = 0; i < D.size(); i++) {
			p[i] = i; // 意思是自己到达自己，自己的前驱就是自己
		}
		ShortPathTable2 P(G.numVertexes, p);
		for (k = 0; k < G.numVertexes; ++k) {
			for (v = 0; v < G.numVertexes; ++v) {
				for (w = 0; w < G.numVertexes; ++w) {
					if (D[v][w] > D[v][k] + D[k][w]) {
						D[v][w] = D[v][k] + D[k][w];
						P[v][w] = P[v][k]; // 前驱的改变由此时最短路径决定
					}
				}
			}
		}

		cout <<endl;
		for (v = 0; v < G.numVertexes; ++v) {
			for (w = 0; w < G.numVertexes; w++) {
				cout << P[v][w] <<" ";
			}
			cout << endl;
		}
		cout <<endl;

		// 显示
		for (v = 0; v < G.numVertexes; ++v) {
			for (w = v + 1; w < G.numVertexes; w++) {
				printf("v%d-v%d weight: %d ", v, w, D[v][w]);
				k=P[v][w];
				printf(" path: %d", v);
				while (k != w) {
					printf(" -> %d", k);
					k = P[k][w];
				}
				printf(" -> %d\n", w);
			}
			printf("\n");
		}
	}

	// 弗洛伊德算法
	void Test7() {
		MGraph G(Gra);
		My_Floyd(G);
	}
}
