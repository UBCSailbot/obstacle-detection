#include <io/DangerZoneSerializer.h>
#include "DangerZoneSerializerTest.h"
#include <dangerzone.pb.h>

DangerZoneSerializerTest::DangerZoneSerializerTest() {

}

TEST_F(DangerZoneSerializerTest, SerializerTest) {

    std::vector<DangerZone> dangerZones;
    const DangerZone &inputDangerZone = DangerZone(10.0, 20.0, 0);
    dangerZones.push_back(inputDangerZone);

    auto message = DangerZoneSerializer::serializeToZmq(dangerZones);
    sailbot::DangerZones protoDangerZones;
    protoDangerZones.ParseFromArray(message.data(), message.size());
    auto dangerZone = protoDangerZones.danger_zone(0);

    EXPECT_EQ(dangerZone.starboard_angle(), inputDangerZone.getStarboardAngleDeg());
    EXPECT_EQ(dangerZone.port_angle(), inputDangerZone.getPortAngleDeg());
    EXPECT_TRUE(message.size() > 0);
}
