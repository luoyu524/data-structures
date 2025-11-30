#define _CRT_SECURE_NO_WARNINGS 1
#include"string.h"
namespace lydly
{
	const size_t string::npos = -1;

	string::iterator string::begin()
	{
		return _str;
	}

	string::iterator string::end()
	{
		return _str + _size;
	}

	string::const_iterator string::begin() const
	{
		return _str;
	}

	string::const_iterator string::end() const
	{
		return _str + _size;
	}

	size_t string::size() const
	{
		return _size;
	}

	size_t string::capacity() const
	{
		return _capacity;
	}

	char& string::operator[](size_t i)
	{
		assert(i < _size);
		return _str[i];
	}

	const char& string::operator[](size_t i) const
	{
		assert(i < _size);
		return _str[i];
	}

	void string::reserve(size_t n)
	{
		if (n > _capacity)
		{
			char* tmp = new char[n + 1];
			if (_str)
			{
				memcpy(tmp, _str, _size + 1);
				delete[] _str;
			}
			_str = tmp;
			_capacity = n;
		}
	}

	void string::push_back(char ch)
	{
		if (_size == _capacity)
		{
			reserve(_capacity == 0 ? 4 : 2 * _capacity);
		}
		_str[_size++] = ch;
		_str[_size] = '\0';
	}

	void string::append(const char* str)
	{
		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			size_t newcapacity = _size + len > 2 * _capacity ? _size + len : 2 * _capacity;
			reserve(newcapacity);
		}
		memcpy(_str + _size, str, len + 1);
		_size += len;
	}
	
	string& string::operator+=(char ch)
	{
		push_back(ch);
		return *this;
	}

	string& string::operator+=(const char* str)
	{
		append(str);
		return *this;
	}

	void string::insert(size_t pos, char ch)
	{
		assert(pos <= _size);
		if (_size == _capacity)
		{
			reserve(_capacity == 0 ? 4 : 2 * _capacity);
		}
		size_t end = _size + 1;
		while (end > pos)
		{
			_str[end] = _str[end - 1];
			end--;
		}
		_str[pos] = ch;
		_size++;
	}

	void string::insert(size_t pos, const char* str)
	{
		assert(pos <= _size);
		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			size_t newcapacity = _size + len > 2 * _capacity ? _size + len : 2 * _capacity;
			reserve(newcapacity);
		}
		size_t end = _size + len;
		while (end > pos + len - 1)
		{
			_str[end] = _str[end - len];
			end--;
		}
		for (size_t i = 0; i < len; i++)
		{
			_str[pos + i] = str[i];
		}
		_size++;
	}

	void string::erase(size_t pos, size_t len)
	{
		assert(pos < _size);
		if (len == npos || len >= _size - pos)
		{
			//后面的全删
			_str[pos] = '\0';
			_size = pos;
		}
		else
		{
			memmove(_str + pos, _str + pos + len, _size + 1 - (pos + len));
			_size -= len;
		}
	}

	size_t string::find(char ch, size_t pos) const
	{
		assert(pos < _size);
		for (size_t i = pos; i < _size; i++)
		{
			if (_str[i] == ch)
				return i;
		}
		return npos;
	}

	size_t string::find(const char* str, size_t pos) const
	{
		assert(pos < _size);
		const char* p = strstr(_str, str);
		if (p == nullptr)
		{
			return npos;
		}
		else
		{
			return p - _str;
		}
	}

	string string::substr(size_t pos, size_t len) const
	{
		assert(pos < _size);
		if (len > _size - pos)
		{
			len = _size - pos;
		}
		string ret;
		ret.reserve(len);
		for (size_t i = 0; i < len; i++)
		{
			ret += _str[pos + i];
		}
		return ret;
	}

	bool string::operator<(const string& s) const
	{
		size_t len1 = _size;
		size_t len2 = s._size;
		size_t i1 = 0, i2 = 0;
		while (i1 < len1 && i2 < len2)
		{
			if (_str[i1] < s._str[i2])
			{
				return true;
			}
			else if (_str[i1] > s._str[i2])
			{
				return false;
			}
			else
			{
				i1++;
				i2++;
			}
		}

		return i1 == len1 && i2 < len2;
	}

	bool string::operator<=(const string& s) const
	{
		return *this < s || *this == s;
	}

	bool string::operator>(const string& s) const
	{
		return !(*this <= s);
	}

	bool string::operator>=(const string& s) const
	{
		return !(*this < s);
	}

	bool string::operator==(const string& s) const
	{
		size_t len1 = _size;
		size_t len2 = s._size;
		size_t i1 = 0, i2 = 0;
		while (i1 < len1 && i2 < len2)
		{
			if (_str[i1] != s._str[i2])
			{
				return false;
			}
			else
			{
				i1++;
				i2++;
			}
		}
		return i1 == len1 && i2 == len2;
	}

	bool string::operator!=(const string& s) const
	{
		return !(*this == s);
	}

	void string::clear()
	{
		_str[0] = '\0';
		_size = 0;
	}

	void string::swap(string& s)
	{
		std::swap(_str, s._str);
		std::swap(_size, s._size);
		std::swap(_capacity, s._capacity);
	}

	std::ostream& operator<<(std::ostream& os, const string& s)
	{
		for (size_t i = 0; i < s.size(); i++)
		{
			os << s[i];
		}
		return os;
	}

	std::istream& operator>>(std::istream& is, string& s)
	{
		s.clear();
		char buff[256];
		size_t i = 0;
		char ch = is.get();
		while (ch != ' ' && ch != '\n')
		{
			buff[i++] = ch;
			ch = is.get();
			if (i == 255)
			{
				buff[i] = '\0';
				s += buff;
				i = 0;
			}
		}
		if (i > 0)
		{
			buff[i] = '\0';
			s += buff;
		}
		return is;
	}

}