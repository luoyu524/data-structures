#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<queue>
#include"UnionFindSet.h"
using namespace std;

// 邻接矩阵 图
namespace Matrix
{
	// V顶点类型 W边权值类型 MAX_W表示边不存在的值 Direction表示图是否有向
	template<class V, class W, W MAX_W = INT_MAX, bool Direction = false>
	class Graph
	{
	public:

		Graph(const V* vertexs, size_t n)
		{
			_vertexs.reserve(n);
			for (size_t i = 0; i < n; ++i)
			{
				_vertexs.push_back(vertexs[i]);
				_vIndexMap[vertexs[i]] = i;
			}

			// MAX_W 作为不存在边的标识值
			// 初始化时默认没有边，边需要一条一条手动添加，用AddEdge函数
			_matrix.resize(n);
			for (auto& e : _matrix)
			{
				e.resize(n, MAX_W);
			}
		}

		// 找到一个顶点的映射下标
		size_t GetVertexIndex(const V& v)
		{
			auto ret = _vIndexMap.find(v);
			if (ret != _vIndexMap.end())
			{
				return ret->second;
			}
			else
			{
				throw invalid_argument("不存在的顶点");
				return -1;
			}
		}

		// 添加一条边，src和dst代表两端顶点，w是权值
		void AddEdge(const V& src, const V& dst, const W& w)
		{
			size_t srci = GetVertexIndex(src);
			size_t dsti = GetVertexIndex(dst);

			_matrix[srci][dsti] = w;
			//如果是无向图，则[dsti][srci]也需添加边
			if (Direction == false)
			{
				_matrix[dsti][srci] = w;
			}
		}

		// 参数是遍历的起始顶点
		void BFS(const V& src)
		{
			// 得到起始顶点的下标
			size_t srcindex = GetVertexIndex(src);
			// 防止一个顶点被多次遍历，用一个数组标记被遍历过的下标
			vector<bool> visited;
			visited.resize(_vertexs.size(), false);

			// 起点入队列
			queue<int> q;
			q.push(srcindex);
			visited[srcindex] = true;

			cout << "BFS遍历: ";
			while (!q.empty())
			{
				size_t front = q.front();
				// 打印出当前遍历顶点
				cout << _vertexs[front] << ' ';

				// 队头元素出队列
				q.pop();

				// 队头元素顶点所有没遍历过的相邻顶点入队列，在领接矩阵中查询相邻顶点
				for (size_t i = 0; i < _vertexs.size(); ++i)
				{
					if (visited[i] == false && _matrix[front][i] != MAX_W)
					{
						// 遍历过的顶点标记为true
						visited[i] = true;
						q.push(i);
					}
				}
				
			}

			// 如果该图不是连通图，这种方法会使某些顶点没遍历到
			for (bool check : visited)
			{
				if (check == false)
				{
					cout << "该图不是连通图，还有未遍历到的顶点";
				}
			}
			cout << endl;
		}


		void _DFS(size_t srcIndex, vector<bool>& visited)
		{
			// 当前遍历顶点
			cout << _vertexs[srcIndex] << ' ';
			visited[srcIndex] = true;

			// 找srcIndex的相邻顶点，遍历下去
			for (size_t i = 0; i < _vertexs.size(); ++i)
			{
				if (visited[i] == false && _matrix[srcIndex][i] != MAX_W)
				{
					_DFS(i, visited);
				}
			}
		}

		void DFS(const V& src)
		{
			// 得到起始顶点的下标
			size_t srcindex = GetVertexIndex(src);

			// 防止一个顶点被多次遍历，用一个数组标记被遍历过的下标
			vector<bool> visited;
			visited.resize(_vertexs.size(), false);

			cout << "DFS遍历: ";
			_DFS(srcindex, visited);
			cout << endl;
		}

		typedef Graph<V, W, MAX_W, Direction> Self;
		struct Edge
		{
			V _srci;
			V _dsti;
			W _w;

			Edge(const V& srci, const V& dsti, const W& w)
				:_srci(srci)
				, _dsti(dsti)
				, _w(w)
			{ }

			bool operator<(const Edge& eg) const
			{
				return _w < eg._w;
			}

			bool operator>(const Edge& eg) const
			{
				return _w > eg._w;
			}
		};

		Graph() = default;

