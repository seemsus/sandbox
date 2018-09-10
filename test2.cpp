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
void init()
{
  Month_Day["JAN"] = 1;
  Month_Day["FEB"] = 2;
  Month_Day["MAR"] = 3;
  Month_Day["APR"] = 4;
  Month_Day["MAY"] = 5;
  Month_Day["JUN"] = 6;
  Month_Day["JUL"] = 7;
  Month_Day["AUG"] = 8;
  Month_Day["SEP"] = 9;
  Month_Day["OCT"] = 10;
  Month_Day["NOV"] = 11;
  Month_Day["DEC"] = 12;
}

// helper function
bool inbetween(int start, int end, int val)
{
  if((val >= start) && (val <= end)) return true;
  else if((val <= start) && (val >= end)) return true;
  return false;
}

bool between(std::string month, int day)
{
  if(inbetween(
    Month_Day[timeline.start_month], 
    Month_Day[timeline.end_month], 
    Month_Day[month])
  )
  {
    if(inbetween(
          stoi(timeline.start_day),
          stoi(timeline.end_day),
          day)
      )
    {
      return true;
    }
  }
  return false;
}

bool input_date()
{
  char input;
  do{
    std::cout << "Enter start date followed by end date: (Mmm dd Mmm dd)" << std::endl;
    std::cin >> timeline.start_month;
    std::cin >> timeline.start_day;
    std::cin >> timeline.end_month;
    std::cin >> timeline.end_day;
    for(auto & i : timeline.start_month) i = toupper(i);
    for(auto & i : timeline.end_month)   i = toupper(i);
    
    if(Month_Day.find(timeline.start_month) != Month_Day.end())
      if(Month_Day.find(timeline.end_month) != Month_Day.end())
        return true;
      
    std::cout << "Retry? Y/N" << std::endl;
    std::cin >> input;
    if(toupper(input) == 'N')
      return false;
  }while(1);
}

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


int main(int argc, char** argv)
{
  int opt = 0;
  int j = 0;
  std::string input_data;
  std::string Exact_month;
  int day;
  std::map<std::string, int> count;
  
  init();
	get_Logs();
  
  do
	{
    j = 0;
		std::cout<<"select an option"<<std::endl;
		std::cout<<"0:menu"<<std::endl;
		std::cout<<"1:list all commits"<<std::endl;
		std::cout<<"2:list all commits by user"<<std::endl;
		std::cout<<"3:list all number of commits by date"<<std::endl;
    std::cout<<"4:list all commits of date" << std::endl;
    std::cout<<"5:Exit"<<std::endl;
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
        if(input_date() == false) break;
        
        for(auto a : users)
        {
          for(auto b : a.commits)
          {
            Exact_month = b.date.substr(4, 3);
            day = stoi(b.date.substr(8, 2));
            for(auto & i : Exact_month)   i = toupper(i);
            
            if(between(Exact_month, day))
              count[b.name]++;
          }
        }
        std::cout << std::endl;
        for(auto c : count)
        {
          std::cout << j++ << ":\t" << c.first << "\t" << c.second << std::endl;
        }
        std::cout << std::endl;
				break;
      case 4:
        if(input_date() == false) break;
        for(auto a : users)
        {
          for(auto b : a.commits)
          {
            Exact_month = b.date.substr(4, 3);
            day = stoi(b.date.substr(8, 2));
            for(auto & i : Exact_month)   i = toupper(i);
            
            if(between(Exact_month, day))
            {
              std::cout << std::endl;
              std::cout << b.commit  << std::endl;
              std::cout << b.name    << std::endl;
              std::cout << b.date    << std::endl;
              std::cout << b.message << std::endl;
            }
          }
        }
        std::cout << std::endl;
        break;
      default:
        break;
		}
	}while(opt != 5);
  
  return 0;
}




