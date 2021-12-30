#pragma once
#include"scanner.h"
#include<list>
#include<string>
#include<vector>
#include<iostream>

enum class SyntaxTree_t
{
	root_t,
	if_sttmnt, rpt_sttmnt, asgn_sttmnt, read_sttmt, wrt_sttmnt,
	op_exp, const_exp, id_exp
};
struct SyntaxTree {
	SyntaxTree_t type{ SyntaxTree_t::root_t };
	SyntaxTree* sibling{ nullptr };
	std::vector<SyntaxTree*> children;
	std::string title;
	std::string subtitle;
};


SyntaxTree stmt_sequence(std::list<tokens>&);
SyntaxTree statement(std::list<tokens>&);
SyntaxTree if_stmt(std::list<tokens>&);
SyntaxTree repeat_stmt(std::list<tokens>&);
SyntaxTree assign_stmt(std::list<tokens>&);
SyntaxTree read_stmt(std::list<tokens>&);
SyntaxTree write_stmt(std::list<tokens>&);
SyntaxTree expr(std::list<tokens>&);
SyntaxTree comp_op(std::list<tokens>&);
SyntaxTree simple_expr(std::list<tokens>&);
SyntaxTree add_op(std::list<tokens>&);
SyntaxTree term(std::list<tokens>&);
SyntaxTree mul_op(std::list<tokens>&);
SyntaxTree factor(std::list<tokens>&);

SyntaxTree stmt_sequence(std::list<tokens>& t)
{
	SyntaxTree* prnt = new SyntaxTree;
	*prnt = statement(t);
	SyntaxTree* tmp_prnt = prnt;
	while ((!t.empty()) && t.front().token == ";")
	{
		t.pop_front();
		SyntaxTree* sblng = new SyntaxTree;
		*sblng = statement(t);
		tmp_prnt->sibling = sblng;
		tmp_prnt = sblng;
	}
	return *prnt;
}

SyntaxTree statement(std::list<tokens>& t)
{
	if ((!t.empty()) && t.front().token_type == "RESERVED_WORD")
	{
		if ((!t.empty()) && t.front().token == "if")
		{
			return if_stmt(t);
		}
		else if ((!t.empty()) && t.front().token == "repeat")
		{
			return repeat_stmt(t);
		}
		else if ((!t.empty()) && t.front().token == "read")
		{
			return read_stmt(t);
		}
		else if ((!t.empty()) && t.front().token == "write")
		{
			return write_stmt(t);
		}
	}
	return assign_stmt(t);
}

SyntaxTree if_stmt(std::list<tokens>& t)
{
	SyntaxTree prnt;
	prnt.type = SyntaxTree_t::if_sttmnt;
	prnt.title = "if";
	prnt.children.resize(2);
	if ((!t.empty()) && t.front().token == "if")
	{
		t.pop_front();
	}
	SyntaxTree* test = new SyntaxTree;
	*test = expr(t);
	prnt.children[0] = test;
	if ((!t.empty()) && t.front().token == "then")
	{
		t.pop_front();
	}
	SyntaxTree* then_part = new SyntaxTree;
	*then_part = stmt_sequence(t);
	prnt.children[1] = then_part;
	if ((!t.empty()) && t.front().token == "else")
	{
		t.pop_front();
		SyntaxTree* else_part = new SyntaxTree;
		*else_part = stmt_sequence(t);
		prnt.children.push_back(else_part);
	}
	if ((!t.empty()) && t.front().token == "end")
	{
		t.pop_front();
	}
	return prnt;
}

SyntaxTree repeat_stmt(std::list<tokens>& t)
{
	SyntaxTree prnt;
	prnt.type = SyntaxTree_t::rpt_sttmnt;
	prnt.title = "repeat";
	prnt.children.resize(2);
	if ((!t.empty()) && t.front().token == "repeat")
	{
		t.pop_front();
	}
	SyntaxTree* body = new SyntaxTree;
	*body = stmt_sequence(t);
	prnt.children[0] = body;
	if ((!t.empty()) && t.front().token == "until")
	{
		t.pop_front();
	}
	SyntaxTree* test = new SyntaxTree;
	*test = expr(t);
	prnt.children[1] = test;
	return prnt;
}

SyntaxTree assign_stmt(std::list<tokens>& t)
{
	SyntaxTree prnt;
	prnt.type = SyntaxTree_t::asgn_sttmnt;
	prnt.title = "assign";
	prnt.children.resize(1);
	if ((!t.empty()) && t.front().token_type == "IDENTIFEIER")
	{
		prnt.subtitle = t.front().token;
		t.pop_front();
	}
	if ((!t.empty()) && t.front().token == ":=")
	{
		t.pop_front();
	}
	SyntaxTree* exprssn = new SyntaxTree;
	*exprssn = expr(t);
	prnt.children[0] = exprssn;
	return prnt;
}

