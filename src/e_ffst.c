#include "fig.h"
#include "resources.h"
#include "object.h"
#include "mode.h"
#include "paintop.h"
#include "d_text.h"
#include "u_create.h"
#include "u_elastic.h"
#include "u_list.h"
#include "u_draw.h"
#include "u_drag.h"
#include "u_search.h"
#include "w_canvas.h"
#include "w_drawprim.h"
#include "w_indpanel.h"
#include "w_mousefun.h"
#include "w_msgpanel.h"
#include "w_setup.h"
#include "w_util.h"
#include "w_layers.h"
#include "e_ffst.h"
#include "e_scale.h"
#include "f_read.h"
#include "f_util.h"
#include "u_bound.h"
#include "u_fonts.h"
#include "u_free.h"
#include "u_markers.h"
#include "u_redraw.h"
#include "u_undo.h"
#include "w_cursor.h"
#include "w_util.h"

// #taskFreeSelection
//----------------------------------- Code Starts Here ----------------------------------
/* INFO:  This  is  the  file that  describes  the  free selection.  The  first  function 
 *   'ffst_selected' is the one called when  your  shortcut  is  clicked.  The left mouse
 *   button is linked to the next function 'init_border_drawing'. That function describes
 *   the general behavior of selection.  The left  mouse button is linked to the function
 *   'create_selectArea'.  Inside  that  function,  an  elastic  box  is defined. Then, a 
 *   function is  called  to tag the  objects inside this box and a function is called to
 *   create  the compound with this selected objects that will move.  We called this GLUE
 *   CODE. Your work stars here.
 * GOAL:  PLEASE, read the code in 'create_selectArea'. The first  step is create the tag
 *   codes ('tag_obj_in_region1'). You  can  try  create  your own code OR go to the next
 *   hashtag and get a hint.
 */

//----------------------------------- Code Ends Here ------------------------------------

/**************************************** BASE CODE ************************************/

F_compound *temp = NULL;

void ffst_selected(void)
{
	set_mousefun("corner point", "", "", "", "", "");
	canvas_kbd_proc = null_proc;
	canvas_locmove_proc = null_proc;
	canvas_leftbut_proc = init_border_drawing;
	canvas_middlebut_proc = null_proc;
	canvas_rightbut_proc = null_proc;
	set_cursor(crosshair_cursor);
	reset_action_on();
}

void init_border_drawing(int x, int y)
{
	cur_x = fix_x = x;
	cur_y = fix_y = y;
	set_mousefun("final point", "", "cancel", "", "", "");
	draw_mousefun_canvas();

	// set mouse actions
	canvas_locmove_proc = resizing_box;
	canvas_leftbut_proc = create_selectArea;
	canvas_middlebut_proc = null_proc;
	canvas_rightbut_proc = cancel_box;

	// create box to draw
	elastic_box(fix_x, fix_y, cur_x, cur_y);
	set_cursor(null_cursor);
	set_action_on();
}

static void
cancel_box(void)
{
	elastic_box(fix_x, fix_y, cur_x, cur_y);
	/* erase last lengths if appres.showlengths is true */
	erase_box_lengths();
	ffst_selected();
	draw_mousefun_canvas();
}

static void
create_selectArea(int x, int y)
{
	elastic_box(fix_x, fix_y, cur_x, cur_y);
	int x_min, x_max, y_min, y_max;

	x_min = min2(fix_x, x);
	y_min = min2(fix_y, y);
	x_max = max2(fix_x, x);
	y_max = max2(fix_y, y);
	tag_obj_in_region1(x_min, y_min, x_max, y_max);

	// Create the compound
	create_compoundobject(1, 1);
	draw_mousefun_canvas();
}
static void
break_comp(void)
{
	init_break();
	ffst_selected();
}


/************************************** GLUE CODE **************************************/


