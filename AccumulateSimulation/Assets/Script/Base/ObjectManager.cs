using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectManager : SingletonMonoBehaviour<ObjectManager> {
    List<ObjectBase> m_ObjList = new List<ObjectBase>();

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        int i;
        float deltaTime = Time.deltaTime;
        for(i = 0; i < m_ObjList.Count; i++) {
            m_ObjList[i].Execute(deltaTime);
        }
        for(i = 0; i < m_ObjList.Count; i++) {
            m_ObjList[i].LateExecute(deltaTime);
        }
	}

    /// <summary>
    /// リストへの登録
    /// </summary>
    /// <param name="newObj">登録するオブジェクト</param>
    public void RegistrationList(ObjectBase newObj) {
        m_ObjList.Add(newObj);
    }
}
