/*
 * FIG : Facility for Interactive Generation of figures
 * Copyright (c) 1985-1988 by Supoj Sutanthavibul
 * Parts Copyright (c) 1989-2015 by Brian V. Smith
 * Parts Copyright (c) 1991 by Paul King
 * Parts Copyright (c) 2016-2020 by Thomas Loimer
 *
 * Parts Copyright (c) 1995 by C. Blanc and C. Schlick
 *
 * Any party obtaining a copy of these files is granted, free of charge, a
 * full and unrestricted irrevocable, world-wide, paid up, royalty-free,
 * nonexclusive right and license to deal in this software and documentation
 * files (the "Software"), including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense and/or sell copies of
 * the Software, and to permit persons who receive copies from any such
 * party to do so, with the only requirement being that the above copyright
 * and this permission notice remain intact.
 *
 */

/**************** IMPORTS ****************/

#include "fig.h"
#include "resources.h"
#include "mode.h"
#include "object.h"
#include "paintop.h"
#include "e_addpt.h"
#include "e_arrow.h"
#include "e_convert.h"
#include "u_draw.h"
#include "u_elastic.h"
#include "u_list.h"
#include "u_redraw.h"
// #taskUndoRedo_03: Create
/*------------------------------------ Code Starts Here------------------------*/
// Include the header file for the undo and the free function.

/*------------------------------------ Code Ends Here--------------------------*/
#include "u_create.h"
#include "w_canvas.h"
#include "w_drawprim.h"
#include "w_file.h"
#include "w_layers.h"
#include "w_msgpanel.h"
#include "w_setup.h"
#include "e_deletept.h"
#include "e_scale.h"
#include "f_read.h"
#include "u_bound.h"
#include "u_markers.h"
#include "u_translate.h"
#include "w_cmdpanel.h"
#include "w_indpanel.h"
#include "w_color.h"

extern void swap_depths(void); /* w_layers.c */
extern void swap_counts(void); /* w_layers.c */

/*************** EXPORTS *****************/

/*
 * Object_tails *usually* points to the last object in each linked list in
 * objects.  The exceptions occur when multiple objects are added to a figure
 * (e.g. file read, break compound, undo delete region).  In these cases,
 * the added objects are appended to the object lists (and saved_objects is
 * set up to point to the new objects) but object_tails is not changed.
 * This speeds up a subsequent undo operation which need only set
 * all the "next" fields of objects pointed to by object_tails to NULL.
 */
F_compound saved_objects = {0, 0, {0, 0}, {0, 0}, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, False, NULL, NULL};
F_compound object_tails = {0, 0, {0, 0}, {0, 0}, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, False, NULL, NULL};
F_arrow *saved_for_arrow = (F_arrow *)NULL;
F_arrow *saved_back_arrow = (F_arrow *)NULL;
F_line *latest_line;	 /* for undo_join (line) */
F_spline *latest_spline; /* for undo_join (spline) */

int last_action = F_NULL;

/*************** LOCAL *****************/

static int last_object;
static F_pos last_position, new_position;
static int last_arcpointnum;
static F_point *last_prev_point, *last_selected_point, *last_next_point;
static F_sfactor *last_selected_sfactor;
static F_linkinfo *last_links;
static F_arrow *last_for_arrow, *last_back_arrow;
static int last_linkmode;
static double last_origin_tension, last_extremity_tension;
// #taskUndoRedo_03: Create
/*------------------------------------Code Starts Here------------------------*/
// Initialize the boolean variables for freeze_redo_cleanup and freeze_undo_additions.
// Create pointer variables for the undo_stack and redo_stack.

/*------------------------------------Code Ends Here--------------------------*/

// #taskUndoRedo_03: Create
/*------------------------------------Code Starts Here------------------------*/
// The following methods are given to you for use in further code.

/*------------------------------------Code Ends Here--------------------------*/
void undo_add(F_history **stack);
void undo_delete(F_history **stack);
void undo_move(F_history **stack);
void undo_change(F_history **stack);
void undo_glue(F_history **stack);
void undo_break(F_history **stack);
void undo_load(F_history **stack);
void undo_scale(F_history **stack);
void undo_addpoint(F_history **stack);
void undo_deletepoint(F_history **stack);
void undo_add_arrowhead(F_history **stack);
void undo_delete_arrowhead(F_history **stack);
void undo_convert(F_history **stack);
void undo_open_close(F_history **stack);
void undo_join_split(F_history **stack);
void set_action_object(int action, int object);
void swap_newp_lastp(F_history **stack);
void pop_stack(F_history **stack);
void swap_stack(F_history **stack);

