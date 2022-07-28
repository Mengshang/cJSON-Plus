#include <iostream>
#include "cJSON_Plus.h"
#include <cJSON.h>
int main() {
	cJSON_Plus json;
	json.insert("Name", "梦殇");
	json.insert("School", "北京大学");
	json.insert<const char*>("熟悉语言", {
			"C++",
			"Java",
			"Python"
		});
	json.insert("描述", "练习时长两年半");
	json.insert("是ikun吗", true);
	std::cout << json << std::endl;
	return 1;
}