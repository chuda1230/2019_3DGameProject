#pragma once
class CMesh;
class CShader;
class CCamera;

class CGameObject 
{
public: 
	CGameObject();    
	virtual ~CGameObject();
	BoundingOrientedBox			m_xmOOBB;	//����ǥ���� �ٿ���ڽ��� ������ǥ�� Ʈ�������Ͽ� ���� �ٿ���ڽ��� �����.

	XMFLOAT3					m_xmf3MovingDirection;
	float						m_fMovingSpeed = 0.0f;
	float						m_fMovingRange = 0.0f;
	XMFLOAT3					m_xmf3Position;
	XMFLOAT3					m_xmf3Right;
	XMFLOAT3					m_xmf3Up;
	XMFLOAT3					m_xmf3Look;
	XMFLOAT3					m_xmf3CameraOffset;
	XMFLOAT3					m_xmf3Velocity;
	XMFLOAT3					m_xmf3RotationAxis;
	CCamera						*m_pCamera = NULL;
	float						m_fRotationSpeed = 0.0f;

	DWORD						m_dwColor;

private: 
	int m_nReferences = 0;
public: 
	void AddRef() 
	{ 
		m_nReferences++; 
	} 
	void Release() 
	{ 
		if (--m_nReferences <= 0) 
			delete this; 
	}
public:
	//��� ���۸� �����Ѵ�.
	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	//��� ������ ������ �����Ѵ�.
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	XMFLOAT4X4 m_xmf4x4World;
	CMesh *m_pMesh = NULL;
	CShader *m_pShader = NULL;

public: 
	void Rotate(XMFLOAT3 *pxmf3Axis, float fAngle);
	void ReleaseUploadBuffers();
	void SetColor(DWORD dwColor) { m_dwColor = dwColor; }
	virtual void SetMesh(CMesh *pMesh); 
	virtual void SetShader(CShader *pShader);
	virtual void Animate(float fTimeElapsed);
	virtual void OnPrepareRender(); 
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera);
	//virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera, UINT nInstances, D3D12_VERTEX_BUFFER_VIEW d3dInstancingBufferView);

	//���� ��ü�� ���� ��ȯ ��Ŀ��� ��ġ ���Ϳ� ����(x-��, y-��, z-��) ���͸� ��ȯ�Ѵ�.
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetLook();
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();
	//���� ��ü�� ��ġ�� �����Ѵ�.
	void SetPosition(float x, float y, float z); 
	void SetPosition(XMFLOAT3 xmf3Position);
	//���� ��ü�� ���� x-��, y-��, z-�� �������� �̵��Ѵ�.
	void MoveStrafe(float fDistance = 1.0f); 
	void MoveUp(float fDistance = 1.0f);
	void MoveForward(float fDistance = 1.0f);
	//���� ��ü�� ȸ��(x-��, y-��, z-��)�Ѵ�.
	void Rotate(float fPitch = 10.0f, float fYaw = 10.0f, float fRoll = 10.0f);

};
class CRotatingObject : public CGameObject 
{
public: 
	CRotatingObject(); 
	virtual ~CRotatingObject();
private: 
	XMFLOAT3 m_xmf3RotationAxis; 
	float m_fRotationSpeed;
public: 
	void SetRotationSpeed(float fRotationSpeed) 
	{
		m_fRotationSpeed = fRotationSpeed; 
	} 
	void SetRotationAxis(XMFLOAT3 xmf3RotationAxis) 
	{ 
		m_xmf3RotationAxis = xmf3RotationAxis; 
	}
		virtual void Animate(float fTimeElapsed);
};

class CWallsObject : public CGameObject
{
public:
	CWallsObject();
	virtual ~CWallsObject();
	//void Render(HDC hDCFrameBuffer, CCamera *pCamera);
	void RotateTrace(float right_x, float right_y, float right_z, float up_x, float up_y, float up_z, float look_x, float look_y, float look_z);

public:
	XMFLOAT4					m_pxmf4WallPlanes[6];
};

