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
        fDiff2 = (pos2.y - pos2.y);

        pPos->x = pos2.x + fDiff1;
        pPos->y = pos2.y + fDiff2;
    }

    return nRet;
}