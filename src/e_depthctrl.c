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
/* GOAL: Create the function "bringtofront". It will allow the user to move objects to 
 *   the front of a new xFig file by manipulating depth.
 * INFO: There are two type cases in this method, one for compound objects and one for 
 *   single objects. 
 * 
 *   First Step:
 *          You have to check if the passed object is compound or single for that you can 
 *          compare it to "O_COMPOUND" which is a generic object variable
 *   FOR COMPOUND OBJECTS:
 *   1. When handling compound objects, think of ways to figure out the minimum and 
 *      maximum depth in a compound as well as the smallest depth in occupy. Look in
 *      'f_util.c' for methods to help you out with this.
 *   2. If the max depth minus the min depth is smaller than the smallest depth occupied,
 *      you will need to offset the compound's depth by a certain amount. Think of what
 *      you are attempting to offset when completing this calculation. Try to draw a
 *      picture to represent some compounds overlapping each other. Assign the compounds
 *      a depth, how would you mathematically compute which object to bring forward and
 *      by what amount?
 *   3. After you have completed the if else for offsetting the compound, you will need
 *      to swap the offset depth value of F_line *p by creating a temp F_compound pointer.
 *   4. Remove the compound depth of the copy pointer.
 *   FOR SINGLE OBJECTS:
 *   1. Create a variable to store p's the old layer's depth.
 *   2. Test three cases for the single objects.
 *   3. For the FIRST case, if the min depth is > 0 and the object's depth is not equal
 *      to 0, change the sent in pointer's depth p to the minimum depth. Then, add this
 *      depth to the single object and finally remove the old layer's depth.
 *   4. In the SECOND case, if the min depth is 0 but the object's depth is not equal to 0,
 *      let the user know that "Depth 0 occupied, moving object anyway". Rather than
 *      changing the pointer's depth p to the minimum depth, we can just set it to 0.
 *      As the one you created above you'll also need to add the new depth and remove the 
 *      old one
 *   5. Create a default case if the above two conditions are not applicable.
 *   6. Redisplay the object.
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
 *   FOR COMPOUND OBJECTS:
 *   1. Look in f_util.c to find helper methods for finding largest or smallest depths in
 *      order to find out what to offset your compound by.
 *   2. There is a default case for offsetting if the (max depth in the compound minus the
 *      smallest depth in the compound) is smaller than the (possible max depth(999) - the max 
 *      occupied depth).
 *   3. THere is also an edge case if the max occupied depth is occupied.
 *   4. You will then have to offset the depth of the compound by swapping.
 *   5. Finally, remove the copy compound used to swap.
 *   FOR SINGLE OBJECTS:
 *   1. Create a variable to store the old layer's depth.
 *   2. Test three cases for the single objects.
 *   3. For the FIRST case, if the min depth is > 0 and the object's depth is not equal
 *      to 0, change the sent in pointer's depth p to the minimum depth. Then, add this
 *      depth to the single object and finally remove the old layer's depth.
 *   4. In the SECOND case, if the min depth is 0 but the object's depth is not equal to 0,
 *      let the user know that "Depth 0 ocupied, moving object anyway". Rather than
 *      changing the pointer's depth p to the minimum depth, we can just set it to 0.
 *   5. Create a default case if the above two conditions are not applicable.
 *   6. Redisplay the object.
 *   FOR SINGLE OBJECTS:
 *   1. Keep track of the single objects depth that will eventually be changed.
 *   2. You should have one normal case for if the largest occupied depth is not the max overall depth.
 *   3. In this case you should change your single object's depth to the max depth and remove the old one.
 *   4. You will also have one edge case if the largest occupied depth is the max overall depth.
 *   5. In this case you will need to change the single object's depth to the max overall depth.
 *   6. You will also need a default case if the single object is already at max overall depth when attempting to sendtoback.
 *   7. Finally, redisplay your object. 
 */

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
