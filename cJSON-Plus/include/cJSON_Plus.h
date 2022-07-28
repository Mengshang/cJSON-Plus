#pragma once

#include <string>
#include <ostream>

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
	void insert(const char* key, cJSON_Plus& value);
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
	const char* toString() const;
	std::string toStdString() const;
	cJSON_Plus operator[](const char* key) const;
	cJSON_Plus& operator=(int& value);
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
	insert(key, temp);
}

static inline std::ostream& operator<<(std::ostream& os, const cJSON_Plus& value) {
	return os << value.toString();
}