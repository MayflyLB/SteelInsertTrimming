#ifndef OSHEETOPERATOR_H
#define OSHEETOPERATOR_H
#include "DataStruction.h"
#include "uf_part.h"
#include "uf_obj.h"
#include "uf_obj_types.h"
#include "uf_layer.h"
#include "../../Include/PublicFun.h"
#include "RetOffsetSheet.h"
#include "../Include/CurveAttrE.h"

class DllExport CommonOperation : public CommonTraits::Struct_Type
{
    typedef CommonTraits::Struct_Type Struct_Type;
public:

    CommonOperation(const CommonTraits::Struct_Type&);
    //�ͷ�ָ��ָ�����Դ.
    ~CommonOperation();

    void operator()(const CurveAttrE& temp)
    {
        creataDST(temp(0));
        creataUST(temp());
    }

private:
    void creataDST(const vector<TrimCurveData> &m_CurveDataDw)
    {
        for (int i=0;i<m_CurveDataDw.size();i++)
        {
            getCurvesInfo(m_CurveDataDw[i]);
            createBodyDST();
            createDetailDST();
        }
        return;
    }


    void creataUST(const vector<TrimCurveData> &m_CurveDataUp)
    {
        for (int i = 0; i < m_CurveDataUp.size(); i++)
        {
            getCurvesInfo(m_CurveDataUp[i]);
            createBodyUST();
            createDetailUST();
        }
        return;
    }

    void getCurvesInfo(const TrimCurveData& info);



    void createBodyDST();
    void createBodyUST();

    void createDetailDST();
    void createDetailUST();


//     void initialParamDST();
//     void initialParamUSTE();
//     void initialParamUSTL();


        //1��ģ 0��ģ
    void createShapeBlank(int col1, int col2, int flagUD = 1);
    void extrudBlankBody(tag_t& extrud, tag_t sheetTag);//�������� flagλtrueʱ,
    void extrudBlankBodyUDST(tag_t& extrud, tag_t sheetTag);

    tag_t createExtrudeBodyEx(const vccdata &vcc, double thiness, double ext = 0);  //�������򴴽�������

    void offsetFace(tag_t face_t, double dist);//TODO

    void extractFaces(tag_t extrud, vector<tag_t>&sideFaces, vector<tag_t>&cutShapeFaces,
        vector<tag_t>&floorFaces,vector<tag_t>&backBoard, int col[4]);//��ȡë��������� ������
    void extrudeVertex(const vccdata &vcc, bool flag, double len = 100);//�ӳ��ޱ��ߵ�������

    vector<tag_t> BooleanOper(tag_t& extrud, tag_t sheetsSet, tag_t flagT = 0, bool is_sub = true, bool is_del = true,
        bool is_ThrowError = false, bool is_keepTarget = false, bool is_keepTool = true);

    vector<tag_t> BooleanOperUDC_ST(tag_t& extrud, tag_t flagT, tag_t sheetsSet, bool flag = true, bool isSetEx = false);

    //ƫ�����ڴ��������� ���õ�Ƭ��
    //tag_t createOffsetSheet( vccdata vcc, bool flag = true);

    tag_t createOffsetSheetEx(vccdata vcc);

    //��ǰ�ڻ�ȡ���ޱ��ߺ͸�����  �ƶ��� Ƭ�����һ��(�·�)
    void offsetCurveSet();
    //�����ݶ�
    void createToolBlank();

    //���˳������z�Ḻ����ɽǶ�С��90�ȵ���
    void filterZFace(vector<tag_t>&faces);

    void finishTool(tag_t face, vector<tag_t>& bodys_);

    void splinesProcessToLinesDUST(vector<tag_t> &tempSplines);

private:
    Session *theSession;
    Part *workPart;

    std::vector<CurveData> m_assistLD;//������
    std::vector<CurveData> m_trimLD;//�ޱ���
    std::vector<vccdata> m_trimVCC;//�����ޱ���

    double m_minDist;//�ޱ�����Ŀ��Ƭ����̾���
    double m_curvesMoveDist;

    vector<CurveData*> m_simplePro;

    tag_t m_extrud;

    ////��������
    tag_t sheetTag;
    RetOffsetSheet *m_retOffsetSheet;
    vector<tag_t> m_tempObj;
    vector<tag_t> m_tempBody;
};

#endif // !SHEETOPERATOR_H