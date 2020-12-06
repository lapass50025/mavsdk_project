#include "common.h"



/*
 *
 */
int main(int argc, char** argv)
{
    mavsdk::Mavsdk mavsdk;
    std::shared_ptr<mavsdk::System> system;
    std::shared_ptr<mavsdk::Telemetry> telemetry;
    std::shared_ptr<mavsdk::Action> action;
    std::shared_ptr<mavsdk::Mission> mission;

    std::vector<mavsdk::Mission::MissionItem> misionVector;

    double fLatitude = 0;
    double fLongitude = 0;
    float fAltitude = 0;

    std::string strUrl;

    int nRet = 0;


     // URL 설정하기
    if( argc == 1 )
    {
        strUrl = "udp://14540";
    }
    else
    {
        strUrl = argv[1];
    }    

    // System 객체 얻기
    nRet = InitSystem(strUrl, &mavsdk, &system);

    // Telemetry 객체 얻기
    if( nRet )
    {
        telemetry = std::make_shared<mavsdk::Telemetry>(system);
    }

    // Telemetry 초기화하기
    if( nRet )
    {
        nRet = InitTelemetry(system, telemetry);
    }

    // 현재 위치 정보 출력하기
    if( nRet )
    {
        nRet = GetGPSPosition(telemetry, &fLatitude, &fLongitude, &fAltitude);
        std::cout << fLatitude << std::endl;
        std::cout << fLongitude << std::endl;
        std::cout << fAltitude << std::endl;
    }

    // Action 객체 얻기
    if( nRet )
    {
        action = std::make_shared<mavsdk::Action>(system);
    }

#if 0
    // Arm 하기
    if( nRet )
    {
        nRet = ActionArm(telemetry, action);
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    // 이륙하기
    if( nRet )
    {
        nRet = ActionTakeoff(telemetry, action);
        std::this_thread::sleep_for(std::chrono::seconds(20));
    }

    // 착륙하기
    if( nRet )
    {
        nRet = ActionLand(telemetry, action);
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
#endif

    // Mission 객체 초기화하기
    if( nRet )
    {
        mission = std::make_shared<mavsdk::Mission>(system);
    }

    // Mission WayPoint 생성하기
    if( nRet )
    {
        nRet = MissionMakePoint(&misionVector, fLatitude, fLongitude, fAltitude + 1.0f);
    }

    // Mission Upload 하기
    if( nRet )
    {
        nRet = MissionUpload(mission, &misionVector);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    if( nRet )
    {
        ActionArm(telemetry, action);
    }

    // Mission 실행하기
    if( nRet )
    {
        nRet = MissionRun(mission);
    }

    std::this_thread::sleep_for(std::chrono::seconds(3));

    // 착륙하기
    if( nRet )
    {
        nRet = ActionRtl(telemetry, action);
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    return 0;
}
