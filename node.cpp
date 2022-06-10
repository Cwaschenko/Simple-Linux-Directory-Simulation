#include "node.hpp"

Node::Node()
{
	this->name = " ";
	this->type = ' ';	
	this->parent = nullptr;	
}

Node::Node(std::string name, char type)
{
	this->name = name;
	this->type = type;
	this->parent = nullptr;
}

void Node::RemoveHelper(Node* subtree)
{
	if(subtree->GetChildren().empty())				
		{
			for(size_t i = 0; i < this->children.size(); ++i)
			{
				if(subtree->GetName() == this->children[i]->GetName())
				{
					this->children.erase(this->children.begin() + i);
				}
			}

			delete subtree;
		}
	else
	{
		for(size_t i = 0; i < this->children.size(); ++i)
		{	
			Node* ToBeRemoved = subtree->children[i];

			if(ToBeRemoved->GetType() == 'f')
			{
				this->children.erase(this->children.begin() + i);
				delete ToBeRemoved;
			}
			else
			{
				subtree->RemoveHelper(ToBeRemoved);
			}
		
		}
	}
}
void Node::AddChild(Node* child)
{

	child->SetParent(this);
	this->children.push_back(child);
}

void Node::AddChild(std::string name, char type)
{


	Node* child = new Node(name, type);
	child->SetParent(this);
	this->children.push_back(child);
}

void Node::SetParent(Node* parent)
{
	this->parent = parent;
}

void Node::SetType(char type)
{
	this->type = type;
}

Node* Node::GetChild(std::string name)
{
	Node* DesiredChild = nullptr;
	for(size_t i = 0; i < this->children.size(); ++i)
	{
		if(this->children.at(i)->GetName() == name)
		{
			DesiredChild = this->children.at(i);
		}
	}
	return DesiredChild;

}

Node* Node::GetParent()
{
	return this->parent;
}

std::vector<Node*> Node::GetChildren()
{
	return this->children;
}

std::string Node::GetName()
{
	return this->name;
}

char Node::GetType()
{
	return this->type;
}

bool Node::RemoveChild(std::string name)
{ 
	Node* CurrentNode = nullptr; 
	for(size_t i = 0; i < this->children.size(); ++i)
	{
		CurrentNode = this->children[i];

		if(CurrentNode->GetName() == name)
		{
			if(CurrentNode->GetType() == 'f') // if node is a file, delete it from the vector then deallocate
			{
				this->children.erase(this->children.begin() + i);	
				delete CurrentNode;	
				return true;
			}
			else
			{
				this->RemoveHelper(CurrentNode);
				return true;
			}
		}
	}
	return false;
	
}	
