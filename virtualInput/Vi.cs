using UnityEngine;
using System.Runtime.InteropServices;

public static class Vi{
	[DllImport ("unityVrpn")]
	private static extern double vrpnAnalogExtern(string address, int channel, int frameCount);

	[DllImport ("unityVrpn")]
	private static extern bool vrpnButtonExtern(string address, int channel, int frameCount);
	
	
	public static double vrpnAnalog(string address, int channel){
		return vrpnAnalogExtern (address, channel, Time.frameCount);
	}
	
	public static bool vrpnButton(string address, int channel){
		return vrpnButtonExtern (address, channel, Time.frameCount);	
	}
}
