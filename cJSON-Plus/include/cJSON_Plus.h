#pragma once

#include <string>
#include <ostream>
#include <map>

typedef struct cJSON cJSON;

class cJSON_Plus {
public:
	explicit cJSON_Plus();
	explicit cJSON_Plus(cJSON* json);
	cJSON_Plus(const cJSON_Plus& other);
	cJSON_Plus(cJSON_Plus&& other) noexcept;
	~cJSON_Plus();
	void insert(const char* key, const char* value);
	void insert(const char* key, const std::string& value);
	void insert(const char* key, const int& value);
	void insert(const char* key, const float& value);
	void insert(const char* key, const double& value);
	void insert(const char* key, const bool& value);
	void insert(const char* key, const std::nullptr_t&& value);
	void insert(const char* key, cJSON_Plus& value, bool copy_flag = false);
	template<class _Ty>
	void insert(const char* key, const std::map<const char*, _Ty>& value);
	template<class _Ty, unsigned int size>
	void insert(const char* key, _Ty value[size]);
	template<class _Ty>
	void insert(const char* key, std::initializer_list<_Ty> value);
	const cJSON_Plus get(const char* key) const;
	void replace(const char* key, const char* value);
	void replace(const char* key, const std::string& value);
	void replace(const char* key, const int& value);
	void replace(const char* key, const float& value);
	void replace(const char* key, const double& value);
	void replace(const char* key, const bool& value);
	void replace(const char* key, cJSON_Plus& value);
	void remove(const char* key);
	void swap(cJSON_Plus& other);
	template<class _Ty>
	static cJSON_Plus fromStdMap(const std::map<const char*, _Ty>& value);
	static cJSON_Plus fromCommonText(const char* json);
	cJSON_Plus cJSON_Plus::fromCommonText(const std::string& json);
	const char* toString() const;
	std::string toStdString() const;
	cJSON_Plus operator[](const char* key) const;
	cJSON_Plus& operator=(const char* value);
	cJSON_Plus& operator=(const std::string& value);
	cJSON_Plus& operator=(const int& value);
	cJSON_Plus& operator=(const float& value);
	cJSON_Plus& operator=(const double& value);
	cJSON_Plus& operator=(const bool& value);
	cJSON_Plus& operator=(cJSON_Plus& value);
	cJSON_Plus& operator=(cJSON_Plus&& value) noexcept;
private:
	cJSON_Plus(cJSON* json, cJSON_Plus* parent_);
	cJSON* object_;
	cJSON_Plus* parent_ = nullptr;
};

template<class _Ty>
void cJSON_Plus::insert(const char* key, const std::map<const char*, _Ty>& value)
{
	cJSON_Plus temp;
	for (auto& key_value_pair : value) {
		temp.insert(key_value_pair.first, key_value_pair.second);
	}
	insert(key, temp, true);
}

template<class _Ty, unsigned int size>
void cJSON_Plus::insert(const char* key, _Ty value[size])
{
	cJSON_Plus temp(cJSON_CreateArray());
	for (int i = 0; i < size; ++i) {
		temp.insert("", value[i]);
	}
	insert(key, temp);
}

template<class _Ty>
void cJSON_Plus::insert(const char* key, std::initializer_list<_Ty> value)
{
	cJSON_Plus temp(cJSON_CreateArray());
	for (auto& element : value) {
		temp.insert("", element);
	}
	insert(key, temp, true);
}

template<typename _Ty>
cJSON_Plus cJSON_Plus::fromStdMap(const std::map<const char*, _Ty>& value)
{
	cJSON_Plus temp;
	for (auto& key_value_pair : value) {
		temp.insert(key_value_pair.first, key_value_pair.second);
	}
	return temp;
}

static inline std::ostream& operator<<(std::ostream& os, const cJSON_Plus& value) {
	return os << value.toString();
}

static inline void swap(cJSON_Plus& _left, cJSON_Plus& _right) {
	_left.swap(_right);
}