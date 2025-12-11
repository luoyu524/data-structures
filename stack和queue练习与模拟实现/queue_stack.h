#pragma once
#include<deque>
#include<list>
#include<vector>
using namespace std;

template<class T, class Container = deque<T>>
class queue
{
private:
	Container _con;

public:
	void push(const T& x)
	{
		_con.push_back(x);
	}

	void pop()
	{
		_con.pop_front();
	}

	T& front()
	{
		return _con.front();
	}

	const T& front() const
	{
		return _con.front();
	}

	T& back()
	{
		return _con.back();
	}

	const T& back() const
	{
		return _con.back();
	}

	bool empty() const
	{
		return _con.empty();
	}

	size_t size() const
	{
		return _con.size();
	}
};


template<class T, class Container = deque<T>>
class stack
{
private:
	Container _con;

public:
	void push(const T& x)
	{
		_con.push_back(x);
	}

	void pop()
	{
		_con.pop_back();
	}

	T& top()
	{
		return _con.back();
	}

	const T& top() const
	{
		return _con.back();
	}

	bool empty() const
	{
		return _con.empty();
	}

	size_t size() const
	{
		return _con.size();
	}
};


namespace lydly
{
	
	template<class T>
	class less
	{
	public:
		bool operator()(const T& x, const T& y)
		{
			return x < y;
		}
	};

	template<class T>
	class greater
	{
	public:
		bool operator()(const T& x, const T& y)
		{
			return x > y;
		}
	};

	template<class T, class Container = vector<T>, class Compare = less<T>>
	class priority_queue
	{
	private:
		Container _con;

	public:
		priority_queue()
		{
		}

		void push(const T& x)
		{
			_con.push_back(x);
			adjustup(_con.size() - 1);
		}

		void pop()
		{
			swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			adjustdown(0);
		}

		const T& top() const
		{
			return _con[0];
		}

		bool empty() const
		{
			return _con.empty();
		}

		size_t size() const
		{
			return _con.size();
		}
	private:
		void adjustup(int child)
		{
			//构造一个less或greater的对象
			Compare com;

			int parent = (child - 1) / 2;
			while (child > 0)
			{
				if (com(_con[parent], _con[child]))
				{
					swap(_con[child], _con[parent]);

					// 
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}

		void adjustdown(size_t parent)
		{
			//构造一个less或greater的对象
			Compare com;

			size_t child = parent * 2 + 1;
			while (child < _con.size())
			{
				if (child + 1 < _con.size() && com(_con[child], _con[child + 1]))
				{
					++child;
				}

				if (com(_con[parent], _con[child]))
				{
					swap(_con[child], _con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}

	};
}