//PROTOTYPE
/**sergio manuel salazar dos santos 934805603**/

#include "creation_7.h"

/*FUNCOES*/
/*****Putstr*******/
char* Putstr(char* str)
{
  int i; char* ptr;
  ptr = (char*)calloc(strlen(str), sizeof(char));
  if(ptr == NULL){
    perror("NULL!\n");
    return NULL;
    
  }
  for(i=0; (ptr[i] = str[i]); i++){
    if(ptr[i] == '\0')
      break;
    
  }
  return (ptr);
  
}
/***ReadConsole***/
char *ReadConsole(FILE* stream,size_t n)
{
  int i, NBytes;
  char caracter;
  char *value=NULL;
  for(i=0, NBytes=8; (caracter=getc(stream)) != EOF; i++){
    if((i==NBytes) | (i==0)){
      NBytes=2*NBytes;
      value=(char*)realloc(value, NBytes*sizeof(char));
      if(value==NULL)
	perror(value);
      
    }
    *(value+i)=caracter;
    if(caracter=='\n'){
      *(value+i)='\0';
      break;
      
    }
    if(i == n){
      *(value+i)='\0';
      break;
      
    }
    
  }
  return value;
  
}
/***getnum***/
int getnum(int min, int max)
{
  int num;
  for(num=0; !scanf("%d",&num) || num<min || num>max ; getchar()){
    perror("loop status");
    
  }
  return num;
  
}

