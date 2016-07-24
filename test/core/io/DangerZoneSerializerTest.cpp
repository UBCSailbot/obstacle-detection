#include <io/DangerZoneSerializer.h>
#include "DangerZoneSerializerTest.h"
#include <dangerzone.pb.h>

using namespace std::chrono;


DangerZoneSerializerTest::DangerZoneSerializerTest() {

}

TEST_F(DangerZoneSerializerTest, SerializerTest) {

    std::vector<DangerZone> dangerZones;
    DangerZone inputDangerZone = DangerZone(10.0, 20.0, 0);
    inputDangerZone.set_latitude(49.225236);
    inputDangerZone.set_longitude(-123.090731);
    inputDangerZone.setTime(duration_cast<seconds>(system_clock::now().time_since_epoch()));
    dangerZones.push_back(inputDangerZone);

    auto message = DangerZoneSerializer::serializeToZmq(dangerZones);
    sailbot::DangerZones protoDangerZones;
    protoDangerZones.ParseFromArray(message.data(), message.size());
    auto dangerZone = protoDangerZones.danger_zone(0);

    EXPECT_EQ(dangerZone.starboard_angle(), inputDangerZone.getStarboardAngleDeg());
    EXPECT_EQ(dangerZone.port_angle(), inputDangerZone.getPortAngleDeg());
    EXPECT_EQ(dangerZone.time().seconds(), inputDangerZone.getTime().count());
    EXPECT_EQ(dangerZone.longitude(),inputDangerZone.get_longitude());
    EXPECT_EQ(dangerZone.latitude(),inputDangerZone.get_latitude());
    EXPECT_TRUE(message.size() > 0);
}
