/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#include "stdafx.h"
#include "listview.h"

ListView::ListView(void):m_nCurrItem(0),m_iBorderWidth(4)
{
	m_sItemColor=EGSColor(0.f,0.f,1.f,1.f);
	m_sTextColor=EGSColor(0.0f,1.0f,0.0f,1.0f);
	m_cScroll.style=FALSE;
	m_cScroll.width=16;
}


/**\brief
 * ȡ���б����ϵ��ַ���
 */
char* ListView::GetItemText(unsigned int _nWhere)
{
	if(_nWhere>=m_vItems.size())return NULL;
	else return m_vItems[_nWhere].GetText();
}


/**\brief
 * ����һ���б���
 *
 *\param	_iWhere	�����λ�ã�Ϊ-1ʱ�嵽��β
 *\param	_str	�������ϵ�����
 *\return	BOOL	�����Ƿ�ɹ�
 */
BOOL ListView::InsertItem(unsigned int _iWhere,char* str)
{
	EGCButton t_cItem;
	t_cItem.SetTextColor(m_sTextColor);
	t_cItem.SetTextStyle(BTN_TEXT_LEFT);
	t_cItem.SetBlend(TRUE);
	t_cItem.SetText(str);

	if(_iWhere=-1){m_vItems.push_back(t_cItem);return TRUE;}
	else if(_iWhere>m_vItems.size())return FALSE;
	else
	{
		m_vItems.insert(m_vItems.begin()+_iWhere,t_cItem);
		return TRUE;
	}

	return TRUE;
}


/**\brief 
 * ɾ��һ���б��Ĭ�ϲ���ʱ�����βԪ��
 */
BOOL ListView::DeleteItem(unsigned int _iWhere)
{
	if(m_vItems.size()<=0)return FALSE;

	if(_iWhere==-1){m_vItems.pop_back();return TRUE;}
	else if(_iWhere>=m_vItems.size())return FALSE;
	{
		m_vItems.erase(m_vItems.begin()+_iWhere);
		return TRUE;
	}

	return TRUE;
}


/**\brief
 * �����б�
 */
void ListView::OnDraw(void)
{
	// ��Ⲣ�����߶�
	if((m_sRect.height-m_iBorderWidth*2)%ITEM_HEIGHT!=0)
		m_sRect.height-=(m_sRect.height-m_iBorderWidth*2)%ITEM_HEIGHT-ITEM_HEIGHT;

	// ���ƹ�����
	m_cScroll.x=m_sRect.x+m_sRect.width-m_cScroll.width-m_iBorderWidth;
	m_cScroll.y=m_sRect.y+m_iBorderWidth;
	m_cScroll.MaxLength=m_sRect.height-m_iBorderWidth*2;
	m_cScroll.draw();

	//һЩ��Ա��ֵ
	m_nMaxItemNum	=(m_sRect.height-m_iBorderWidth*2)/ITEM_HEIGHT;
	m_iItemWidth	=m_sRect.width-m_iBorderWidth*2-m_cScroll.width-1;
	m_iItemX		=m_sRect.x+m_iBorderWidth;
	m_iFirstY		=m_sRect.y+m_sRect.height-ITEM_HEIGHT-m_iBorderWidth;

	// �����б���
	unsigned int t_iNum;	//Ҫ��Ⱦ��ĸ���
	unsigned int t_iWhich;	//����һ�ʼ��Ⱦ
	if(m_vItems.size()<=m_nMaxItemNum){t_iNum=m_vItems.size();t_iWhich=0;}
	else
	{
		t_iNum=m_nMaxItemNum;
		if(IsActive())
		{
			if(EGInput::GetSysInput()->GetMouse()->GetWheelState()<0)
				m_cScroll.SetPos(m_cScroll.GetPos()+0.1f);
			if(EGInput::GetSysInput()->GetMouse()->GetWheelState()>0)
				m_cScroll.SetPos(m_cScroll.GetPos()-0.1f);
		}
		t_iWhich=(unsigned int)((m_vItems.size()-m_nMaxItemNum)*m_cScroll.GetPos());
	}

	for(unsigned int i=t_iWhich;i<(t_iNum+t_iWhich);++i)
	{
		m_vItems[i].SetNormalColor(m_sItemColor);
		m_vItems[i].SetRect(EGSRect(m_iItemX,m_iFirstY-(i-t_iWhich)*ITEM_HEIGHT,m_iItemWidth,ITEM_HEIGHT-1));
		m_vItems[i].draw();
		if(m_vItems[i].GetState()==BUTTON_CLICK)m_nCurrItem=i;
	}

}
