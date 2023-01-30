// Provide file-level documentation block as described in tutorial specification

/* !
@file q.c
@author Herman Nur Arif Bin Abdul Rashid (hermannurarif.b)
@course CSD1121
@section IMGD
@tutorial assignment 2
@date 14/09/2022
@brief This file contains 2 functions, one to draw a tree and the other to draw an animal
*//*______________________________________________________________________*/

// Provide function-level documentation block as described in tutorial
#include <stdio.h>

/* !
When this function is called upon, a tree will be drawn
*//*______________________________________________________________*/

// specification for function draw_tree
void draw_tree(void) {
	printf("    *\n");
	printf("   ***\n");
	printf("  *****\n");
	printf(" *******\n");
	printf("*********\n");
	printf("    #\n");
	printf("    #\n");
	printf("    #\n");
	printf("    #\n");
}
// Provide function-level documentation block as described in tutorial

/*!
When this function is called upon a cat will be drawn
*//*______________________________________________________________*/

// specification for function draw_animal
void draw_animal(void) {
	// equivalently standard library function puts can be
	// used to write text to standard output
	printf("  /\\     /\\\n");
	printf(" /  \\___/  \\\n");
	printf("(           )    -------\n");
	printf("(   '   '   )   / Hello  \\\n");
	printf("(     _     )  <  Junior  |\n");
	printf("(           )   \\ Coder! /\n");
	printf(" |         |     -------\n");
	printf(" |    |    |\n");
	printf(" |    |    |\n");
	printf("(_____|_____)\n");
}



