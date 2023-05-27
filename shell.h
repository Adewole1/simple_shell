#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DATA_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

#define HISTORY_FILE	".shell_history_log"
#define HISTORY_SIZE	4096

#define CMD_ZERO		0
#define CMD_ONE		1
#define CMD_TWO		2
#define CMD_THREE		3

#define STRTOK 0
#define GETLINE 0

#define TO_LOWERCASE		1
#define TO_UNSIGNED_INTEGER	2

#define NEG_BUFFER -1
#define GET_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024

extern char **environ;

/**
 * struct list_str - singly linked list
 *
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct list_str
{
	int num;
	char *str;
	struct list_str *next;
} list_data_struct;

/**
 * struct info_data - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @line_count_tag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @tag: the tag node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @history_count: the history line number count
 */
typedef struct info_data
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int line_count_tag;
	char *fname;
	list_data_struct *env;
	list_data_struct *history;
	list_data_struct *tag;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int history_count;
} data_struct;

/**
 * struct cmds - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */

typedef struct cmds
{
	char *type;
	int (*func)(data_struct *);
} commands_struct;

int isInteractive(data_struct *info);
int isDelim(char s, char *delim_str);
int isExec(data_struct *info, char *path);
int isAlpha(int c);

int shellHistory(data_struct *info);
int shellExit(data_struct *info);
int shellCd(data_struct *info);
int shellHelp(data_struct *info);
int shellTag(data_struct *info);
int unsetTag(data_struct *info, char *str);
int printTag(list_data_struct *node);
int setTag(data_struct *info, char *str);
ssize_t shellGetinput(data_struct *info);
int shellGetNextline(data_struct *info, char **ptr, size_t *length);
int printDec(int input, int fd);
void rmvComments(char *buf);
ssize_t chainedBuf(data_struct *info, char **buf, size_t *len);
void checkChainBuf(data_struct *info, char *buf,
		size_t *p, size_t i, size_t len);
ssize_t shellReadBuffer(data_struct *info, char *buf, size_t *i);
int checkChain(data_struct *info, char *buf, size_t *p);
int toInt(char *str);
char *shellDupChars(char *pathstr, int start, int stop);
char *findCmdPath(data_struct *info, char *pathstr, char *cmd);
void signalHandler(int sig_num);
void shellPuts(char *str);
int shellPutchar(char c);
int replaceTag(data_struct *info);
int replaceVariables(data_struct *info);

int shellEnv(data_struct *info);
char **getEnv(data_struct *info);
char *shellGetEnv(data_struct *info, const char *name);
int setEnv(data_struct *info, char *var, char *value);
int shellSetEnv(data_struct *info);
int shellUnsetEnv(data_struct *info);
int unSetEnv(data_struct *info, char *var);
int shellPopulateEnv(data_struct *info);

void printError(data_struct *info, char *estr);
void errorPuts(char *str);
int errorPutchar(char c);
int errToInt(char *str);
int shellPutFD(char c, int fd);
int shellPutsFDCount(char *str, int fd);

void initData(data_struct *info, char **av);
void freeData(data_struct *info, int all);
void clearData(data_struct *info);

int writeShellHistory(data_struct *info);
int readShellHistory(data_struct *info);
int addShellHistoryList(data_struct *info, char *buf, int line_count);
char *getShellHistory(data_struct *info);
int modShellHistoryLine(data_struct *info);
size_t getListDataLen(const list_data_struct *h);
char **getListDataStr(list_data_struct *head);
list_data_struct *addListNode(list_data_struct **head,
		const char *str, int num);
size_t printListData(const list_data_struct *h);
list_data_struct *getNodeStartswith(list_data_struct *node,
		char *prefix, char c);
ssize_t getIndexNode(list_data_struct *head, list_data_struct *node);
list_data_struct *addListEndNode(list_data_struct **head,
		const char *str, int num);
int deleteIndexNode(list_data_struct **head, unsigned int index);
void freeListData(list_data_struct **head_ptr);
size_t printStringList(const list_data_struct *h);

void *reAlloc(void *ptr, unsigned int old_size, unsigned int new_size);
int freePointer(void **ptr);
char *memFill(char *s, char b, unsigned int n);
void freeStrings(char **pp);

int shellMainloop(data_struct *info, char **argv);
int findCommand(data_struct *info);
void findShellCMD(data_struct *info);
void shellFork(data_struct *info);

char *toString(long int num, int base, int flags);
int strLength(char *s);
char *strJoin(char *dest, char *src);
char *strCopy(char *dest, char *src);

int strCompare(char *s1, char *s2);
char *strDup(const char *str);
char *strChrSearch(char *str, char c);
char *strJoinN(char *dest, char *src, int n);

char *strCopyN(char *dest, char *src, int n);
char **strSplit(char *str, char *d);
int replaceStr(char **old, char *new);

char *nodeStartsWith(const char *haystack, const char *needle);
char **strSplitDelim(char *str, char d);

#endif
