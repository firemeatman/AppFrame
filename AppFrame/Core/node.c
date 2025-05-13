#include "node.h"

//static Node_Struct _rootNode = {
//	.name = "RootNode",
//	.childListHead = LIST_HEAD_INIT(_rootNode.childListHead),
//	.childNum = 0,
//	.parent = APP_NULL,
//};

#define __ZERO_SAFE_DEC(n) do{\ 
	if (n != 0) {(n)--;}\
}while(0);


static void _init_node(Node_Struct* node);


static void _init_node(Node_Struct* node)
{
	node->list = LIST_HEAD_INIT(node->list);
	node->childNodeList = APP_NULL;
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
	}
	//else {
	//	Node_add_child(&_rootNode, new_node);
	//}

leave:
	if (status<0) {
		APP_SAFE_FREE(new_node)
	}
	return new_node;
}


void Node_delete(Node_Struct* node)
{
	struct Node_Struct* nodePos;
	struct Node_Struct* childNodeList = node->childNodeList;

	if (!node) {
		return;
	}

	Node_moveout(node);

//TODO: 需要遍历删除
	//list_for_each_entry(nodePos, &(childNodeList->list), list) {
	//	Node_delete(node);
	//}

	//APP_SAFE_FREE(node);
}


int Node_add_child(Node_Struct* node, Node_Struct* child)
{
	if (child->parent || child == APP_NULL) {
		return -1;
	}

	// 没有子节点
	if (!(node->childNodeList)) {
		node = child;
		node->childNum = 1;
	}else { // 已有就加到末尾
		list_add_tail(&(child->list), &(node->childNodeList));
		node->childNum++;
	}
	
	child->parent = node;

	return 0;
}


int Node_reparent(Node_Struct* node, Node_Struct* new_parent)
{
	if (!(node->parent) || new_parent == APP_NULL) {
		return -1;
	}
	if (Node_moveout(node) < 0) {
		return -1;
	}
	
	node->parent = new_parent;
	Node_add_child(node->parent, node);

	return 0;
}


int Node_moveout(Node_Struct* node)
{
	if (!node) {
		return -1;
	}
	if (!list_singel(node->list)) {
		list_del(node->list);
	}
	__ZERO_SAFE_DEC(node->parent->childNum);
	node->parent = APP_NULL;
	
	return 0;
}


int Node_count_child_num(Node_Struct* node)
{
	struct Node_Struct* nodePos;
	struct Node_Struct* childNodeList = node->childNodeList;
	int num = 0;

	if (!node) {
		return -1;
	}
	
	list_for_each_entry(nodePos, &(childNodeList->list), list){
		num++;
	}

	return num;
}


Node_Struct* Node_find_child(Node_Struct* node, Node_Struct* child)
{
	struct Node_Struct* nodePos;
	struct Node_Struct* childNodeList = node->childNodeList;

	if (!node) {
		return APP_NULL;
	}

	list_for_each_entry(nodePos, &(childNodeList->list), list) {
		if (nodePos == child) {
			return nodePos;
		}
	}

	return APP_NULL;
}