// #taskFreeSelection
//-------------------------------------Code Starts Here----------------------------------
/* INFO: To tag all objects, you will need: a different function to tag each type of 
 *   object (a functions to tag ellipces, another to tag arcs, etc.) and a general 
 *   function to call them. Let's start creanting the general one. 
 * GOAL: Create the function 'tag_obj_in_region1' that call all the others. It receives
 *   the max and min point position of the selected region (the four points of the 
 *   retangle), and returns nothing.
 *
 * tag_obj_in_region1()
 * {
 *
 * }
 *
 * GOAL: Now, make the functions to tag the objects inside the global compound 'objects'
 *   that matches with the selected area. For each object, you need verify if the
 *   object is inside the area, mark tagged and then call the function 
 *   'toggle_[object_type]highlight' from the file 'u_markers.h'.
 * HINT: Think carefully. Analyze what information you have about the position of each
 *   object. You can do that. But if you are having trouble, let's work together. Go to
 *   the next hashtag.
 */
   
//------------------------------------ Code Ends Here -----------------------------------

static void
create_compoundobject(int x, int y)
{
	(void)x;
	(void)y;
	F_compound *c;
	if ((c = create_compound()) == NULL)
		return;

	// dont create compound if nothing is selected
	if (compose_compound1(c) == 0)
	{
		free((char *)c);
		ffst_selected();
		draw_mousefun_canvas();
		put_msg("Empty compound, ignored");
		return;
	}
	/*
	 * Make the bounding box exactly match the dimensions of the compound.  */
	compound_bound(c, &c->nwcorner.x, &c->nwcorner.y,
				   &c->secorner.x, &c->secorner.y);

	/* if zero width or height in the compound, adjust to next positioning  grid point or a few pixels if positioning grid is "ANY" */
	if (c->nwcorner.x == c->secorner.x)
	{
		if (cur_pointposn != P_ANY)
		{
			c->secorner.x += point_spacing();
			c->secorner.x = ceil_coords_x(c->secorner.x, c->secorner.y);
		}
	}
	if (c->nwcorner.y == c->secorner.y)
	{
		if (cur_pointposn != P_ANY)
		{
			c->secorner.y += point_spacing();
			c->secorner.y = ceil_coords_y(c->secorner.x, c->secorner.y);
		}
	}

	// cleanup for creating new compound
	c->next = NULL;
	clean_up();
	set_action(F_GLUE);
	toggle_markers_in_compound(c);
	list_add_compound(&objects.compounds, c);
	mask_toggle_compoundmarker(c);
	set_latestcompound(c);
	temp = c;
	set_modifiedflag();
	move_selected1(); // Allows for clean progression of functions  draw_mousefun_canvas();
}

// #taskFreeSelection
//------------------------------------- Code Starts Here --------------------------------
/* HINT: If you do not know what objects  are  inside a  compound, look into the function
 *   that creates a compound in the file 'object.h'  and go back to the hashtag before to
 *   finalize you work.      																						  	
 * GOAL: If you do not know anything. Let's work step by step.  First,  inside a compound
 *   there are a lot of objects lists.  For  instance,  the ellipses  are in the ellipses 
 *   list, the arcs in the arcs list. To select a ellipse:						
 *   1) look at each object in the linked list objects.ellipses;									
 *   2) verify if the object is in the active layer using 'active_layer'.							
 *   3) verify if center less the radiuses is smaller the minimum point of the selection.		
 *   4) verify if center more the radiuses is bigger them the maximum point of the selection.	
 *   5) If True, tag the object and call 'toggle_ellipsehighlight'.								
 *																								
 *   You need to do that for ellipse, arc, line, spline, text and compound.						
 *   																							
 * HINTS:																						
 *   a) arc or spline: use the fuction 'arc_bound' or 'spline_bound'. It receives the				
 *      object and four variables that will assume the box position of the object.				
 *   b) text: use 'text_bound'. This function receives the same arguments above plus 8 	
 *      variables that are not relevant here.																
 *   c) line: for each line, verify each point. For a line being tagged, all points of it 		
 *      need to be inside the selected area.  													
 *   d) compound: use the fuction 'any_active_in_compound' ('w_layers.c') to check active 
 *      layer.
 */

//----------------------------------- Code ends Here ------------------------------------


