#ifndef TERMINAL_HPP
#define TERMINAL_HPP
#include "filesystem.hpp"
#include <iostream>
#include <string>
#include <sstream>

class Terminal
{
	private:
		FileSystem* fs;
	public:
		Terminal();
		void Run();
};

#endif
