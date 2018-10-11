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
	int Comment;
	int Code;
	int Space;
	bool deleted;
	bool NewFile;
	
	void CntRst()
	{
		Comment = 0;
		Code = 0;
		Space = 0;
		deleted = false;
		NewFile = false;
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
std::regex Diff("(diff.*)");
std::regex Cfile("(diff --git a/.*.c b/.*.c)");
std::regex Hfile("(diff --git a/.*.h b/.*.h)");
std::regex Cppfile("(diff --git a/.*.cpp b/.*.cpp)");
std::regex CComment_open("(.*\\/\\*.*)");
std::regex CComment_close("(.*\\*\\/.*)");
std::regex CppComment("(.*\\/\\/.*)");
std::regex Plus_Code("(\\+[^\\+\\n]+)");
std::regex Minus_Code("(\\-[^\\-\\n]+)");
std::regex MinusPlus_Code("(\\-\\+.*)");
std::regex Deleted("(deleted file mode .*)");
std::regex NewFile("(new file mode .*)");

/*********************************************************
FUNCTIONS AND IMPLEMENTATIONS
*********************************************************/
int DiffCount(std::string name, std::string input)
{
	std::string line;
	std::ifstream lfile(input);
	bool comment = false;
	
	if(!lfile.is_open())
		return -1; //fail to open file
	
	while(getline(lfile,line))
	{
		if(std::regex_match(line,Diff)&&(std::regex_match(line,Cfile)
			||std::regex_match(line,Cppfile)||std::regex_match(line,Hfile)))
		{
			Counter tmp;
			tmp.Name = line;
			tmp.CntRst();
			while(getline(lfile,line))
			{
				if(std::regex_match(line,Cfile)||std::regex_match(line,Cppfile)
					||std::regex_match(line,Hfile))
				{
					list.push_back(tmp);
					tmp.Name = line;
					tmp.CntRst();
				}
				else if(std::regex_match(line,Diff))
					break;
				else if(std::regex_match(line,Plus_Code)||
						std::regex_match(line,Minus_Code)||
						std::regex_match(line,MinusPlus_Code))
				{
					comment?tmp.Comment++:tmp.Code++;
				}
				else if(std::regex_match(line,CComment_open))
					comment = true;
				else if(std::regex_match(line,CComment_close))
					comment = false;
				else if(std::regex_match(line,CppComment))
					tmp.Comment++;
				else if(std::regex_match(line,Deleted))
				{
					tmp.deleted = true;
					list.push_back(tmp);
					break;
				}
				else if(std::regex_match(line,NewFile))
				{
					tmp.NewFile = true;
					list.push_back(tmp);
					tmp.CntRst();
					break;
				}
			}
			list.push_back(tmp);
			
			for(auto i:users)
			{
				if(name == i.name)
				{
					i.counters.push_back(tmp);
				}
			}
		}
	}
	return 0;
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
			name = line.substr(line.find_first_of('/')+1,line.find_first_of('@')-1);
			DiffCount(name,line);
		}
		Lfile.close();
	}
	
	//generate final report
	std::ofstream Ofile;
	Ofile.open("result/Final.txt");
	if(Ofile.is_open())
	{
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
			Ofile<<"/**************"<<i.name<<" ************/"
						<<"\n commits: "<<i.commits
						<<"\n Code: "<<Code
						<<"\n Comment: "<<Comment
						<<"\n deleted: "<<deleted
						<<"\n New Files: "<<NewFile
						<<"\n Score : "<<score<<"\n";
		}
		Ofile.close();
	}
	
/*
	if(result != -1)
	{
		for(int i = 0;i < list.size();i++)
		{
			if(list[i].deleted)
				std::cout<<list[i].Name<<" is deleted"<<std::endl;
			else
			{
				std::cout<<list[i].Name<<std::endl;
				std::cout<<"Comments changed: "<<list[i].Comment<<std::endl;
				std::cout<<"Code changed: "<<list[i].Code<<std::endl;
			}
		}
	}
	else
		std::cout<<"fail to open file"<<std::endl;
*/
}