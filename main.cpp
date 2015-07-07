/*************************************************************************
	> File Name: test.cpp
	> Author: leon
	> Mail: sjzlyl406@163.com 
	> Created Time: 2015年06月30日 星期二 09时49分14秒
 ************************************************************************/

#include<iostream>
#include"calcultor.h"

int main(void)
{
	while(true) {
		try{
			std::cout<<"input an expression:";
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
			std::cout<<"\ninput again? Enter y or n:";
			char c;
			std::cin >> c;
			if(std::cin && (c == 'n' || c == 'N'))
				break;
		}
	}
	return 0;
}

