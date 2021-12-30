#pragma once
#include"validation.h"
#include"scanner.h"
#include"parse_funcs.h"
#include"syntax_tree.h"
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

SyntaxTree test_tree_gen()
{
	std::ifstream x("test_validity.txt");
	std::stringstream iss;
	iss << x.rdbuf();
	std::string test_str = iss.str();
	x.close();
	std::list<tokens> tokens_list;
	getToken(test_str, tokens_list);
	return parse(tokens_list);
}

void test_scrpt_gen()
{
	std::ifstream file_in("test_validity.txt");
	std::stringstream ss;
	ss << file_in.rdbuf();
	std::string test_str = ss.str();
	file_in.close();
	std::list<tokens> tokens_list;
	getToken(test_str, tokens_list);
	std::ofstream file_out("gvz_script.dot", std::ofstream::trunc);
	SyntaxTree Tree = parse(tokens_list);
	test_str = gen_script(Tree);
	ss.str(test_str);
	file_out << ss.rdbuf();
	file_out.close();
}

void test_draw_tree(std::string argv_string)
{
	std::ifstream file_in("test_validity.txt");
	std::stringstream ss;
	ss << file_in.rdbuf();
	std::string test_str = ss.str();
	file_in.close();
	draw_tree(test_str, argv_string);
}