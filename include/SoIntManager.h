// --------------------------------------------------------------------------------------
/*! 
	Copyright (C) 2002 by the SGADE authors
	For conditions of distribution and use, see copyright notice in SoLicense.txt

	\file		SoIntManager.h
	\date		Sep 19 2001
	\ingroup	SoIntManager

	See the \a SoIntManager module for more information.
*/
// --------------------------------------------------------------------------------------

#ifndef SO_INTERRUPT_MANAGER_H
#define SO_INTERRUPT_MANAGER_H

#ifdef __cplusplus
	extern "C" {
#endif


// --------------------------------------------------------------------------------------
/*! 
	\defgroup SoIntManager SoIntManager
	\brief	  Interrupt handling routines.

	Singleton

	This module contains all functionality to get control over interrupts. You can 
	enable/disable each unique interrupt. Or enable/disable them all at once. You can 
	install one interrupt handler (function) for each interrupt type.

	One very very important thing to remember is that you might be using some interrupts
	indirectly. For example when you use the \a SoSpriteManager or the \a SoTimer modules
	then you will be using interrupts indirectly (cause these modules use interrupts). 
	These modules will probably even implicitly enable these interrupts. That's why you 
	sometimes find that the interrupt master is enabled even though you never did so. So
	watch out...

*/ //! @{
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// Includes
// --------------------------------------------------------------------------------------

#include "SoSystem.h"
#include "SoDisplay.h"

// --------------------------------------------------------------------------------------
// Defines
// --------------------------------------------------------------------------------------

// ---------------------------------------
/*!
	\name Interrupt types
	
	These constants can be used to uniquely identify different interrupts.
	
	The values of these constants are according to their bit-position in the
	interrupt registers. For example we can use (1 << SO_INTERRUPT_TYPE_VBLANK)
	to enable the VBlank interrupt in the interrupt enable register. So do not mess with
	their values.


*///@{   
// ---------------------------------------
#define SO_INTERRUPT_TYPE_VBLANK	0	
#define SO_INTERRUPT_TYPE_HBLANK	1	
#define SO_INTERRUPT_TYPE_VTRIGGER	2	
#define SO_INTERRUPT_TYPE_TIMER_0	3	
#define SO_INTERRUPT_TYPE_TIMER_1	4	
#define SO_INTERRUPT_TYPE_TIMER_2	5	
#define SO_INTERRUPT_TYPE_TIMER_3	6	
#define SO_INTERRUPT_TYPE_SERIAL	7 
#define SO_INTERRUPT_TYPE_DMA_0		8
#define SO_INTERRUPT_TYPE_DMA_1		9
#define SO_INTERRUPT_TYPE_DMA_2		10
#define SO_INTERRUPT_TYPE_DMA_3		11
#define SO_INTERRUPT_TYPE_KEYPAD	12
#define SO_INTERRUPT_TYPE_CART		13
#define SO_NUM_INTERRUPT_TYPES		14
//@} 
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// Typedefs
// --------------------------------------------------------------------------------------

/*!
	\brief Interrupt handler type definition;

	This prototype defines interrupt handlers. When you want to install an interrupt 
	handler you have to pass the installer a function of this type. Simply it's just
	a function with no parameters and which returns nothing.
*/
typedef void (*SoInterruptHandler)( void );

// --------------------------------------------------------------------------------------
// Public Functions
// --------------------------------------------------------------------------------------

void SoIntManagerInitialize( void );

void SoIntManagerSetInterruptHandler(	 u32 a_InterruptType, SoInterruptHandler a_IntHandler );

void SoIntManagerEnableInterruptMaster(  void );
void SoIntManagerDisableInterruptMaster( void );

void SoIntManagerEnableInterrupt(	   u32 a_InterruptType );
void SoIntManagerDisableInterrupt(	   u32 a_InterruptType );

// Deprecated functions
#define SoIntManagerAddInterruptHandler    SO_DEPRECATED_FUNCTION(SoIntManagerAddInterruptHandler, use_SoIntManagerSetInterruptHandler)
#define SoIntManagerRemoveInterruptHandler SO_DEPRECATED_FUNCTION(SoIntManagerAddInterruptHandler, use_SoIntManagerSetInterruptHandler_with_a_NULL_parameter)

// --------------------------------------------------------------------------------------
// Private Functions;
// Declared here, used in .c, implemented in .S
// --------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------------
/*! 
	\brief The interrupt handler

	\internal

	This is the function that is called when an interrupt occurs. It checks what 
	interrupt occured and calls the installed interrupt handler for that specific 
	interrupt type.
*/
// --------------------------------------------------------------------------------------
void SoIntManagerInterruptHandler( void );

//! \internal Declared here because we need in both the .C and the assembly.
extern SoInterruptHandler g_InterruptHandlers[ SO_NUM_INTERRUPT_TYPES ];

// --------------------------------------------------------------------------------------
// EOF
// --------------------------------------------------------------------------------------

//! @}

#ifdef __cplusplus
} // extern "C"
#endif

#endif

