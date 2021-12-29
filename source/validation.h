#ifndef __VALIDATOR__
#define __VALIDATOR__
#include"scanner.h"
#include<list>
#include<string>


bool check_stmt_sequence(std::list<tokens>&);
bool check_statement(std::list<tokens>&);
bool check_if_stmt(std::list<tokens>&);
bool check_repeat_stmt(std::list<tokens>&);
bool check_assign_stmt(std::list<tokens>&);
bool check_read_stmt(std::list<tokens>&);
bool check_write_stmt(std::list<tokens>&);
bool check_expr(std::list<tokens>&);
bool check_comp_op(std::list<tokens>&);
bool check_simple_expr(std::list<tokens>&);
bool check_add_op(std::list<tokens>&);
bool check_term(std::list<tokens>&);
bool check_mul_op(std::list<tokens>&);
bool check_factor(std::list<tokens>&);

bool check_stmt_sequence(std::list<tokens>& t)
{
	if (check_statement(t) == false)
	{
		return false;
	}
	while (t.front().token == ";")
	{
		t.pop_front();
		if (check_statement(t) == false)
		{
			return false;
		}
	}
	return true;
}

bool check_statement(std::list<tokens>& t)
{
	if (t.front().token_type == "RESERVED_WORD")
	{
		if (t.front().token == "if")
		{
			return check_if_stmt(t);
		}
		else if (t.front().token == "repeat")
		{
			return check_repeat_stmt(t);
		}
		else if (t.front().token == "read")
		{
			return check_read_stmt(t);
		}
		else if (t.front().token == "write")
		{
			return check_write_stmt(t);
		}
	}
	else if (t.front().token_type == "IDENTIFEIER")
	{
		return check_assign_stmt(t);
	}
	else
	{
		return false;
	}
}

bool check_if_stmt(std::list<tokens>& t)
{
	if (t.front().token == "if")
	{
		t.pop_front();
	}
	else
	{
		return false;
	}
	if (check_expr(t) == false)
	{
		return false;
	}
	if (t.front().token == "then")
	{
		t.pop_front();
	}
	else
	{
		return false;
	}
	if (check_stmt_sequence(t) == false)
	{
		return false;
	}
	if (t.front().token == "else")
	{
		t.pop_front();
		if (check_stmt_sequence(t) == false)
		{
			return false;
		}
	}
	if (t.front().token == "end")
	{
		t.pop_front();
	}
	else
	{
		return false;
	}
	return true;
}

bool check_repeat_stmt(std::list<tokens>& t)
{
	if (t.front().token == "repeat")
	{
		t.pop_front();
	}
	else
	{
		return false;
	}
	if (check_stmt_sequence(t) == false)
	{
		return false;
	}
	if (t.front().token == "until")
	{
		t.pop_front();
	}
	else
	{
		return false;
	}
	if (check_expr(t) == false)
	{
		return false;
	}
	return true;
}

bool check_assign_stmt(std::list<tokens>& t)
{
	if (t.front().token_type == "IDENTIFEIER")
	{
		t.pop_front();
	}
	else
	{
		return false;
	}
	if (t.front().token == ":=")
	{
		t.pop_front();
	}
	else
	{
		return false;
	}
	if (check_expr(t) == false)
	{
		return false;
	}
	return true;
}

bool check_read_stmt(std::list<tokens>& t)
{
	if (t.front().token == "read")
	{
		t.pop_front();
	}
	else
	{
		return false;
	}
	if (t.front().token_type == "IDENTIFEIER")
	{
		t.pop_front();
	}
	else
	{
		return false;
	}
	return true;
}

bool check_write_stmt(std::list<tokens>& t)
{
	if (t.front().token == "write")
	{
		t.pop_front();
	}
	else
	{
		return false;
	}
	if (check_expr(t) == false)
	{
		return false;
	}
	return true;
}

bool check_expr(std::list<tokens>& t)
{
	if (check_simple_expr(t) == false)
	{
		return false;
	}
	if (check_comp_op(t) == true)
	{
		if (check_simple_expr(t) == false)
		{
			return false;
		}
	}
	return true;
}

bool check_comp_op(std::list<tokens>& t)
{
	if (t.front().token == "<" || t.front().token == "=")
	{
		t.pop_front();
		return true;
	}
	else
	{
		return false;
	}
}

bool check_simple_expr(std::list<tokens>& t)
{
	if (check_term(t) == false)
	{
		return false;
	}
	while (check_add_op(t) == true)
	{
		if (check_term(t) == false)
		{
			return false;
		}
	}
	return true;
}

bool check_add_op(std::list<tokens>& t)
{
	if (t.front().token == "+" || t.front().token == "-")
	{
		t.pop_front();
		return true;
	}
	else
	{
		return false;
	}
}

bool check_term(std::list<tokens>& t)
{
	if (check_factor(t) == false)
	{
		return false;
	}
	while (check_mul_op(t) == true)
	{
		if (check_factor(t) == false)
		{
			return false;
		}
	}
	return true;
}

bool check_mul_op(std::list<tokens>& t)
{
	if (t.front().token == "*" || t.front().token == "/")
	{
		t.pop_front();
		return true;
	}
	else
	{
		return false;
	}
}

bool check_factor(std::list<tokens>& t)
{
	if (t.front().token == "(")
	{
		t.pop_front();
		if (check_expr(t) == false)
		{
			return false;
		}
		if (t.front().token == ")")
		{
			t.pop_front();
		}
		else
		{
			return false;
		}
	}
	else if (t.front().token_type == "NUMBER" || t.front().token_type == "IDENTIFEIER")
	{
		t.pop_front();
	}
	else
	{
		return false;
	}
	return true;
}

bool is_syntax_valid(std::list<tokens> t) {
	return check_stmt_sequence(t);
}

#endif // !__VALIDATOR_H__

