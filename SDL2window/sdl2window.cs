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
	public enum Mode3d {Active = 0, SideBySide = 1};
	
	public int Display_Number;
	public Mode3d Display_3d_Type;
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
			Rect view = Cameras[i].camera.rect;
			int width =  (int) ( ((float)getWidth ()) * view.width );
			int height = (int) ( ((float)getHeight()) * view.height);
			CamMode curMode = CameraModes[i];
			
			if (Display_3d_Type == Mode3d.SideBySide && curMode != CamMode.Both){
				width /= 2;
			}
			
			Cameras[i].camera.targetTexture = new RenderTexture(width, height, 16, RenderTextureFormat.ARGB32);
			Cameras[i].camera.targetTexture.Create();
			addCamera (Cameras[i].camera.targetTexture.GetNativeTextureID(), curMode, view.x, view.y, view.width, view.height, winRef);
			
			Cameras[i].camera.rect = new Rect(0,0,1,1);
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
