//
// Created by Mohamed F. Razzk on 15/11/2021.
//
#ifndef __SCANNER_H__
#define __SCANNER_H__
#include <string>
#include <list>

enum scan_state { START, INCOMMENT, INNUM, INID, INASSIGN, DONE };
scan_state state = START;

std::string RES_WORDS[] =
{
	  "if",  "then", "else",   "end"
 ,"repeat", "until", "read", "write"
};

// IMP. NOTE: token_type needs to be enum to avoid spelling problems 
struct tokens {
	std::string token, token_type;
};

bool isDigit(char d) { return (d >= '0' && d <= '9'); }

bool isLetter(char l)
{
	return (l >= 'a' && l <= 'z' || l >= 'A' && l <= 'Z');
}

bool isSpace(char s) { return (s == ' ' || s == '\t' || s == '\n'); }

bool isSymbol(char c) {
	return(c == '+' || c == '-' || c == '*' || c == '/' || c == '='
		|| c == '<' || c == '>' || c == '(' || c == ')' || c == ';');

}

void getToken(std::string l, std::list<tokens>& code_tokens)
{
	std::string mytoken;
	bool res_flag = false;
	int i = 0;
	tokens token;
	scan_state state = START;

	while (state != DONE) {

		switch (state) {
		case START:
			if (isSpace(l[i])) {
				i++;
				if (i == l.length()) state = DONE;
				else state = START;
			}
			else if (isDigit(l[i])) {
				state = INNUM;
			}
			else if (isLetter(l[i])) {
				state = INID;
			}
			else if (l[i] == ':') {
				state = INASSIGN;
			}
			else if (l[i] == '{') {
				i++;
				state = INCOMMENT;
			}
			else if (isSymbol(l[i])) {
				switch (l[i]) {
				case ';': token = { std::string(1,(l[i])),"SEMICOLON" }; code_tokens.emplace_back(token); break;
				case '+': token = { std::string(1,(l[i])),"MATH_OPERATION" }; code_tokens.emplace_back(token); break;
				case '-': token = { std::string(1,(l[i])),"MATH_OPERATION" }; code_tokens.emplace_back(token); break;
				case '*': token = { std::string(1,(l[i])),"MATH_OPERATION" }; code_tokens.emplace_back(token); break;
				case '/': token = { std::string(1,(l[i])),"MATH_OPERATION" }; code_tokens.emplace_back(token); break;
				case '=': token = { std::string(1,(l[i])),"EQUAL_OPERATION" }; code_tokens.emplace_back(token); break;
				case '<': token = { std::string(1,(l[i])),"LESS_OPERATION" }; code_tokens.emplace_back(token); break;
				case '>': token = { std::string(1,(l[i])),"GREATER_OPERATION" }; code_tokens.emplace_back(token); break;

				}
				i++;
				if (i == l.length()) state = DONE;
				else state = START;
			}
			else state = DONE;
			break;

		case INCOMMENT:
			if (state == INCOMMENT) {
				while (l[i] != '}') {
					i++;
				}
				i++;
				if (i == l.length()) state = DONE;
				else state = START;
			}
			break;

		case INNUM:
			while (isDigit(l[i]) || l[i] == '.') {
				mytoken += l[i];
				i++;
			}

			token = { mytoken,"NUMBER" };
			code_tokens.emplace_back(token);


			mytoken = "";
			if (i == l.length()) state = DONE;
			else state = START;
			break;

		case INID:

			while (isLetter(l[i])) {
				mytoken += l[i];
				i++;
			}

			for (int i = 0; i < 8; i++)
			{
				if (RES_WORDS[i] == mytoken) res_flag = 1;
			}

			if (res_flag)
			{
				token = { mytoken,"RESERVED_WORD" };
				code_tokens.emplace_back(token);

			}

			else

			{
				token = { mytoken,"IDENTIFEIER" };
				code_tokens.emplace_back(token);

			}

			mytoken = "";
			res_flag = 0;
			if (i == l.length()) state = DONE;
			else state = START;
			break;

		case INASSIGN:
			if (l[i] == ':') {
				i += 2;
				token = { ":=","ASSIGNMENT" };
				code_tokens.emplace_back(token);
				state = START;
			}
			else {
				if (i == l.length()) state = DONE;
				else state = START;
			}
			break;
		case DONE:
			break;
		}
	}
}

#endif // !__SCANNER_H__

