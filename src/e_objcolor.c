/*
 * FIG : Facility for Interactive Generation of figures
 * Copyright (c) 1991 by Paul King
 * Parts Copyright (c) 1989-2007 by Brian V. Smith
 *
 * Any party obtaining a copy of these files is granted, free of charge, a
 * full and unrestricted irrevocable, world-wide, paid up, royalty-free,
 * nonexclusive right and license to deal in this software and documentation
 * files (the "Software"), including without limitation the rights to use,
 * copy, modify, merge, publish distribute, sublicense and/or sell copies of
 * the Software, and to permit persons who receive copies from any such
 * party to do so, with the only requirement being that the above copyright
 * and this permission notice remain intact.
 *
 */

#include "fig.h"
#include "resources.h"
#include "object.h"
#include "mode.h"
#include "paintop.h"
#include "d_text.h"
#include "u_create.h"
#include "u_list.h"
#include "u_draw.h"
#include "u_search.h"
#include "w_canvas.h"
#include "w_drawprim.h"
#include "w_indpanel.h"
#include "w_mousefun.h"
#include "w_msgpanel.h"
#include "w_setup.h"
#include "w_util.h"

#include "e_scale.h"
#include "f_util.h"
#include "u_bound.h"
#include "u_fonts.h"
#include "u_free.h"
#include "u_redraw.h"
#include "w_cursor.h"
#include "w_util.h"

static void init_color_object(F_line *p, int type, int x, int y, int px, int py);
static void init_color_border(F_line *p, int type, int x, int y, int px, int py);

#define up_part(lv, rv, mask)    \
    if (cur_updatemask & (mask)) \
    (lv) = (rv)

void color_line(F_line *line);
void color_line_border(F_line *line);
void color_ellipse(F_ellipse *ellipse);
void color_ellipse_border(F_ellipse *ellipse);
void color_arc(F_arc *arc);
void color_arc_border(F_arc *arc);
void color_spline(F_spline *spline);
void color_spline_border(F_spline *spline);
void change_fillstyle(void *object);

// initializing mouse and canvas controls
void objcolor_selected(void)
{
    set_mousefun("change fill color", "", "change border color",
                 LOC_OBJ, LOC_OBJ, LOC_OBJ);
    canvas_kbd_proc = null_proc;
    canvas_locmove_proc = null_proc;
    canvas_ref_proc = null_proc;
    init_searchproc_left(init_color_object);  // this controls left click
    init_searchproc_right(init_color_border); // this controls right click
    canvas_leftbut_proc = object_search_left;
    canvas_middlebut_proc = null_proc;
    canvas_rightbut_proc = object_search_right;
    set_cursor(pick9_cursor);
    /* manage on the update buttons */
    manage_update_buts();
    reset_action_on();
}

// #taskQuickColoring_newFiles
//----------------------------------- Code Starts Here ----------------------------------
/* INFO: This file has the functions to manage the quick coloring. Above this area, there
 *   are the declarations and the main function 'objcolor_selected'.  It is that function
 *   that needs to be linked to the icon.  What is happening inside this function?  Below
 *   this area,  there are fuctions to color the objects and borders for lines, ellipses,
 *   arcs,  and splines. In the end,  we have the function 'change_fillstyle' that checks
 *   that the fill style is legal for the color in the object.
 * GOAL: Create TWO functions to control the object's initial fill color and border color
 *   The  functions  have already been  declared  ABOVE in this file.  They do not return
 *   anything, and have six arguments: a 'p' pointer object  and five  int variables that
 *   represent coordinates passed as its arguments.
 * 
 * How to do that?
 * INFO:  Follow the  instructions below to build the  functions.   The two functions are
 *   nearly the same, just the one instruction is different, the step (d). Use the global
 *   pointers  in the file  'object.h',  to manipulate the object 'p'.  Use the variables
 *   that represent a pointer to the current object and a pointer to a new object.        
 * GOAL: To each function do:
 *   1) Define the function.
 *   2) Define a 'switch' statement that calls the  necessary  functions according to the
 *      type of object. Test five types:  O_COMPOUND,  O_POLYLINE,  O_ELLIPSE, O_ARC, and
 *      O_SPLINE.  When  the  object  is a compound,  just set a message  "Break compound
 *      before coloring objects". For the other cases:
 *      a) Using  a  function  from  'w_cursor.h', set  a  temporary  cursor  passing  in
 *         'wait_cursor' as its argument.
 *      b) Cast the object p to the appropriate type and set it as the current object.
 *      c) Call a function  from  'u_create.h',  to make a copy of the current object and
 *         set it into the new object.
 *      d) Call the function to color the new respective object OR the border.
 *      e) Call a function from 'u_list.h' to change the current object to the new one.
 *      f) Call a function from 'u_redraw.h'  to  redisplay the current object.  It should
 *         redraw anything near the old object.
 *      g) Call a function from 'u_redraw.h'  to redisplay the new object.  It should draw
 *         the new one.
 *      h) Write a message stating that the object's fill color has changed.
 *
 *      The default case should just return the function.
 *
 *   3) Reset the cursor.                                                               */
 
