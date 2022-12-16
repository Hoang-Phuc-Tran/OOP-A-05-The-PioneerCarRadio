/*
 * FILE:        AmFmRadio.cpp
 * Project:	    PROG 1385 - Assignment 3
 * Author:	    Hoang Phuc Tran
 * Student ID:  8789102
 * Date:		June 23, 2022
 * Description:  This file contains all methods for the AmFmRadio class.
 *	- 2 constructors
 *		AmFmRadio(bool newOn = false);
		AmFmRadio(bool newOn, Freqs newButton[]);
 *	- a destructor
 *		~AmFmRadio()
 *	- accessors
 *		double GetCurrentStation();     
		int GetNewVolume();             
		char* GetFrequency();          
		Freqs* GetButton();            
		bool GetDisplayOutPut();        
 *	- Mutators
 *		int SetCurrentStation(double newCurrentStation);
 *		void ToggleDisplayOutPut();
 *		int SetVolume(int volume);
 *		int SetVolume();
 *		int SelectCurrentStation(int button_num);
 *		int SetButton(int button_num);
 *		void ToggleFrequency();
 *		bool IsRadioOn();
 *	- Methods
 *		void ShowCurrentSettings();
 *		void ScanUp();
 *		void ScanDown();
 */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AmFmRadio.h"




 /*  -- Method Header Comment
	 Name	: AmFmRadio -- CONSTRUCTOR
	 Purpose : to instantiate a new AmFmRadio object - given a set of attribute values
	 Inputs	:	newOn			Bool		on
	 Outputs	:	NONE
	 Returns	:	Nothing
 */
AmFmRadio::AmFmRadio(bool newOn)
{
	// Loop to assgin new value to members of 5 struct Freqs
	for (int i = 0; i < MAX_FREQS; ++i)
	{
		button[i].AMFreq = MINIMUM_AM;
		button[i].FMFreq = MINIMUM_FM;
		button[i].currentStation = MINIMUM_FM;
		button[i].volumeStruct = INIT_VOLUME;
		copyButton[i].AMFreq = 0;
	}

	// Assign new value to private member data of class AmFmRadio
	displayOutPut = false;
	current_station = INIT_STATION;
	strcpy(frequency, "AM");
	newVolume = 0;
	on = newOn;
	strcpy(copyFrequency, "");
}

/*  -- Method Header Comment
	 Name	: AmFmRadio -- CONSTRUCTOR
	 Purpose : to instantiate a new AmFmRadio object - given a set of attribute values
	 Inputs	:	newOn			Bool		on
				newButton		Freqs       button
	 Outputs	:	NONE
	 Returns	:	Nothing
 */
AmFmRadio::AmFmRadio(bool newOn, Freqs newButton[])
{
	// Loop to assgin new value to members of 5 struct Freqs
	for (int i = 0; i < MAX_FREQS; i++)
	{
		button[i].AMFreq = newButton[i].AMFreq;
		button[i].FMFreq = newButton[i].FMFreq;
		button[i].currentStation = MINIMUM_FM;
		button[i].volumeStruct = INIT_VOLUME;
		copyButton[i].AMFreq = 0;
	}

	// Loop to assgin new value to members of 5 struct Freqs
	displayOutPut = false;
	current_station = INIT_STATION;
	strcpy(frequency, "AM");
	newVolume = 0;
	on = newOn;
	strcpy(copyFrequency, "");
}

/*  -- Method Header Comment
	Name	: ~AmFmRadio -- DESTRUCTOR
	Purpose : to destroy the AmFmRadio object - free up the memory associated with the object
	Inputs	:	NONE
	Outputs	:	a final message from the object before being destroyed
	Returns	:	Nothing
*/
AmFmRadio::~AmFmRadio()
{
	if (displayOutPut)
	{
		printf("Destroying AmFmRadio\n");
	}
}

/*  -- Method Header Comment
	Name	: PowerToggle
	Purpose : this method will switch the radio to on if it is off, and otherwise.
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	NONE
*/
void AmFmRadio::PowerToggle()
{
	// Check if the radio is on or off
	if( on == false )
	{
		// assign the saved volume to volume if the radio is off
		newVolume = button[0].volumeStruct;
		// set the radio to on
		on = true;
	}
	else
	{
		// save the current volume if the radio is on 
		button[0].volumeStruct = newVolume;	
		// Set the volume to 0
		newVolume = 0;
		// set the radio to off
		on = false;
	}

}

/*  -- Method Header Comment
	Name	: IsRadioOn
	Purpose : this method will return the current status of "on" private member data.
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	on			bool 
*/
bool AmFmRadio::IsRadioOn() 
{
	return on;
}

