#include "catch/catch.hpp"
#include "../node.hpp"

TEST_CASE ("Node")
{
	Node n("root",'d');
	CHECK ("root" == n.GetName());
	CHECK ('d' == n.GetType());
	CHECK (nullptr == n.GetParent());
	CHECK (0 == n.GetChildren().size());

	Node * child = new Node ("child",'f');
	n.AddChild(child);
	CHECK (child == n.GetChild("child"));
	CHECK((&n == child->GetParent()));

	n.AddChild("second",'f');
	CHECK ('f' == n.GetChild("second")->GetType()); 

	Node * parent = new Node ("parent", 'd');
	n.SetParent (parent);
	CHECK (parent == n.GetParent());

	CHECK(2 == n.GetChildren().size());
	n.RemoveChild("second");
	CHECK(1 == n.GetChildren().size());

	delete child;
	delete parent;
}
