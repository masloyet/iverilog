#ifndef __vpi_user_H
#define __vpi_user_H
/*
 * Copyright (c) 1999 Stephen Williams (steve@icarus.com)
 *
 *    This source code is free software; you can redistribute it
 *    and/or modify it in source code form under the terms of the GNU
 *    General Public License as published by the Free Software
 *    Foundation; either version 2 of the License, or (at your option)
 *    any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */
#if !defined(WINNT)
#ident "$Id: vpi_user.h,v 1.2 1999/08/18 03:44:49 steve Exp $"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __vpiHandle *vpiHandle;

/*
 * This structure is created by the VPI application to provide hooks
 * into the application that the compiler/simulator can access.
 */
typedef struct t_vpi_systf_data {
      int type;
      int subtype;
      char *tfname;
      int (*calltf)(char*);
      int (*compiletf)(char*);
      int (*sizetf)();
      char *user_data;
} s_vpi_systf_data, *p_vpi_systf_data;

/* The type in the above structure can have one of the following
   values: */
#define vpiSysTask  1
#define vpiSysFunc  2


typedef struct t_vpi_time {
      int type;
      unsigned int high;
      unsigned int low;
      double real;
} s_vpi_time, *p_vpi_time;

#define vpiScaledRealTime 1
#define vpiSimTime        2
#define vpiSuppressTime   3

/*
 * This structure holds values that are passed back and forth between
 * the simulator and the application.
 */
typedef struct t_vpi_value {
      int format;
      union {
	    char*str;
	    int scalar;
	    int integer;
	    double real;
	    struct t_vpi_time *time;
	    struct t_vpi_vecval *vector;
	    struct t_vpi_strengthval *strength;
	    char*misc;
      } value;
} s_vpi_value, *p_vpi_value;

/* These are valid codes for the format of the t_vpi_value structure. */
#define vpiBinStrVal    1
#define vpiOctStrVal    2
#define vpiDecStrVal    3
#define vpiHexStrVal    4
#define vpiScalerVal    5
#define vpiIntVal       6
#define vpiReadVal      7
#define vpiStringVal    8
#define vpiVectorVal    9
#define vpiStrengthVal 10
#define vpiTimeVal     11
#define vpiObjTypeVal  12
#define vpiSuppressVal 13


/* OBJECT CODES */
#define vpiConstant     7
#define vpiNet         36
#define vpiReg         48
#define vpiSysTaskCall 57
#define vpiTimeVar     63
#define vpiSysTfCall   85
#define vpiArgument    89


/* PROPERTIES */
#define vpiType       1
#define vpiName       2
#define vpiFullName   3
#define vpiConstType 43
#   define vpiDecConst    1
#   define vpiRealConst   2
#   define vpiBinaryConst 3
#   define vpiOctConst    4
#   define vpiHexConst    5
#   define vpiStringConst 6


/* VPI FUNCTIONS */
extern void vpi_register_systf(const struct t_vpi_systf_data*ss);
extern void vpi_printf(const char*fmt, ...);

/*
 * This function allows a vpi application to control the simulation
 * engine. The operation parameter specifies the function to
 * perform. The remaining parameters (if any) are interpreted by the
 * operation. The vpi_sim_control definition was added to P1364-2000
 * 14 July 1999. See PLI Task Force ID: PTF-161
 *
 * vpiFinish - perform the $finish operation, as soon as the user
 *             function returns. This operation takes a single
 *             parameter, a diagnostic exit code.
 *
 * vpiStop -
 * vpiReset -
 * vpiSetInteractiveScope -
 */
extern int  vpi_sim_control(int operation, ...);
#define vpiStop 1
#define vpiFinish 2
#define vpiReset  3
#define vpiSetInteractiveScope 4

extern vpiHandle  vpi_handle(int type, vpiHandle ref);
extern vpiHandle  vpi_iterate(int type, vpiHandle ref);
extern vpiHandle  vpi_scan(vpiHandle iter);

extern int   vpi_get(int property, vpiHandle ref);
extern char* vpi_get_str(int property, vpiHandle ref);
extern void  vpi_get_value(vpiHandle expr, p_vpi_value value);

extern int vpi_free_object(vpiHandle ref);


/* This is the table of startup routines included in each module. */
extern void (*vlog_startup_routines[])();

#ifdef __cplusplus
}
#endif

/*
 * $Log: vpi_user.h,v $
 * Revision 1.2  1999/08/18 03:44:49  steve
 *  declare vou_sim_control
 *
 * Revision 1.1  1999/08/15 01:23:56  steve
 *  Convert vvm to implement system tasks with vpi.
 *
 */
#endif
