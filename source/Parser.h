#ifndef __PARSER_H__

#include"scanner.h"
#include<list>
#include<string>
#include<vector>
enum class SyntaxTree_t
{
	root_t,
	if_sttmnt, rpt_sttmnt, asgn_sttmnt, read_sttmt, wrt_sttmnt,
	op_exp, const_exp, id_exp 
};
struct SyntaxTree {
	SyntaxTree* sibling;
	SyntaxTree_t type;
	std::vector<SyntaxTree*> children;
	std::string title;
	std::string subtitle;
};

void stmt_sequence(std::list<tokens>);
void statement(std::list<tokens>);
void if_stmt(std::list<tokens>);
void repeat_stmt(std::list<tokens>);
void assign_stmt(std::list<tokens>);
void read_stmt(std::list<tokens>);
void write_stmt(std::list<tokens>);
void exp(std::list<tokens>);
void comparison_op(std::list<tokens>);
void simple_exp(std::list<tokens>);
void add_op(std::list<tokens>);
void term(std::list<tokens>);
void mul_op(std::list<tokens>);
void factor(std::list<tokens>);

void stmt_sequence(std::list<tokens> t) {
	statement(t);

}

#endif // !__PARSER_H__

