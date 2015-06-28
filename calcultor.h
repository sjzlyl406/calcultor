/*************************************************************************
	> File Name: calcultor.h
	> Author: leon
	> Mail: sjzlyl406@163.com 
	> Created Time: 2015年06月28日 星期日 12时18分17秒
 ************************************************************************/

#ifndef CALCULTOR_H
#define CALCULTOR_H


#include<iostream>
#include<sstream>
#include<stdexcept>
#include<algorithm>
#include<string>
#include<stack>

#define ERRORRANGE 0.0000001

class Calcultor
{
	public:

		Calcultor(const std::string &program) : program_(program){}
		const double Evaluate(std::string program);
		const double Evaluate();

	public:
		std::string program_;


	public:
		void PreTreatment();
		size_t ExtractNum(const std::string &program, size_t i, double &, bool);

		bool FindChar(const std::string &program, const char c);
		void CalParen(std::string &program);
		void CalMulAndDiv(std::string &program);
		void CalPluAndMin(std::string &program);

		const double Expression(std::string program);

		void WriteDouble(std::string &program,size_t left, size_t right, double result);

};



#endif
