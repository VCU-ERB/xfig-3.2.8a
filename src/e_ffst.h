#include "object.h"

#ifndef E_FFST_H
#define E_FFST_H


//Initials 
void init_border_drawing(int x, int y); 
void move_selected1(void); 
extern void ffst_selected(void);
static void init_break(void); 
//Glue 
static void create_selectArea(int x, int y); 
static void cancel_box(void); 
static void create_compoundobject(int x, int y); 
void tag_obj_in_region1(int xmin, int ymin, int xmax, int ymax); 

// #taskFreeSelection
//------------------------------------- INFO Starts Here---------------------------------
// INFO: Functions you created.
static void sel_line(int xmin, int ymin, int xmax, int ymax);
static void get_line(F_line** list); 
static void get_arc(F_arc** list); 
static void sel_arc(int xmin, int ymin, int xmax, int ymax); 
static void get_compound(F_compound** list); 
static void sel_compound(int xmin, int ymin, int xmax, int ymax); 
static void get_ellipse(F_ellipse** list); 
static void sel_ellipse(int xmin, int ymin, int xmax, int ymax); 
static void get_spline(F_spline** list); 
static void sel_spline(int xmin, int ymin, int xmax, int ymax); 
static void get_text(F_text** list); 
static void sel_text(int xmin, int ymin, int xmax, int ymax); 
//----------------------------------- INFO Ends Here ------------------------------------

//Move
static void init_move(F_line* p, int type, int x, int y, int px, int py),  
init_arb_move(F_line* p, int type, int x, int y, int px, int py),  
init_constrained_move(F_line* p, int type, int x, int y, int px, int py); 
static int compose_compound1(F_compound *c);
//F_compound *temp = NULL;
//This allows for the compound to be broken in in init_break after it is moved F_compound* temp; 

#endif