/*******************************************************************************/
/**
*      @file : font.h
*   @version : 2
*      @date : October 21, 2015
*    @author : Enzo IGLESIS
* @copyright : Copyright (c) 2015 Enzo IGLESIS
*******************************************************************************/

#ifndef FONT_H_
#define FONT_H_
/**** COLOR *****/
    /* FOREGROUND */
#define F_BLACK         "\x1B[30m"      /* set foreground to color black */
#define F_RED           "\x1B[31m"      /* set foreground to color red */
#define F_GREEN         "\x1B[32m"      /* set foreground to color green */
#define F_YELLOW        "\x1B[33m"      /* set foreground to color yellow */
#define F_BLUE          "\x1B[34m"      /* set foreground to color blue */
#define F_MAGENTA       "\x1B[35m"      /* set foreground to color magenta */
#define F_CYAN          "\x1B[36m"      /* set foreground to color cyan */
#define F_WHITE         "\x1B[37m"      /* set foreground to color white */
#define F_GRAY          "\x1B[1;30m"    /* set foreground to color gray */
#define F_LIGHTRED      "\x1B[1;31m"    /* set foreground to color lightred */
#define F_LIGHTGREEN    "\x1B[1;32m"    /* set foreground to color lightgreen */
#define F_LIGHTYELLOW   "\x1B[1;33m"    /* set foreground to color lightyellow */
#define F_LIGHTBLUE     "\x1B[1;34m"    /* set foreground to color lightblue */
#define F_LIGHTMAGENTA  "\x1B[1;35m"    /* set foreground to color lightmagenta */
#define F_LIGHTCYAN     "\x1B[1;36m"    /* set foreground to color lightcyan */
#define F_LIGHTWHITE    "\x1B[1;37m"    /* set foreground to color lightwhite */
    /* BACKGROUND */
#define B_BLACK         "\x1B[40m"      /* set background to color black */
#define B_RED           "\x1B[41m"      /* set background to color red */
#define B_GREEN         "\x1B[42m"      /* set background to color green */
#define B_YELLOW        "\x1B[43m"      /* set background to color yellow */
#define B_BLUE          "\x1B[44m"      /* set background to color blue */
#define B_MAGENTA       "\x1B[45m"      /* set background to color magenta */
#define B_CYAN          "\x1B[46m"      /* set background to color cyan */
#define B_WHITE         "\x1B[47m"      /* set background to color white */
#define B_GRAY          "\x1B[40;1m"    /* set background to color gray */
#define B_LIGHTRED      "\x1B[41;1m"    /* set background to color lightred */
#define B_LIGHTGREEN    "\x1B[42;1m"    /* set background to color lightgreen */
#define B_LIGHTYELLOW   "\x1B[43;1m"    /* set background to color lightyellow */
#define B_LIGHTBLUE     "\x1B[44;1m"    /* set background to color lightblue */
#define B_LIGHTMAGENTA  "\x1B[45;1m"    /* set background to color lightmagenta */
#define B_LIGHTCYAN     "\x1B[46;1m"    /* set background to color lightcyan */
#define B_LIGHTWHITE    "\x1B[47;1m"    /* set background to color lightwhite */
    /* FOREGROUND & BACKGROUND */
#define DEFAULTCOLOR    "\x1B[0;m"

/**** MISCELLANEOUS ****/
#define BOLDFONT        "\x1b[1m"   /* bold characters */
#define UNDERLINEFONT   "\x1B[4m"   /* Underlined characters */
#define SINGLEWIDTH     "\x1B#5"    /* Normal, single-width characters */
#define DOUBLEWIDTH     "\x1B#6"    /* Creates double-width characters */

/**** SCREEN ****/
#define CLEARSCREEN     "\x1B[2J"   /* clear the screen */
#define CLEARLINE       "\x1B[2K"   /* clear line */

/**** CURSOR ****/
#define CURSORHOME      "\x1B[H"    /* brings back the cursor to (1,1) */
#define SAVECURSOR      "\x1B[s"    /* save the cursor position */
#define RESTORECURSOR   "\x1B[u"    /* restor the cursor to the saved position */
#define CURSORUP        "\x1B[A"    /* change the current cursor position to (x,y-1) */
#define CURSORDOWN      "\x1B[B"    /* change the current cursor position to (x,y+1) */
#define CURSORLEFT      "\x1B[D"    /* change the current cursor position to (x-1,y-1) */
#define CURSORRIGHT     "\x1B[C"    /* change the current cursor position to (x+1,y) */
#define gotoxy(X,Y)     printf("\x1B[%02u;%02uf", (unsigned int)(Y), (unsigned int )(X))    /* change the current cursor position to (x,y) */

#endif /* FONT_H_ */
