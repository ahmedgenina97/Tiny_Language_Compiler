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
	/*
	think of a way to find the width needed for each node to avoid overlaps of
	nodes in the syntax tree, e.g., count the number of leaf nodes to get a good
	guess of the width you need. also count the number of children to determine
	the orientation of the the child nodes 
	*/
	// uint32_t n_leaf_nodes;
};