
#include "MENU.h"
#include "../JOY/JOY.h"
#include "../OLED/OLED.h"
static menu_t main_menu;
static menu_t current_menu;
static uint8_t current_line = 0; // f�rste linje er linjen under tittel
static JOY_direction_t last_direction = neutral;

static unsigned int quit = 0;	//bool
	

void MENU_display_menu(menu_t menu, uint8_t curr_line) {
	if (menu.item != NULL_PTR) {
		current_menu = *menu.parent;
		MENU_back(menu);
		return;
	}
	uint8_t page = 0;
	OLED_clear_display();
	OLED_print_header(menu.title);
	OLED_goto_line(++page);

	for (uint8_t i = 0; i < menu.number_of_submenus; i++) {
		if (i == (curr_line) ) {
			OLED_print_inverted_string(menu.submenus[i]->title);
		}
		else {
			OLED_print_string(menu.submenus[i]->title);
		}
		
		OLED_goto_line(++page);
	}
	

	
	
}


menu_t* MENU_add_submenu(char* t, void(*func)(), /*uint8_t num,*/ menu_t* p) {
	
	
	p->submenus[p->number_of_submenus] = malloc(sizeof(menu_t)*5);
	//menu_t* submenu = p->submenus[p->number_of_submenus];
	
	
	p->submenus[p->number_of_submenus]->title = t;
	p->submenus[p->number_of_submenus]->number_of_submenus = 0;
	p->submenus[p->number_of_submenus]->item = *func;
	p->submenus[p->number_of_submenus]->parent = p;
	p->submenus[p->number_of_submenus]->submenus = malloc(sizeof(menu_t)*5);
	
	p->number_of_submenus++;
	
	return p->submenus[p->number_of_submenus-1];



}



void MENU_choose(menu_t choice) {
	
	/*OLED_emphasized_inverted_string(choice.title);*/
	_delay_ms(1000);
	
	if (choice.item == NULL_PTR) {
		if (choice.submenus[0] != NULL_PTR) {
			MENU_display_menu(choice,0);
		}
	}
	else {
		OLED_clear_display();
		choice.item();
	}
	
}


void MENU_back(menu_t this) {
	
	if (this.parent != NULL_PTR) {
		MENU_display_menu(*this.parent,0);
	}/*
	else {
		OLED_clear_display();
		
		OLED_goto_line(4);
		OLED_goto_column(70);
		OLED_print_string("    Q U I T");
	
		OLED_print_rocket();
		
		
	}*/
	
	
}



void MENU_print_rocket() {
	
	
	//�vre vannrette strek
	OLED_goto_line(2);
	OLED_goto_column(50);
	
	for (uint8_t i = 50; i < 95; i++) {
		*ext_oled_data = 0b11000000;
	}
	
	
	
	//Nedre vannrette strek
	OLED_goto_line(6);
	OLED_goto_column(50);
	
	for (uint8_t i = 50; i < 95; i++) {
		*ext_oled_data = 0b00000011;
	}
	
	
	
	//Loddrett strek
	for (uint8_t i = 3; i <= 5; i++) {
		OLED_goto_line(i);
		OLED_goto_column(50);
		*ext_oled_data = FILL;
		*ext_oled_data = FILL;
	}
	
	
	//Rocket-nose<3<3
	OLED_goto_line(3);
	OLED_goto_column(95);
	
	*ext_oled_data = 0b00000011;
	*ext_oled_data = 0b00000110;
	*ext_oled_data = 0b00001100;
	*ext_oled_data = 0b00011000;
	*ext_oled_data = 0b00110000;
	*ext_oled_data = 0b01100000;
	*ext_oled_data = 0b11000000;
	*ext_oled_data = 0b10000000;
	
	OLED_goto_line(4);
	OLED_goto_column(95+7);
	
	*ext_oled_data = 0b10000001;
	*ext_oled_data = 0b11000011;
	*ext_oled_data = 0b01100110;
	*ext_oled_data = 0b00111100;
	
	
	OLED_goto_line(5);
	OLED_goto_column(95);
	*ext_oled_data = 0b11000000;
	*ext_oled_data = 0b01100000;
	*ext_oled_data = 0b00110000;
	*ext_oled_data = 0b00011000;
	*ext_oled_data = 0b00001100;
	*ext_oled_data = 0b00000110;
	*ext_oled_data = 0b00000011;
	*ext_oled_data = 0b00000001;
	
	JOY_direction_t dir = JOY_getDirection();
	//Stjernest�v
	while (dir != left)  {
		for(uint8_t j = 3; j <=5 ; j++) {
			OLED_goto_line(j);
			for(uint8_t i = 0; i< 50; i++) {
				*ext_oled_data = rand() % 255;
			}
			
		}
		_delay_ms(200);
		dir = JOY_getDirection();
		
	}
	
}




