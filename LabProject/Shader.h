#pragma once
class CCamera;
class CGameObject;
class CPlayer;
class CWallsObject;

//���� ��ü�� ������ ���̴����� �Ѱ��ֱ� ���� ����ü(��� ����)�̴�. 
struct CB_GAMEOBJECT_INFO { XMFLOAT4X4 m_xmf4x4World; };
class CShader
{

public: CShader(); virtual ~CShader();
private: 
	int m_nReferences = 0;
public:
	void AddRef() { m_nReferences++; } 
		void Release() { if (--m_nReferences <= 0) delete this; }
		virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout(); 
		virtual D3D12_RASTERIZER_DESC CreateRasterizerState();
		virtual D3D12_BLEND_DESC CreateBlendState();
		virtual D3D12_DEPTH_STENCIL_DESC CreateDepthStencilState();
		virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob); 
		virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);
		D3D12_SHADER_BYTECODE CompileShaderFromFile(const WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderProfile, ID3DBlob **ppd3dShaderBlob);
		virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature);
		virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
		virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList); 
		virtual void ReleaseShaderVariables();
		virtual void UpdateShaderVariable(ID3D12GraphicsCommandList *pd3dCommandList, XMFLOAT4X4 *pxmf4x4World);
		virtual void OnPrepareRender(ID3D12GraphicsCommandList *pd3dCommandList);
		virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera);
		
protected: 
	ID3D12PipelineState **m_ppd3dPipelineStates = NULL; 
	int m_nPipelineStates = 0;
};

class CDiffusedShader : public CShader {
public: CDiffusedShader(); 
		virtual ~CDiffusedShader();
		virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
		virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob); 
		virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);
		virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature);
};

//��CObjectsShader�� Ŭ������ ���� ��ü���� �����ϴ� ���̴� ��ü�̴�. 
class CObjectsShader : public CShader {
public:    CObjectsShader();    
		   virtual ~CObjectsShader();
		   virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList); 
		   virtual void AnimateObjects(float fTimeElapsed);
		   virtual void ReleaseObjects();
		   virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout(); 
		   virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob);
		   virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);
		   virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature);
		   virtual void ReleaseUploadBuffers();
		   virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera);
		   
public:
	CGameObject **m_ppObjects = NULL;
	
	//CPlayer						*m_pPlayer = NULL;
	int m_nObjects = 0;
};
class CRailShader : public CObjectsShader 
{
public:    CRailShader();
		   virtual ~CRailShader();
		   virtual void AnimateObjects(float fTimeElapsed);
		   virtual void ReleaseObjects();
		  //virtual D3D12_INPUT_LAYOUT_DESC CreateInputLayout();
		  // virtual D3D12_SHADER_BYTECODE CreateVertexShader(ID3DBlob **ppd3dShaderBlob);
		  //virtual D3D12_SHADER_BYTECODE CreatePixelShader(ID3DBlob **ppd3dShaderBlob);
		  //virtual void CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature);
		   virtual void ReleaseUploadBuffers();
		   virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera);
		   CGameObject **m_RailObjects = NULL;
		   vector<CWallsObject*> m_vRails;
		   int m_nRails = 0;
		   XMFLOAT3 FlatPos;
		   XMFLOAT3 FlatUp;
		   XMFLOAT3 FlatLook;
		   XMFLOAT3 FlatRight;
		
};