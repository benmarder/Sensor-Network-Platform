

#ifndef MESSAGE_H
#define MESSAGE_H
struct Message {
  short int source; 
  short int dest;
  short int part;
  //time?
  char data[24] ;
}


#endif