SyntaxTree read_stmt(std::list<tokens>& t)
{
	SyntaxTree prnt;
	prnt.type = SyntaxTree_t::read_sttmt;
	prnt.title = "read";
	prnt.children.resize(0);
	if ((!t.empty()) && t.front().token == "read")
	{
		t.pop_front();
	}
	if ((!t.empty()) && t.front().token_type == "IDENTIFEIER")
	{
		prnt.subtitle = t.front().token;
		t.pop_front();
	}
	return prnt;
}

SyntaxTree write_stmt(std::list<tokens>& t)
{
	SyntaxTree prnt;
	prnt.type = SyntaxTree_t::wrt_sttmnt;
	prnt.title = "write";
	prnt.children.resize(1);
	if ((!t.empty()) && t.front().token == "write")
	{
		t.pop_front();
	}
	SyntaxTree* exprssn = new SyntaxTree;
	*exprssn = expr(t);
	prnt.children[0] = exprssn;
	return prnt;
}

SyntaxTree expr(std::list<tokens>& t)
{
	SyntaxTree prnt;
	prnt = simple_expr(t);
	if ((!t.empty()) && (t.front().token == "<" || t.front().token == "="))
	{
		SyntaxTree super_prnt = comp_op(t);
		super_prnt.children.resize(2);
		SyntaxTree* child1 = new SyntaxTree;
		*child1 = prnt;
		super_prnt.children[0] = child1;
		SyntaxTree* child2 = new SyntaxTree;
		*child2 = simple_expr(t);
		super_prnt.children[1] = child2;
		return super_prnt;
	}
	return prnt;
}

SyntaxTree comp_op(std::list<tokens>& t)
{
	SyntaxTree prnt;
	prnt.type = SyntaxTree_t::op_exp;
	prnt.children.resize(2);
	prnt.title = "op";
	prnt.subtitle = t.front().token;
	t.pop_front();
	return prnt;
}

SyntaxTree simple_expr(std::list<tokens>& t)
{
	SyntaxTree prnt;
	prnt = term(t);
	while ((!t.empty()) && (t.front().token == "+" || t.front().token == "-"))
	{
		SyntaxTree super_prnt = add_op(t);
		super_prnt.children.resize(2);
		SyntaxTree* chldrn = new SyntaxTree[2];
		chldrn[0] = prnt;
		chldrn[1] = term(t);
		super_prnt.children[0] = &(chldrn[0]);
		super_prnt.children[1] = &(chldrn[1]);
		prnt = super_prnt;
	}
	return prnt;
}

SyntaxTree add_op(std::list<tokens>& t)
{
	SyntaxTree prnt;
	prnt.type = SyntaxTree_t::op_exp;
	prnt.children.resize(2);
	prnt.title = "op";
	prnt.subtitle = t.front().token;
	t.pop_front();
	return prnt;
}

SyntaxTree term(std::list<tokens>& t)
{
	SyntaxTree prnt = factor(t);
	while ((!t.empty()) && (t.front().token == "*" || t.front().token == "/"))
	{
		SyntaxTree super_prnt = mul_op(t);
		super_prnt.children.resize(2);
		SyntaxTree* term1 = new SyntaxTree;
		*term1 = prnt;
		super_prnt.children[0] = term1;
		SyntaxTree* term2 = new SyntaxTree;
		*term2 = factor(t);
		super_prnt.children[1] = term2;
		prnt = super_prnt;
	}
	return prnt;
}

SyntaxTree mul_op(std::list<tokens>& t)
{
	SyntaxTree prnt;
	prnt.type = SyntaxTree_t::op_exp;
	prnt.children.resize(2);
	prnt.title = "op";
	prnt.subtitle = t.front().token;
	t.pop_front();
	return prnt;
}

SyntaxTree factor(std::list<tokens>& t)
{
	SyntaxTree prnt;
	if ((!t.empty()) && t.front().token == "(")
	{
		t.pop_front();
		prnt = expr(t);
		if ((!t.empty()) && t.front().token == ")")
		{
			t.pop_front();
		}
	}
	else if ((!t.empty()) && t.front().token_type == "NUMBER")
	{
		prnt.type = SyntaxTree_t::const_exp;
		prnt.title = "const";
		prnt.subtitle = t.front().token;
		t.pop_front();
	}
	else if ((!t.empty()) && t.front().token_type == "IDENTIFEIER")
	{
		prnt.type = SyntaxTree_t::id_exp;
		prnt.title = "id";
		prnt.subtitle = t.front().token;
		t.pop_front();
	}
	return prnt;
}

SyntaxTree parse(std::list<tokens> t)
{
	return stmt_sequence(t);
}