// #taskUndoRedo_03: Create
/*------------------------------------ Code Starts Here -------------------------------*/
/* Below you will create the undo method.
 * 1. If the undo_stack is empty, display the message "Nothing to undo" and return.
 * 2. You will create a switch statement with the expression undo_stack -> last_action
 * 3. There will be 16 case constant expressions for each object manipulation in xfig.
 * 4. Each statement that corresponds with the expression will call the corresponding
 * method. eg: case F_ADD will call undo_add and send in the undo_stack address.
 * 5. The ending default case will display the message "Nothing to undo" and return.
 * 6. In the end display "Undo complete".
 */
void undo(void)
{
}
/*------------------------------------ Code Ends Here ---------------------------------*/

// #taskUndoRedo_03: Create
/*------------------------------------ Code Starts Here -------------------------------*/
/* Below you will create the redo method.
 * 1. If the undo_stack is empty, display the message "nothing to redo" and return.
 * 2. After the if statement, print the following using stdout:
 * "last_action: %d\n", redo_stack->last_action"
 * 3. You will create a switch statement with the expression redo_stack -> last_action
 * 4. There will be 16 case constant expressions for each manipulation in xfig.
 * 5. Each statement that corresponds with the expression will call the corresponding
 * method. eg: case F_ADD will call undo_add and send in the redo_stack address.
 * 6. The ending default case will display the message "Nothing to redo" and return.
 * 7. The end switch statement will display "Redo complete".
 */
void redo(void)
{
}
/*------------------------------------ Code Ends Here ---------------------------------*/

void undo_join_split(F_history **stack)
{
	F_line swp_l;
	F_spline swp_s;
	if (last_object == O_POLYLINE)
	{
		new_l = (*stack)->saved_objects->lines; /* the original */
		old_l = (*stack)->latest_line;			/* the changed object */
		/* swap old with new */
		memcpy(&swp_l, old_l, sizeof(F_line));
		memcpy(old_l, new_l, sizeof(F_line));
		memcpy(new_l, &swp_l, sizeof(F_line));
		/* this assumes that the object are at the end of the objects list */
		/* correct the depth counts if necessary */
		if (!new_l->next && old_l->next)
		{ /* join undo */
			add_depth(O_POLYLINE, old_l->next->depth);
		}
		else if (new_l->next && !old_l->next)
		{ /* split undo */
			remove_depth(O_POLYLINE, new_l->next->depth);
		}
		// set_action_object(F_JOIN, O_POLYLINE);
		(*stack)->last_action = F_JOIN;
		(*stack)->last_object = O_POLYLINE;
		redisplay_lines(new_l, old_l);
	}
	else
	{
		new_s = (*stack)->saved_objects->splines; /* the original */
		old_s = (*stack)->latest_spline;		  /* the changed object */
		/* swap old with new */
		memcpy(&swp_s, old_s, sizeof(F_spline));
		memcpy(old_s, new_s, sizeof(F_spline));
		memcpy(new_s, &swp_s, sizeof(F_spline));
		/* this assumes that the object are at the end of the objects list */
		/* correct the depth counts if necessary */
		if (!new_s->next && old_s->next)
		{ /* join undo */
			add_depth(O_SPLINE, old_s->next->depth);
		}
		else if (new_s->next && !old_s->next)
		{ /* split undo */
			remove_depth(O_SPLINE, new_s->next->depth);
		}
		(*stack)->last_action = F_JOIN;
		(*stack)->last_object = O_SPLINE;
		redisplay_splines(new_s, old_s);
	}

	swap_stack(stack);
}

// #taskUndoRedo_03: Create
/*------------------------------------ Code Starts Here -------------------------------*/
/* below you will edit the undo_addpoint function
 * 1. You will first need to tempoarily stop objects from freeing. This will allow you
 *    to access data without error.
 * 2. Create an if_statement where the statement will occur when the stack's last object
 *    is O_POLYLINE.
 * 3. If this is true, call linepoint_deleting() and send in the corresponding
 *    points/lines.
 * 4. If this is untrue, call splinepoint_deleting and send in the corresponding
 *    points/splines.
 * 5. You will then need to manually remove the undo stack elements.
 * 6. If the stack is currently referencing the undo_stack, call swap_stack and
 *    poop_stack respectively.
 * 7. Else... call the swap_stack(stack) and pop_stack(&undo_stack).
 * 8. Your last line should unfreeze redo cleanup and allow it to free the stack.
 */
void undo_addpoint(F_history **stack)
{
}
/*------------------------------------ Code Ends Here ---------------------------------*/

// #taskUndoRedo_03: Create
/*------------------------------------ Code Starts Here -------------------------------*/
/* below you will edit the undo_deletepoint function
 * this function is completely identical to undo_addpoint
 */
// TIP: remember to update relevant markers if the last object is an O_POLYLINE.
void undo_deletepoint(F_history **stack)
{
}
/*------------------------------------ Code Ends Here ---------------------------------*/

