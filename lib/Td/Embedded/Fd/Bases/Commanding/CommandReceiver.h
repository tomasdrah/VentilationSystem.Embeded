//
// Created by tomasdrah on 16.03.2024.
//

#ifndef VENTILATIONSYSTEM_EMBEDED_COMMANDRECEIVER_H
#define VENTILATIONSYSTEM_EMBEDED_COMMANDRECEIVER_H

namespace TdEmbeddedFd {

    class DataArray {
    public:
        unsigned char GetByte(unsigned char position) {
            if (position > ArrayLength) { return 0; }
            return Array[position];
        }

        void SetByte(unsigned char position, unsigned char data) {
            Array[position] = data;
            IncreaseTheSizeUpTo(position, sizeof(char));
        }

        void AddByte(unsigned char data) {
            Array[ArrayLength] = data;
            IncreaseTheSizeUpTo(ArrayLength, sizeof(unsigned char));
        }

        void Clear() {
            for (unsigned char &c: Array) {
                c = 0;
            }
            ArrayLength = 0;
        }

        void SetData(unsigned char *data, unsigned char dataLength) {
            for (unsigned char i = 0; i < dataLength; ++i) {
                Array[i] = data[i];
            }
            ArrayLength = dataLength;
        }

        void IncreaseTheSizeUpTo(unsigned char position, unsigned char dataSize) {
            if (ArrayLength < position + dataSize) {
                ArrayLength = position + dataSize;
            }
        }

        static constexpr unsigned char MaxArraySize = 100;
        unsigned char Array[MaxArraySize]{};
        unsigned char ArrayLength = 0;
    };

    class Command {
    public:
        char GetCommandId() {
            return ActualCommandId;
        }

        void SetNewCommandId(char commandId) {
            ActualCommandId = commandId;
            CommandIsNew = true;
        }

        bool GetIsCommandNew() {
            return CommandIsNew;
        }

        bool IsCommandStarted() {
            return CommandIsStarted;
        }

        void SetIsCommandStarted() {
            CommandIsStarted = true;
        }

        bool GetIsCommandFinished() {
            return CommandIsFinished;
        }

        void SetIsCommandFinished() {
            CommandIsFinished = true;
        }

        void ClearTheCommand() {
            ActualCommandId = -1;

            Args.Clear();
            Response.Clear();

            CommandIsNew = false;
            CommandIsStarted = false;
            CommandIsFinished = false;
        }


        DataArray *GetArgs() {
            return &Args;
        }

        void SetArgs(unsigned char *arguments, unsigned char argLength) {
            Args.SetData(arguments, argLength);
        }

        unsigned char GetArgsLength() {
            return Args.ArrayLength;
        }

        DataArray *GetResponse() {
            return &Response;
        }

        void SetResponse(unsigned char *response, unsigned char respLength) {
            Response.SetData(response, respLength);
        }

        unsigned char GetResponseLength() {
            return Response.ArrayLength;
        }

    private:
        char ActualCommandId = -1;

        DataArray Args = DataArray();
        DataArray Response = DataArray();

        bool CommandIsNew = false;
        bool CommandIsStarted = false;
        bool CommandIsFinished = false;
    };

    class CommandHolder {
    public:
        char MaximumParalelCommands() {
            return CommandsBuffer;
        }

        bool NewCommandWithArgs(char commandId, unsigned char *arguments, unsigned char argLength) {
            NewCommand(commandId);
            Commands[0].SetArgs(arguments, argLength);
            return true;
        }

        bool NewCommandWithArgsDataArray(char commandId, DataArray *arguments) {
            NewCommand(commandId);
            Commands[0].SetArgs(arguments->Array, arguments->ArrayLength);
            return true;
        }

        bool NewCommand(char commandId) {
            Commands[0].ClearTheCommand();
            Commands[0].SetNewCommandId(commandId);
            return true;
        }

