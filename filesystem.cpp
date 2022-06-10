#include "filesystem.hpp"

FileSystem::FileSystem()
{
	this->root = new Node("root", 'd');
	this->currentDirectory = this->root;

}

FileSystem::~FileSystem()
{
	this->currentDirectory = this->root;
	for(auto& CurrentNode : this->currentDirectory->GetChildren())
	{	
		this->rm(CurrentNode->GetName() );	
	}
	
	delete this->root;
}

void FileSystem::AddNode(Node* NewNode)
{
	this->currentDirectory->AddChild(NewNode);	
}

std::string FileSystem::mkdir(std::string name)
{
	if (this->currentDirectory->GetChild(name) != nullptr)
	{
		return "Error: " + name + " exists";
	}
	else
	{
		Node* NewNode = new Node(name, 'd');
		this->AddNode(NewNode);
		return "directory " + name + " created successfully";
	}
}

std::string FileSystem::touch(std::string name)
{
	if (this->currentDirectory->GetChild(name) != nullptr)
	{
		return "Error: " + name + " exists";
	}
	else
	{
		Node* NewNode = new Node(name, 'f');
		this->AddNode(NewNode);
		return "file " + name + " created successfully";
	}
}

std::string FileSystem::pwd()
{
	Node* traversalNode = this->currentDirectory;
	std::string branchList = "";
	std::vector<std::string> Branches;

	if(traversalNode->GetParent() == nullptr)
	{
		branchList = "/" + traversalNode->GetName();
	}
	else
	{
		while (traversalNode->GetParent() != nullptr) // starts at current node and works back to root
		{
			if (traversalNode->GetParent()->GetParent() == nullptr)
			{	
				Branches.push_back(traversalNode->GetName());
			}
			else
			{
				Branches.push_back("/" + traversalNode->GetName());
			}	
			traversalNode = traversalNode->GetParent();
		}

		Branches.push_back("/" + this->root->GetName() + "/");
		
		while(!Branches.empty())	
		{
			branchList += Branches.back();
			Branches.pop_back();
		}
	}
	return branchList;
}

std::string FileSystem::ls()
{
	//list all nodes in current directory
	std::string list = "";
	std::string current = "";
	Node* currentNode = nullptr;
	for(size_t i = 0; i < this->currentDirectory->GetChildren().size(); ++i)
	{
		currentNode = this->currentDirectory->GetChildren()[i]; 
		if (currentNode->GetType() == 'f')
		{
			current =  "f " + currentNode->GetName() +"\n";
		}
		else
		{
			current = "d " + currentNode->GetName() +"\n";
		}
		list += current;
	}
	return list;
}

std::string FileSystem::rm(std::string name)
{
	bool RemovedSuccessful = this->currentDirectory->RemoveChild(name);	
	if( RemovedSuccessful)
	{
		return name + " removed successfully";
	}
	else
	{
		return "No such file or directory";
	}
}

std::string FileSystem::mv(std::string from, std::string to)
{
	Node* PreExistingNode = this->FindNode(from);
	if (PreExistingNode == nullptr)
	{
		return "file not found";
	}
	else
	{
		Node* NewNode = new Node(to ,PreExistingNode->GetType());
		this->currentDirectory->RemoveChild(PreExistingNode->GetName());
		this->currentDirectory->AddChild(NewNode);
		return "file/dir renamed successfully";
	}
}

Node* FileSystem::FindNode(std::string name)
{
	Node* currentNode;
	for(size_t i = 0; i < this->currentDirectory->GetChildren().size(); ++i)
	{
		currentNode = this->currentDirectory->GetChildren()[i]; 
		if (currentNode->GetName() == name)
		{
			return currentNode;
 		}
		
	}	
	
	return nullptr;
}


std::string FileSystem::cd(std::string dirname)
{
	if (dirname == "..")
	{
		if(this->currentDirectory->GetParent() == nullptr)
		{
			return "can't change to directory ..";
		}
		else
		{
			this->currentDirectory = this->currentDirectory->GetParent();
			return this->pwd();
		}

	}
		Node* DisiredDirectory = this->FindNode(dirname);
		
	       	if (DisiredDirectory == nullptr)
		{
			return dirname + ": no such directory"; 
		}
		if (DisiredDirectory->GetType() == 'd')
		{
			this->currentDirectory = DisiredDirectory;
			return this->pwd();

		}
		else
		{
			return dirname + ": is not a directory";
		}
}
