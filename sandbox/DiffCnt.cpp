#include <iostream>
#include <cstring>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <regex>
#include <map>

/*********************************************************
CLASS DECLARATION & DEFINATIONS
*********************************************************/
class Counter
{
	public:
	std::string Name;
	long unsigned int Comment;
	long unsigned int Code;
	long unsigned int Space;
	long unsigned int deleted;
	long unsigned int NewFile;
	
	void Print()
	{
		std::cout<<Name<<std::endl;
		std::cout<<"Code "<<Code<<std::endl;
		std::cout<<"Comment "<<Comment<<std::endl;
		std::cout<<"Space "<<Space<<std::endl;
		std::cout<<"deleted "<<deleted<<std::endl;
		std::cout<<"New "<<NewFile<<std::endl;
		std::cout<<"***********************************************"<<std::endl;
	}
	
	void Reset()
	{
		Comment = 0;
		Code = 0;
		Space = 0;
		deleted = 0;
		NewFile = 0;
	}
};

class user
{
	public:
	std::string name;
	int commits;
	std::vector<Counter> counters;
};
/*********************************************************
GLOBAL VARIABLES
*********************************************************/
std::vector<Counter> list;
std::vector<user> users;
int Weights[5];

//regex global templates
std::regex Diff("(diff [^\\n]+)");
std::regex Cfile("(diff --git a\\/[^\\n]+\\.c b\\/[^\\n]+\\.c)");
std::regex Hfile("(diff --git a\\/[^\\n]+\\.h b\\/[^\\n]+\\.h)");
std::regex Cppfile("(diff --git a\\/[^\\n]+\\.cpp b\\/[^\\n]+\\.cpp)");
std::regex CComment("([+|-]\\/\\*[^\\n]+\\*\\/)");
std::regex CComment_open("(.*\\/\\*.*)");
std::regex CComment_close("(.*\\*\\/.*)");
std::regex CppComment("([^\\n]+\\/\\/[^\\n]+)");
std::regex Code("([+|-][^\\+\\n]+)");
std::regex Deleted("(deleted file mode [^\\n]+)");
std::regex NewFile("(new file mode [^\\n]+)");
std::regex Nspace("(\\+|\\-)[\\s]+");

/*********************************************************
FUNCTIONS AND IMPLEMENTATIONS
*********************************************************/
int DiffCount(std::string name, std::string input)
{
	std::string line;
	std::ifstream lfile(input);
	Counter tmp;
	bool comment = false;
	
	if(!lfile.is_open())
		return -1; //fail to open file
	
	tmp.Name = name;
	tmp.Reset();
	while(getline(lfile,line))
	{
		if((std::regex_match(line,Cfile)||std::regex_match(line,Cppfile)||std::regex_match(line,Hfile)))
		{
			//std::cout<<line<<std::endl;
			while(getline(lfile,line))
			{
				//
				if(std::regex_match(line,Diff))
					break;
				//check for comments
				else if(std::regex_match(line,CComment))
				{
					tmp.Comment++;
					comment = false;
				}
				else if(std::regex_match(line,CComment_open))
				{
					tmp.Comment++;
					comment = true;
				}
				else if(std::regex_match(line,CComment_close))
				{
					tmp.Comment++;
					comment = false;
				}
				else if(std::regex_match(line,CppComment))
				{
					tmp.Comment++;
				}
				//check for space
				else if(std::regex_match(line,Nspace))
				{
					tmp.Space++;
				}
				//check for code
				else if(std::regex_match(line,Code))
				{
					comment?tmp.Comment++:tmp.Code++;
				}
				//check for new files or deleted files
				else if(std::regex_match(line,Deleted))
				{
					tmp.deleted++;
					break;
				}
				else if(std::regex_match(line,NewFile))
				{
					tmp.NewFile++;
					break;
				}
			}
		}
	}
	list.push_back(tmp);
	for(auto& i:users)
	{
		if(tmp.Name == i.name)
		{
			i.counters.push_back(tmp);
			break;
		}
	}
	return 0;
}

