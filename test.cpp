#include <iostream>
#include <cstring>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <regex>

class logs{
	public:
	std::string commit;
	std::string name;
	std::string date;
	std::string message;
};

class user{
	public:
	std::string name;
	std::string email;
	std::vector<logs> commits;
};

std::vector<logs> log_list;
std::vector<user> users;

void get_Logs()
{
	std::string line;
	std::ifstream lfile("log.txt");
	if(lfile.is_open())
	{
		std::regex r_commit("(commit) (.*)");
		std::regex r_author("(Author:) (.*)");
		while(getline(lfile,line))
		{
			if (std::regex_match (line,r_commit))
			{
				//generate logs of each entry
				logs tmp;
				tmp.commit = line.substr(line.find_first_of(' ')+1);
				getline(lfile,line);
				if(!std::regex_match (line,r_author))
					getline(lfile,line);
				tmp.name = line.substr(line.find_first_of('<'),line.find_first_of('>'));
				getline(lfile,line);
				tmp.date = line.substr(line.find_first_of(' ')+3);
				getline(lfile,line);
				getline(lfile,line);
				tmp.message = line;
				log_list.push_back(tmp);
				
				//match each entry to user
				bool inserted = false;
				for(int i=0;i<users.size();i++)
				{
					if(tmp.name == users[i].name)
					{
						users[i].commits.push_back(tmp);
						inserted = true;
						break;
					}
				}
				
				if(inserted == false)
				{
					//std::cout<<tmp.name<<"inserted"<<std::endl;
					user tmp_user;
					tmp_user.name = tmp.name;
					tmp_user.commits.push_back(tmp);
					users.push_back(tmp_user);
				}
				
			}
		}
		lfile.close();
	}
	else
		std::cout<<"fail"<<std::endl;
}


int main()
{

	get_Logs();
#if 0
	for(int i = 0; i < log_list.size();i++)
	{
		std::cout<<log_list[i].commit<<std::endl;
		std::cout<<log_list[i].name<<std::endl;
		std::cout<<log_list[i].date<<std::endl;
		std::cout<<log_list[i].message<<"\n\n"<<std::endl;
	}
#endif
	
#if 1
	for(int i = 0; i < users.size();i++)
	{
		std::cout<<users[i].name<<"\t"<<users[i].commits.size()<<std::endl;
	}
#endif
	return 0;
}




