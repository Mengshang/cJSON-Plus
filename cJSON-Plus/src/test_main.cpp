#include <iostream>
#include "cJSON_Plus.h"
#include <cJSON.h>
int main() {
	cJSON_Plus json;
	json.insert("Name", "����");
	json.insert("School", "������ѧ");
	json.insert<const char*>("��Ϥ����", {
			"C++",
			"Java",
			"Python"
		});
	json.insert("����", "��ϰʱ�������");
	json.insert("��ikun��", true);
	std::cout << json << std::endl;
	return 1;
}