/*  -- Method Header Comment
	Name	: SetVolume
	Purpose : this method set new volume to "int newVolume" data member.
			  IF the input's value < 0, sets to 0
			  IF the input's value > 100, sets to 100
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	int - 0 if set to 0, 2 if set to 100, 1 otherwise
*/
int AmFmRadio::SetVolume()
{
	char buf[20] = "";

	printf("\nEnter the volume level (0 - 100). ");
	//Get input from the user
	fgets(buf, sizeof buf, stdin);
	// convert the string to interger
	newVolume = atoi(buf);

	if( newVolume < 0 ) //if user enters volume less than 0, volume = 0
	{
		newVolume = 0;
		return 0;
	}

	if( newVolume > 100 ) //if user enters volume greater than 100, volume = 100
	{
		newVolume = 100;
		return 2;
	}
	return 1;
}

/*  -- Method Header Comment
	Name	: ToggleFrequency
	Purpose : This method will save the current_station before switching AM 
			frequency to FM frequency and otherwise.
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	NONE
*/
void AmFmRadio::ToggleFrequency()
{
	// Check the frequency is AM or FM
	if( strcmp(frequency, "AM") == 0 )
	{
		// Saved the current_station value before switching to FM frequency
		button[0].currentStation = current_station;
		strcpy(frequency, "FM");
		// Assign the current_station value of FM after switching
		current_station = button[1].currentStation;
	}
	else
	{
		// Saved the current_station before switch to AM frequency
		button[1].currentStation = current_station;
		strcpy(frequency, "AM");
		// Assign the current_station value of AM after switching
		current_station = button[0].currentStation;
	}
}

/*  -- Method Header Comment
	Name	: SetButton
	Purpose : This method will Sets current_station to a field of freqs[button_num]. 
	Inputs	:	button_num		int
	Outputs	:	NONE
	Returns	:	1 if set successfully, 0 otherwise
*/
int AmFmRadio::SetButton(int button_num)
{
	// Check if button_num is out of range
	if( (button_num >= 0) && (button_num <= 4) )
	{
		// Check the frequency is AM of FM frequency
		if( strcmp("AM", frequency) == 0 )
		{
			// sets the current_station value to button[button_num].AMFreq
			// Before assigning, we cast the value to int
			button[button_num].AMFreq = (int)current_station;
		}
		else
		{
			// sets the current_station value to button[button_num].AMFreq
			// Before assigning, we cast the value to float
			button[button_num].FMFreq = (float)current_station;
		}
		return 1;
	}
	return 0;
}

/*  -- Method Header Comment
	Name	: SelectCurrentStation
	Purpose : This method will set a field of freqs[button_num] to current_station
	Inputs	:	button_num		int
	Outputs	:	NONE
	Returns	:	1 if set successfully, 0 otherwise
*/
int AmFmRadio::SelectCurrentStation(int button_num)
{
	// Check if button_num is out of range
	if( (button_num >= 0) && (button_num <= 4) )
	{
		// Check the frequency is AM of FM frequency 
		if( strcmp("AM", frequency) == 0 )
		{
			// Set the button[button_num].AMFreq to current_station
			current_station = button[button_num].AMFreq;
		}
		else
		{
			// Set the button[button_num].AMFreq to current_station
			current_station = button[button_num].FMFreq;
		}
		return 1;
	}
	return 0;
}

/*  -- Method Header Comment
	Name	: ShowCurrentSettings
	Purpose : This method will display all current settings of the radio to stdout.
	Inputs	:	NONE
	Outputs	:	All the current settings
	Returns	:	NONE
*/
void AmFmRadio::ShowCurrentSettings()
{
	// Check is the radio is on or off
	if( on == true )
	{
		printf("\n\nRadio is on. \n");
	}
	else
	{
		printf("\n\nRadio is off. \n");
	}

	printf("\nFrequency: %s\n", frequency);
	printf("Volume: %d\n", newVolume);
	if (strcmp(frequency, "AM") == 0) {
		printf("Current Station: %d %s\n", (int)current_station, frequency);
	}
	else {
		printf("Current Station: %.1f %s\n", current_station, frequency);
	}
	printf("AM Button Settings: ");
	
	// Loop to display all the AM frequency of the radio
	for( int i = 0; i < 5; ++i )
	{
		printf("%d) %6d ", i + 1, button[i].AMFreq);
	}

	printf("\nFM Button Settings: ");
	// Loop to display all the FM frequency of the radio
	for( int j = 0; j < 5; ++j )
	{
		printf("%d) %6.1f ", j + 1, button[j].FMFreq);
	}
}

/*  -- Method Header Comment
	Name	: ScanUp
	Purpose : This method will change the current_station by incrementing by 10 
			  If on AM band, 0.2 if on FM band
	Inputs	:	NONE
	Outputs	:	the value of current_station and frequency
	Returns	:	NONE
*/
void AmFmRadio::ScanUp()
{
	if( strcmp("AM", frequency) == 0 )
	{
		//if current_station is 1700, the current_station becomes 530
		if( current_station == MAX_AM)
		{
			current_station = MINIMUM_AM;
		}
		else
		{
			// Incrementing by 10 
			current_station = current_station + 10;
		}
	}
	else
	{
		//if the current_station is 107.9, the current_station becomes 87.9
		//Note: car radios jump .2 for the FM. That's how it's modeled here.
		if( current_station >= MAX_FM)
		{
			current_station = MINIMUM_FM;
		}
		else
		{
			// Incrementing by 0.2
			current_station = current_station + .2;
		}
	}
	if (displayOutPut)
	{
		printf("\nCurrent station: %f %s\n", current_station, frequency);
	}
}

