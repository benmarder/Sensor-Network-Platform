

#ifndef MESSAGE_H
#define MESSAGE_H


struct Message {
	byte minimum_threshold;
	byte maximum_threshold;
  short int source; 
  short int dest;
  short int part;
  //time?
  char data[24] ;
};


#endif