/**********fillvec*************/
int* fillvec(int num, int size)
{
  int* x;
  int i;
  if(size > 0){
    x=calloc(size, sizeof(int));
    for(i=0; i<=size; i++){
      x[i]=num;
      //printf("x[%d]-> %d\n",i,x[i]);//troubleshooting
      
    }
    
  }else{
    return NULL;
    
  }
  return x;
  
}
/*******ReadFiletoMem*******/
void* ReadFiletoMem(void* datatype, FILE* filename)
{
  int i , n;
  fseek(filename, 0, SEEK_SET);
  datatype=calloc(1,sizeof(*datatype));
  for(i=0, n=1; fread((datatype+i), sizeof(*datatype), 1, filename); datatype=realloc(datatype, n*sizeof(*datatype))){
    i++;
    n++;
    if(feof(filename))
      break;
    if(ferror(filename)){
      perror("status:");
      return NULL;
      
    }
    
  }
  return datatype;
  
}
/**GetChar()**/
unsigned char GetChar()
{
  unsigned char x;
  unsigned char value;			
  for(value=getchar(); x!='\n'; x=getchar());
  if(value=='\0')
    return 1;
  x='0';
  return value;
  
}
/******/
//sintaxe muito muito importante, mais importante doque a semantica.
//I learn allot reading other peoples code.
char* ReadConsoleSer(FILE* stream)
{
  int i, NBytes;
  char caracter;
  char* value=NULL;
  for(i=0, NBytes=8; (caracter=getc(stream)) != EOF;i++){
    if((i==NBytes) | (i==0)){
      NBytes=2*NBytes;
      value=(char*)realloc(value,NBytes*sizeof(char)+2);
      if(value==NULL)
	perror(value);
      
    }
    *(value+i)=caracter;
    if(caracter=='\n'){
      *(value+i)='\r';
      i++;
      *(value+i)='\n';
      i++;
      *(value+i)='\0';
      break;
      
    }
    
  }
  return value;
  
}
/******/
int getnumber(char* x)
{
  int num;
  if(sscanf(x, "%d", &num))
    return num;
  else
    return 0;
  
}
/***infor***/
int infor(char* inf, int Size_Inf, FILE* stream)
{
  int n;
  char* a;
  a=calloc(1024, sizeof(char));
  while((n=fscanf(stream, "%s", a))){
    if(strlen(a) > (Size_Inf-3)){
      printf("overflow retry.\n");
      continue;
      
    }
    strncpy(inf, a, (Size_Inf-3));
    strcat(inf, "\r\n");
    break;
    
  }
  free(a);
  return n;
  
}
/***SetSerial***/
int SetupSerial(int fd,struct termios *oldtio,struct termios *newtio,speed_t speed)
{
  //portcomunication setup file descriptor
  int c;
  
  //save old configuration and prepare newtio
  tcgetattr(fd, oldtio);
  bzero(newtio, sizeof(newtio));
  
  //BAUDRATE: Set bps rate. You could also use cfsetispeed and cfsetospeed.
  //CRTSCTS : output hardware flow control (only used if the cable has
  //          all necessary lines. See sect. 7 of Serial-HOWTO)
  //CS8     : 8n1 (8bit,no parity,1 stopbit)
  //CLOCAL  : local connection, no modem control
  //CREAD   : enable receiving characters

  //newtio->c_cflag = speed | CRTSCTS | CS8 | CLOCAL | CREAD;
  //newtio->c_cflag = speed | CS8 | CLOCAL | CREAD;
  newtio->c_cflag = speed | CS8 | CREAD;
  
  //ICANON  : enable canonical input
  //disable all echo functionality, and don't send signals to calling program

  //newtio->c_lflag = ICANON | ECHOE;
  //newtio->c_lflag = ISIG;
  //newtio->c_lflag = ECHO;
  //newtio->c_lflag = ECHOK;
  //newtio->c_lflag = FLUSHO;
  //newtio->c_lflag = ICANON;
  newtio->c_lflag = ICANON | IEXTEN;
  //newtio->c_lflag = ICANON | IEXTEN | FLUSHO;
  //newtio->c_lflag = ICANON | IEXTEN | ECHOKE;
  //newtio->c_lflag = ICANON | IEXTEN | PENDIN;
  
  //IGNPAR  : ignore bytes with parity errors
  //ICRNL   : map CR to NL (otherwise a CR input on the other computer
  //          will not terminate input)
  //otherwise make device raw (no other input processing)

  //newtio->c_iflag |= (IGNPAR | ICRNL);
  //newtio->c_iflag |= (INPCK | ISTRIP);
  newtio->c_iflag |= INPCK;
  //newtio->c_iflag |= (INPCK | ICRNL);
  
  //Raw output. first option.

  //newtio->c_oflag |= 0;
  //newtio->c_oflag |= (OPOST | ONLCR);
  newtio->c_oflag |= OPOST;
  //newtio->c_oflag &= ~OPOST;
    
  //initialize all control characters 
  //default values can be found in /usr/include/termios.h, and are given
  //in the comments, but we don't need them here
  
  newtio->c_cc[VINTR]    = 0;     // Ctrl-c -0  
  newtio->c_cc[VQUIT]    = 0;     // Ctrl-\ -0
  newtio->c_cc[VERASE]   = 0;     // del -0
  newtio->c_cc[VKILL]    = 0;     // @ -0
  newtio->c_cc[VEOF]     = 4;    // Ctrl-d -4
  newtio->c_cc[VTIME]    = 0;     // inter-character timer unused -0
  newtio->c_cc[VMIN]     = 1;     // blocking read until 1 character arrives -1
  newtio->c_cc[VSWTC]    = 0;     // '\0' -0
  newtio->c_cc[VSTART]   = 0;     // Ctrl-q -0
  newtio->c_cc[VSTOP]    = 0;     // Ctrl-s -0
  newtio->c_cc[VSUSP]    = 0;     // Ctrl-z -0
  newtio->c_cc[VEOL]     = 0;     // '\0' -0
  newtio->c_cc[VREPRINT] = 0;     // Ctrl-r -0
  newtio->c_cc[VDISCARD] = 0;     // Ctrl-u -0
  newtio->c_cc[VWERASE]  = 0;     // Ctrl-w -0
  newtio->c_cc[VLNEXT]   = 0;     // Ctrl-v -0
  newtio->c_cc[VEOL2]    = 0;     // '\0' -0
  
//now clean the modem line and activate the settings for the port
  tcflush(fd, TCIFLUSH);
  if(tcsetattr(fd, TCSANOW, newtio) != 0){
    tcsetattr(fd, TCSANOW, oldtio);
    close(fd);
    return -1;
  }
  return 0;
}
/******/
int ReadInt(int nmin, int nmax)
{
  int num;
  int flag;
  for(flag=1; flag;){
    for( num=0; !scanf("%d",&num); getchar());
    //printf("num: %d nmin: %d nmax: %d\n",num, nmin, nmax);
    if((num < nmin) || (num > nmax))
      continue;
    flag=0;
    }
  return num;
  }
char *Write(int fd,char *string,char *end)
{
  char *ordem;
  ordem=(char *)calloc(strlen(string)+strlen(end),sizeof(char));
  strcpy(ordem,string);
  strcat(ordem,end);
  if(write(fd, ordem, strlen(ordem))){
    printf("sent -> %s", ordem);
    return ordem;
  }else{
    return NULL;
 }
}
