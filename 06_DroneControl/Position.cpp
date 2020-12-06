#include "common.h"



/*
 *
 */
int PositionNextPoint(POINTTYPE pos1, POINTTYPE pos2, POINTTYPE *pPos)
{
    double fDiff1 = 0.0f;
    double fDiff2 = 0.0f;

    int nRet = 1;

    

    if( nRet )
    {        
        fDiff1 = (pos2.x - pos1.x);
        fDiff2 = (pos2.y - pos1.y);

        pPos->x = pos2.x + fDiff1;
        pPos->y = pos2.y + fDiff2;
    }

    return nRet;
}


/*
 *
 */
int PositionFootPerpendicular(POINTTYPE pos1, POINTTYPE pos2, double fDistance, POINTTYPE *pPos3, POINTTYPE *pPos4)
{
    double a = 0.0f;
    double a1 = 0.0f;
    double angle = 0.0f;

    int nRet = 1;


    
    // 수선의 발 구하기
    angle = -atan2((pos2.x - pos1.x), (pos2.y - pos1.y));
    pPos3->x = pos1.x + sin(angle) * fDistance;
    pPos3->y = pos1.y + cos(angle) * fDistance;

    angle = angle * 180 / 3.14;
    angle = angle + 180;

    if( angle >= 360 )
    {
        angle = angle - 360.0f;
    }

    angle = angle * 3.14 / 180;

    // 반대편 수선의 발 구하기
    pPos4->x = pos1.x + sin(angle) * fDistance;
    pPos4->y = pos1.y + cos(angle) * fDistance;

    return nRet;
}