using UnityEngine;
using System.Collections;

public class AutoFov : MonoBehaviour {
	//public Transform target;
	public float width = 16f;
	public float height = 9f;
	public Transform screen;
	
	void LateUpdate () {
		//Re-activate projection matrix so that it recalculates with new fov
		camera.ResetProjectionMatrix();
		
		float xdist = transform.position.x - screen.position.x;
		float ydist = transform.position.y - screen.position.y;
		float zdist = transform.position.z - screen.position.z;
		
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
