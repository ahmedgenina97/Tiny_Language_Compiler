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

bool draw_tree(std::string token_txt) {
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
	ShellExecuteA(NULL, "open", "cmd.exe",
		"/c \"Graphviz\\bin\\dot.exe -Tsvg > output.svg gvz_script.dot\"", NULL, SW_SHOW);
	Sleep(1000);
	ShellExecuteA(NULL, "open", "cmd.exe", "/c \"output.svg\"", NULL, SW_SHOW);
	return true;
}