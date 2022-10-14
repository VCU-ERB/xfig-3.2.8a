// Author Jason Reed

#include "fig.h"
#include "resources.h"
#include "mode.h"
#include "object.h"
#include "u_search.h"
#include "u_create.h"
#include "e_depthctrl.h"
#include "u_list.h"
#include "w_canvas.h"
#include "w_mousefun.h"
#include "w_msgpanel.h"
#include "w_layers.h"
#include "d_text.h"
#include "u_bound.h"
#include "u_markers.h"
#include "u_redraw.h"
#include "w_cursor.h"
#include "f_util.h"
#include "u_create.h"

depthctrl_selected(void)
{
    set_mousefun("Bring to Front", "Adjust Depth", "Send to Back", "", "", ""); // control indicator
    canvas_kbd_proc = null_proc;
    canvas_locmove_proc = null_proc;
    canvas_ref_proc = null_proc;
    init_searchproc_left(bringtofront);
    init_searchproc_middle(adjustdepth);
    init_searchproc_right(sendtoback);
    canvas_leftbut_proc = object_search_left;
    canvas_middlebut_proc = object_search_middle;
    canvas_rightbut_proc = object_search_right;
    set_cursor(pick15_cursor);
}

// #taskSendBack_newFiles
//----------------------------------- Code Starts Here ----------------------------------
/* GOAL: Create the function "bringtofront".  It will allow  the user  to move objects to 
 *   the front  of a new xFig file by manipulating depth.  This function will receive two 
 *   information: the object and the type.  
 * INFO: Type is a integer that describe the object type. You can see all possible types 
 *   in the file 'object.h' in the section 'object codes'. Use the function 'adjustDepth'
 *   in this file as a reference for creating your functions.
 * 
 * FIRST STEP:  There are two type cases in this method, one for compound objects and one 
 *   for single objects. You have to check if the passed object is compound or not. 
 * 
 *  FOR COMPOUND OBJECTS:
 *   1. Find the largest and smallest depth and the minimum depth in occupy. Look in
 *      'f_util.c' and in the next functions for methods to help you out with this.
 *   2. Create a integer variable 'offeset' to help you change the depth.
 *   3. If the max depth minus the min depth is smaller than the minimum depth occupied,
 *      you will need to offset the compound's depth by a certain amount (offset = somthing).
 *      If its not, you need another offset value. 
 *      
 *      This is the  complicated  part of the task!  Think of what you are  attempting to
 *      offset when completing this calculation.  Try to draw a picture to represent some
 *      compounds  overlapping  each other.  Assign the c ompounds a depth, how would you
 *      mathematically compute which object to bring forward and by what amount?
 * 
 *   4. After you have completed the if  else for offsetting the compound,  you will need
 *      to swap the offset object depth value of by creating  a temp  F_compound pointer.
 *      First,  use the function to copy compounds in  the file  "u_create.c" to copy the
 *      object.  Than, use the function  'offset_compound_depth'  in this file.  Use  the 
 *      function 'add_compound_depth' ("u_list.c") to correct the state. Finally, use the
 *      function 'remove_compound_depth' ("u_list.c") to remove the compound depth of the
 *      copy pointer.
 *  
 *  FOR SINGLE OBJECTS:
 *   1. Create a variable and store the object old depth.
 *   2. In this situation we have three cases for changing the depth.
 *   3. For the FIRST case, if the min depth is  >  0 and the object's depth is not equal
 *      to 0: change the object depth to the minimum depth minus 1.  Then, add this depth
 *      to the single object  (use function  'add_depth'  from "u_list.c") and remove the
 *      old object depth (function 'remove_depth' from "u_list.c").
 *   4. In the SECOND case, if the minimum depth is 0 but the object's depth is not equal
 *      to 0, let the user know that  "Depth 0 is occupied, moving object anyway". Rather 
 *      than changing the pointer's depth p to the minimum depth, we can just set it to 0.
 *      As the one you created above you'll also need to add the new depth and remove the 
 *      old one.
 *   5. The LAST case is a default case.  If the above two conditions are not  applicable,
 *      just send a message to the user.
 *   
 *   LAST STEP: Redisplay the object.
 */

void bringtofront(F_line *p, int type)
{
    
}
//----------------------------------- Code ends Here ------------------------------------


