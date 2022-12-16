/*
 * FILE:        carDriver.cpp
 * Project:	    PROG 1385 - Assignment 5
 * Author:	    Hoang Phuc Tran
 * Student ID:  8789102
 * Date:		July 21, 2022
 * Description:  This file is used as a testing harness for PioneerCarRadio class. It will display all the attributes of AmFmRadio class.
 */

#include "PioneerCarRadio.h"

int main()
{
	// Declare a pointer to PioneerCarRadio class
	PioneerCarRadio* ptrPioneerCarRadio = NULL;

	// Initilize a an array of 5 struct Freqs that contains the initial radio preset values
	Freqs NewPresets[MAX_FREQS] = { {1000, 102.1}, {1210, 104.3}, {800, 100.1}, {700,99.3}, {1300,89.7} };

	// Allocate a memory for new a pointer to PioneerCarRadio class
	ptrPioneerCarRadio = new PioneerCarRadio(false, NewPresets);

	// Check if the RadioManagment method is called successfully
	if (ptrPioneerCarRadio->RadioManagement() == SUCCESS) {

		// Free the memory for the pointer that we have allocated
		delete(ptrPioneerCarRadio);
		return SUCCESS;
	}

	else {
		// Free the memory for the pointer that we have allocated
		delete(ptrPioneerCarRadio);
		return FAILURE;
	}


	return SUCCESS;
}