#pragma once

#include <map>
#include <cstdlib>


class SString
{
public:
	SString() {
		init(0);
	}


	~SString() {
		del();
	}


	SString(const char* str) {
		size_t len = strlen(str);
		char* data = new char[len + 1];
		memcpy(data, str, len);
		data[len] = 0;
		init(data);
	}


	SString(const SString& str) {
		init(str._data);
	}

	SString(SString&& str) {
		init(str._data);
	}


	SString operator + (const SString& other) {
		char* new_data = new char[_size + other._size + 1];
		memcpy(new_data, _data, _size);
		memcpy(new_data+_size, other._data, other._size);
		new_data[_size + other._size] = 0;
		del();
		init(new_data);
	}

	SString& operator = (const SString& other) {
		init(other._data);
	}

private:
	static std::map<char*, size_t> _links; 

	void del() {
		if (_data) {
			_links[_data]--;
			if (_links[_data] <= 0) {
				delete[] _data;
			}
		}
		_size = 0;
	}

	void init(char* data) {
		_data = data;
		if(_data) {
			if(_links[_data])
				_links[_data]++;
			else
				_links[_data] = 1;
			_size = strlen(data);
		} else {
			_size = 0;
		}
	}


	char* _data;
	size_t _size;
};