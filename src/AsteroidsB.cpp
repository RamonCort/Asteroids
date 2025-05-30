#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<list>
#include<cstdlib>
using namespace std;

#define color SetConsoleTextAttribute
#define ARRIBA 72
#define  IZQUIERDA 75
#define DERECHA 77 
#define ABAJO 80
#define ENTER 13
void  cursor(int x, int y){
	HANDLE hprincipal;
	hprincipal= GetStdHandle (STD_OUTPUT_HANDLE);
	COORD possion;
	possion.X = x;
	possion.Y = y;
	SetConsoleCursorPosition(hprincipal, possion);
}
void ocultar(){
	HANDLE hprincipal;
	hprincipal= GetStdHandle (STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cdi;
	cdi.dwSize = 2;
	cdi.bVisible= FALSE;
	SetConsoleCursorInfo(hprincipal,&cdi);	
}
void MARGEN_LIMITE(){
	HANDLE hprincipal;
	hprincipal= GetStdHandle (STD_OUTPUT_HANDLE);
	for (int i=2; i<120;i++){
		color(hprincipal, 8);
		cursor(i,3);printf("%c",205);
	    cursor(i,28);printf("%c",205);
	}for(int i=4; i<28;i++){
		cursor(2,i); printf("%c",186);
		cursor(119,i); printf("%c",186);
		
		
	}
	cursor (2,3);printf("%c",201);
	cursor (2,28);printf("%c",200);
	cursor (119,3);printf("%c",187);
	cursor (119,28);printf("%c",188);
}
class MOVIL{
	int x,y;
	int vida;
	int oportunidades;
	int nave;
	public:
		MOVIL(int _x, int _y, int _vida, int _oportunidades, int _nave): x(_x),y(_y),vida(_vida), oportunidades(_oportunidades) ,nave(_nave){}
		int X(){return x;}
		int Y(){return y;}
		int go(){return oportunidades;}
		void vid() {vida --;}
		void vid2(){ vida =3;}
		void dibujar();
		void borrar();
		void mover();
		void Mostrar_vida();
		void death();
		
};
void MOVIL::dibujar(){
    HANDLE hprincipal;
    hprincipal = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (nave){
    case 1:
        color(hprincipal, 5);
        cursor(x, y); printf("  %c", 94);
        color(hprincipal, 6);
        cursor(x, y + 1); printf(" %c%c%c", 47, 207, 92);
        color(hprincipal, 5);
        cursor(x, y + 2); printf("%c%c %c%c", 60, 229, 229, 62);
        break;
    case 2:
        color(hprincipal, 3);
        cursor(x, y); printf("  %c", 65);
        color(hprincipal, 5);
        cursor(x, y + 1); printf(" %c%c%c", 40, 207, 41);
        color(hprincipal, 7);
        cursor(x, y + 2); printf("%c%c %c%c", 174, 190, 190, 175);
        break;
    case 3:
        color(hprincipal, 4);
        cursor(x, y); printf("  %c", 143);
        color(hprincipal, 7);
        cursor(x, y + 1); printf(" %c%c%c", 60, 190, 62);
        color(hprincipal, 3);
        cursor(x, y + 2); printf("%c%c %c%c", 174, 254, 254, 175);
        break;
    case 4:
        color(hprincipal, 8);
        cursor(x, y); printf("  %c", 143);
        color(hprincipal, 3);
        cursor(x, y + 1); printf(" %c%c%c", 174, 220, 175);
        color(hprincipal, 1);
        cursor(x, y + 2); printf("%c%c %c%c", 241, 190, 190, 241);
        break;
    }
}
void MOVIL::borrar(){
	cursor(x,y);   printf("       ");
	cursor(x,y+1); printf("       ");
	cursor(x,y+2); printf("       ");
}
void MOVIL::mover(){
	borrar();
	if (GetAsyncKeyState(VK_LEFT) && x > 3 or GetAsyncKeyState('A')  && x > 3 ) {
        x--;
    }
    if (GetAsyncKeyState(VK_RIGHT)  && x + 8 < 119 or GetAsyncKeyState('D')  && x + 8 < 119) {
        x++;
    }
    if (GetAsyncKeyState(VK_UP)  && y > 4 or GetAsyncKeyState('W')  && y > 4) {
        y--;
    }
    if (GetAsyncKeyState(VK_DOWN) && y + 3 < 28 or GetAsyncKeyState('S')  && y + 3 < 28) {
        y++;
    }

    if (GetAsyncKeyState('V') ) {
    	HANDLE hprincipal;
    hprincipal = GetStdHandle(STD_OUTPUT_HANDLE);
    	color(hprincipal, 5);
        cursor(58, 14); printf("PAUSE");
        cursor(42, 15); printf("Press any key to continue with the game");
        system("pause> NUL");
        cursor(58, 14); printf("                                                   ");
        cursor(42, 15); printf("                                                   ");
    }

    dibujar();
    Mostrar_vida();
	 
}
		

void MOVIL::Mostrar_vida(){
	cursor(45,2); printf("Opportunities %i",oportunidades);
	cursor(84,2); printf("Lives");
	cursor(90,2); printf("     ");
	for(int i=0; i<vida; i++){
		cursor(90+i,2);printf("%c",157);
	}
	
}
void MOVIL::death(){
	
	if (vida==0){
	HANDLE hprincipal;
	hprincipal= GetStdHandle (STD_OUTPUT_HANDLE);
		borrar();
		color(hprincipal, 4);
		cursor(x,y); printf(" '''' ");
		cursor(x,y+1); printf(" ''*' ");
		cursor(x,y+2); printf("  .** . ");
		Sleep(200);
		borrar();
		cursor(x,y); printf("''*");
		cursor(x,y+1); printf("''");
		cursor(x,y+2); printf(" '' ");
		Sleep(200);
		borrar();
			oportunidades--;
			vida=3;
			Mostrar_vida();
			dibujar();
	}


}
void insertarPuntaje(int puntajes[], int nuevoPuntaje, int size) {
    for (int i = size - 1; i >= 0; --i) {
        if (i == 0 || puntajes[i - 1] >= nuevoPuntaje) {
            puntajes[i] = nuevoPuntaje;
            break;
        }
        puntajes[i] = puntajes[i - 1];
    }
}
class Item{
	int x,y;
	int counter;
	public:
	Item(int _x, int _y): x(_x),y(_y){}
	int X(){return x;}
	int Y(){return y;}
	void dibujar();
	void mover();
	void colision(class MOVIL &N);
	
		
};
void Item::dibujar(){
	HANDLE hprincipal;
	hprincipal= GetStdHandle (STD_OUTPUT_HANDLE);
	int a = 0;

		a = rand()%8 +1;
	color(hprincipal, a);
	
	cursor(x,y); printf("%c",207);
	
}
void Item::mover(){
	counter++;
    if (counter % 3 == 0) { 
	cursor(x,y);printf("  ");
	y++;
	if (y>27){
		x=rand()%113 +4;
		y=4	;
	}
	dibujar();
}
}
void Item::colision(class MOVIL &N){
	if(x >= N.X() && x< N.X() +5 && y>= N.Y() && y<N.Y() +3)
	{
		N.vid2();
		N.borrar();
		N.dibujar();
		N.Mostrar_vida();
		x=rand()%113 +4;
		y=4	;
		
	}
}
class AST{
	int x,y;
	public:
	AST(int _x, int _y): x(_x),y(_y){}
	int X(){return x;}
	int Y(){return y;}
	void dibujar();
	void mover();
	void colision(class MOVIL &N);
	
};
void AST::dibujar(){
	HANDLE hprincipal;
	hprincipal= GetStdHandle (STD_OUTPUT_HANDLE);

	color(hprincipal, 4);
	
	cursor(x,y); printf("%c",184);
	
}
void AST::mover(){
	cursor(x,y);printf(" ");
	y++;
	if (y>27){
		x=rand()%113 +4;
		y=4	;
	}
	dibujar();
	
}
void AST::colision(class MOVIL &N){
	if(x >= N.X() && x< N.X() +5 && y>= N.Y() && y<N.Y() +3)
	{
		N.vid();
		N.borrar();
		N.dibujar();
		N.Mostrar_vida();
		x=rand()%113 +4;
		y=4	;
		
	}
}
class Proyectil{
		int x, y;
		public:
		Proyectil(int _x, int _y): x(_x), y(_y){}
		int X(){return x;}
		int Y(){return y;}
		void mover ();
		bool fuera ();
			
	};
	void Proyectil::mover(){
		cursor(x,y); printf(" ");
		 y--;
		cursor (x,y); printf("*");
		
	}
	bool Proyectil::fuera()
	{
		if ( y == 4) return true;
		return false;
	}

    int seleccionar_nave() {
    int opciones[4] = { 1, 2, 3, 4 };
    int seleccion = 0;
    bool seleccionado = false;
    HANDLE hprincipal = GetStdHandle(STD_OUTPUT_HANDLE);

    while (!seleccionado) {
        color(hprincipal, 6);
        cursor(47, 7); printf("Choose your space craft style");
        color(hprincipal, 6);
        cursor(43 , 9); printf("Press the arrows to change the cursor");
        color(hprincipal, 6);
        cursor(43, 11); printf("Press Enter to select the spacecraft");
        color(hprincipal, 5);
        cursor(30, 18); printf("  %c", 94);
        color(hprincipal, 6);
        cursor(30, 19); printf(" %c%c%c", 47, 207, 92);
        color(hprincipal, 5);
        cursor(30, 20); printf("%c%c %c%c", 60, 229, 229, 62);

        color(hprincipal, 3);
        cursor(50, 18); printf("  %c", 65);
        color(hprincipal, 5);
        cursor(50, 19); printf(" %c%c%c", 40, 207, 41);
        color(hprincipal, 7);
        cursor(50, 20); printf("%c%c %c%c", 174, 190, 190, 175);

        color(hprincipal, 4);
        cursor(70, 18); printf("  %c", 143);
        color(hprincipal, 7);
        cursor(70, 19); printf(" %c%c%c", 60, 190, 62);
        color(hprincipal, 3);
        cursor(70, 20); printf("%c%c %c%c", 174, 254, 254, 175);

        color(hprincipal, 8);
        cursor(90, 18); printf("  %c", 143);
        color(hprincipal, 3);
        cursor(90, 19); printf(" %c%c%c", 174, 220, 175);
        color(hprincipal, 1);
        cursor(90, 20); printf("%c%c %c%c", 241, 190, 190, 241);

        color(hprincipal, 2);
        cursor(30 + seleccion * 20 + 2, 21); printf("^");
        cursor(30 + seleccion * 20 + 2, 22); printf("|");
        cursor(30 + seleccion * 20 + 1, 23); printf("|%c|", 'A' + seleccion);


        if (kbhit()) {
            char tecla = getch();
            switch (tecla) {
            case IZQUIERDA:
            cursor(30 + seleccion *20 + 2, 21); printf("  ");
            cursor(30 + seleccion * 20 +2, 22); printf("  ");
            cursor(30 + seleccion *20 + 1, 23); printf("   ");
                seleccion = (seleccion - 1 + 4) % 4;
                break;
            case DERECHA:
            	cursor(30 + seleccion * 20 + 2, 21); printf("  ");
                cursor(30 + seleccion *20 +2, 22); printf("  ");
                cursor(30 + seleccion *20 +1, 23); printf("   ");
                seleccion = (seleccion + 1) % 4;
                break;
            case ENTER:
                seleccionado = true;
                break;
            }
            	MARGEN_LIMITE();
        }
    }
    return opciones[seleccion];
}

int main()
{
 int top[5] = {0, 0, 0, 0, 0};
	HANDLE hprincipal;
	hprincipal= GetStdHandle (STD_OUTPUT_HANDLE);
	

	while (true) { 
	system("cls");
	ocultar();
    MARGEN_LIMITE();
    cursor(50, 14);
    printf("Welcome to the game ");
    cursor(44, 15);
    printf("Press any key to enter the game");
    cursor(50, 20);
    system("pause > NUL");
    cursor(50, 14);
    printf("                                                   "); 
    cursor(44, 15);
    printf("                                                   ");  
     cursor(50, 20);
    printf("                                                   ");  

    int nave_seleccionada=seleccionar_nave();
    system("cls");
	ocultar();
 MARGEN_LIMITE();
 cursor(50, 5);
 color(hprincipal, 4);
    printf("How to play");
    cursor(24, 7);
    color(hprincipal, 5);
    printf("Shoot and destroy the highest number of asteroids to accumulate points");
    cursor(18, 8);
    printf("Be careful because if the asteroids collide with your spacecraft, it will deduct lives");
    cursor(19, 9);
    printf("Every three lives lost will subtract one chance, and you have three chances in total");
    cursor(50, 10);
    printf("But don't worry!");
    cursor(5, 11);
    printf("Within the game there is an item that changes colors which will refill the three lives of the attempt you are in.");
    cursor(51, 13);
    color(hprincipal, 1);
    printf("Game Controls");
    cursor(20, 16);
    color(hprincipal, 7);
    printf("W ->UP");
    cursor(10, 18);
    color(hprincipal, 7);
    printf("A->LEFT");
     cursor(20, 18);
    color(hprincipal, 7);
    printf("S->DOWN");
     cursor(30, 18);
    color(hprincipal, 7);
    printf("D->RIGHT");
    cursor(90, 16);
    color(hprincipal, 7);
    printf("(%c)->UP",94);
    cursor(79, 18);
    color(hprincipal, 7);
    printf("(%c)->LEFT",60);
     cursor(90, 18);
    color(hprincipal, 7);
    printf("(v)->DOWN");
     cursor(101, 18);
    color(hprincipal, 7);
    printf("(%c)->RIGHT",62);
    cursor(50, 18);
    color(hprincipal, 7);
    printf("(%c%c) -> Bullets",95,95);
    cursor(53, 19);
    color(hprincipal, 7);
    printf("(SPACE)");
    cursor(52, 23);
     color(hprincipal, 7);
    printf("'V'->PAUSE");
 
    
    system("pause > NUL");
    system("cls");
	ocultar();
    MARGEN_LIMITE();
 Item I(6,7);
	MOVIL N(50,20,3,3,nave_seleccionada);
	N.dibujar();
	N.Mostrar_vida();
	


list<AST*> A;
list<AST*>::iterator itA;
for(int i=0; i<5; i++){
	A.push_back(new AST(rand()%75 +3,  rand()%5 +4));
	
}

list<Proyectil*> B;
list<Proyectil*>::iterator it;
	bool game_over;
	game_over = false;
	int puntaje = 0;
    int sleep_time = 30;  
    int incremento_velocidad = 5;  
    
	while(!game_over){
		
	
				HANDLE hprincipal;
	hprincipal= GetStdHandle (STD_OUTPUT_HANDLE);
	int a = 0;

		a = rand()%8 +1;
	color(hprincipal, a);
		cursor (4,2); printf("SCORE %i", puntaje);
	
		 if (GetAsyncKeyState(VK_SPACE)) {
            B.push_back(new Proyectil(N.X() + 2, N.Y() - 1));
        }
		 for(it = B.begin(); it != B.end () ; it++)
		 {
		 	
		 	(*it)->mover();
		 	if((*it)->fuera()){
		 		cursor ((*it)->X(), (*it)->Y()); printf (" ");
		 		delete(*it);
		 		it = B.erase (it);
			 }
		 }
		for(itA = A.begin(); itA != A.end(); itA ++){
			(*itA)-> mover();
			(*itA)-> colision(N);
			
		}
		for(itA = A.begin(); itA != A.end(); itA++){
			for (it= B.begin(); it != B.end (); it++){
				if((*itA)-> X () == (*it)-> X() && ((*itA)-> Y() +1 == (*it)->Y() || (*itA)->Y() == (*it)-> Y() ))
				{
				 cursor ((*it)->X(), (*it) -> Y()); printf (" ");
				 delete(*it);
				 it= B.erase(it);
				 A.push_back (new AST(rand()%75+3, 4));
				 cursor ((*itA)->X(), (*itA) -> Y()); printf (" ");
				 delete(*itA);
				 itA= A.erase(itA);
				 puntaje += 10;
				 
			
				  if (puntaje % 30 == 0 && sleep_time > incremento_velocidad) {
                        sleep_time -= incremento_velocidad;
    
				 
				}
				
			}
			
		}
	}
	 if (puntaje >= 30){

					I.dibujar();
					I.mover();
					I.colision(N);
				}
		if( N.go() == 0) {
		game_over = true;
		}
        N.death();
		N.mover();
		
		Sleep(sleep_time);
	}

        system("cls");
     HANDLE hprincipal;
	hprincipal= GetStdHandle (STD_OUTPUT_HANDLE);
        MARGEN_LIMITE();
        cursor(55, 10);
        color(hprincipal, 4);
        printf("GAME OVER");
        cursor(52, 12);
        printf("Your score was %i",puntaje);
    insertarPuntaje(top, puntaje, 5);
    color(hprincipal, 7);
        cursor(52,14);
        printf("Mejores 5 puntajes:\n");
        
        for (int i = 0; i < 5; i++) {
        	color(hprincipal, 6);
        	cursor(63,17 + i);
            printf("%i\n", top[i]);
            cursor (55,17+i);
            printf("Top %i\n",  i+1);
    
        }
        cursor(39, 15); color(hprincipal, 7);
        printf("Press 'L' to exit the game or 'C' to restart");
        bool exit_game = false;
while (!exit_game) {
    if (kbhit()) {
        char key = getch();
        if (key == 'L' or key == 'l') {
            exit(0);
        } 
        if (key == 'C' or key == 'c') {
            exit_game = true;
        }
    }
}
}



    return 0;
}