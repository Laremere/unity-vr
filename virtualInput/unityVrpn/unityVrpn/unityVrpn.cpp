// unityVrpn.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <map>
#include <vector>
#include "vrpn_Analog.h"
#include "vrpn_Button.h"
#include <string>

using namespace std;

struct stampedAnalog{
	int frameCount;
	vrpn_Analog_Remote* analog;
	vector<double> *current;
};

void VRPN_CALLBACK handle_analog(void *userdata, vrpn_ANALOGCB b) 
{ 
	stampedAnalog* ref = (stampedAnalog*)userdata;
	ref->current->resize(b.num_channel);
	for (int i=0; i< b.num_channel; i++)
		(*ref->current)[i] = (double) b.channel[i];
} 

map<string, stampedAnalog*> analogMap = map<string, stampedAnalog*>();


extern "C" __declspec( dllexport ) double vrpnAnalogExtern(char* _address, int channel, int frameCount){
	string address = string(_address);
	stampedAnalog* ref = 0;
	try {
		ref = analogMap.at(address);
	} catch(out_of_range){
		ref = new stampedAnalog;
		ref->frameCount = -1;
		ref->analog = new vrpn_Analog_Remote(_address);
		ref->current = new vector<double>();
		ref->analog->register_change_handler((void*)ref, handle_analog);
		analogMap[address] = ref;
	}
	if (ref->frameCount != frameCount){
		ref->analog->mainloop();
		ref->frameCount = frameCount;
	}

	double result = 0;
	try{
		result = ref->current->at(channel);
	} catch (out_of_range){
	}
	return result;
}




struct stampedButton{
	int frameCount;
	vrpn_Button_Remote* button;
	vector<bool> *current;
};

void VRPN_CALLBACK handle_button(void *userdata, vrpn_BUTTONCB b) 
{ 
	stampedButton* ref = (stampedButton*)userdata;
	if ((unsigned long int) b.button >= ref->current->size()){
		ref->current->resize(b.button + 1);
	}

	(*ref->current)[b.button] = (bool) b.state;
} 

map<string, stampedButton*> buttonMap = map<string, stampedButton*>();


extern "C" __declspec( dllexport ) bool vrpnButtonExtern(char* _address, int channel, int frameCount){
	string address = string(_address);
	stampedButton* ref = 0;
	try {
		ref = buttonMap.at(address);
	} catch(out_of_range){
		ref = new stampedButton;
		ref->frameCount = -1;
		ref->button = new vrpn_Button_Remote(_address);
		ref->current = new vector<bool>();
		ref->button->register_change_handler((void*)ref, handle_button);
		buttonMap[address] = ref;
	}
	if (ref->frameCount != frameCount){
		ref->button->mainloop();
		ref->frameCount = frameCount;
	}

	bool result = false;
	try{
		result = ref->current->at(channel);
	} catch (out_of_range){
	}
	return result;
}