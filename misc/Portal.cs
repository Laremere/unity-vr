using UnityEngine;
using System.Collections;

public class Portal : MonoBehaviour {
	private static bool renderingPortal = false;
	
	public Transform otherPortal;
	
	public void OnWillRenderObject(){
		if (renderingPortal){
			return;
		}
		
	}
}