void undo_break(F_history **stack)
{
	list_delete_objects(&objects, (*stack)->saved_objects->compounds);
	/* remove the depths from this compound because they'll be added in right after */
	list_add_compound(&objects.compounds, (*stack)->saved_objects->compounds);
	(*stack)->last_action = F_GLUE;
	toggle_markers_in_compound((*stack)->saved_objects->compounds);
	mask_toggle_compoundmarker((*stack)->saved_objects->compounds);
	swap_stack(stack);
}

// #taskUndoRedo_03: Create
/*------------------------------------ Code Starts Here -------------------------------*/
/* below you will edit the undo_glue function
 * 1. Remove the current compound by calling list_delete_compound. Send in the compound
 *    object address and the compounds from *stack. Call tail and send in the address
 *    of the objects and the address of the object tails.
 * 2. Add the objects from the deleted compound to &objects by calling append_objects.
 * 3. Add the depths by calling add_compound_depth.
 * 4. Set the last_action of the stack to F_BREAK.
 */

/* 1. Paste the following after your above implemented code so that markers do not
 *    appear in compound:
	mask_toggle_compoundmarker((*stack)->saved_objects->compounds);
	toggle_markers_in_compound((*stack)->saved_objects->compounds);
	if (cur_mode != F_GLUE && cur_mode != F_BREAK)
	{
		set_tags((*stack)->saved_objects->compounds, 0);
	}
	swap_stack(stack);
*/
void undo_glue(F_history **stack)
{
}
/*------------------------------------ Code Ends Here ---------------------------------*/

void undo_convert(F_history **stack)
{

	switch ((*stack)->last_object)
	{
	case O_POLYLINE:
		if ((*stack)->saved_objects->lines->type == T_BOX ||
			(*stack)->saved_objects->lines->type == T_ARCBOX)
		{
			box_2_box((*stack)->latest_line);
		}
		else
		{
			spline_line((*stack)->saved_objects->splines);
		}
		break;
	case O_SPLINE:
		line_spline((*stack)->saved_objects->lines, (*stack)->next->saved_objects->splines->type);
		break;
	}

	// similar logic to add/del point, but this is likely wrong
	if (*stack == undo_stack)
	{
		swap_stack(stack);
		pop_stack(&undo_stack);
		pop_stack(&undo_stack);
		redo_stack->saved_objects->lines = undo_stack->saved_objects->lines;
	}
	else
	{
		pop_stack(&undo_stack);
		pop_stack(&undo_stack);
		redo_stack->saved_objects->lines = undo_stack->saved_objects->lines;
	}
}

// #taskUndoRedo_03: Create
/*------------------------------------ Code Starts Here -------------------------------*/
/* Below you will implement the undo_add_arrowhead method.
 * 1. You will first need to tempoarily stop objects from freeing.
 * 2. Create a switch statement with the expression (*stack)->last_object
 * 3. You will have three corresponding switch cases. O_POLYLINE, O_SPLINE, and O_ARC
 * 4. For each case, you will call the delete delete function that corresponds with each
 * case and send in the corresponding lines, splines, or arcs.
 * 5. The default case should return from the statement.
 * 6. Unfreeze the cleanup.
 * 7. Paste the following on the last lines of the method:
	F_arrow * tmp_for_arrow = (*stack)->saved_for_arrow;
	F_arrow * tmp_back_arrow = (*stack)->saved_back_arrow;

	pop_stack(stack);

	//set saved arrow info
		(*stack)->last_action = F_DELETE_ARROW_HEAD;
	(*stack)->saved_for_arrow = tmp_for_arrow;
	(*stack)->saved_back_arrow = tmp_back_arrow;
	swap_stack(stack);
*/
void undo_add_arrowhead(F_history **stack)
{
}
/*------------------------------------ Code Ends Here ---------------------------------*/

void undo_delete_arrowhead(F_history **stack)
{
	switch ((*stack)->last_object)
	{
	case O_POLYLINE:
		if ((*stack)->saved_for_arrow)
			(*stack)->saved_objects->lines->for_arrow = (*stack)->saved_for_arrow;
		if ((*stack)->saved_back_arrow)
			(*stack)->saved_objects->lines->back_arrow = (*stack)->saved_back_arrow;
		redisplay_line((*stack)->saved_objects->lines);
		break;
	case O_SPLINE:
		if ((*stack)->saved_for_arrow)
			(*stack)->saved_objects->splines->for_arrow = (*stack)->saved_for_arrow;
		if ((*stack)->saved_back_arrow)
			(*stack)->saved_objects->splines->back_arrow = (*stack)->saved_back_arrow;
		redisplay_spline((*stack)->saved_objects->splines);
		break;
	case O_ARC:
		if ((*stack)->saved_for_arrow)
			(*stack)->saved_objects->arcs->for_arrow = (*stack)->saved_for_arrow;
		if ((*stack)->saved_back_arrow)
			(*stack)->saved_objects->arcs->back_arrow = (*stack)->saved_back_arrow;
		redisplay_arc((*stack)->saved_objects->arcs);
		break;
	default:
		return;
	}
	(*stack)->last_action = F_ADD_ARROW_HEAD;
	swap_stack(stack);
}