        bool HasCommandWithId(char commandId) {
            for (auto &command: Commands) {
                if (command.GetCommandId() == commandId) {
                    return true;
                }
            }
            return false;
        }

        bool HasNewCommandWithId(char commandId) {
            for (auto &command: Commands) {
                if (command.GetCommandId() == commandId and command.GetIsCommandNew()) {
                    return true;
                }
            }
            return false;
        }

        bool HasFinishedCommandWithId(char commandId) {
            for (auto &command: Commands) {
                if (command.GetCommandId() == commandId and command.GetIsCommandFinished()) {
                    return true;
                }
            }
            return false;
        }

        bool HasNewCommand() {
            for (auto &command: Commands) {
                if (command.GetIsCommandNew()) {
                    return true;
                }
            }
            return false;
        }

        bool HasFinishedCommand() {
            for (auto &command: Commands) {
                if (command.GetIsCommandFinished()) {
                    return true;
                }
            }
            return false;
        }

        char GetNewCommandId() {
            for (auto &command: Commands) {
                if (command.GetIsCommandNew()) {
                    return command.GetCommandId();
                }
            }
            return -1;
        }

        char GetFinishedCommandId() {
            for (auto &command: Commands) {
                if (command.GetIsCommandFinished()) {
                    return command.GetCommandId();
                }
            }
            return -1;
        }

        char GetNewCommandPositionId() {
            for (unsigned char i = 0; i < CommandsBuffer; ++i) {
                if (Commands[i].GetIsCommandNew()) {
                    return (char)i;
                }
            }
            return -1;
        }

        char GetFinishedCommandPositionId() {
            for (unsigned char i = 0; i < CommandsBuffer; ++i) {
                if (Commands[i].GetIsCommandFinished()) {
                    return (char)i;
                }
            }
            return -1;
        }

        char GetCommandPositionIdByCommandId(char commandId) {
            for (unsigned char i = 0; i < CommandsBuffer; ++i) {
                if (Commands[i].GetCommandId() == commandId) {
                    return (char)i;
                }
            }
            return -1;
        }

        char GetNewCommandPositionIdByCommandId(char commandId) {
            for (unsigned char i = 0; i < CommandsBuffer; ++i) {
                if (Commands[i].GetCommandId() == commandId and Commands[i].GetIsCommandNew()) {
                    return (char)i;
                }
            }
            return -1;
        }

        char GetFinishedCommandPositionIdByCommandId(char commandId) {
            for (unsigned char i = 0; i < CommandsBuffer; ++i) {
                if (Commands[i].GetCommandId() == commandId and Commands[i].GetIsCommandFinished()) {
                    return (char)i;
                }
            }
            return -1;
        }

        Command *GetNewCommand() {
            return GetCommandByPositionId(GetNewCommandPositionId());
        }

        Command *GetFinishedCommand() {
            return GetCommandByPositionId(GetFinishedCommandPositionId());
        }

        Command *GetNewCommandById(char commandId) {
            return GetCommandByPositionId(GetNewCommandPositionIdByCommandId(commandId));
        }

        Command *GetCommandById(char commandId) {
            return GetCommandByPositionId(GetCommandPositionIdByCommandId(commandId));
        }

        Command *GetFinishedCommandById(char commandId) {
            return GetCommandByPositionId(GetFinishedCommandPositionIdByCommandId(commandId));
        }

        Command *GetCommandByPositionId(char commandPositionId) {
            if (commandPositionId < 0) {
                commandPositionId = 0;
            }
            if (commandPositionId > CommandsBuffer - 1) {
                commandPositionId = CommandsBuffer - 1;
            }
            return &Commands[(unsigned char)commandPositionId];
        }


    private:
        static constexpr char CommandsBuffer = 1;
        Command Commands[CommandsBuffer]{};
    };
} // TdEmbeddedFd

#endif //VENTILATIONSYSTEM_EMBEDED_COMMANDRECEIVER_H
