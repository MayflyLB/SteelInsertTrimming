#ifndef _CURTTERATTRE_H
#define _CURTTERATTRE_H
#include "../Include/assistFun.h"
struct  TrimCurveData   //һ��ָ�������ݣ�����
{
    vector<CurveData*>* trim_;
    vector<CurveData*>* assist_;
};

class CurveAttrE
{
public:
    enum CurveType
    {
        UPType,
        DwType
    };

    CurveAttrE(){ srand((unsigned)time(NULL)); }
    ~CurveAttrE()
    {
        delelteCurveData();
    }
    void writeAttrToCurves(std::vector<TrimCurveData>& curveSet, CurveType cae);

   
    const vector<TrimCurveData>& retUpCurveData()const 
    {
        return m_CurveDataUp;
    }
    const vector<TrimCurveData>& retDwCurveData()const 
    {
        return m_CurveDataDw;
    }
    //��ģ�ޱ���
    const vector<TrimCurveData>&operator()()const 
    {
        return m_CurveDataUp;
    }

    //��ģ�ޱ���
    const vector<TrimCurveData>&operator()(int a)const
    {
        return m_CurveDataDw;
    }
    //������� ����
    void writeOld(std::vector<TrimCurveData>& curveSet);

    inline void getTrimCurves()
    {
        getAllTrimCurves();
        getAtrrToCurves();
    }
    inline void getTrimCurves(const vector<NXOpen::TaggedObject *>&temp)
    {
        getCurrentTrimCurves(temp);
        getAtrrToCurves();
    }

private:

    inline void getCurrentTrimCurves(const vector<NXOpen::TaggedObject *>&temp)
    {
        m_tempCurves.clear();
        for (int i=0;i<temp.size();i++)
            m_tempCurves.push_back(temp[i]->GetTag());
    }
    size_t getAllTrimCurves();
    void getAtrrToCurves();
    void delelteCurveData();
private:
    vector<TrimCurveData> m_CurveDataUp;//һ��ָ�������ݣ�����
    vector<TrimCurveData> m_CurveDataDw;//һ��ָ�������ݣ�����
    vector<tag_t> m_tempCurves;

    vector<CurveData> m_allTrimCurves;
    static const char curveTypeTitle[64];//UF_ATTR_string
    static const char UPAssist[64];
    static const char UPTrime[64];
    static const char DwAssist[64];
    static const char DwTrim[64];
    static const char GroupFlagTitle[64];//UF_ATTR_integer
};




#endif