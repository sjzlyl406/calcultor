/*************************************************************************
	> File Name: calcul_parser.cpp
	> Author: leon
	> Mail: sjzlyl406@163.com 
	> Created Time: 2015年06月27日 星期六 19时53分05秒
 ************************************************************************/

#include<iostream>
#include"calcul_parser.h"

void Parser::PreTreatment()
{
	size_t i = 0;
	for(;i != program_.size();++i)
		if(isspace(program_[i]))
			program_.erase(i--, 1);
}
const TokenType GetToken(const bool ignorSign = false)
{
	
}

const double Parser::Evaluate()
{
	PreTreatment();
	Type = NONE;
	if(!program_.size())
		Type_ = END;
	pWord_ = program_.c_str();

	std::cout << program_ << std::endl;

	return 1.0;
}

int main(void)
{
	Parser p("1 2 dfas   dsafa");

	p.Evaluate();

	return 0;
}
