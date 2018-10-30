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
	int Comment;
	int Code;
	int Space;
	int deleted;
	int NewFile;
	int score;
	std::vector<Counter> counters;
	
	void Zero()
	{
		commits = 0;
		Comment = 0;
		Code = 0;
		Space = 0;
		deleted = 0;
		NewFile = 0;
		score = 0;
	}
	
};

/*********************************************************
GLOBAL VARIABLES
*********************************************************/
std::vector<Counter> list;
std::vector<user> users;
int Total_Score;
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

void calc_score()
{
	for(auto& i : users)
	{
		for(auto& j : i.counters)
		{
			i.Comment += j.Comment;
			i.Code += j.Code;
			i.Space += j.Space;
			i.deleted += j.deleted;
			i.NewFile += j.NewFile;
		}
		i.score = (i.Code * Weights[0])+(i.Comment * Weights[1])+
					(i.Space * Weights[2])+(i.deleted * Weights[3])+
					(i.NewFile * Weights[4]);
		Total_Score += i.score;
	}
	
	std::ifstream dupe("../sandbox/Duplicate.txt");
	if(dupe.is_open())
	{
		std::string line;
		while(1)
		{
			if(std::regex_match(line,Code) || getline(dupe,line))
			{
				if(std::regex_match(line,Code))
				{
					std::string pri;
					pri = line.substr(line.find_first_of('<')+1,line.find_first_of('>')-2);
					for(auto& i :users)
					{
						//std::cout<< pri << "  " << i.name << std::endl;
						if(pri == i.name)
						{
							while(getline(dupe,line)&&(!std::regex_match(line,Code)&&line.length()!=0))//check for dupes
							{
								std::string sub;
								sub = line.substr(line.find_first_of('<')+1,line.find_first_of('>')-1);
								for(int j = 0;j<users.size();j++)
								{
									std::cout<<sub<<" "<<users[j].name<<std::endl;
									if(users[j].name == sub)//matched dupe
									{
										i.commits += users[j].commits;
										i.Comment += users[j].Comment;
										i.Code += users[j].Code;
										i.Space += users[j].Space;
										i.deleted += users[j].deleted;
										i.NewFile += users[j].NewFile;
										i.score += users[j].score;
									
										users.erase(users.begin()+j);
										break;
									}
								}
							}
							break;
						}
					}
				}
				else
					continue;
			}
			else
				break;
		}
	}
	else
	{
		std::cout<<"fail to load duplicate names config file"<<std::endl;
	}
}

void gen_html()
{
	std::ofstream Ofile;
	int T_commits = 0;
	int T_Code = 0;
	int T_Comments = 0;
	int T_Space = 0;
	int T_Deleted = 0;
	int T_New = 0;
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
		Ofile<<"<th>No. of Commits lines</th>\n";
		Ofile<<"<th>No. of Code lines</th>\n";
		Ofile<<"<th>No. of Comment lines</th>\n";
		Ofile<<"<th>No. of Space lines</th>\n";
		Ofile<<"<th>No. of Deleted files lines</th>\n";
		Ofile<<"<th>No. of New Files lines</th>\n";
		Ofile<<"<th>Total Score</th>\n";
		Ofile<<"<th>Percentile</th>\n";
		Ofile<<"</tr>\n";
		
		for(auto& i : users)
		{
			double percentile = ((double)i.score / (double)Total_Score)*100;
			Ofile<<"<tr>\n";
			Ofile<<"<td>"<<i.name<<"</td>\n"
				 <<"<td>"<<i.commits<<"</td>\n"
				 <<"<td>"<<i.Code<<"</td>\n"
				 <<"<td>"<<i.Comment<<"</td>\n"
				 <<"<td>"<<i.Space<<"</td>\n"
				 <<"<td>"<<i.deleted<<"</td>\n"
				 <<"<td>"<<i.NewFile<<"</td>\n"
				 <<"<td>"<<i.score<<"</td>\n"
				 <<"<td>"<<percentile<<"%</td>\n";
			Ofile<<"</tr>\n";
			//add up to get total
			T_commits += i.commits;
			T_Code += i.Code;
			T_Comments += i.Comment;
			T_Space += i.Space;
			T_Deleted += i.deleted;
			T_New += i.NewFile;
		}
		
		Ofile<<"<tr>\n";
		Ofile<<"<td>Total</td>\n"
			 <<"<td>"<<T_commits<<"</td>\n"
			 <<"<td>"<<T_Code<<"</td>\n"
			 <<"<td>"<<T_Comments<<"</td>\n"
			 <<"<td>"<<T_Space<<"</td>\n"
			 <<"<td>"<<T_Deleted<<"</td>\n"
			 <<"<td>"<<T_New<<"</td>\n"
			 <<"<td>"<<Total_Score<<"</td>\n"
			 <<"<td>100%</td>\n";
		Ofile<<"</tr>\n";
			
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
	
	//initialize total score
	Total_Score = 0; 
	//initialize temp strings from input
	std::string W0 = argv[1];
	std::string W1 = argv[2];
	std::string W2 = argv[3];
	std::string W3 = argv[4];
	std::string W4 = argv[5];
	//convert input strings to weightages
	Weights[0] = std::stoi(W0);
	Weights[1] = std::stoi(W1);
	Weights[2] = std::stoi(W2);
	Weights[3] = std::stoi(W3);
	Weights[4] = std::stoi(W4);
	
	std::ifstream Lfile{"result/List.txt"};
	std::ifstream Rfile{"result/report.txt"};
	std::ifstream Users{"KnownUsers.txt"};
	std::string line,name;
	//generate all users frm previous exe
	if(Rfile.is_open())
	{
		while(getline(Rfile,line))
		{
			user tmp;
			tmp.Zero();
			tmp.name = line.substr(0,line.find_first_of('@'));
			getline(Rfile,line);
			tmp.commits = stoi(line);
			for(auto& i : users)
			{
				if(i.name == tmp.name)
				{
					i.commits += tmp.commits;
					continue;
				}
			}
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
	calc_score();
	gen_html();
#if 0
	//generate final report in text
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