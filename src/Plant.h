/**
 *作者：范修盛
 *2011年10月30日
 */
#pragma once
#ifndef __PLANT_H__
#define __PLANT_H__

#include "texture.h"
#include "terrain.h"
#include "Object.h"

/**\brief
 * 树的渲染类
 */
class Plant:public Object
{
public:
	Plant();
	~Plant();

	/**\brief
	 * 载入纹理
	 */
	BOOL Load(char* body,char* branch);

	/**\brief
	 * 设置树的粗细
	 */
	void SetSize(float _size)	{m_szTree=_size;}

	/**\brief
	 * 设置树的高度
	 */
	void SetHeight(float h)		{m_height=h;}

	/**\brief
	 * 设置枝叶的宽度
	 */
	void SetBranchWidth(float w){m_fBranchWidth=w;}

	/**\brief
	 * 从INI文件载入树的参数
	 */
	BOOL LoadIni(char* filename,char* index,float x,float z);

	/**\brief
	 * 植物的渲染
	 */
	virtual void OnRender();


private:
	/**\brief
	 * 绘制一个树枝
	 */
	void RenderSingleBranch(float width , float height);

	/**\brief
	 * 绘制树枝
	 */
	void RenderBranch();

	/**\brief
	 * 绘制树身
	 */
	void RenderTreebody();

	/**\brief
	 * 绘制树的头部
	 */
	void RenderTop(float width ,float height);


	EGCTexture	treebody;		// 树干的纹理
	EGCTexture	treebranch;		// 树枝的纹理
	float		m_szTree;		// 粗细
	float		m_fBranchWidth;	// 枝叶的宽度
	float		m_height;		// 高度
};

#endif
