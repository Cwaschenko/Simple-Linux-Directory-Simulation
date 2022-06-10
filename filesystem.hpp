#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <bits/stdc++.h>
#include "node.hpp"
#include <string>


class FileSystem
{
	private:
		Node* root;
		Node* currentDirectory;
	public:
		void AddNode(Node* NewNode);
		Node* FindNode(std::string name);
		FileSystem();
		~FileSystem();
		std::string mkdir(std::string name);
		std::string touch(std::string name);
		std::string pwd();
		std::string ls();
		std::string rm(std::string name);
		std::string mv(std::string from, std::string to);
		std::string cd(std::string dirname);
		
};

#endif
