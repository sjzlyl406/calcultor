/*************************************************************************
	> File Name: test.cpp
	> Author: leon
	> Mail: sjzlyl406@163.com 
	> Created Time: 2015年06月30日 星期二 09时49分14秒
 ************************************************************************/
/*********************************************************************
 * (C) Copyright Leon 2015. Permission to copy, use, modify, sell and
 * distribute this software is granted provided this copyright notice appears
 * in all copies. This software is provided "as is" without express or implied
 * warranty, and with no claim as to its suitability for any purpose.
 *
 * ****************************************************************/

#include<iostream>
#include"calcultor.h"

int main(void)
{
	while(true) {
		try{
//			std::cout<<"input an expression:";
			std::string str;
			getline(std::cin,str);

			if(str == "exit")
				break;

			Calcultor c;
			double result;
			result = c.Evaluate(str);

			if(!str.empty())
				std::cout<< str << " = "<< result<< std::endl;
		}
		catch(const std::exception &e)
		{
			std::cout<< e.what() <<std::endl;
			std::cout<<"input again? Enter y or n:";
			char c;
			std::cin >> c;
			if(std::cin && (c == 'n' || c == 'N'))
				break;
		}
	}
	return 0;
}

