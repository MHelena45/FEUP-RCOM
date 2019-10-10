#include "statemachine.h"

int receiverSM(unsigned char byte) {
	static int state = START;
	switch(state){
		case START: 
			if(byte == FLAG)
				state = FLAG_RCV;
			break;
		case FLAG_RCV:
			if(byte == FLAG)
				state = FLAG_RCV;
			else if(byte == A)
				state = A_RCV;
			else
				state = START;
			break;
		case A_RCV:
			if(byte == FLAG)
				state = FLAG_RCV;
			else if(byte == C_SET)
				state = C_RCV;
			else
				state = START;
			break;
		case C_RCV: 
			if(byte == (A ^ C_SET))
				state = BCC_OK;
			else if(byte == FLAG)
				state = FLAG_RCV;
			else
				state = START;
			break;			
		case BCC_OK:
			if(byte == FLAG)
				return true;
			else
				state = START;
			break;
		}
		
		return false;
}
