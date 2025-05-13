/*
 * @Description: ��ֲLinux2.6�ں�list.h
 * @Version: V1.0
 * @Autor: https://blog.csdn.net/qq_16933601
 * @Date: 2020-09-12 22:54:51
 * @LastEditors: Carlos
 * @LastEditTime: 2020-09-16 00:35:17
 */

#ifdef __cplusplus 
extern "C" {
#endif  //__cplusplus

#ifndef _CORE_LIST_H
#define _CORE_LIST_H
 //ԭ������ɾ����ָ���λ�ã����������޸ĳ� 0
// # define POISON_POINTER_DELTA 0
// #define LIST_POISON1  ((void *) 0x00100100 + POISON_POINTER_DELTA)
// #define LIST_POISON2  ((void *) 0x00200200 + POISON_POINTER_DELTA)


//#define NULL ((void *)0)
#define LIST_POISON1  ((void *)0)
#define LIST_POISON2  ((void *)0)

//����member��type�е�λ��
#define offsetof(type, member)  (size_t)(&((type*)0)->member)

//����member�ĵ�ַ��ȡtype����ʼ��ַ
// typeof���Ǳ�׼����
//#define container_of(ptr, type, member) ({          \
//        const typeof(((type *)0)->member)*__mptr = (ptr);    \
//    (type *)((char *)__mptr - offsetof(type, member)); })

// ptr: �ṹ���Աָ��
// type: �ṹ������
// member: �ṹ���Ա����
#define container_of(ptr, type, member) ({          \
        void* __mptr = (ptr);    \
    (type *)((char *)__mptr - offsetof(type, member)); })



//����ṹ
struct list_head
{
	struct list_head* prev;
	struct list_head* next;
};
#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head* list)
{
	list->next = list;
	list->prev = list;
}

static inline void init_list_head(struct list_head* list)
{
	list->prev = list;
	list->next = list;
}

#ifndef CONFIG_DEBUG_LIST
static inline void __list_add(struct list_head* new,
	struct list_head* prev,
	struct list_head* next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}
#else
extern void __list_add(struct list_head* new,
	struct list_head* prev,
	struct list_head* next);
#endif

//��ͷ�����
/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
#ifndef CONFIG_DEBUG_LIST
static inline void list_add(struct list_head* new, struct list_head* head)
{
	__list_add(new, head, head->next);
}
#else
extern void list_add(struct list_head* new, struct list_head* head);
#endif
//��β�����
static inline void list_add_tail(struct list_head* new, struct list_head* head)
{
	__list_add(new, head->prev, head);
}

static inline  void __list_del(struct list_head* prev, struct list_head* next)
{
	prev->next = next;
	next->prev = prev;
}

static inline void list_del(struct list_head* entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = LIST_POISON1;
	entry->prev = LIST_POISON2;
}


static inline void __list_splice(struct list_head* list,
	struct list_head* head)
{
	struct list_head* first = list->next;
	struct list_head* last = list->prev;
	struct list_head* at = head->next;

	first->prev = head;
	head->next = first;

	last->next = at;
	at->prev = last;
}
/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static inline int list_empty(const struct list_head* head)
{
	return head->next == head;
}

static inline int list_singel(const struct list_head* head)
{
	return head->next == LIST_POISON1 || head->prev == LIST_POISON2;
}

/**
 * list_splice - join two lists
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 */
static inline void list_splice(struct list_head* list, struct list_head* head)
{
	if (!list_empty(list))
		__list_splice(list, head);
}
/**
 * list_replace - replace old entry by new one
 * @old : the element to be replaced
 * @new : the new element to insert
 *
 * If @old was empty, it will be overwritten.
 */
static inline void list_replace(struct list_head* old,
	struct list_head* new)
{
	new->next = old->next;
	new->next->prev = new;
	new->prev = old->prev;
	new->prev->next = new;
}

static inline void list_replace_init(struct list_head* old,
	struct list_head* new)
{
	list_replace(old, new);
	INIT_LIST_HEAD(old);
}
/**
 * list_move - delete from one list and add as another's head
 * @list: the entry to move
 * @head: the head that will precede our entry
 */
static inline void list_move(struct list_head* list, struct list_head* head)
{
	__list_del(list->prev, list->next);
	list_add(list, head);
}

/**
 * list_move_tail - delete from one list and add as another's tail
 * @list: the entry to move
 * @head: the head that will follow our entry
 */
static inline void list_move_tail(struct list_head* list,
	struct list_head* head)
{
	__list_del(list->prev, list->next);
	list_add_tail(list, head);
}
#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define list_first_entry(ptr, type, member) \
    list_entry((ptr)->next, type, member)

#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)
/**
 * list_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define list_for_each_entry(pos, head, member)      \
	for (pos = list_entry((head)->next, typeof(*pos), member);	\
	     &pos->member != (head); 	\
	     pos = list_entry(pos->member.next, typeof(*pos), member))
 /**
  * list_for_each_prev	-	iterate over a list backwards
  * @pos:	the &struct list_head to use as a loop cursor.
  * @head:	the head for your list.
  */
#define list_for_each_prev(pos, head) \
	for (pos = (head)->prev;  pos != (head); \
        	pos = pos->prev)


#ifdef __cplusplus
}
#endif  //__cplusplus