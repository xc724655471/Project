#pragma once


// MyStatic

class MyStatic : public CStatic
{
	DECLARE_DYNAMIC(MyStatic)

public:
	MyStatic();
	virtual ~MyStatic();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	bool isCurrentWind;
};


