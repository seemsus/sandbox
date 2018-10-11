#include <iostream>
#include <cstring>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <regex>
#include <map>

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

class Timing
{
  public:
  std::string start_month;
  std::string start_day;
  std::string end_month;
  std::string end_day;
};

std::vector<logs> log_list;
std::vector<user> users;
std::map<std::string, int> Month_Day;
Timing timeline;

// initializer
void init(char ** argv)
{
  Month_Day["Jan"] = 1;
  Month_Day["Feb"] = 2;
  Month_Day["Mar"] = 3;
  Month_Day["Apr"] = 4;
  Month_Day["May"] = 5;
  Month_Day["Jun"] = 6;
  Month_Day["Jul"] = 7;
  Month_Day["Aug"] = 8;
  Month_Day["Sep"] = 9;
  Month_Day["Oct"] = 10;
  Month_Day["Nov"] = 11;
  Month_Day["Dec"] = 12;
  timeline.start_month = argv[1];
  timeline.start_day   = argv[2];
  timeline.end_month   = argv[3];
  timeline.end_day     = argv[4];
}

// helper function
bool inbetween(int start, int end, int val)
{
  if((val >= start) && (val <= end)) return true;
  else if((val <= start) || (val >= end)) return true;
  return false;
}

void get_Logs()
{
	std::string line;
  std::string Exact_month;
  int day;
  
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
        
        Exact_month = tmp.date.substr(4, 3);
        day = stoi(tmp.date.substr(8, 2));
        
				getline(lfile,line);
				getline(lfile,line);
				tmp.message = line;
				log_list.push_back(tmp);
				
        // check month
        if(inbetween(
              Month_Day[timeline.start_month], 
              Month_Day[timeline.end_month], 
              Month_Day[Exact_month])
          )
        {
          // check day
          if(inbetween(
                stoi(timeline.start_day),
                stoi(timeline.end_day),
                day)
            )        
          {
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
        
			}
		}
		lfile.close();
	}
	else
		std::cout<<"fail"<<std::endl;
}


int main(int argc, char** argv)
{
  int opt = 0;
  int j = 0;
  init(argv);
	get_Logs();
  
  do
	{
		std::cout<<"select an option"<<std::endl;
		std::cout<<"0:menu"<<std::endl;
		std::cout<<"1:list all commits"<<std::endl;
		std::cout<<"2:list all commits by user"<<std::endl;
		std::cout<<"3:exit"<<std::endl;
    std::cout << "Enter option no:     ";
		std::cin >> opt;
    std::cout << std::endl;
		switch(opt)
		{
			case 0: 
				break;
			case 1:
        for(auto i : log_list)
        {
          std::cout << i.commit << std::endl;
          std::cout << i.name << std::endl;
          std::cout << i.date << std::endl;
          std::cout << i.message << std::endl;
          std::cout << std::endl;
          std::cout << std::endl;
        }
				break;
			case 2:
        j = 0;
				for(auto b : users)
        {
          std::cout<<j++ << ":\t" << b.name<<"\t"<<b.commits.size()<<std::endl;
        }
				std::cout<<"enter user no:\t     ";
				std::cin>>opt;
        while(opt >= users.size() || opt < 0)
        {
          std::cout << "invalid selection! Try again." << std::endl;
          std::cout<<"enter user no:\t";
          std::cin >> opt;
        }
        std::cout << std::endl;
        for(auto i : users[opt].commits)
        {
          std::cout << i.commit  << std::endl;
          std::cout << i.name    << std::endl;
          std::cout << i.date    << std::endl;
          std::cout << i.message << std::endl;
          std::cout << std::endl;
          std::cout << std::endl;
        }
				break;
			case 3:
				break;
      default:
        break;
		}
	}while(opt != 3);
  
  return 0;
}




