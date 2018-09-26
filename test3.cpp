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
  std::string start_year;
  std::string start_month;
  std::string start_day;
  std::string end_year;
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
  timeline.start_year  = argv[1];
  timeline.start_month = argv[2];
  timeline.start_day   = argv[3];
  timeline.end_year    = argv[4];
  timeline.end_month   = argv[5];
  timeline.end_day     = argv[6];
}

// helper function
bool inbetween(int start, int end, int val)
{
  if((val >= start) && (val <= end)) return true;
  return false;
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
  init(argv);
	get_Logs();
  std::string Exact_month;
  int day, year, cnt = 0;

  std::ofstream file("commit.txt");
  if(file.is_open())
  {
    for(auto i : users)
    {
      for(auto j : i.commits)
      {
        file << j.commit << "\n";
      }
    }
    file.close();
  }
  
  for(auto i : users)
	{
    for(auto j : i.commits)
    {
      year = stoi(j.date.substr(19, 5));
      if(inbetween(
        stoi(timeline.start_year),
        stoi(timeline.end_year),
        year
      ))
      {
        Exact_month = j.date.substr(4, 3);
        if(inbetween(
              Month_Day[timeline.start_month], 
              Month_Day[timeline.end_month], 
              Month_Day[Exact_month])
          )
        {
          day = stoi(j.date.substr(8, 2));
          if(inbetween(
                stoi(timeline.start_day),
                stoi(timeline.end_day),
                day)
            )
          {
            cnt++;
          }
        }
      }
    }
    std::cout<< i.name <<"\t"<< cnt <<std::endl;
    cnt = 0;
	}

  return 0;
}