void undo_change(F_history **stack)
{
	char *swp_comm;
	F_compound swp_c;
	F_line swp_l;
	F_spline swp_s;
	F_ellipse swp_e;
	F_arc swp_a;
	F_text swp_t;

	switch ((*stack)->last_object)
	{
	case O_POLYLINE:
		new_l = (*stack)->saved_objects->lines;		  /* the original */
		old_l = (*stack)->saved_objects->lines->next; /* the changed object */
		/* account for depths */
		remove_depth(O_POLYLINE, old_l->depth);
		add_depth(O_POLYLINE, new_l->depth);
		/* swap old with new */
		memcpy(&swp_l, old_l, sizeof(F_line));
		memcpy(old_l, new_l, sizeof(F_line));
		memcpy(new_l, &swp_l, sizeof(F_line));
		/* but keep the next pointers unchanged */
		swp_l.next = old_l->next;
		old_l->next = new_l->next;
		new_l->next = swp_l.next;

		redisplay_lines(new_l, old_l);
		break;
	case O_ELLIPSE:
		new_e = (*stack)->saved_objects->ellipses;
		old_e = (*stack)->saved_objects->ellipses->next;
		/* account for depths */
		remove_depth(O_ELLIPSE, old_e->depth);
		add_depth(O_ELLIPSE, new_e->depth);
		/* swap old with new  */
		memcpy(&swp_e, old_e, sizeof(F_ellipse));
		memcpy(old_e, new_e, sizeof(F_ellipse));
		memcpy(new_e, &swp_e, sizeof(F_ellipse));
		/* but keep the next pointers unchanged */
		swp_e.next = old_e->next;
		old_e->next = new_e->next;
		new_e->next = swp_e.next;

		redisplay_ellipses(new_e, old_e);
		break;
	case O_TXT:
		new_t = (*stack)->saved_objects->texts;
		old_t = (*stack)->saved_objects->texts->next;
		/* account for depths */
		remove_depth(O_TXT, old_t->depth);
		add_depth(O_TXT, new_t->depth);
		/* swap old with new */
		memcpy(&swp_t, old_t, sizeof(F_text));
		memcpy(old_t, new_t, sizeof(F_text));
		memcpy(new_t, &swp_t, sizeof(F_text));
		/* but keep the next pointers unchanged */
		swp_t.next = old_t->next;
		old_t->next = new_t->next;
		new_t->next = swp_t.next;

		redisplay_texts(new_t, old_t);
		break;
	case O_SPLINE:
		new_s = (*stack)->saved_objects->splines;
		old_s = (*stack)->saved_objects->splines->next;
		/* account for depths */
		remove_depth(O_SPLINE, old_s->depth);
		add_depth(O_SPLINE, new_s->depth);
		/* swap old with new */
		memcpy(&swp_s, old_s, sizeof(F_spline));
		memcpy(old_s, new_s, sizeof(F_spline));
		memcpy(new_s, &swp_s, sizeof(F_spline));
		/* but keep the next pointers unchanged */
		swp_s.next = old_s->next;
		old_s->next = new_s->next;
		new_s->next = swp_s.next;

		redisplay_splines(new_s, old_s);
		break;
	case O_ARC:
		new_a = (*stack)->saved_objects->arcs;
		old_a = (*stack)->saved_objects->arcs->next;
		/* account for depths */
		remove_depth(O_ARC, old_a->depth);
		add_depth(O_ARC, new_a->depth);
		/* swap old with new */
		memcpy(&swp_a, old_a, sizeof(F_arc));
		memcpy(old_a, new_a, sizeof(F_arc));
		memcpy(new_a, &swp_a, sizeof(F_arc));
		/* but keep the next pointers unchanged */
		swp_a.next = old_a->next;
		old_a->next = new_a->next;
		new_a->next = swp_a.next;

		redisplay_arcs(new_a, old_a);
		break;
	case O_COMPOUND:
		new_c = (*stack)->saved_objects->compounds;
		old_c = (*stack)->saved_objects->compounds->next;
		/* account for depths */
		remove_compound_depth(old_c);
		add_compound_depth(new_c);
		/* swap old with new */
		memcpy(&swp_c, old_c, sizeof(F_compound));
		memcpy(old_c, new_c, sizeof(F_compound));
		memcpy(new_c, &swp_c, sizeof(F_compound));
		/* but keep the next pointers unchanged */
		swp_c.next = old_c->next;
		old_c->next = new_c->next;
		new_c->next = swp_c.next;

		redisplay_compounds(new_c, old_c);
		break;
	case O_FIGURE:
		/* swap saved figure comments with current */
		swp_comm = objects.comments;
		objects.comments = (*stack)->saved_objects->comments;
		(*stack)->saved_objects->comments = swp_comm;

		break;
	case O_ALL_OBJECT:
		swp_c = objects;
		objects = *((*stack)->saved_objects);
		*((*stack)->saved_objects) = swp_c;
		new_c = &objects;
		old_c = (*stack)->saved_objects;
		/* account for depths */
		remove_compound_depth(old_c);
		add_compound_depth(new_c);

		set_modifiedflag();
		redisplay_zoomed_region(0, 0, BACKX(CANVAS_WD), BACKY(CANVAS_HT));
		break;
	}
	swap_stack(stack);
}

