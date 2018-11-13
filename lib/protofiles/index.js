const ProtoBuf = require('protobufjs');
const path = require('path');

const currentDataBuilder = ProtoBuf.loadProtoFile(path.join(__dirname, 'messages', 'currentdata.proto'));

const GPSCoordinate = currentDataBuilder.build('sailbot.GPSCoordinate');
const GPSCoordinateExact = currentDataBuilder.build('sailbot.GPSCoordinateExact');
const CurrentData = currentDataBuilder.build('sailbot.CurrentData');
const PowerData = currentDataBuilder.build('sailbot.PowerData');
const UnixTimestamp = currentDataBuilder.build('sailbot.UnixTimestamp');
const WaypointMessage = currentDataBuilder.build('sailbot.WaypointMessage');
const ErrorMessage = currentDataBuilder.build('sailbot.ErrorMessage');
const ParameterMessage = currentDataBuilder.build('sailbot.ParameterMessage');
const GenericLogMessage = currentDataBuilder.build('sailbot.GenericLogMessage');
const WaypointCommand = currentDataBuilder.build('sailbot.Command.WaypointCommand');
const SimulatorData = currentDataBuilder.build('sailbot.Command.SimulatorData');
const ComponentCommand = currentDataBuilder.build('sailbot.Command.ComponentCommand');
const ComponentCommands = currentDataBuilder.build('sailbot.Command.ComponentCommands');
const Command = currentDataBuilder.build('sailbot.Command');

const serverMessageBuilder = ProtoBuf.loadProtoFile(path.join(__dirname, 'messages', 'servermessage.proto'));
const CurrentDataServerMessage = serverMessageBuilder.build('sailbot.CurrentDataServerMessage');

const messagesBuilder = ProtoBuf.loadProtoFile(path.join(__dirname, 'messages', 'messages.proto'));
const Sailbot = messagesBuilder.build('Sailbot');
const MOMessage = Sailbot.MOMessage;
const MTMessage = Sailbot.MTMessage;
const HTTPRequest = Sailbot.HTTPRequest;

const testingCommandResponseBuilder = ProtoBuf.loadProtoFile(path.join(__dirname, 'messages', 'testingcommandresponse.proto'));
const TestingCommandResponse  = testingCommandResponseBuilder.build('Sailbot').TestingCommandResponse;

const testingCommandBuilder = ProtoBuf.loadProtoFile(path.join(__dirname, 'messages', 'testingcommand.proto'));
const TestingCommand = testingCommandBuilder.build('Sailbot').TestingCommand;

module.exports = {
    GPSCoordinate,
    GPSCoordinateExact,
    CurrentData,
    PowerData,
    UnixTimestamp,
    WaypointMessage,
    ErrorMessage,
    ParameterMessage,
    GenericLogMessage,
    WaypointCommand,
    SimulatorData,
    ComponentCommand,
    ComponentCommands,
    Command,
    CurrentDataServerMessage,
    MOMessage,
    MTMessage,
    HTTPRequest,
    TestingCommandResponse,
    TestingCommand
};
