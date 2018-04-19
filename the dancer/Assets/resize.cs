using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class resize : MonoBehaviour {

    public oscReceiver oscR;
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        Vector3 s = transform.localScale;
        s.x = s.y = s.z = oscR.noiseFractal;
        transform.localScale = s;
	}
}