/*
 * When a single object is created, it is appended to the appropriate list
 * in objects.	It is also placed in the appropriate list in saved_objects.
 *
 * When a number of objects are created (usually by reading them in from
 * a file or undoing a remove-all action), they are appended to the lists in
 * objects and also saved in saved_objects.  The pointers in object_tails
 * will be set to point to the last members of the lists in objects prior to
 * the appending.
 *
 * Note: The read operation will set the pointers in object_tails while the
 * remove-all operation will zero pointers in objects.
 */

// #taskUndoRedo_03: Create
/*------------------------------------ Code Starts Here -------------------------------*/
/* Below you will implement the undo_add function.
 * 1. Create 4 integer variables for the minimum x and y and the maximum.
 * 2. You will have seven cases for O_POLYLINE, O_ELLIPSE, O_TXT, O_SPLINE, O_ARC,
 *    O_COMPOUND, and O_ALL_OBJECT.
 * 3. For each case, you will call the list_delete method for the corresponding objects.
 * 4. You will then redisplay the object.
 * 5. For O_ALL_OBJECT, you will need to call cut_objects, compound_bound, and
 *    redisplay_zoomed_region.
 * 6. Outside of the switch statement, set the stack's last action to F_DELETE and call
 *    swap_stack.
 */
void undo_add(F_history **stack)
{
}
/*------------------------------------ Code Ends Here ---------------------------------*/

// #taskUndoRedo_03: Create
/*------------------------------------ Code Starts Here -------------------------------*/
/* Below you will implement the undo_delete function. You are given the O_FIGURE and
 * O_ALL_OBJECT cases. You will be implementing the cases for O_POLYLINE, O_ELLIPSE,
 * O_TXT, O_SPLINE, O_ARC, and O_COMPOUND. For each case, you will add the corresponding
 * object (line, ellipse, etc...) and send in the respective object addresses and stack
 * objects. You will then redisplay the object.
 */
void undo_delete(F_history **stack)
{
}
/*------------------------------------ Code Ends Here ---------------------------------*/

// With recorded last position, calculate difference between old and new coordinates, and use built-in translate functions
void undo_move(F_history **stack)
{
	int dx, dy;
	int xmin1, ymin1, xmax1, ymax1;
	int xmin2, ymin2, xmax2, ymax2;
	int dum;

	dx = (*stack)->last_x - (*stack)->new_x;
	dy = (*stack)->last_y - (*stack)->new_y;
	switch ((*stack)->last_object)
	{
	case O_POLYLINE:
		line_bound((*stack)->saved_objects->lines, &xmin1, &ymin1, &xmax1, &ymax1);
		translate_line((*stack)->saved_objects->lines, dx, dy);
		line_bound((*stack)->saved_objects->lines, &xmin2, &ymin2, &xmax2, &ymax2);
		adjust_links(last_linkmode, last_links, dx, dy, 0, 0, 1.0, 1.0, False);
		redisplay_regions(xmin1, ymin1, xmax1, ymax1,
						  xmin2, ymin2, xmax2, ymax2);
		break;
	case O_ELLIPSE:
		ellipse_bound((*stack)->saved_objects->ellipses, &xmin1, &ymin1, &xmax1, &ymax1);
		translate_ellipse((*stack)->saved_objects->ellipses, dx, dy);
		ellipse_bound((*stack)->saved_objects->ellipses, &xmin2, &ymin2, &xmax2, &ymax2);
		redisplay_regions(xmin1, ymin1, xmax1, ymax1,
						  xmin2, ymin2, xmax2, ymax2);
		break;
	case O_TXT:
		text_bound((*stack)->saved_objects->texts, &xmin1, &ymin1, &xmax1, &ymax1,
				   &dum, &dum, &dum, &dum, &dum, &dum, &dum, &dum);
		translate_text((*stack)->saved_objects->texts, dx, dy);
		text_bound(saved_objects.texts, &xmin2, &ymin2, &xmax2, &ymax2,
				   &dum, &dum, &dum, &dum, &dum, &dum, &dum, &dum);
		redisplay_regions(xmin1, ymin1, xmax1, ymax1,
						  xmin2, ymin2, xmax2, ymax2);
		break;
	case O_SPLINE:
		spline_bound((*stack)->saved_objects->splines, &xmin1, &ymin1, &xmax1, &ymax1);
		translate_spline((*stack)->saved_objects->splines, dx, dy);
		spline_bound((*stack)->saved_objects->splines, &xmin2, &ymin2, &xmax2, &ymax2);
		list_delete_spline(&objects.splines, (*stack)->saved_objects->splines);
		list_add_spline(&objects.splines, (*stack)->saved_objects->splines);
		redisplay_regions(xmin1, ymin1, xmax1, ymax1,
						  xmin2, ymin2, xmax2, ymax2);
		break;
	case O_ARC:
		arc_bound((*stack)->saved_objects->arcs, &xmin1, &ymin1, &xmax1, &ymax1);
		translate_arc((*stack)->saved_objects->arcs, dx, dy);
		arc_bound((*stack)->saved_objects->arcs, &xmin2, &ymin2, &xmax2, &ymax2);
		redisplay_regions(xmin1, ymin1, xmax1, ymax1,
						  xmin2, ymin2, xmax2, ymax2);
		break;
	case O_COMPOUND:
		compound_bound((*stack)->saved_objects->compounds, &xmin1, &ymin1, &xmax1, &ymax1);
		translate_compound((*stack)->saved_objects->compounds, dx, dy);
		compound_bound((*stack)->saved_objects->compounds, &xmin2, &ymin2, &xmax2, &ymax2);
		adjust_links(last_linkmode, last_links, dx, dy, 0, 0, 1.0, 1.0, False);
		redisplay_regions(xmin1, ymin1, xmax1, ymax1,
						  xmin2, ymin2, xmax2, ymax2);
		break;
	}
	swap_newp_lastp(stack);
	swap_stack(stack);
}

