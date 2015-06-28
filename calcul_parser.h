/*************************************************************************
	> File Name: parser.h
	> Author: leon
	> Mail: sjzlyl406@163.com 
	> Created Time: 2015年05月27日 星期六 19时32分04秒
 ************************************************************************/

#ifndef PARSER_H
#define PARSER_H


#include<string>
#include<map>
#include<stdexcept>
#include<cmath>
#include<sstream>
#include<cstdlib>

class Parser
{
	public:
		enum TokenType
		{
			NONE		,
			NUM			,
			DOT			=	'.',

			PLUS		=	'+',
			MINUS		=	'-',
			MULTIPY		=	'*',
			DIVIDE		=	'/',

			EQUAL		=	'=',
			LHPAREN		=	'(',
			RHPAREN		=	')',

			END
		};
	private:
		std::string program_;

		const char * pWord_;
		const char * pWordStart_;

		TokenType Type_;
		std::string word_;
		double value_;

	public:
		Parser(const std::string &program) : program_(program){
		}

		const double Evaluate();
		const double Evaluate(const std::string &program);

		std::map<std::string, double> symbols_;

	private:
		void PreTreatment();
		const TokenType GetToken(const bool ignoreSign = false);
		const double Expression(const bool get);
		const double AddSubtract(const bool get);
		const double Term(const bool get);
		const double Primary(const bool get);

};


#endif