// #taskSendBack_newFiles
//----------------------------------- Code Starts Here ----------------------------------
/* GOAL: Create the function "sendtoback". It will allow the user to move objects to 
 *   the back of a new xFig file by manipulating depth.
 * INFO: There are two type cases in this method, one for compound objects and one for 
 *   single objects. 
 * 
 *   FOR COMPOUND OBJECTS:
 *   1. Find the largest and smallest depth and the minimum depth in occupy.
 *   2. Create a integer variable 'offeset' to help you change the depth.
 *   3. There are two cases to control here. 
 *   2. There is a default case for offsetting if the (max depth in the compound minus the
 *      smallest depth in the compound) is smaller than the (possible max depth(999) minus
 *      the max occupied depth).
 *   3. There is also an edge case if the max occupied depth is occupied.
 *   4. You will then have to offset the depth of the compound by swapping.
 *   5. Finally, remove the copy compound used to swap.
 * 
 *   FOR SINGLE OBJECTS:
 *   1. Create a variable and store the object old depth.
 *   2. In this situation we have three cases for changing the depth.
 *   3. The  FIRST  case is the normal case for if the largest occupied  depth is not the
 *      max overall depth. If the minimum depth is >0 and the object's depth is not equal
 *      to 0. Change the object's depth to the max depth plus one and remove the old one.
 *   4. The  SECOND  case  is one  edge case  where the largest occupied depth is the max
 *      overall depth. If the mininum depth is 0 but the object's depth is not equal to 0,
 *      let  the user know that "Depth 0 is ocupied,  moving object anyway".  Rather than
 *      changing the object depth p to the maximum depth,  just set it to 999.  Than, add
 *      the new depth and remove the old one.
 *   5. The LAST case is a default case.  If the above two conditions are not  applicable,
 *      just send a message to the user.
 *
 *  LAST STEP: Redisplay the object.                                   */

void sendtoback(F_line* p, int type)
{
 
}
//----------------------------------- Code ends Here ------------------------------------

void adjustdepth(F_line* p, int type) //sets depth to input value from attributes panel
{
    if (type == O_COMPOUND) //for compound objects
    {
        int maxc = find_largest_depth(p); //largest depth in compound
        int minc = find_smallest_depth(p);//smallest depth in compound
        int offset = 0;
        
        //minc becomes cur_depth preserving relative depths

        if ((maxc - minc) < (999 - cur_depth)) // default case
        {
            offset = (cur_depth - minc);
        }
        else //edge case
        {
            offset = 999 - maxc;
        }

        F_compound* c_old = copy_compound(p);
        offset_compound_depth(p, offset);
        add_compound_depth(p);
        remove_compound_depth(c_old);
    }
    else
    {
        int old = p->depth;
        p->depth = cur_depth;
        add_depth(type, p->depth);
        remove_depth(type, old);
    }
    redisplay_object(p, type);
    
}

// local helper functions

int get_min_depth() //minimum depth with an object
{
    int i = 0;
    int ans = -2;
    while (ans == -2)
    {
        if (object_depths[i] != 0)
        {
            ans = i;
        }
        i = i + 1;
    }
    return ans;
}

int get_max_depth() //maximum depth with an object
{
    int i = 999;
    int ans = 1000;
    while (ans == 1000)
    {
        if (object_depths[i] != 0)
        {
            ans = i;
        }
        i = i - 1;
    }
    return ans;
}

void redisplay_object(F_line* p, int type) // call to redraw any object type
{
    switch (type)
    {
    case O_POLYLINE: redisplay_line((F_line*)p);         break;
    case O_ARC: redisplay_arc((F_arc*)p);           break;
    case O_ELLIPSE: redisplay_ellipse((F_ellipse*)p);   break;
    case O_SPLINE: redisplay_spline((F_spline*)p);     break;
    case O_TXT: redisplay_text((F_text*)p);         break;
    case O_COMPOUND: redisplay_compound((F_compound*)p); break;
    }
}

void offset_compound_depth(F_compound *p, int offset)
{
    F_line* l;
    F_arc* a;
    F_ellipse* e;
    F_spline* s;
    F_text* t;
    F_compound* c1;

    for (l = p->lines; l != NULL; l = l->next)
    {
        l->depth = l->depth + offset;
    }
    for (a = p->arcs; a != NULL; a = a->next)
    {
        a->depth = a->depth + offset;
    }
    for (e = p->ellipses; e != NULL; e = e->next)
    {
        e->depth = e->depth + offset;
    }
    for (s = p->splines; s != NULL; s = s->next)
    {
        s->depth = s->depth + offset;
    }
    for (t = p->texts; t != NULL; t = t->next)
    {
        t->depth = t->depth + offset;
    }
    for (c1 = p->compounds; c1 != NULL; c1 = c1->next)
    {
        offset_compound_depth(c1, offset);
    }
}
