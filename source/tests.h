#pragma once
#ifndef __TESTS_H__
#define __TESTS_H__

#include"validation.h"
#include<fstream>
#include<sstream>
#include<iostream>
#include<list>

bool test_validation()
{
	std::ifstream x("test_validity.txt");
	std::stringstream iss;
	iss << x.rdbuf();
	std::string test_str = iss.str();
	x.close();
	std::list<tokens> tokens_list;
	getToken(test_str, tokens_list);
	return is_syntax_valid(tokens_list);
}

#endif // !__TESTS_H__