/*  -- Method Header Comment
	Name	: ScanDown
	Purpose : This method will change the current_station by decrementing by 10
			  If on AM band, 0.2 if on FM band
	Inputs	:	NONE
	Outputs	:	the value of current_station and frequency
	Returns	:	NONE
*/
void AmFmRadio::ScanDown()
{
	if (strcmp("AM", frequency) == 0)
	{
		//if current_station is 1700, the current_station becomes 530
		if (current_station <= MINIMUM_AM)
		{
			current_station = MAX_AM;
		}
		else
		{
			// Decrementing by 10
			current_station = current_station - 10;
		}
	}
	else
	{
		//if the current_station is 107.9, the current_station becomes 87.9
		//Note: car radios jump .2 for the FM. That's how it's modeled here.
		if (current_station <= MINIMUM_FM)
		{
			current_station = MAX_FM;
		}
		else
		{
			// Decrementing by 0.2
			current_station = current_station - .2;
		}
	}
	if (displayOutPut)
	{
		printf("\nCurrent station: %f %s\n", current_station, frequency);
	}
}

/*  -- Method Header Comment
	Name	: SetCurrentStation
	Purpose : This method will set the new value to current_station data member
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	1 if set successfully, 0 otherwise
*/
int AmFmRadio::SetCurrentStation(double newCurrentStation)
{
	// Check if the frequency is AM or PM
	if (strcmp("AM", frequency) == 0)
	{
		// Check if the newCurrentStation is out of range
		if (newCurrentStation <= MAX_AM && newCurrentStation >= MINIMUM_AM)
		{
			current_station = newCurrentStation;
			return 1;
		}
	}
	else
	{
		// Check if the newCurrentStation is out of range
		if (newCurrentStation <= MAX_FM && newCurrentStation >= MINIMUM_FM)
		{
			current_station = newCurrentStation;
			return 1;
		}
	}

	return 0;
}

/*  -- Method Header Comment
	Name	: SetVolume
	Purpose : This method will set the new value to newVolume data member
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	1 if set successfully, 0 otherwise
*/
int AmFmRadio::SetVolume(int volume)
{

	if (volume < 0) //if user enters volume less than 0, volume = 0
	{
		newVolume = 0;
		return 1;
	}
	else if (volume > 100) //if user enters volume greater than 100, volume = 100
	{
		newVolume = 100;
		return 2;
	}
	else
	{
		newVolume = volume;
	}

	return 0;
}

/*  -- Method Header Comment
	Name	: ToggleDisplayOutPut
	Purpose : This method will switch the displayOutPut to false if true and otherwise.
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	NONE
*/
void AmFmRadio::ToggleDisplayOutPut()
{
	displayOutPut = !displayOutPut;
}

/*  -- Method Header Comment
	Name	: GetCurrentStation
	Purpose : This method will return the value of current_station data member.
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	current_station		double
*/
double AmFmRadio::GetCurrentStation()
{
	return current_station;
}

/*  -- Method Header Comment
	Name	: GetFrequency
	Purpose : This method will copy the value from "frequency" data member to "copyFrequency" data member 
	then return the address of copyFrequency
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	the string contain a copy of frequency data member
*/
char* AmFmRadio::GetFrequency()
{
	
	strcpy(copyFrequency, frequency);

	return copyFrequency;
}

/*  -- Method Header Comment
	Name	: GetButton
	Purpose : This method will copy the value from "Freqs button[]" to "Freqs copyButton[]" 
	then return the address of "Freqs copyButton[]"
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	the copy of `freqs` array     Freqs*
*/
Freqs* AmFmRadio::GetButton()
{
	// Declare a new Freqs array
	//Freqs copyButton[MAX_FREQS];
	// Loop to copy
	for (int i = 0; i < MAX_FREQS; i++) 
	{
		copyButton[i] = button[i];
	}
	return &copyButton[0];
}

/*  -- Method Header Comment
	Name	: GetNewVolume
	Purpose : This method will return the value of newVolume data member.
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	newVolume		int
*/
int AmFmRadio::GetNewVolume()
{
	return newVolume;
}

/*  -- Method Header Comment
	Name	: GetDisplayOutPut
	Purpose : This method will return the value of displayOutPut data member.
	Inputs	:	NONE
	Outputs	:	NONE
	Returns	:	displayOutPut		bool
*/
bool AmFmRadio::GetDisplayOutPut()
{
	return displayOutPut;
}

