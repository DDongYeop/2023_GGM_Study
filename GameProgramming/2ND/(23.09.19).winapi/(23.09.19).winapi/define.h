#pragma once
#define SINGLE(type)		\
private:					\
	type() {}				\
	~type() {}				\
public:						\
	static type* GetInst()	\
	{						\
		static type m_pInst;\
		return &m_pInst;	\
	}	
#define WINDOW_CLASS_NAME L"DONGYEOP"