void MENU_initialize(){

	//Initializing Main Menu
	main_menu.title = "Main Menu";
	main_menu.number_of_submenus = 0;
	main_menu.item = NULL_PTR;
	main_menu.parent = NULL_PTR;
	main_menu.submenus = malloc(sizeof(menu_t)*5);
	
	
	
	
	
	
	
	menu_t* settings_m = MENU_add_submenu("Settings", NULL_PTR, &main_menu);
	menu_t* tonja_m = MENU_add_submenu("Tonja", NULL_PTR, &main_menu);
	menu_t* karl_m = MENU_add_submenu("Karl", NULL_PTR, &main_menu);
	menu_t* rocket_f = MENU_add_submenu("Rocket", &MENU_print_rocket, tonja_m);
	
	menu_t* lillagenser_m = MENU_add_submenu("Lilla genser", NULL_PTR, tonja_m);
	menu_t* ocd_m = MENU_add_submenu("ocd", NULL_PTR, tonja_m);
	menu_t* regnbue_m = MENU_add_submenu("Regnbue", NULL_PTR, tonja_m);
	
	menu_t* kul_m = MENU_add_submenu("Kul", NULL_PTR, karl_m);
	menu_t* svartbukse_m = MENU_add_submenu("Svart bukse", NULL_PTR, lillagenser_m);
	//printf("first submenu is %s\n", main_menu.submenus[0]->title);
	
	current_menu = main_menu;
	
	//main_menu.number_of_submenus = 3;
	
	
	
}


void MENU_run_menu(void){
	MENU_display_menu(main_menu,0);
		while(!quit) {
		
		
			JOY_direction_t dir = JOY_getDirection();
		
			/*printf("dir: ");
			JOY_getDirectionString();
			printf("\n");*/
			menu_t choice = *current_menu.submenus[current_line];		
		
		 
		
				switch (dir) {	
			
					case up:
					
						if (current_line > 0 && last_direction == neutral) {
							current_line--;
							MENU_display_menu(current_menu, current_line);
						}
						last_direction = dir;
						_delay_ms(100);
						break;
				
					case down:
						printf("menus %d\n",current_menu.number_of_submenus);
						if ((current_line < (current_menu.number_of_submenus-1)) && last_direction == neutral) {
							current_line++;
							printf("current line = %d\n", current_line);
						
							MENU_display_menu(current_menu, current_line);
						}
						last_direction = dir;
						_delay_ms(100);
						break;
			
					case right:
						if (last_direction == neutral) {
							MENU_choose(choice);
							current_menu = choice;
							current_line = 0;
							MENU_display_menu(current_menu, current_line);
						
						}
						last_direction = dir;
						_delay_ms(100);
						break;
				
					case left:	
						if(last_direction == neutral){
						MENU_back(current_menu);
							if (current_menu.parent != NULL_PTR) {
								current_menu = *current_menu.parent;
							}
							else {
								//quit = 1;
							}
							current_line = 0;
						}
					
						last_direction = dir;
						_delay_ms(100);
						break;
					
					case neutral:
						last_direction = dir;
						_delay_ms(100);
						break;
				}
		
		
		
		
		
		}
}