using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class testScript : ObjectBase {

	// Use this for initialization
	void Start () {
		m_OrderNumber = 3;
		ObjectManager.Instance.RegistrationList(this, m_OrderNumber);

	}

    //public override void Execute(float deltaTime) {
    //    int a = 0;
    //    while(true) {
    //        a++;
    //        if(a > 10) {
    //            break;
    //        }
    //    }
    //}

    void Update() {
        int a = 0;
        while(true) {
            a++;
            if(a > 10) {
                break;
            }
        }
    }

    public override void LateExecute(float deltaTime) {

	}
}
