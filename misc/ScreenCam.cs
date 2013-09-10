using UnityEngine;
using System.Collections;

[ExecuteInEditMode]
public class ScreenCam : MonoBehaviour {
	//public Transform target;
	public float width = 16f;
	public float height = 9f;
	public Transform screen;
	
	void LateUpdate () {
		//Re-activate projection matrix so that it recalculates with new fov
		camera.ResetProjectionMatrix();
		
		//Get distances given relative rotation
		transform.eulerAngles = screen.eulerAngles;
		Vector3 relative = transform.position - screen.position;
		
		float xdist = Vector3.Dot(relative, screen.right.normalized);
		float ydist = Vector3.Dot (relative, screen.up.normalized);
		float zdist = Vector3.Dot (relative, screen.forward.normalized);
		
		//Calculate new Fov
		float fov;
		float distance;
		distance =  (float) Mathf.Abs (zdist);
		fov =  2 * Mathf.Atan(height * 0.5f / distance) * Mathf.Rad2Deg;
		camera.fieldOfView = fov;	
		
		//Set obliqueness
		Matrix4x4 mat = camera.projectionMatrix;
		mat[0, 2] = -2f * (float) xdist / width;
		mat[1, 2] = -2f * (float) ydist / height;
		camera.projectionMatrix = mat;
		
		//Debug.Log (target.camera.projectionMatrix);
	}
}
