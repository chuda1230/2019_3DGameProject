#pragma once
#include "Timer.h"
#include "Shader.h"
#include "GameObject.h"

class CPlayer;
class CShader;

class CScene
{
public:
	CScene();
	~CScene();
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam); 
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	void ReleaseObjects();
	bool ProcessInput(UCHAR *pKeysBuffer);
	void AnimateObjects(float fTimeElapsed);   
	void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera);
	void ReleaseUploadBuffers();
	//�׷��� ��Ʈ �ñ׳��ĸ� �����Ѵ�. 
	ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	ID3D12RootSignature *GetGraphicsRootSignature();

	CPlayer						*m_pPlayer = NULL;
	int							m_nObjects = 0;
	CGameObject					**m_ppObjects = NULL;
	CWallsObject				*m_pWallsObject = NULL;
	vector<CWallsObject*> m_walls;
	CWallsObject				**m_WallsObject = NULL;					
	double spawntime = 0;
public: 
	//��ġ(Batch) ó���� �ϱ� ���Ͽ� ���� ���̴����� ����Ʈ�� ǥ���Ѵ�.
	CObjectsShader *m_pShaders = NULL;
	CRailShader *m_rShaders = NULL;
	int m_nShaders = 0;
	int m_nrShaders = 0;


	//CShader **m_ppShaders = NULL; 
	//int m_nShaders = 0;
	ID3D12RootSignature *m_pd3dGraphicsRootSignature = NULL;
	//��Ʈ �ñ׳��ĸ� ��Ÿ���� �������̽� �������̴�. 
	ID3D12PipelineState *m_pd3dPipelineState; 
	//���������� ���¸� ��Ÿ���� �������̽� �������̴�. 
};

class CPlayerScene : public CScene
{
public:
	CPlayerScene();
	virtual ~CPlayerScene();
	
	virtual void BuildObjects();
	virtual void CreateObjects();
	virtual void ReleaseObjects();

	void CheckObjectByWallCollisions();
	virtual void Animate(float fElapsedTime);
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera);
};