// #taskFreeSelection
//----------------------------------- Code Starts Here ----------------------------------
/* GOAL: The second part of your work is creating the compound with the tagged objects.
 *   The main function is 'create_compoundobject' and its done in the code above. Read
 *   this function and create the function 'compose_compound1', that receives the new
 *   compound and put the selected objects. If it did not find anything, return 0, in
 *   other case, return 1. After that, create a function for each object type to get the
 *   tagged ones.
 */

compose_compound1() 
{
/* 	1) Set 'defer_update_layers' to defer updating of layer buttons until we've composed
 *	   the entire compound. 
 *	2) Call the funtions to get all tagged objects. 
 *	3) Now update the layer buttons setting 'defer_update_layers' and calling the  
 *	   function ('w_layers.c'). 
 *  4) Verify the lists of objects inside de compound. If one of them is not null
 *  return 1, or return 0. 
 */
}

/* HINT: In the function to get the tagged objects, when you find a tagged object, before
 *   remove from the original compound and put into the new one, call the function 
 *   'remove_depth' from the file 'u_list.c'. For compounds, use the function
 *   'remove_compound_depth'.
 */

//----------------------------------- Code ends Here ------------------------------------//



/************************************** MOVE  CODE *************************************/


void move_selected1(void)
{
	set_mousefun("move object", "horiz/vert move", "", LOC_OBJ, LOC_OBJ, LOC_OBJ);
	canvas_kbd_proc = null_proc;
	canvas_locmove_proc = null_proc;
	init_searchproc_left(init_arb_move);
	init_searchproc_middle(init_constrained_move);
	canvas_leftbut_proc = object_search_left;
	canvas_middlebut_proc = object_search_middle;
	canvas_rightbut_proc = null_proc;
	return_proc = break_comp;
	set_cursor(pick9_cursor);
	reset_action_on();
}

static void
init_arb_move(F_line *p, int type, int x, int y, int px, int py)
{
	constrained = MOVE_ARB;
	init_move(p, type, x, y, px, py);
	canvas_middlebut_proc = null_proc;
	set_mousefun("place object", "", "cancel", LOC_OBJ, LOC_OBJ, LOC_OBJ);
	draw_mousefun_canvas();
}

static void
init_constrained_move(F_line *p, int type, int x, int y, int px, int py)
{
	constrained = MOVE_HORIZ_VERT;
	init_move(p, type, x, y, px, py);
	canvas_middlebut_proc = canvas_leftbut_proc;
	canvas_leftbut_proc = null_proc;
	set_mousefun("", "place object", "cancel", LOC_OBJ, LOC_OBJ, LOC_OBJ);
	draw_mousefun_canvas();
}

// #taskFreeSelection
//------------------------------------- Code Starts Here---------------------------------
// GOAL: At the end. read the MOVE code above and create the 'init_move' function. 

static void
init_move(F_line *p, int type, int x, int y, int px, int py)
{
//  The line below turn off all markers 
	update_markers(0);
/*	GOAL: Now, for each type of object:
 *  1) set the cursor to wait;
 *	2) populate the current variable with the object p;
 *  3) call the function list_delete ('u_list.c');
 * 	4) call the fuction that redraw anything near the object (redisplay);
 * 	5) set the cursor to null;
 * 	6) init the dragging using the apropriated function ('u_drag.c'). For O_TXT objects,
 *     use x and y. For the others, use px and py.
 * 
 * 	The default case should just return the funcion.
 */
}	

//----------------------------------- Code Ends Here ------------------------------------


/************************************** BREAK CODE **************************************/

static void
init_break(void)
{
	cur_c = temp;
	mask_toggle_compoundmarker(cur_c);
	clean_up();
	list_delete_compound(&objects.compounds, cur_c);
	tail(&objects, &object_tails);
	append_objects(&objects, cur_c, &object_tails);
	toggle_markers_in_compound(cur_c);
	set_tags(cur_c, 0);
	set_action(F_BREAK);
	set_latestcompound(cur_c);
	set_modifiedflag();
	ffst_selected();
}