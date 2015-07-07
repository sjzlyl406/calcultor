/*************************************************************************
	> File Name: function.h
	> Author: leon
	> Mail: sjzlyl406@163.com 
	> Created Time: 2015年07月01日 星期三 14时06分37秒
 ************************************************************************/

#ifndef FUNCTION_H
#define FUNCTION_H

#include<map>
#include<iostream>
#include<string>
#include<cmath>
#include<stdexcept>
#include<sstream>
#include<cctype>

class Function
{
	public:
		/* construct function */
		Function();
		Function(const std::string &str);

		/* return the value */
		const double Evaluate();
		const double Evaluate(std::string program);

		bool GetState();

	private:
		std::string program_;

		std::string strFunc;
		double num1, num2;

		bool g_status;
	private:
		/* Check correction */
		bool Check();

		/* Extract the Info from Expression */
		bool Explain();

		/* Function */
		const double Expression();
};



#endif
