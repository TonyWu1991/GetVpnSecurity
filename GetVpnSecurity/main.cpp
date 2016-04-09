#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <sstream>
#include <ParserDom.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>  
#include <process.h>  
using namespace std;
using namespace htmlcxx;

string readFileIntoString(char * filename)
{
	ifstream ifile(filename);
	//将文件读入到ostringstream对象buf中
	ostringstream buf;
	char ch;
	while (buf && ifile.get(ch))
		buf.put(ch);
	ifile.close();
	//返回与流对象buf关联的字符串
	return buf.str();
}

int main()
{
	//解析一段Html代码
	string html = readFileIntoString("getsecurity.txt");
	cout << html << endl;
	return 0;
	HTML::ParserDom parser;
	tree<HTML::Node> dom = parser.parseTree(html);
	//输出整棵DOM树
	cout << dom << endl;
	//输出树中所有的超链接节点
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();
	//for (; it != end; ++it)
	//{
	//	if (strcmp(it->tagName().c_str(), "A") == 0)
	//	{
	//		it->parseAttributes();
	//		cout << it->attribute("href").second << endl;
	//	}
	//}
	//输出所有的文本节点
	it = dom.begin();
	end = dom.end();
	string	afterAnalyse;
	string	analyseConsequence;
	cout << "开始提取密码" << endl;
	for (; it != end; ++it)
	{
		if ((!it->isTag()) && (!it->isComment()))
		{
			afterAnalyse = it->text();
			if (afterAnalyse.find("密a码：") != string::npos)
			{
				analyseConsequence += afterAnalyse;
			}
		}
	}
	
	//cout << analyseConsequence << endl;

	ofstream ofile("data.txt", ofstream::out);               //此处将数据存入txt，out为打开并清空文件  
	ofile << analyseConsequence << endl;                                //此处勿忘输入回车  
	ofile.close();
	
	cout << endl;
	system("pause");
}