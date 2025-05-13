#include "node.h"

static Node_Struct _rootNode = {
	.name = "RootNode",
	.childListHead = LIST_HEAD_INIT(_rootNode.childListHead),
	.childNum = 0,
	.parent = APP_NULL,
};


static void _init_node(Node_Struct* node);


static void _init_node(Node_Struct* node)
{
	node->childListHead = LIST_HEAD_INIT(_rootNode.childListHead);
	node->childNum = 0;
	node->parent = APP_NULL;
}


Node_Struct* Node_create(Node_Struct* parent)
{
	int status = 0;
	Node_Struct* new_node = APP_NULL;

	new_node = (Node_Struct*)APP_MALLOC(sizeof(Node_Struct));
	if (!new_node) {
		status = -1;
		goto leave;
	}
	_init_node(new_node);

	if (parent) {
		status = Node_add_child(parent, new_node);
		if (status < 0) {goto leave;}
	}else {
		Node_add_child(&_rootNode, new_node);
	}

leave:
	if (status<0) {
		APP_SAFE_FREE(new_node)
	}
	return new_node;
}


int Node_add_child(Node_Struct* node, Node_Struct* child)
{
	if (child->parent) {
		return -1;
	}

	list_add_tail(&(child->childListHead), &(node->childListHead));
	child->parent = node;

	return 0;
}


int Node_remove_child(Node_Struct* node, Node_Struct* child)
{
	child->parent = APP_NULL;
	list_del(child);
	return 0;
}


int Node_reparent(Node_Struct* node, Node_Struct* new_parent)
{
	if (!(node->parent)) {
		return -1;
	}
	if (Node_remove_child(node->parent, node) < 0) {
		return -1;
	}
	node->parent = new_parent;
	list_add_tail(&(node->childListHead), &(new_parent->childListHead));

	return 0;
}