		// 传递一个图，作为构造最小生成树的结果。返回总权值
		W Kruskal(Self& minTree)
		{
			// 所有顶点拷贝，初始不带任何边
			minTree._vertexs = _vertexs;
			minTree._vIndexMap = _vIndexMap;
			minTree._matrix.resize(_vertexs.size());
			for (auto& e : minTree._matrix)
			{
				e.resize(_vertexs.size(), MAX_W);
			}

			// priority_queue用于按照权值排序边
			priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
			for (size_t i = 0; i < _matrix.size(); ++i)
			{
				for (size_t j = 0; j < _matrix[i].size(); ++j)
				{
					// 无向图，只要判断领接矩阵一半的边
					if (i < j && _matrix[i][j] != MAX_W)
					{
						pq.push(Edge(i, j, _matrix[i][j]));
					}
				}
			}

			// 记录总权值
			W total = W();

			// 贪心算法，从最小的边开始选，将选出的边两端顶点放入一个集合
			// size记录已选出边数
			int size = 0;

			UnionFindSet ufs(_vertexs.size());

			while (!pq.empty())
			{
				Edge min = pq.top();
				pq.pop();
				// 边两端顶点不在一个集合，说明不会构成环，则添加这条边到最小生成树，两个顶点放到一个集合
				if (ufs.FindRoot(min._srci) != ufs.FindRoot(min._dsti))
				{
					minTree.AddEdge(min._srci, min._dsti, min._w);
					total += min._w;
					size++;

					ufs.Union(min._srci, min._dsti);
				}
			}

			// 若size不等于n-1，说明构建最小生成树失败，返回一个默认值W()
			if (size == _vertexs.size() - 1)
			{
				return total;
			}
			else
			{
				return W();
			}
		}

		// 给一个起点
		W Prim(Self& minTree, const V& src)
		{
			size_t srci = GetVertexIndex(src);
			size_t n = _vertexs.size();

			minTree._vertexs = _vertexs;
			minTree._vIndexMap = _vIndexMap;
			minTree._matrix.resize(n);
			for (size_t i = 0; i < n; ++i)
			{
				minTree._matrix[i].resize(n, MAX_W);
			}

			// X和Y集合
			vector<bool> X(n, false);
			vector<bool> Y(n, true);
			X[srci] = true;
			Y[srci] = false;

			// 从X->Y集合中连接的边里面选出最小的边
			priority_queue<Edge, vector<Edge>, greater<Edge>> minq;
			// 先把srci连接的边添加到队列中
			for (size_t i = 0; i < n; ++i)
			{
				if (_matrix[srci][i] != MAX_W)
				{
					minq.push(Edge(srci, i, _matrix[srci][i]));
				}
			}

			size_t size = 0;
			W total = W();

			while (!minq.empty())
			{
				Edge min = minq.top();
				minq.pop();

				if (!X[min._dsti])
				{
					minTree.AddEdge(min._srci, min._dsti, min._w);
					
					X[min._dsti] = true;
					Y[min._dsti] = false;
					++size;
					total += min._w;
					if (size == n - 1)
						break;

					for (size_t i = 0; i < n; ++i)
					{
						if (_matrix[min._dsti][i] != MAX_W && Y[i])
						{
							minq.push(Edge(min._dsti, i, _matrix[min._dsti][i]));
						}
					}
				}
			}

			if (size == n - 1)
			{
				return total;
			}
			else
			{
				return W();
			}
		}

	private:
		map<V, size_t> _vIndexMap;   // 每个顶点映射一个下标
		vector<V> _vertexs;			 // 顶点集合
		vector<vector<W>> _matrix;   // 领接矩阵 存储边
	};

}




// 临接表
namespace LinkTable
{
	// 定义边结构, W是权值类型
	template<class W>
	struct LinkEdge
	{
		int _srcIndex;
		int _dstIndex;
		W _w;
		LinkEdge<W>* _next;

		LinkEdge(const W& w)
			: _srcIndex(-1)
			, _dstIndex(-1)
			, _w(w)
			, _next(nullptr)
		{ }
	};

	template<class V, class W, bool Direction = false>
	class Graph
	{
		typedef LinkEdge<W> Edge;
	public:

		Graph(const V* vertexs, size_t n)
		{
			_vertexs.reserve(n);
			for (size_t i = 0; i < n; ++i)
			{
				_vertexs.push_back(vertexs[i]);
				_vIndexMap[vertexs[i]] = i;
			}

			_linkTable.resize(n, nullptr);
		}

		size_t GetVertexIndex(const V& v)
		{
			auto ret = _vIndexMap.find(v);
			if (ret != _vIndexMap.end())
			{
				return ret->second;
			}
			else
			{
				throw invalid_argument("不存在的顶点");
				return -1;
			}
		}

		// 添加边
		void AddEdge(const V& src, const V& dst, const W& w)
		{
			size_t srcindex = GetVertexIndex(src);
			size_t dstindex = GetVertexIndex(dst);

			Edge* sd_edge = new Edge(w);
			sd_edge->_srcIndex = srcindex;
			sd_edge->_dstIndex = dstindex;
			sd_edge->_next = _linkTable[srcindex];
			_linkTable[srcindex] = sd_edge;

			// 如果是无向图，还要反过来添加一次
			if (Direction == false)
			{
				Edge* ds_edge = new Edge(w);
				ds_edge->_srcIndex = dstindex;
				ds_edge->_dstIndex = srcindex;
				ds_edge->_next = _linkTable[dstindex];
				_linkTable[dstindex] = ds_edge;
			}
		}


	private:
		map<string, int> _vIndexMap; // 顶点到下标的映射
		vector<V> _vertexs;			 // 顶点集合
		vector<Edge*> _linkTable;    // 边的集合的领接表
	};

}