void undo_load(F_history **stack)
{
	F_compound temp;
	char ctemp[PATH_MAX];

	/* swap objects in current figure/figure we're restoring */
	temp = objects;
	objects = *(*stack)->saved_objects;
	*(*stack)->saved_objects = temp;
	/* swap filenames */
	strcpy(ctemp, cur_filename);
	update_cur_filename(save_filename);
	strcpy(save_filename, ctemp);
	/* restore colors for the figure we are restoring */
	swap_depths();
	swap_counts();
	swap_colors();
	colors_are_swapped = False;
	/* in case current figure doesn't have the colors shown in the fill/pen colors */
	current_memory = -1;
	show_pencolor();
	show_fillcolor();
	/* redisply that figure */
	redisplay_canvas();
	(*stack)->last_action = F_LOAD;
	swap_stack(stack);
}

void undo_scale(F_history **stack)
{
	char *swp_comm;
	F_compound swp_c;
	F_line swp_l;
	F_spline swp_s;
	F_ellipse swp_e;
	F_arc swp_a;
	F_text swp_t;

	switch ((*stack)->last_object)
	{
	case O_POLYLINE:
		new_l = (*stack)->saved_objects->lines;
		old_l = (*stack)->saved_objects->lines->next;
		/* account for depths */
		remove_depth(O_POLYLINE, old_l->depth);
		add_depth(O_POLYLINE, new_l->depth);

		list_delete_line(&objects.lines, old_l);
		list_add_line(&objects.lines, new_l);

		(*stack)->saved_objects->lines = old_l;
		new_l->next = old_l->next;
		(*stack)->saved_objects->lines->next = new_l;

		redisplay_lines(new_l, old_l);
		break;
	case O_ELLIPSE:
		new_e = (*stack)->saved_objects->ellipses;
		old_e = (*stack)->saved_objects->ellipses->next;
		/* account for depths */
		remove_depth(O_ELLIPSE, old_e->depth);
		add_depth(O_ELLIPSE, new_e->depth);

		list_delete_ellipse(&objects.ellipses, old_e);
		list_add_ellipse(&objects.ellipses, new_e);

		(*stack)->saved_objects->ellipses = old_e;
		new_e->next = old_e->next;
		(*stack)->saved_objects->ellipses->next = new_e;

		redisplay_ellipses(new_e, old_e);
		break;
	case O_TXT:

		new_t = (*stack)->saved_objects->texts;
		old_t = (*stack)->saved_objects->texts->next;
		/* account for depths */
		remove_depth(O_TXT, old_t->depth);
		add_depth(O_TXT, new_t->depth);

		list_delete_text(&objects.texts, old_t);
		list_add_text(&objects.texts, new_t);

		(*stack)->saved_objects->texts = old_t;
		new_t->next = old_t->next;
		(*stack)->saved_objects->texts->next = new_t;

		redisplay_texts(new_t, old_t);
		break;
	case O_SPLINE:
		new_s = (*stack)->saved_objects->splines;
		old_s = (*stack)->saved_objects->splines->next;
		/* account for depths */
		remove_depth(O_SPLINE, old_s->depth);
		add_depth(O_SPLINE, new_s->depth);
		/* swap old with new */

		list_delete_spline(&objects.splines, old_s);
		list_add_spline(&objects.splines, new_s);

		(*stack)->saved_objects->splines = old_s;
		new_s->next = old_s->next;
		(*stack)->saved_objects->splines->next = new_s;

		// set_action_object(F_EDIT, O_SPLINE);
		redisplay_splines(new_s, old_s);
		break;
	case O_ARC:
		new_a = (*stack)->saved_objects->arcs;
		old_a = (*stack)->saved_objects->arcs->next;
		/* account for depths */
		remove_depth(O_ARC, old_a->depth);
		add_depth(O_ARC, new_a->depth);
		/* swap old with new */

		list_delete_arc(&objects.arcs, old_a);
		list_add_arc(&objects.arcs, new_a);

		(*stack)->saved_objects->arcs = old_a;
		new_a->next = old_a->next;
		(*stack)->saved_objects->arcs->next = new_a;

		// set_action_object(F_EDIT, O_ARC);
		redisplay_arcs(new_a, old_a);
		break;
	case O_COMPOUND:
		new_c = (*stack)->saved_objects->compounds;
		old_c = (*stack)->saved_objects->compounds->next;
		/* account for depths */
		remove_compound_depth(old_c);
		add_compound_depth(new_c);
		/* swap old with new */

		list_delete_compound(&objects.compounds, old_c);
		list_add_compound(&objects.compounds, new_c);

		(*stack)->saved_objects->compounds = old_c;
		new_c->next = old_c->next;
		(*stack)->saved_objects->compounds->next = new_c;

		// set_action_object(F_EDIT, O_COMPOUND);
		redisplay_compounds(new_c, old_c);
		break;
	case O_FIGURE:
		/* swap saved figure comments with current */
		swp_comm = objects.comments;
		objects.comments = (*stack)->saved_objects->comments;
		(*stack)->saved_objects->comments = swp_comm;
		break;
	case O_ALL_OBJECT:
		swp_c = objects;
		objects = *((*stack)->saved_objects);
		*((*stack)->saved_objects) = swp_c;
		new_c = &objects;
		old_c = (*stack)->saved_objects;
		/* account for depths */
		remove_compound_depth(old_c);
		add_compound_depth(new_c);
		set_modifiedflag();
		redisplay_zoomed_region(0, 0, BACKX(CANVAS_WD), BACKY(CANVAS_HT));
		break;
	}
	swap_stack(stack);
}

