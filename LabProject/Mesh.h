#pragma once

//������ ǥ���ϱ� ���� Ŭ������ �����Ѵ�.
class CVertex
{
public:
	//������ ��ġ �����̴�(��� ������ �ּ��� ��ġ ���͸� ������ �Ѵ�).    
	XMFLOAT3 m_xmf3Position;
public:
	CVertex()
	{
		m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	CVertex(XMFLOAT3 xmf3Position)
	{
		m_xmf3Position = xmf3Position;
	}
	CVertex(float x, float y, float z) { m_xmf3Position = XMFLOAT3(x, y, z); }
	~CVertex() { }
};


class CPolygon{
public:
	CPolygon(int nVertices);
	virtual ~CPolygon();

	int							m_nVertices;
	CVertex						*m_pVertices;

	void SetVertex(int nIndex, CVertex vertex);
};


class CMesh {
public:    
	CMesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	CMesh(int nPolygons);
	virtual ~CMesh();
private: 
	int m_nReferences = 0;

	int							m_nPolygons;
	CPolygon					**m_ppPolygons;

public:
	BoundingOrientedBox			m_xmOOBB;	//�ٿ���ڽ��� �Ǿ �ȴ�.

public: 
	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }
	void ReleaseUploadBuffers();
protected: 
	ID3D12Resource *m_pd3dVertexBuffer = NULL; 
	ID3D12Resource *m_pd3dVertexUploadBuffer = NULL;
	D3D12_VERTEX_BUFFER_VIEW m_d3dVertexBufferView;
	D3D12_PRIMITIVE_TOPOLOGY m_d3dPrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	UINT m_nSlot = 0;
	UINT m_nVertices = 0;
	UINT m_nStride = 0;
	UINT m_nOffset = 0;
protected: 
	ID3D12Resource *m_pd3dIndexBuffer = NULL;
	ID3D12Resource *m_pd3dIndexUploadBuffer = NULL; 
	/*�ε��� ����(�ε����� �迭)�� �ε��� ���۸� ���� ���ε� ���ۿ� ���� �������̽� �������̴�. �ε��� ���۴� ���� ����(�迭)�� ���� �ε����� ������.*/ 
	D3D12_INDEX_BUFFER_VIEW m_d3dIndexBufferView;
	UINT m_nIndices = 0; 
	//�ε��� ���ۿ� ���ԵǴ� �ε����� �����̴�. 
	UINT m_nStartIndex = 0; 
	//�ε��� ���ۿ��� �޽��� �׸��� ���� ���Ǵ� ���� �ε����̴�. 
	int m_nBaseVertex = 0; 
	//�ε��� ������ �ε����� ������ �ε����̴�. 
public: 
	void SetPolygon(int nIndex, CPolygon *pPolygon);
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, UINT nInstances); 
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, UINT nInstances, D3D12_VERTEX_BUFFER_VIEW d3dInstancingBufferView);
	//virtual void Render(HDC hDCFrameBuffer, XMFLOAT4X4 xmf4x4World, CCamera *pCamera);
	void SetOOBB(XMFLOAT3 xmCenter, XMFLOAT3 xmExtents, XMFLOAT4 xmOrientation) { m_xmOOBB = BoundingOrientedBox(xmCenter, xmExtents, xmOrientation); }
};





 class CDiffusedVertex : public CVertex 
 {
 protected: 
	 //������ �����̴�.    
	 XMFLOAT4 m_xmf4Diffuse;
 public: 
	 CDiffusedVertex() 
	 { 
		 m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		 m_xmf4Diffuse = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f); 
	 } 
	 CDiffusedVertex(float x, float y, float z, XMFLOAT4 xmf4Diffuse) { 
		 m_xmf3Position = XMFLOAT3(x, y, z);
		 m_xmf4Diffuse = xmf4Diffuse; 
	 } 
	 CDiffusedVertex(XMFLOAT3 xmf3Position, XMFLOAT4 xmf4Diffuse) {
		 m_xmf3Position = xmf3Position;
		 m_xmf4Diffuse = xmf4Diffuse;
	 } 
	 ~CDiffusedVertex() { }
 };
 class CTriangleMesh : public CMesh 
 { 
 public:    
	 CTriangleMesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	 virtual ~CTriangleMesh() { } 
 };
 class CCubeMeshDiffused : public CMesh 
 {
 public: //������ü�� ����, ����, ������ ���̸� �����Ͽ� ������ü �޽��� �����Ѵ�. 
	 CCubeMeshDiffused(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, float fWidth = 2.0f, float fHeight = 2.0f, float fDepth = 2.0f); 
	 virtual ~CCubeMeshDiffused(); 
 };


 class CAirplaneMeshDiffused : public CMesh 
 { 
 public: 
	 CAirplaneMeshDiffused(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, float fWidth = 20.0f, float fHeight = 20.0f, float fDepth = 4.0f, XMFLOAT4 xmf4Color = XMFLOAT4(1.0f, 1.0f, 0.0f, 0.0f)); 
	virtual ~CAirplaneMeshDiffused(); 
 };
 
 class CWallMesh : public CMesh
 {
 public:
	 XMFLOAT3					m_xmf3Right;
	 XMFLOAT3					m_xmf3Up;
	 XMFLOAT3					m_xmf3Look;
	 CWallMesh(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, float fWidth = 20.0f, float fHeight = 30.0f, float fDepth = 3.0f);
	 virtual ~CWallMesh();
 };
