
#ifndef __CORE_NODE_H_
#define __CORE_NODE_H_

#ifdef __cplusplus 
extern "C" {
#endif  //__cplusplus


#include "Memory/mem.h"
#include "dataStruct/list.h"


typedef struct {
	const char* name;

	struct list_head childListHead;
	int childNum;
	struct Node_Struct* parent;
	//int refCount;
} Node_Struct;


Node_Struct* Node_create(Node_Struct* parent);
int Node_delete(Node_Struct* node);

// ����ӽڵ㡣�½ڵ�child����û�и��ڵ㣬����������Node_reparent()��
int Node_add_child(Node_Struct* node, Node_Struct* child);
// ɾ���ӽڵ㡣�����ͷ�Node���ڴ档
int Node_remove_child(Node_Struct* node, Node_Struct* child);
// �������ڵ㡣node�������и��ڵ㣬���û�и��ڵ������Node_add_child()��
int Node_reparent(Node_Struct* node, Node_Struct* new_parent);

int Node_get_node_num();


#ifdef __cplusplus
}
#endif  //__cplusplus

#endif