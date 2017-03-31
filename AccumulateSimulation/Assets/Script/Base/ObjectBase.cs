using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectBase : MonoBehaviour {

	// Use this for initialization
	void Start () {
        ObjectManager.Instance.RegistrationList(this);
	}
	
    public virtual void Execute(float deltaTime) {

    }

    public virtual void LateExecute(float deltaTime) {

    }
}
