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
	//���ļ����뵽ostringstream����buf��
	ostringstream buf;
	char ch;
	while (buf && ifile.get(ch))
		buf.put(ch);
	ifile.close();
	//������������buf�������ַ���
	return buf.str();
}

int main()
{
	//����һ��Html����
	string html = readFileIntoString("getsecurity.txt");
	cout << html << endl;
	return 0;
	HTML::ParserDom parser;
	tree<HTML::Node> dom = parser.parseTree(html);
	//�������DOM��
	cout << dom << endl;
	//����������еĳ����ӽڵ�
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
	//������е��ı��ڵ�
	it = dom.begin();
	end = dom.end();
	string	afterAnalyse;
	string	analyseConsequence;
	cout << "��ʼ��ȡ����" << endl;
	for (; it != end; ++it)
	{
		if ((!it->isTag()) && (!it->isComment()))
		{
			afterAnalyse = it->text();
			if (afterAnalyse.find("��a�룺") != string::npos)
			{
				analyseConsequence += afterAnalyse;
			}
		}
	}
	
	//cout << analyseConsequence << endl;

	ofstream ofile("data.txt", ofstream::out);               //�˴������ݴ���txt��outΪ�򿪲�����ļ�  
	ofile << analyseConsequence << endl;                                //�˴���������س�  
	ofile.close();
	
	cout << endl;
	system("pause");
}