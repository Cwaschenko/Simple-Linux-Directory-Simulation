#include "terminal.hpp"

Terminal::Terminal()
{
	this->fs = new FileSystem;
}

void Terminal::Run()
{
	bool ExitCalled = false;
	std::string input = "";
	std::string cmd = "";
	std::string node = "";
	std::string AdditionalNode = "";

		
	while (!(ExitCalled))
	{
		std::cout << "$ ";	
		std::getline(std::cin, input);
		std::stringstream ss(input);
		ss >> cmd;
		
		if (input == "ls") 
		{
			std::cout << fs->ls()+"\n";
		}			
		else if (cmd == "mkdir") 
		{
			ss >> node;
			std::cout << fs->mkdir(node)+"\n";
		}
		else if (cmd == "cd")
		{
			ss >> node;
			std::cout << fs->cd(node)+"\n";
		}
		else if (input == "pwd")
		{
			std::cout << fs->pwd()+"\n";
		}
		else if (cmd == "touch") 
		{
			ss >> node;
			std::cout << fs->touch(node)+"\n";
		}
		else if (cmd == "mv")
		{
			ss >> node >> AdditionalNode;
			std::cout << fs->mv(node, AdditionalNode)+"\n";
		}		
		else if(cmd == "rm")
		{
			ss >> node;
			std::cout << fs->rm(node)+"\n";
		}
		else if (input== "exit")
		{
			ExitCalled = true;
		}
		input = "";
		cmd = "";
		node = "";
	}	
}
