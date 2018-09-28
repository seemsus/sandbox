#include <iostream>
#include <cstring>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <regex>
#include <map>

class Counter
{
	public:
	std::string Name;
	int Comment;
	int Code;
	bool deleted;
	
	void CntRst()
	{
		Comment = 0;
		Code = 0;
		deleted = false;
	}
};

std::vector<Counter> list;

int DiffCount(std::string input)
{
	//regular expressions
	/*
	try{
		std::regex test("(.*\*\/)");
	}
	catch (const std::regex_error& e) {
        std::cout << "regex_error caught: " << e.what() << '\n';
        if (e.code() == std::regex_constants::error_brack) {
            std::cout << "The code was error_brack\n";
        }
    }
	*/
	
	std::regex Diff("(diff.*)");
	std::regex Cfile("(diff --git a/.*.c b/.*.c)");
	std::regex Cppfile("(diff --git a/.*.cpp b/.*.cpp)");
	std::regex CComment_open("(.*\\/\\*.*)");
	std::regex CComment_close("(.*\\*\\/.*)");
	std::regex CppComment("(.*\\/\\/.*)");
	std::regex Plus_Code("(\\+[^\\+\\n]+)");
	std::regex Minus_Code("(\\-[^\\-\\n]+)");
	std::regex MinusPlus_Code("(\\-\\+.*)");
	std::regex Deleted("(deleted file mode .*)");
	
	
	
	std::string line;
	std::ifstream lfile(input);
	bool comment = false;
	
	if(!lfile.is_open())
		return -1; //fail to open file
	
	while(getline(lfile,line))
	{
		//if(std::regex_match(line,Diff))
		//	std::cout<<line<<std::endl;
		if(std::regex_match(line,Diff)&&(std::regex_match(line,Cfile)
			||std::regex_match(line,Cppfile)))
		{
			Counter tmp;
			tmp.Name = line;
			tmp.CntRst();
			while(getline(lfile,line))
			{
				if(std::regex_match(line,Cfile)||std::regex_match(line,Cppfile))
				{
					list.push_back(tmp);
					tmp.Name = line;
					tmp.CntRst();
				}
				else if(std::regex_match(line,Diff))
					break;
				else if(std::regex_match(line,Plus_Code)|
						std::regex_match(line,Minus_Code)|
						std::regex_match(line,MinusPlus_Code))
				{
					comment?tmp.Comment++:tmp.Code++;
					//std::cout<<line<<std::endl;
				}
				else if(std::regex_match(line,CComment_open))
					comment = true;
				else if(std::regex_match(line,CComment_close))
					comment = false;
				else if(std::regex_match(line,CppComment))
					tmp.Comment++;
				
				
				//if deleted files are not counted
				else if(std::regex_match(line,Deleted))
				{
					tmp.deleted = true;
					list.push_back(tmp);
					break;
				}
				
				//std::cout<<tmp.Name<<std::endl;
				//std::cout<<"Comments changed: "<<tmp.Comment<<std::endl;
				//std::cout<<"Code changed: "<<tmp.Code<<std::endl;
			}
			list.push_back(tmp);
		}
	}
	return 0;
}



int main(void)
{
	int result;
	std::string file{"Sample_diff"};
	result = DiffCount(file);
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
}