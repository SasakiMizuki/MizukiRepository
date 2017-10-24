using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class EstablishmentController : ObjectBase {
	public const int MAX_WIDTH = 320;
	public const int MAX_HEIGHT = 180;
	private float m_EstablishA = 0.5f;
	private float m_EstablishB = 0.5f;
	private float m_EstablishAnswerA = 0.5f;
	private float m_EstablishAnswerB = 0.5f;
	private float m_ConfirmEstablishA;
	private float m_ConfirmEstablishB;
	public Text m_EstablishAText;
	public Text m_EstablishBText;
	private bool[,] m_BlockSetFlag = new bool[MAX_WIDTH,MAX_HEIGHT];    // 左下を0,0とし格納する。
	[SerializeField]
	private Image m_BlockImage;
	[SerializeField]
	private Transform m_BlockParent;
	[SerializeField]
	private Text m_ExecuteNumText;
	private int m_TotalExecuteNumber = 0;
	[SerializeField]
	private Text m_LoadingText;
	private int m_ExecuteNumber;
	private bool m_isExecute = false;
	private int MAX_WIDTH_HALF;
	Color[] m_BlockColors = new Color[7];
	[SerializeField]
	GameObject m_deleteObj;
	//private List<int> m_NextList = new List<int>();
	//private List<int> m_DontNextList = new List<int>();

	private int m_LoopCounter;      // 無限ループ防止用カウンター

	[SerializeField]
	private Text m_ConfirmTextA;
	[SerializeField]
	private Text m_ConfirmTextB;
	// Use this for initialization
	void Start () {
		// Calculation();	// 確率計算
		MAX_WIDTH_HALF = MAX_WIDTH / 2;
		m_BlockSetFlag = new bool[MAX_WIDTH, MAX_HEIGHT];
		m_LoadingText.enabled = false;
		ObjectManager.Instance.RegistrationList(this);
		m_BlockColors[0] = Color.red;
		m_BlockColors[1] = new Color(1.0f,0.65f,0);
		m_BlockColors[2] = Color.yellow;
		m_BlockColors[3] = Color.green;
		m_BlockColors[4] = Color.cyan;
		m_BlockColors[5] = Color.blue;
		m_BlockColors[6] = new Color(0.5f,0,0.5f);
		//m_BlockColors[0] = new Color(1.0f, 0.5f, 0.5f);
		//m_BlockColors[1] = new Color(1.0f, 0.65f, 0.2f);
		//m_BlockColors[2] = new Color(1.0f, 1.0f, 0.5f);
		//m_BlockColors[3] = new Color(0.5f, 1.0f, 0.5f);
		//m_BlockColors[4] = new Color(0.5f, 1.0f, 1.0f);
		//m_BlockColors[5] = new Color(0.5f, 0.5f, 1.0f);
		//m_BlockColors[6] = new Color(1.0f, 0.5f, 1.0f);

		var newObj = (Image)Instantiate(m_BlockImage);
		newObj.transform.SetParent(m_BlockParent);
		newObj.rectTransform.anchoredPosition = new Vector3(0 + 1, 0, 0);
		newObj.rectTransform.localScale = new Vector3(1.0f, 1.0f, 1.0f);
		m_TotalExecuteNumber++;
		m_ExecuteNumText.text = m_TotalExecuteNumber.ToString() + "回目";
		m_BlockSetFlag[MAX_WIDTH_HALF, 0] = true;
		ConfirmCalution();
	}

	public override void Execute(float deltaTime) {
		if(!m_isExecute)
			return;
		OneExecute();
		m_ExecuteNumber--;
		if(m_ExecuteNumber <= 0) {
			m_isExecute = false;
			m_LoadingText.enabled = false;
		}
	}

	/// <summary>
	/// 確率計算
	/// </summary>
	public void Calculation() {
		m_EstablishA = float.Parse(m_EstablishAText.text);	// InputFieldから取得
		m_EstablishB = float.Parse(m_EstablishBText.text);	// 同上
		float sum = m_EstablishA + m_EstablishB;            // 計算
		m_EstablishA = m_EstablishA / sum;
		m_EstablishB = m_EstablishB / sum;
	}

	// 確率計算
	public void ConfirmCalution() {
		int FlagNum = 0;
		for(int i = 0; i < MAX_WIDTH; i ++) {
			int j = 0;
			while(j < MAX_HEIGHT) {
				if(!m_BlockSetFlag[i, j]) {
					break;
				}
				j++;
			}
			if(i == 0) {
				if(m_BlockSetFlag[i + 1, j])
					FlagNum++;
			}else if(i == MAX_WIDTH - 1) {
				if(m_BlockSetFlag[i - 1, j])
					FlagNum++;
			}else {
				if(m_BlockSetFlag[i + 1, j] || m_BlockSetFlag[i - 1, j])
					FlagNum++;
			}
		}
		m_EstablishAnswerA = ( (float)FlagNum / MAX_WIDTH ) * m_EstablishA;
		m_EstablishAnswerB = ( (float)(MAX_WIDTH - FlagNum) / MAX_WIDTH ) * m_EstablishB;
		float sum = m_EstablishAnswerA + m_EstablishAnswerB;
		m_ConfirmEstablishA = m_EstablishAnswerA / sum;
		//Debug.Log("FlagNum / MAX_WIDTH" + (float)FlagNum / MAX_WIDTH);
		//Debug.Log("m_ConfirmEstablishA" + m_ConfirmEstablishA);
	}

    // 実行
	public void OneExecute() {
		int flagHeight;
		flagHeight = 0;
		m_LoopCounter = 0;
		bool Next = false;
		float FromZeroToOne = Random.Range(0.0f, 1.0f);
		ConfirmCalution();
		if(m_ConfirmEstablishA > FromZeroToOne) {
		//if(m_EstablishAnswerA < FromZeroToOne) {
				Next = true;
		} else {
			Next = false;
		}
		int answer = Random.Range(0,MAX_WIDTH);
		
		while(flagHeight < MAX_HEIGHT) {
			if(m_LoopCounter > 10000) {
				m_LoopCounter = 0;
				Next = !Next;
			}
			while(flagHeight < MAX_HEIGHT) {
				if(!m_BlockSetFlag[answer, flagHeight]) {
					break;
				}
				flagHeight++;
			}
			if(Next && ( ( answer == 0 ? false : m_BlockSetFlag[answer - 1, flagHeight] ) || ( answer == MAX_WIDTH - 1 ? false : m_BlockSetFlag[answer + 1, flagHeight] ) )) {
				var newObj = (Image)Instantiate(m_BlockImage);
				newObj.transform.SetParent(m_BlockParent);
				newObj.rectTransform.anchoredPosition = new Vector3(answer - MAX_WIDTH_HALF + 1, flagHeight, 0);
				newObj.rectTransform.localScale = new Vector3(1.0f, 1.0f, 1.0f);
				m_TotalExecuteNumber++;
				m_ExecuteNumText.text = m_TotalExecuteNumber.ToString() + "回目";
				m_BlockSetFlag[answer, flagHeight] = true;
				break;
			} else if(!Next && !( answer == 0 ? false : m_BlockSetFlag[answer - 1, flagHeight] ) && !( answer == MAX_WIDTH - 1 ? false : m_BlockSetFlag[answer + 1, flagHeight] )) {
				var newObj = (Image)Instantiate(m_BlockImage);
                newObj.transform.SetParent(m_BlockParent);
				newObj.rectTransform.anchoredPosition = new Vector3(answer - MAX_WIDTH_HALF + 1, flagHeight, 0);
				newObj.rectTransform.localScale = new Vector3(1.0f, 1.0f, 1.0f);
				m_TotalExecuteNumber++;
				m_ExecuteNumText.text = m_TotalExecuteNumber.ToString() + "回目";
				m_BlockSetFlag[answer, flagHeight] = true;
				break;
			}else {
				m_LoopCounter++;
				answer = Random.Range(0,MAX_WIDTH);
				flagHeight = 0;
			}
		}
	}

	// 1回実行
	public void OneTimeExecute() {
		if(m_isExecute)
			return;
		Calculation();
		m_LoadingText.enabled = true;
		m_isExecute = true;
		m_ExecuteNumber = 1;
	}

	// 100回実行
	public void HandredExecute() {
		if(m_isExecute)
			return;
		Calculation();
		m_LoadingText.enabled = true;
		m_isExecute = true;
		m_ExecuteNumber = 100;
	}

	// 10000回実行
	public void TenThousandExecute() {
		if(m_isExecute)
			return;
		Calculation();
		m_LoadingText.enabled = true;
		m_isExecute = true;
		m_ExecuteNumber = 10000;
	}

	public void HandredExecuteOneTime() {
		if(m_isExecute)
			return;

		StartCoroutine(handredExecute());
	}

	public void TenThousandExecuteOneTime() {
		if(m_isExecute)
			return;
		StartCoroutine(tenThousandExecute());
	}

	IEnumerator handredExecute() {
		Calculation();
		m_LoadingText.enabled = true;
		yield return null;
		for(int i = 0; i < 100; i++) {
			OneExecute();
		}
		m_LoadingText.enabled = false;
	}

	IEnumerator tenThousandExecute() {
		Calculation();
		m_LoadingText.enabled = true;
		yield return null;
		for(int i = 0; i < 10000; i++) {
			OneExecute();
		}
		m_LoadingText.enabled = false;
	}

	public void Reset() {
		SceneManager.LoadScene("main");
	}

	public void Stop() {
		m_ExecuteNumber = 0;
	}

	public void SavePicture() {
		m_deleteObj.SetActive(false);
		StartCoroutine(takeScreenShot());
	}

    // スクリーンショット撮影
	IEnumerator takeScreenShot() {
		yield return new WaitForSeconds(0.1f);
		Application.CaptureScreenshot("../Data/"+ System.DateTime.Now.ToString("yyyy-MMdd-HHmmss") +".png");
		yield return new WaitForSeconds(0.1f);
		m_deleteObj.SetActive(true);
	}
}
