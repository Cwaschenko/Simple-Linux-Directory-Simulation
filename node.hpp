#ifndef NODE_HPP
#define NODE_HPP
#include <iostream>
#include <string>
#include <vector>

class Node
{
	private:
		char type;
		std::string name;
		std::vector<Node*> children;
		Node* parent;
	public:
		Node();
		Node(std::string name, char type);
		void RemoveHelper(Node* subtree);
		void AddChild(Node* child);
		void AddChild(std::string name, char type);
		void SetParent(Node* parent);
		void SetType(char type);
		Node* GetChild(std::string name);	
		Node* GetParent();
		std::vector<Node*> GetChildren();	
		std::string GetName();
		char GetType();
		bool RemoveChild(std::string name);
		
};
#endif
