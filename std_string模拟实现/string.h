#pragma once
#include<iostream>
#include<string.h>
#include<assert.h>

namespace lydly
{
	class string
	{
	public:

		//定义常量npos
		static const size_t npos;

		//拷贝构造函数
		string(const char* str = "") //默认会在结尾加\0
			:_size(strlen(str))
		{
			_capacity = _size;
			_str = new char[_size + 1]; //+1是为了给结尾的\0留位置
			memcpy(_str, str, _size + 1);
			//不能使用strcpy，如果str中间有\0字符就会中间停止拷贝
		}

		//析构函数
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = 0;
			_capacity = 0;
		}

		const char* c_str() const
		{
			return _str;
		}


		//迭代器
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;

		size_t size() const;
		size_t capacity() const;
		char& operator[](size_t i);
		const char& operator[](size_t i) const;

		void reserve(size_t n);
		void push_back(char ch);
		void append(const char* str);
		string& operator+=(char ch);
		string& operator+=(const char* str);

		void insert(size_t pos, char ch);
		void insert(size_t pos, const char* str);
		void erase(size_t pos, size_t len = npos);
		size_t find(char ch, size_t pos = 0) const;
		size_t find(const char* str, size_t pos = 0) const;
		string substr(size_t pos = 0, size_t len = npos) const;

		bool operator<(const string& s) const;
		bool operator<=(const string& s) const;
		bool operator>(const string& s) const;
		bool operator>=(const string& s) const;
		bool operator==(const string& s) const;
		bool operator!=(const string& s) const;
		void clear();
		void swap(string& s);



	private:
		char* _str = nullptr;
		size_t _size = 0; 
		size_t _capacity = 0;

	};

	std::ostream& operator<<(std::ostream& os, const string& s);
	std::istream& operator>>(std::istream& is, string& s);
}