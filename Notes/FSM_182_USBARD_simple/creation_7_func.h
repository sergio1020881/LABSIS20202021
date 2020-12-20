/*creation_7_func.h*/
#ifdef _CREATION_7_FUNC_H_
#else
#define _CREATION_7_FUNC_H
//PROTOTYPE
/***FUNCTION TITLES***/
/***Coloca uma string numa variavel tipo apontador allocando tamanho automatico***/
char* Putstr(char* str);
/***Lê stdin e aloca automaticamente espaço em memória***/
char* ReadConsole(FILE *stream, size_t n);
/***lê apenas numeros de uma string***/
int getnum(int min, int max);
/***preenche vector de tamanho size por num***/
int* fillvec(int num, int size);
/***ReadFiletoMem***/
void* ReadFiletoMem(void* datatype,FILE* filename);
/***GetChar***/
unsigned char GetChar();
/***ReadConsoleR***/
char* ReadConsoleSer(FILE* stream);
/***gets the number out of a string***/
int getnumber(char* x);
/*******/
int infor(char* inf, int Size_Inf, FILE* stream);
/*******/
int SetupSerial(int fd,struct termios *oldtio,struct termios *newtio,speed_t speed);
/*******/
int ReadInt(int nmin, int nmax);
/*******/
char *Write(int fd,char *string,char *end);
/*******/
#endif
