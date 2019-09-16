#pragma once

//정점을 표현하기 위한 클래스를 선언한다.
class CVertex
{
public:
	//정점의 위치 벡터이다(모든 정점은 최소한 위치 벡터를 가져야 한다).    
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
	BoundingOrientedBox			m_xmOOBB;	//바운딩박스가 되어도 된다.

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
	/*인덱스 버퍼(인덱스의 배열)와 인덱스 버퍼를 위한 업로드 버퍼에 대한 인터페이스 포인터이다. 인덱스 버퍼는 정점 버퍼(배열)에 대한 인덱스를 가진다.*/ 
	D3D12_INDEX_BUFFER_VIEW m_d3dIndexBufferView;
	UINT m_nIndices = 0; 
	//인덱스 버퍼에 포함되는 인덱스의 개수이다. 
	UINT m_nStartIndex = 0; 
	//인덱스 버퍼에서 메쉬를 그리기 위해 사용되는 시작 인덱스이다. 
	int m_nBaseVertex = 0; 
	//인덱스 버퍼의 인덱스에 더해질 인덱스이다. 
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
	 //정점의 색상이다.    
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
 public: //직육면체의 가로, 세로, 깊이의 길이를 지정하여 직육면체 메쉬를 생성한다. 
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
