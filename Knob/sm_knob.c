#include<stdio.h>

enum {

	state_00 = 0,
	state_11,
	state_01_cw, 
	state_01_ccw,
	state_10_cw,
	state_10_ccw,
};


typedef enum {

	P_LEFT,
	P_RIGHT,
	P_MAX
	
} KNOB_CH;


typedef struct {

	bool_t PortA[P_MAX];
	bool_t PortB[P_MAX];
	
} Knob_Input;


int8_t state = state_00;
int8_t value[P_MAX];

void Knob_Pin_Read(KNOB_CH rch) {
	
	
	switch(rch) {
	
		case P_LEFT :
		
			Knob_Input.PortA[rch] = RH850_GPIO_GetState(0xAA);
			Knob_Input.PortB[rch] = RH850_GPIO_GetState(0xAB);
			
			if((state != state_00) && (Knob_Input.PortA[rch] == state_00) && (Knob_Input.PortB[rch] == state_00)) {
				
				state = state_00;
			}
			
			else if((state != state_11) && (Knob_Input.PortA[rch] == state_11) && (Knob_Input.PortB[rch] == state_11)) { 
		
				state = state_11;
			}
			
			else if((state == state_00) && (Knob_Input.PortA[rch] == state_00) && (Knob_Input.PortB[rch] == state_11)) {
				
				state = state_01_ccw;
			}
			
			else if((state == state_00) && (Knob_Input.PortA[rch] == state_11) && (Knob_Input.PortB[rch] == state_00)) {
				
				state = state_10_cw;
			}
			
			
			else if((state == state_11) && (Knob_Input.PortA[rch] == state_00) && (Knob_Input.PortB[rch] == state_11)) {
				
				state = state_01_cw;
			}
			
			else if((state == state_11) && (Knob_Input.PortA[rch] == state_11) && (Knob_Input.PortB[rch] == state_00)) {
				
				state = state_10_ccw;
			}
			
			
			//(5ms 딜레이) 
			break;
			
			
		
		
		case  P_RIGHT :
			
			Knob_Cur.CurA[rch] = RH850_GPIO_GetState(0xAC);
			Knob_Cur.CurB[rch] = RH850_GPIO_GetState(0xAD);
			
			if((state != state_00) && (Knob_Input.PortA[rch] == state_00) && (Knob_Input.PortB[rch] == state_00)) {
				
				state = state_00;
			}
			
			else if((state != state_11) && (Knob_Input.PortA[rch] == state_11) && (Knob_Input.PortB[rch] == state_11)) { 
		
				state = state_11;
			}
			
			else if((state == state_00) && (Knob_Input.PortA[rch] == state_00) && (Knob_Input.PortB[rch] == state_11)) {
				
				state = state_01_ccw;
			}
			
			else if((state == state_00) && (Knob_Input.PortA[rch] == state_11) && (Knob_Input.PortB[rch] == state_00)) {
				
				state = state_10_cw;
			}
			
			
			else if((state == state_11) && (Knob_Input.PortA[rch] == state_00) && (Knob_Input.PortB[rch] == state_11)) {
				
				state = state_01_cw;
			}
			
			else if((state == state_11) && (Knob_Input.PortA[rch] == state_11) && (Knob_Input.PortB[rch] == state_00)) {
				
				state = state_10_ccw;
			}
			
			//(5ms 딜레이) 
			break;
			
			
		case default :
			
			break;
	
	}
}


void Knob_Scan(KNOB_CH rch) {
	
	
	Knob_Pin_Read(rch);
	
	
	switch(state) {
	
			case state_00 :
					
				Knob_Pin_Read(rch);
				
				break;
			
			
			case state_11 :
				
				Knob_Pin_Read(rch);
		
				break;
			
			
			case state_01_cw :
			
				Knob_Pin_Read(rch);
				
				if(state == state_00) {
					
					prinf("Knob : state_01_cw\n");
					value[rch]++;
				}
				break;	
				
			case state_01_ccw :
				
				Knob_Pin_Read(rch);
				
				if(state == state_11) {
					
					printf("Knob : state_01_ccw\n");
					value[rch]--;
				}
				break;
				
				
			case state_10_cw :
			
				Knob_Pin_Read(rch);
				
				if(state == state_11) {
					
					printf("Knob : state_10_cw\n");
					value[rch]++;
				}
				break;
			
			case state_10_ccw :
			
				Knob_Pin_Read(rch);
				
				if(state == state_00) {
					
					printf("Knob : state_10_ccw\n");
					value[rch]--;
				}
				break;
			
			case default :
				
				break;	
	}
	
}


int main(void) {

	while(1){	
		Knob_Scan(rch);
	}
}