void gen_html()
{
	std::ofstream Ofile;
	Ofile.open("result/Final.html");
	if(Ofile.is_open())
	{
		Ofile<<"<!DOCTYPE html>\n<html>\n<head>\n<style>\ntable {\n";
		Ofile<<"\tfont-family: arial, sans-serif;\n";
		Ofile<<"\tborder-collapse: collapse;\n";
		Ofile<<"\twidth: 100%;\n}";
		
		Ofile<<"td, th {\n";
		Ofile<<"\tborder: 1px solid #dddddd;\n";
		Ofile<<"\ttext-align: left;\n";
		Ofile<<"\tpadding: 8px;\n}\n";
		
		Ofile<<"tr:nth-child(even) {\n";
		Ofile<<"\tbackground-color: #dddddd;\n}";
		Ofile<<"</style>\n</head>\n<body>\n";
		
		Ofile<<"<h2>Final Report table</h2>\n<table>\n";
		
		Ofile<<"<tr>\n";
		Ofile<<"<th>Name</th>\n";
		Ofile<<"<th>No. of Commits</th>\n";
		Ofile<<"<th>No. of Code</th>\n";
		Ofile<<"<th>No. of Comment</th>\n";
		Ofile<<"<th>No. of Space</th>\n";
		Ofile<<"<th>No. of Deleted files</th>\n";
		Ofile<<"<th>No. of New Files</th>\n";
		Ofile<<"<th>Final Score</th>\n";
		Ofile<<"</tr>\n";
		
		for(auto i : users)
		{
			int Comment = 0;
			int Code = 0;
			int Space = 0;
			int deleted = 0;
			int NewFile = 0;
			for(auto j : i.counters)
			{
				Comment += j.Comment;
				Code += j.Code;
				Space += j.Space;
				deleted += j.deleted;
				NewFile += j.NewFile;
			}
			int score = (Code * Weights[0])+(Comment * Weights[1])+
						(Space * Weights[2])+(deleted * Weights[3])+
						(NewFile * Weights[4]);
			Ofile<<"<tr>\n";
			Ofile<<"<td>"<<i.name<<"</td>\n"
				 <<"<td>"<<i.commits<<"</td>\n"
				 <<"<td>"<<Code<<"</td>\n"
				 <<"<td>"<<Comment<<"</td>\n"
				 <<"<td>"<<Space<<"</td>\n"
				 <<"<td>"<<deleted<<"</td>\n"
				 <<"<td>"<<NewFile<<"</td>\n"
				 <<"<td>"<<score<<"</td>\n";
			Ofile<<"</tr>\n";
		}
		Ofile<<"</table>\n</body>\n</html>\n";
	}
}

int main(int argc, char** argv)
{
	if(argc < 6)
	{
		std::cout<<"invalid program arguments"<<std::endl;
		std::cout<<"Please enter Weightages WC Wc WS WN WD when executing program"<<std::endl;
		return 0;
	}
	
	std::string W0 = argv[1];
	std::string W1 = argv[2];
	std::string W2 = argv[3];
	std::string W3 = argv[4];
	std::string W4 = argv[5];
 
	Weights[0] = std::stoi(W0);
	Weights[1] = std::stoi(W1);
	Weights[2] = std::stoi(W2);
	Weights[3] = std::stoi(W3);
	Weights[4] = std::stoi(W4);
	
	std::ifstream Lfile{"result/List.txt"};
	std::ifstream Rfile{"result/report.txt"};
	std::string line,name;
	//generate all users frm previous exe
	if(Rfile.is_open())
	{
		while(getline(Rfile,line))
		{
			user tmp;
			tmp.name = line.substr(0,line.find_first_of('@'));
			getline(Rfile,line);
			tmp.commits = stoi(line);
			users.push_back(tmp);
		}
	}
	
	//check files
	if(Lfile.is_open())
	{
		while(getline(Lfile,line))
		{
			//std::cout<<line<<std::endl;
			name = line.substr(line.find_first_of('/')+1,line.find_first_of('@')-line.find_first_of('/')-1);
			if(DiffCount(name,line) == -1)
			{
				std::cout<<"fail to open "<<line<<std::endl;
			}
		}
		Lfile.close();
	}
	
	gen_html();
#if 0
	//generate final report
	std::ofstream Ofile;
	Ofile.open("result/Final.txt");
	if(Ofile.is_open())
	{
		for(auto i : users)
		{
			long unsigned int Comment = 0;
			long unsigned int Code = 0;
			long unsigned int Space = 0;
			long unsigned int deleted = 0;
			long unsigned int NewFile = 0;
			for(auto j : i.counters)
			{
				Comment += j.Comment;
				Code += j.Code;
				Space += j.Space;
				deleted += j.deleted;
				NewFile += j.NewFile;
			}
			int score = (Code * Weights[0])+(Comment * Weights[1])+
						(Space * Weights[2])+(deleted * Weights[3])+
						(NewFile * Weights[4]);
			Ofile<<"/**************"<<i.name<<" ************/"
						<<"\n commits: "<<i.commits
						<<"\n Code: "<<Code
						<<"\n Comment: "<<Comment
						<<"\n Space: "<<Space
						<<"\n deleted: "<<deleted
						<<"\n New Files: "<<NewFile
						<<"\n Score : "<<score<<"\n";
		}
		Ofile.close();
	}
#endif
}