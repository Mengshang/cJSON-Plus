#include <iostream>
#include "cJSON.h"
#include "cJSON_Plus.h"

int main() {
	cJSON* json = cJSON_CreateObject();
	cJSON_AddNullToObject(json, "test");
	std::cout << cJSON_Plus(json);
	cJSON_Delete(json);
	return 1;
}