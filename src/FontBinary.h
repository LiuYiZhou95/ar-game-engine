/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#include "structdef.h"

class CharacterBinary;

/**\brief
 * ������һ���ַ�����
 */
class FontBinary
{
public:
	FontBinary(char* fileName);//�ֿ��ļ�
	FontBinary(void);
	~FontBinary(void);

	CharacterBinary	Format(const unsigned char* code);
protected:

	class	Character
	{
	public:
		Character(void){}
		Character(const unsigned char*& inCharacter);
		~Character(void){}

		unsigned int	Format(const unsigned char*&);
		unsigned int	GetLine(unsigned char*& pout,unsigned int line)const;
		unsigned int	GetWidth(void)const{return width_;}
		unsigned int	GetHigh(void)const{return high_;}

	private:
		unsigned int	FormatChinese(const unsigned char*&);
		unsigned int	FormatEnglish(const unsigned char*&);
		void			ChangeModel(void);

		unsigned char	high_;
		unsigned char	width_;
		unsigned char	binary_[32];
	};

	struct AutoPtr
	{
		AutoPtr(void* ptr):ptr_(ptr){}
		~AutoPtr(void){delete []ptr_;}
		void* ptr_;
	};


	Character	character[128];
	static AutoPtr	aptr_;
	static unsigned char*	wordLib_;
	static unsigned int		libSize_;
};


//********************************************************
//ͨ�������Ǹ��ֿ�������ʽ��һ���ַ���
//�ַ��������ܳ���128�����ǳ��ȣ������Ǹ���
//*****************************************************


class CharacterBinary
{
	friend FontBinary;
public:
	CharacterBinary(void);

	//ͨ�������ַ�������ø�ʽ���Ķ����Ƶ���ֻҪ�����ַ�ʽ
	//����ģ������ٵ���Format������
	CharacterBinary(const unsigned char*);
	CharacterBinary(const char*);

	CharacterBinary(const CharacterBinary&);
	~CharacterBinary(void);

	const	unsigned char* GetBinary(void)const{return binary_;}
	unsigned int	GetWidth(void)const{return width_;}
	unsigned int	GetHigh(void)const{return high_;}

	//��ʽ��һ���ִ����õ�һ�������Ƶ��ִ�����
	void			Format(const unsigned char*);
	void			Format(const char*);

	CharacterBinary&	operator = (const CharacterBinary&);
private:
	unsigned int	high_;
	unsigned int	width_;
	unsigned int	size_;
	unsigned char* binary_;
};
