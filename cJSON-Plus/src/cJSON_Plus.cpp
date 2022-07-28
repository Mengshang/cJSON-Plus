#include "cJSON.h"
#include "cJSON_Plus.h"
#include <iostream>
#define DEBUG 1
#if DEBUG
#include <iostream>
void log(const char* data) {
	std::cerr << data << std::endl;
}
#else
void log(const char* data) {
	
}
#endif // DEBUG


cJSON_Plus::cJSON_Plus()
	: object_(cJSON_CreateObject())
{
	log("cJSON_Plus()");
}

cJSON_Plus::cJSON_Plus(cJSON* json)
	: object_(json)
{
	log("cJSON_Plus(cJSON*)");
}

cJSON_Plus::cJSON_Plus(const cJSON_Plus& other)
	: cJSON_Plus(other.object_, other.parent_)
{
	log("cJSON_Plus(const cJSON_Plus&)");
}

cJSON_Plus::cJSON_Plus(cJSON_Plus&& other) noexcept
	: cJSON_Plus(other.object_, other.parent_)
{
	log("cJSON_Plus(cJSON_Plus&&)");
	other.object_ = nullptr;
}

cJSON_Plus::~cJSON_Plus()
{
	log("~cJSON_Plus()");
	if (parent_ == nullptr && object_ != nullptr) {
		cJSON_free(object_);
		object_ = nullptr;
	}
}

void cJSON_Plus::insert(const char* key, const char* value)
{
	cJSON_AddStringToObject(object_, key, value);
}

void cJSON_Plus::insert(const char* key, const std::string& value)
{
	cJSON_AddStringToObject(object_, key, value.c_str());
}

void cJSON_Plus::insert(const char* key, const int& value)
{
	cJSON_AddNumberToObject(object_, key, static_cast<double>(value));
}

void cJSON_Plus::insert(const char* key, const float& value)
{
	cJSON_AddNumberToObject(object_, key, static_cast<double>(value));
}

void cJSON_Plus::insert(const char* key, const double& value)
{
	cJSON_AddNumberToObject(object_, key, value);
}

void cJSON_Plus::insert(const char* key, const bool& value)
{
	cJSON_AddBoolToObject(object_, key, value);
}

void cJSON_Plus::insert(const char* key, cJSON_Plus& value)
{
	value.parent_ = this;
	cJSON_AddItemToObject(object_, key, value.object_);
}

const cJSON_Plus cJSON_Plus::get(const char* key) const
{
	return cJSON_Plus(cJSON_GetObjectItem(object_, key));
}

void cJSON_Plus::replace(const char* key, const char* value)
{
	cJSON_ReplaceItemInObject(object_, key, cJSON_CreateString(value));
}

void cJSON_Plus::replace(const char* key, const std::string& value)
{
	cJSON_ReplaceItemInObject(object_, key, cJSON_CreateString(value.c_str()));
}

void cJSON_Plus::replace(const char* key, const int& value)
{
	cJSON_ReplaceItemInObject(object_, key, cJSON_CreateNumber(static_cast<double>(value)));
}

void cJSON_Plus::replace(const char* key, const float& value)
{
	cJSON_ReplaceItemInObject(object_, key, cJSON_CreateNumber(static_cast<double>(value)));
}

void cJSON_Plus::replace(const char* key, const double& value)
{
	cJSON_ReplaceItemInObject(object_, key, cJSON_CreateNumber(value));
}

void cJSON_Plus::replace(const char* key, const bool& value)
{
	cJSON_ReplaceItemInObject(object_, key, cJSON_CreateBool(value));
}

void cJSON_Plus::replace(const char* key, cJSON_Plus& value)
{
	value.parent_ = this;
	cJSON_ReplaceItemInObject(object_, key, value.object_);
}

const char* cJSON_Plus::toString() const
{
	return cJSON_Print(object_);
}

std::string cJSON_Plus::toStdString() const
{
	return std::string(cJSON_Print(object_));
}

cJSON_Plus& cJSON_Plus::operator=(int& value)
{
	object_->valuedouble = static_cast<double>(value);
	return *this;
}

cJSON_Plus& cJSON_Plus::operator=(const float& value)
{
	object_->valuedouble = static_cast<double>(value);
	return *this;
}

cJSON_Plus& cJSON_Plus::operator=(const double& value)
{
	object_->valuedouble = value;
	return *this;
}

cJSON_Plus& cJSON_Plus::operator=(const bool& value)
{
	object_->valueint = value;
	return *this;
}

cJSON_Plus& cJSON_Plus::operator=(cJSON_Plus& value)
{
	object_ = value.object_;
	return *this;
}

cJSON_Plus& cJSON_Plus::operator=(cJSON_Plus&& value) noexcept
{
	object_ = value.object_;
	value.object_ = nullptr;
	value.parent_ = nullptr;
	return *this;
}

cJSON_Plus& cJSON_Plus::operator=(const char* value)
{
	object_->valuestring = const_cast<char*>(value);
	return *this;
}

cJSON_Plus& cJSON_Plus::operator=(const std::string& value)
{
	object_->valuestring = const_cast<char*>(value.c_str());
	return *this;
}

cJSON_Plus::cJSON_Plus(cJSON* json, cJSON_Plus* parent)
	: object_(json), parent_(parent)
{
	log("private: cJSON_Plus(cJSON*, cJSON_Plus*)");
}

cJSON_Plus cJSON_Plus::operator[](const char* key) const
{
	cJSON* item = cJSON_GetObjectItem(object_, key);
	if (item == nullptr) {
		std::abort();
		// no the item
	}
	return cJSON_Plus(item, const_cast<cJSON_Plus*>(this));
}