/**
 * Now continue to create the header file for objcolor 
 */
//----------------------------------- Code ends Here ------------------------------------

// updates the ellipse's and related object's color and fillstyle
void color_ellipse(F_ellipse *ellipse)
{
    draw_ellipse(ellipse, ERASE);
    up_part(ellipse->fill_style, cur_fillstyle, I_FILLSTYLE);
    up_part(ellipse->fill_color, cur_fillcolor, I_FILL_COLOR);
    change_fillstyle(ellipse); /* make sure it has legal fill style if color changed */
}

// updates the ellipse's and related object's border color
void color_ellipse_border(F_ellipse *ellipse)
{
    draw_ellipse(ellipse, ERASE);
    up_part(ellipse->pen_color, cur_pencolor, I_PEN_COLOR);
}

// updates the arc's and related object's color and fillstyle
void color_arc(F_arc *arc)
{
    draw_arc(arc, ERASE);
    up_part(arc->fill_style, cur_fillstyle, I_FILLSTYLE);
    up_part(arc->fill_color, cur_fillcolor, I_FILL_COLOR);
    change_fillstyle(arc); /* make sure it has legal fill style if color changed */
}

// updates the arc's and related object's border color
void color_arc_border(F_arc *arc)
{
    draw_arc(arc, ERASE);
    up_part(arc->pen_color, cur_pencolor, I_PEN_COLOR);
}

// updates the line's and related object's color and fillstyle
void color_line(F_line *line)
{
    draw_line(line, ERASE);
    up_part(line->thickness, cur_linewidth, I_LINEWIDTH);
    if (line->type != T_PICTURE)
    {
        up_part(line->fill_color, cur_fillcolor, I_FILL_COLOR);
        up_part(line->fill_style, cur_fillstyle, I_FILLSTYLE);
    }
    else if (line->pic->pic_cache && line->pic->pic_cache->subtype == T_PIC_XBM)
    {
        /* only XBM pictures have color */
        up_part(line->pen_color, cur_pencolor, I_PEN_COLOR);
    }
    change_fillstyle(line); /* make sure it has legal fill style if color changed */
}

// updates the line's and related object's border color
void color_line_border(F_line *line)
{
    draw_line(line, ERASE);
    up_part(line->thickness, cur_linewidth, I_LINEWIDTH);
    if (line->type != T_PICTURE)
    {
        up_part(line->pen_color, cur_pencolor, I_PEN_COLOR);
    }
    else if (line->pic->pic_cache && line->pic->pic_cache->subtype == T_PIC_XBM)
    {
        /* only XBM pictures have color */
        up_part(line->pen_color, cur_pencolor, I_PEN_COLOR);
    }
}

// updates the spline's and related object's color and fillstyle
void color_spline(F_spline *spline)
{
    draw_spline(spline, ERASE);
    up_part(spline->fill_style, cur_fillstyle, I_FILLSTYLE);
    up_part(spline->fill_color, cur_fillcolor, I_FILL_COLOR);
    change_fillstyle(spline); /* make sure it has legal fill style if color changed */
}

// updates the spline's and related object's border color
void color_spline_border(F_spline *spline)
{
    draw_spline(spline, ERASE);
    up_part(spline->pen_color, cur_pencolor, I_PEN_COLOR);
}

/* check that the fill style is legal for the color in the object */
/* WARNING: this procedure assumes that splines, lines, arcs and ellipses
        all have the same structure up to the fill_style and color */

void change_fillstyle(void *obj)
{
    F_line *object = obj;
    if (object->fill_color == BLACK || object->fill_color == DEFAULT)
    {
        if (object->fill_style >= NUMSHADEPATS &&
            object->fill_style < NUMSHADEPATS + NUMTINTPATS)
            object->fill_style = UNFILLED;
    }
}