void undo_open_close(F_history **stack)
{
	switch ((*stack)->last_object)
	{
	case O_POLYLINE:
		if ((*stack)->saved_objects->lines->type == T_POLYGON)
		{
			(*stack)->saved_objects->lines->for_arrow = (*stack)->last_for_arrow;
			(*stack)->saved_objects->lines->back_arrow = (*stack)->last_back_arrow;
			(*stack)->last_for_arrow = (*stack)->last_back_arrow = NULL;
		}
		toggle_polyline_polygon((*stack)->saved_objects->lines, (*stack)->last_prev_point,
								(*stack)->last_selected_point);
		break;
	case O_SPLINE:
		if ((*stack)->saved_objects->splines->type == T_OPEN_XSPLINE)
		{
			F_sfactor *c_tmp;

			draw_spline((*stack)->saved_objects->splines, ERASE);
			(*stack)->saved_objects->splines->sfactors->s = (*stack)->last_origin_tension;
			for (c_tmp = (*stack)->saved_objects->splines->sfactors; c_tmp->next != NULL;
				 c_tmp = c_tmp->next)
				;
			c_tmp->s = (*stack)->last_extremity_tension;
			(*stack)->saved_objects->splines->type = T_CLOSED_XSPLINE;
			draw_spline((*stack)->saved_objects->splines, PAINT);
		}
		else
		{
			if (closed_spline((*stack)->saved_objects->splines))
			{
				(*stack)->saved_objects->splines->for_arrow = (*stack)->last_for_arrow;
				(*stack)->saved_objects->splines->back_arrow = (*stack)->last_back_arrow;
				(*stack)->last_for_arrow = (*stack)->last_back_arrow = NULL;
			}
			toggle_open_closed_spline((*stack)->saved_objects->splines, (*stack)->last_prev_point,
									  (*stack)->last_selected_point);
		}
		break;
	}
	swap_stack(stack);
}

// #taskUndoRedo_03: Create
/*------------------------------------ Code Starts Here -------------------------------*/
/* Swap the x and y coordinates of the new_position and last_position.
 * Use the variables new_x, new_y, and last_x and last_y
 * Remember to create a temp variable for swapping.
 */
void swap_newp_lastp(F_history **stack)
{
}
/*------------------------------------ Code Ends Here ---------------------------------*/

// clean_up NORMALLY cleares all stored data from saved_objects. This is now done in update_undo_history, so should not occur here.
// Ideally, all clean_up() calls would be removed, but this is a simpler solution.
void clean_up(void)
{
	return;
}

void set_freeze_undo_additions(Boolean val)
{
	freeze_undo_additions = val;
}

