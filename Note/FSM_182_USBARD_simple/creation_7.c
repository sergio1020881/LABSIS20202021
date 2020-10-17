/***sergio manuel salazar dos santos***/
/***Tel:- 916919898***/
/***Rua do relogio 268, 4770-245 Joane, Vila Nova de famalicao, Braga, Portugal***/
/***CABECALHO Libraries***/
//this program is a learning finite state machine.

#include "creation_7.h"
/***MAIN***/
int main(int argc, char* argv[])
{
  //capture prog arguments.
  if(argc < 2){
    printf("Enter the board use duemilanove or mega or uno ? \n");
    return 0;
  }else if(argc < 3){
    printf("Enter a file name please \n");
    return 0;
  }else if(argc < 4){
    printf("Enter learning mode on or off \n");
    return 0;
  }
  printf("FILE -> %s\n", __FILE__);
  printf("DATE -> %s TIME -> %s\n", __DATE__, __TIME__);
  printf("DATE -> %d\n", __LINE__);
  printf("double -> %d\n", Double(5));
  //printf("Pow -> %f\n", Pow(2,5));
  printf("argv[0] (Progname) -> %s	size: %d	\n", argv[0], strlen(argv[0]));
  printf("argv[1] (Board)-> %s	size: %d	\n", argv[1], strlen(argv[1]));
  printf("argv[2] (Filename)-> %s	size: %d	\n", argv[2], strlen(argv[2]));
  printf("argv[3] (Learnmode) -> %s	size: %d	\n", argv[3], strlen(argv[3]));
  //make decisions relative income arguments.
  if(!strcmp(argv[1], "mega")){
    DEVICE = Putstr(DEVICE_1);
  }else if(!strcmp(argv[1], "duemilanove")){
    DEVICE = Putstr(DEVICE_2);
  }else if(!strcmp(argv[1], "uno")){
    DEVICE = Putstr(DEVICE_3);
  }else if(!strcmp(argv[1], "none")){
    DEVICE = Putstr(DEVICE_4);
  }else{
    printf("Board options mega or duemilanove or uno or none\n");
    return 0;
  }
  
  if(!strcmp(argv[3], "on")){
    LEARN=1;
  }else if(!strcmp(argv[3], "off")){
    LEARN=0;
  }else{
    printf("LEARN mode options on or off\n");
    return 0;
  }
  
  /***Internal Variables***/
  int errno;
  int ires, ores;
  /***USB FILE DESCRIPTOR***/
  int fd;
  struct termios oldtio,newtio;
  
  fd = open(DEVICE,O_RDWR | O_NOCTTY | O_NDELAY);
  printf("file descriptor: %d\n",fd);
  if(fd < 0){ 
	goto EXIT_2;
  }
  //if(SetupSerial(fd,&oldtio,&newtio,BAUDRATE))
   //goto EXIT_3;
  /*********************************************/
  /***nanosleep***/
  //alivea procesador.
  struct timespec* timer_1;
  timer_1 = calloc(1, sizeof(struct timespec));
  timer_1->tv_sec = 0;
  timer_1->tv_nsec = 1000000;
  struct timespec* timer_2;
  timer_2 = calloc(1, sizeof(struct timespec));
  timer_2->tv_sec = 0;
  timer_2->tv_nsec = 1000000;
  /******/
  /***Variables***/
  int i, j, n, KeyFound;
  char leitura[3][buf_size];
  char memory[4][buf_size];
  char hist[buf_size];
  char ordem[SEND];
  /***File that stores de structs***/
  FILE* fsm;
  fsm=fopen(argv[2], "a+");
  if(fsm == NULL)
    goto EXIT_1;
  //Inicialize the primary struct.
  printf("struct size:%d\n\7", sizeof(leitura));
  //saida ou estado inicial.
  strcpy(leitura[0], "0");
  strcpy(leitura[1], "0");
  strcpy(leitura[2], "0");
  strcpy(hist, "empty");
  //delay.
  printf("    Press reset button on target!!\n");
  perror("status ");
  //tcsendbreak(fd,10);
  //tcflush(fd,TCIOFLUSH);
  //tcdrain(fd);
  /***##########CICLOS MAQUINA############***/
  for(ires=0,printf("Entrada: \n");TRUE;strcpy( hist, leitura[2]),KeyFound=0){
    //ENTRADAS.
    strncpy(leitura[2],ReadConsole(stdin,buf_size),buf_size);
    
    //Entrada Serial
    /*
    for(nanosleep(timer_1,NULL);!read(fd, leitura[2], buf_size);nanosleep(timer_2,NULL));
    
    for(ires=0; ires < buf_size; ires++){
      if(leitura[2][ires] == '\r' || leitura[2][ires] == '\n'){
	leitura[2][ires] = '\0';
	break;
      }  
    }
    */
    /*********************************************/
    if(!strcmp( leitura[2], hist))
      continue;
    printf("\nleitura : %d ->  %s\n", ires, leitura[2]);
    if(!strcmp( leitura[2], "exit")){
      Write(fd, "0", "\r\n");
      goto EXIT_1;
    }
/***********************************************************************************************/
    //Search Engine
    //Line By Line Search
    for(i=0,rewind(fsm);fscanf(fsm,"%s %s %s %s\n",memory[0],memory[1],memory[2],memory[3]) != EOF; i++){
      //error check!
      if(ferror(fsm)){ 
        perror("status :");
        errno = 0;
        break;
      }
      //Search Result [Keyfound]
      KeyFound=!strcmp(leitura[0],memory[0]) && !strcmp(leitura[1],memory[1]) && !strcmp(leitura[2],memory[2]);
      if(KeyFound){
	    //printf("struct = %d ", i);
	    //printf("out ->  %s\n", memory[3]);
	    //Update
	    strcpy(leitura[0],leitura[2]);
	    strcpy(leitura[1], memory[3]);
	    //Exit Value.
	    if(!strcmp(leitura[1], "exit")){
	      Write(fd, "0", "\r\n");
	      printf("Exiting\n");
	      goto EXIT_1;
	    }else{
	      //Get number string
	      if(!sscanf(leitura[1], "%[0-9]", ordem))
	        strcpy(ordem,"0");
	      Write(fd, ordem, "\r\n");
	      break;
	    }
      }
    }//for Search
    //Jump to INIC
    if(!KeyFound){
	  Write(fd, leitura[1], "\r\n");
	  printf("No match ");
	  printf("out ->    %s\n", leitura[1]);
    }
  /***********************************************************************************/
  }//for TRUE
  //EXITS
  EXIT_1:
  perror("status: ");
  //tcflush(fd,TCIOFLUSH);
  nanosleep(timer_1,NULL);
  /* restore the old port settings */
  tcsetattr(fd, TCSANOW, &oldtio);
  close(fd);
  free(DEVICE);
  free(timer_1);
  free(timer_2);
  fclose(fsm);
  return 0;
  EXIT_2:
  perror("status: ");
  perror(DEVICE);
  free(DEVICE);
  exit(-1);
  return 0;
  EXIT_3:
  perror("status: ");
  close(fd);
  free(DEVICE);
  tcsetattr(fd, TCSANOW, &oldtio);
  
}//main
