using UnityEngine;
using System.Collections;

public class TrackPosRot : MonoBehaviour {

	public Transform toTrack;
	
	// Update is called once per frame
	void Update () {
		transform.position = toTrack.position;
		transform.eulerAngles = toTrack.eulerAngles;
	}
}
