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
#include"function.h"

#define ERRORRANGE 0.0000001

class Calcultor
{
	public:
		/* construct function */
		Calcultor(){ program_ = "error"; }
		Calcultor(const std::string &program) : program_(program){}
		
		/* return the value */
		const double Evaluate(std::string program);
		const double Evaluate();

	public:
		std::string program_;

	public:

		/* pretreatement */
		void PreTreatment();

		/* get the number from program */
		size_t ExtractNum(const std::string &program, size_t i, double &, bool);

		/* is there is a 'c' in program */
		bool FindChar(const std::string &program);
		bool FindChar(const std::string &program, const char c);

		/* calculate the expression in parenthesis */
		void CalParen(std::string &program);
		void CalFunc(std::string &program);

		/* calculate + - * / */
		void CalMulAndDiv(std::string &program);
		void CalPluAndMin(std::string &program);

		/* function */
		const double Expression(std::string program);

		/* write number into program*/
		void WriteDouble(std::string &program,size_t left, size_t right, double number);

};



#endif
