#include "tetfoo.hpp"

void fieldgentest(){
	Field F;
	for (uint8_t i=0; i<20; i++){
			for (uint8_t j=0; j<10; j++){
				F.dot[i][j]=rand()%9;
			}
	}
	F.print();
}


void tetragentest(){
	for (uint8_t type=0; type<7; type++){
		for (uint8_t color=1; color<9; color++){
			Tetramino T(type, color);
			for (uint8_t rotations=0; rotations<4; rotations++){
				T.rotate();
				T.print();
			}
		}
	}
	
}

void movedown(Tetramino* t, Field* f){
	t->i++;
	if (!everything_is_fine(t,f)){
		t->i--;
		put(t,f);
	}
	
}
void moveright(Tetramino* t, Field* f){
	t->j++;
	if (!everything_is_fine(t,f)){
		t->j--;
	}
	
}
void moveleft(Tetramino* t, Field* f){
	t->j--;
	if (!everything_is_fine(t,f)){
		t->j++;
	}
	
}

bool everything_is_fine(Tetramino* t, Field* f){
		if (DBG1){return true;}
		uint8_t globali, globalj;
		for (uint8_t i=0; i<4;i++){
			for (uint8_t j=0; j<4;j++){
				globali=t->i+i;
				globalj=t->j+j;
				if (t->dot[i][j] && (globali>=20 || globalj>=10)){	//outside the field
					return false;
				}
				if (t->dot[i][j] && f->dot[globali][globalj]){		//intersection with field
					return false;
				}
			}
		}
		return true;	//No intersections, tetramino in the field
}

void tetrado(uint8_t cmd, Tetramino* t, Field* f){
	/*
	 * 	do something
	 * 	'l' - move tetramino left	
	 * 	'r' - move tetramino right		
	 * 	'R' - rotate tetramino
	 * 	'd' - drop
	 * 	't' - tick
	*/
	Tetramino R=*t;
	Tetramino* r=&R;
	switch(cmd){					//cmd manager
		case 'l':
			moveleft(t,f);		//moving R left
			break;
		case 'r':
			moveright(t,f);		//moving R right
			break;
		case 'R':
			R.rotate();	//Hmmm... And yet it turns
			break;
		case 't':
			movedown(t,f);	//Hmmm... And yet it turns
			break;
		case 'd':
			while (everything_is_fine(r,f)){	//moving it down
				R.i++;							//and down
			}
			R.i--;								//one jump and...
			break;
		default:
			throw "Incorrect command";
	}
	if (everything_is_fine(r,f)){	//OK, that's fine
		*t=R;
		return;
	} else {						//OK, that's not fine
		return;
	}
}

void put(Tetramino* t, Field* f){	
	uint8_t globali, globalj;
		for (uint8_t i=0; i<4;i++){
			for (uint8_t j=0; j<4;j++){
				globali=t->i+i;
				globalj=t->j+j;
				if (t->dot[i][j] && (globali>=20 || globalj>=10)){	//outside the field
					throw "Sorry, master, but i can't place this tetramino here";;
				}
				if (t->dot[i][j] && f->dot[globali][globalj]){		//intersection with field
					throw "Sorry, master, but i can't place this tetramino here";
				}
				if (t->dot[i][j]){				//only if [i][j] exists
					f->dot[globali][globalj]=t->dot[i][j];
				}
			}
		}
}

