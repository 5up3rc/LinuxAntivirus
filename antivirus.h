#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <linux/module.h>	
#include <linux/kernel.h>	
#include <linux/init.h>		
#include <linux/fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/list.h>
#include <linux/string.h>
#include <stdbool.h>

//Linked list implementation of Queue
struct node{
        struct dentry *dir;
        struct node * next;
};


/*
 *function prototype
 */
void add_new_node(struct dentry *dir);
struct dentry *delete_node(void*);
int is_empty(void*);
void status_link(void *test);
int check_for_virus(char *filename);
int check_for_whitelist(char *filename);
int remove_garbage_value(char *data, int pagesize);
int read_file(struct file* file, char *data, int size);
#endif