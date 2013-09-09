using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;

public class sdl2window : MonoBehaviour {	
	[DllImport ("sdl2window")]
	private static extern long  openWindow (int displayNum); 
	
	[DllImport ("sdl2window")]
	private static extern void closeWindow (long win); 
	
	[DllImport ("sdl2window")]
	private static extern int getWindowWidth (long win);
	
	[DllImport ("sdl2window")]
	private static extern int getWindowHeight (long win); 
	
	[DllImport ("sdl2window")]
	private static extern void renderWindow (long win); 
	
	[DllImport ("sdl2window")]
	private static extern void addCamera (int textureID, CamMode mode, float x, float y, float w, float h, long win);
	
	public enum CamMode {Left = 0, Right = 1, Both = 2};
	
	public int Display_Number;
	public Transform[] Cameras;
	public CamMode[] CameraModes;
	
	private long  winRef;	
	
	// Use this for initialization
	IEnumerator Start () {
		winRef = openWindow(Display_Number);
		if (Cameras.Length != CameraModes.Length) {
		 /////////////////////////  TO DO:  THROW EXCEPTION HERE
		}
		
		for (int i = 0; i < Cameras.Length; i++){
			Cameras[i].camera.targetTexture = new RenderTexture(getWidth(), getHeight(), 16, RenderTextureFormat.ARGB32);
			Cameras[i].camera.targetTexture = new RenderTexture(1024, 1024, 16, RenderTextureFormat.ARGB32);
			Cameras[i].camera.targetTexture.Create();
			addCamera (Cameras[i].camera.targetTexture.GetNativeTextureID(), CameraModes[i], 0f, 0f, 1f, 1f, winRef);
		}
		
		while (enabled){
			yield return new WaitForEndOfFrame();
			renderWindow (winRef);
		}
	}
	
	void OnApplicationQuit(){
		closeWindow (winRef);	
	}
	
	int getWidth(){
		return getWindowWidth (winRef);	
	}
	int getHeight(){
		return getWindowHeight (winRef);	
	}
}