void set_latest_line_var(F_line *line)
{
	latest_line = line;
}

void set_latest_spline_var(F_spline *spline)
{
	latest_spline = spline;
}

void set_latestarc(F_arc *arc)
{
	saved_objects.arcs = arc;
}

void set_latestobjects(F_compound *objects)
{
	saved_objects = *objects;
}

void set_latestcompound(F_compound *compound)
{
	saved_objects.compounds = compound;
}

void set_latestellipse(F_ellipse *ellipse)
{
	saved_objects.ellipses = ellipse;
}

void set_latestline(F_line *line)
{
	saved_objects.lines = line;
}

void set_latestspline(F_spline *spline)
{
	saved_objects.splines = spline;
}

void set_latesttext(F_text *text)
{
	saved_objects.texts = text;
}

void set_last_prevpoint(F_point *prev_point)
{
	last_prev_point = prev_point;
}

void set_last_selectedpoint(F_point *selected_point)
{
	last_selected_point = selected_point;
}

void set_last_selectedsfactor(F_sfactor *selected_sfactor)
{
	last_selected_sfactor = selected_sfactor;
}

void set_last_nextpoint(F_point *next_point)
{
	last_next_point = next_point;
}

void set_last_arcpointnum(int num)
{
	last_arcpointnum = num;
}

void set_lastposition(int x, int y)
{
	last_position.x = x;
	last_position.y = y;
}

void set_newposition(int x, int y)
{
	new_position.x = x;
	new_position.y = y;
}

void set_action(int action)
{
	last_action = action;
}

void set_action_object(int action, int object)
{
	last_action = action;
	last_object = object;
}

void set_lastlinkinfo(int mode, F_linkinfo *links)
{
	last_linkmode = mode;
	last_links = links;
}

void set_last_tension(double origin, double extremity)
{
	last_origin_tension = origin;
	last_extremity_tension = extremity;
}

void set_last_arrows(F_arrow *forward, F_arrow *backward)
{
	last_for_arrow = forward;
	last_back_arrow = backward;
}

// This is how an action is added to the undo history
void undo_update_history()
{
	if (freeze_undo_additions)
		return;

	// free anything in redo_stack to avoid memory leaks. See u_free.c.
	if (!freeze_redo_cleanup)
		free_history(&redo_stack);

	// add element to undo_stack
	F_history *cur_history = undo_stack;
	undo_stack = create_history();
	undo_stack->next = cur_history;

	undo_stack->saved_objects = create_compound();

	// copy pointers over
	undo_stack->saved_objects->arcs = saved_objects.arcs;
	undo_stack->saved_objects->ellipses = saved_objects.ellipses;
	undo_stack->saved_objects->lines = saved_objects.lines;
	undo_stack->saved_objects->splines = saved_objects.splines;
	undo_stack->saved_objects->comments = saved_objects.comments;
	undo_stack->saved_objects->texts = saved_objects.texts;
	undo_stack->saved_objects->compounds = saved_objects.compounds;

	// clean local saved_objects. This NEEDS to be done, or else freeing redo_stack will free the last object of each type.
	saved_objects.arcs = NULL;
	saved_objects.ellipses = NULL;
	saved_objects.lines = NULL;
	saved_objects.splines = NULL;
	saved_objects.comments = NULL;
	saved_objects.texts = NULL;
	saved_objects.compounds = NULL;

	// copy local variables
	undo_stack->last_action = last_action;
	undo_stack->last_object = last_object;

	undo_stack->last_prev_point = last_prev_point;
	undo_stack->last_next_point = last_next_point;
	undo_stack->last_selected_point = last_selected_point;

	undo_stack->saved_for_arrow = saved_for_arrow;
	undo_stack->saved_back_arrow = saved_back_arrow;

	// clear problematic local variables
	saved_for_arrow = NULL;
	saved_back_arrow = NULL;

	// handle some local variables in groups for ease of access
	undo_stack->latest_line = latest_line;
	latest_line = NULL;
	undo_stack->latest_spline = latest_spline;
	latest_spline = NULL;

	undo_stack->last_selected_sfactor = last_selected_sfactor;
	last_selected_sfactor = NULL;

	undo_stack->new_x = new_position.x;
	undo_stack->new_y = new_position.y;
	undo_stack->last_x = last_position.x;
	undo_stack->last_y = last_position.y;
}

void pop_stack(F_history **stack)
{
	if (*stack != NULL)
		*stack = (*stack)->next;
}

void swap_stack(F_history **stack)
{
	if (*stack == NULL)
		return;
	F_history **other_stack;
	if (*stack == undo_stack)
		other_stack = &redo_stack;
	else if (*stack == redo_stack)
		other_stack = &undo_stack;
	else
		return;

	// remember element
	F_history *element = (*stack);

	// remove element from stack
	pop_stack(stack);

	// add element to other stack
	element->next = *other_stack;
	*other_stack = element;
}