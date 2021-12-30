#pragma once
#include <Windows.h>
#include<shellapi.h>
#include"parse_funcs.h"
#include "validation.h"
#include"scanner.h"
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>

std::string gen_script(SyntaxTree t)
{
	static uint64_t id = 0;
	std::string txt;
	std::string my_id_str = std::to_string(id);
	if (t.type == SyntaxTree_t::root_t)
	{
		txt += "graph {\n";
		txt += "\tnode\n";
	}
	if (!t.title.empty())
	{
		txt += std::to_string(id) + "[label=\"" + t.title;
		// +  
		if (!t.subtitle.empty())
		{
			txt += "\\n(" + t.subtitle + ")";
		}
		txt += "\",";
		std::string shape;
		if (t.type == SyntaxTree_t::asgn_sttmnt || t.type == SyntaxTree_t::if_sttmnt ||
			t.type == SyntaxTree_t::read_sttmt || t.type == SyntaxTree_t::rpt_sttmnt ||
			t.type == SyntaxTree_t::wrt_sttmnt)
		{
			shape = "box";
		}
		else
		{
			shape = "oval";
		}
		txt += "shape=" + shape + "]\n";
		for (size_t i = 0; i < t.children.size(); i++)
		{
			// txt += my_id_str + " -- " + std::to_string(id + i + 1) + "\n";
			id++;
			txt += my_id_str + " -- " + std::to_string(id) + "\n";
			txt += gen_script(*(t.children[i]));
		}
		if (t.sibling != nullptr)
		{
			id++;
			uint64_t i_sblng = id;
			std::string sblng_id_str = std::to_string(i_sblng);
			txt += my_id_str + " -- " + sblng_id_str;
			txt += " subgraph{" + my_id_str + "\t" + sblng_id_str + " rank=\"same\"" + "}\n";
			txt += gen_script(*(t.sibling));

		}
	}
	if (t.type == SyntaxTree_t::root_t) txt += "\n}";
	return txt;
}

bool draw_tree(std::string token_txt, std::string argv_str) {
	std::list<tokens> tokens_list;
	getToken(token_txt, tokens_list);
	if (!is_syntax_valid(tokens_list))
	{
		return false;
	}
	SyntaxTree tree = parse(tokens_list);
	std::ofstream file_out("gvz_script.dot", std::ofstream::trunc);
	std::string script_str = "graph R {\n" + gen_script(tree) + "\n}";
	std::stringstream ss(script_str);
	file_out << ss.rdbuf();
	file_out.close();
	size_t substr_len = argv_str.length();
	while (argv_str[substr_len - 1] != '\\')
	{
		substr_len--;
	}
	substr_len--;
	while (argv_str[substr_len - 1] != '\\')
	{
		substr_len--;
	}
	//substr_len--;
	argv_str = argv_str.substr(0, substr_len);
	argv_str += "Graphviz\\bin";
	//ShellExecuteA(NULL, "open", "dot.exe", NULL,
	//argv_str.data(), SW_SHOW);
	ShellExecuteA(NULL, "open", "dot.exe",
		"/c \"-Tsvg > ../../output.svg ../../gvz_script.dot\"", argv_str.data(), SW_SHOW);
	system("pause");
	//ShellExecuteA(NULL, "open","..\\output.svg", NULL, argv_str.data(), SW_SHOW);
	// ShellExecuteA(NULL, "open", "file.txt", NULL, argv_str.data(), SW_SHOW);
	// " - Tsvg > ../.. /output.svg ../../gvz_script.dot"
	//TCHAR ahmedgnina[MAX_PATH];
	//GetCurrentDirectory(MAX_PATH, ahmedgnina);
	//std::basic_string<TCHAR> strName = ahmedgnina;
	//strName = strName + "\\file.txt";
	//const char* path = strName.c_str();
	//ShellExecuteA(NULL, "open", path, NULL, NULL, SW_SHOWNORMAL);
	// std::cout << strName << std::endl;
	return true;
}