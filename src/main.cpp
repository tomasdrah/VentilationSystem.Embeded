#include<SPI.h>

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_SPIDevice.h>

#include "Embedded/Fd/Bases/Bases.h"
#include "Embedded/Fd/Independent/Independent.h"

#include "Embedded/Fd/Arduino/Comunication/SPI/Ard_SPIMaster.h"
#include "Embedded/Fd/Arduino/Ard_IoPin.h"

auto CommandHolderMaster = TdEmbeddedFd::CommandHolder();
//auto MySpiMaster = TdEmbeddedFd::Ard_SPIMaster();
//auto MySlaveSS1Pin = TdEmbeddedFd::Ard_IoPin(10, OUTPUT);


class MockCommandExecutor : public TdEmbeddedFd::ICommandExecutor {
public:
    void ExecuteCommand(TdEmbeddedFd::Command *command) override {
        Serial.print("Executing cmd:");
        Serial.print((int) command->GetCommandId());
        if (command->GetCommandId() == 13) {
            Serial.print(". Args:");
            Serial.print((char) command->GetArgs()->GetByte(0));
            Serial.print(":");
            Serial.println((int) command->GetArgs()->GetByte(1));
        } else if (command->GetCommandId() == 15) {
            Serial.print(". Duplicating:");
            Serial.print((char) command->GetArgs()->GetByte(0));
            command->GetResponse()->AddByte(command->GetArgs()->GetByte(0));
        } else {
            Serial.println();
        }
    }
};

auto CmdExecutor = MockCommandExecutor();
auto CmdGateway = TdEmbeddedFd::CommandExecutionGateway(&CommandHolderMaster, &CmdExecutor);

void setup(void) {
    Serial.begin(9600);

//    MySpiMaster.TryToInitializeMaster(TdEmbeddedFd::SPITransactionSettings(9600));

    CommandHolderMaster.NewCommand(13);
    Serial.println("M: new cmd 13");
}

void loop(void) {

//    MySpiMaster.SendConstText(&MySlaveSS1Pin, "Hello world \n");
    if (CommandHolderMaster.HasFreeCommand()) {
        auto freeCmd = CommandHolderMaster.GetFreeCommand();
        freeCmd->SetNewCommandId(13);
        freeCmd->GetArgs()->AddByte('x');
        freeCmd->GetArgs()->AddByte(255);
    }
    CmdGateway.Update();

    if (CommandHolderMaster.HasFinishedCommand()) {
        auto finishedCmd = CommandHolderMaster.GetFinishedCommand();
        Serial.print("Finished cmd:");
        Serial.println((int) finishedCmd->GetCommandId());
    }

    delay(5000);


    if (CommandHolderMaster.HasFreeCommand()) {
        auto freeCmd = CommandHolderMaster.GetFreeCommand();
        freeCmd->SetNewCommandId(14);
    }
    CmdGateway.Update();

    if (CommandHolderMaster.HasFinishedCommand()) {
        auto finishedCmd = CommandHolderMaster.GetFinishedCommand();
        Serial.print("Finished cmd:");
        Serial.println((int) finishedCmd->GetCommandId());
    }

    delay(5000);


    if (CommandHolderMaster.HasFreeCommand()) {
        auto freeCmd = CommandHolderMaster.GetFreeCommand();
        freeCmd->SetNewCommandId(15);
        freeCmd->GetArgs()->AddByte('O');
    }
    CmdGateway.Update();

    if (CommandHolderMaster.HasFinishedCommand()) {
        auto finishedCmd = CommandHolderMaster.GetFinishedCommand();
        Serial.print("Finished cmd:");
        Serial.print((int) finishedCmd->GetCommandId());
        Serial.print(" Response:");
        Serial.println((char) finishedCmd->GetResponse()->GetByte(0));
    }

    delay(5000);


    Serial.print(" Cmd 15 has unsent response");
    if (CommandHolderMaster.HasFreeCommand()) {
        auto freeCmd = CommandHolderMaster.GetFreeCommand();
        freeCmd->SetNewCommandId(15);
        freeCmd->GetArgs()->AddByte('S');
    }
    CmdGateway.Update();

    if (CommandHolderMaster.HasFinishedCommand()) {
        auto finishedCmd = CommandHolderMaster.GetFinishedCommand();
        Serial.print("Finished cmd:");
        Serial.print((int) finishedCmd->GetCommandId());
        Serial.print(" Response:");
        Serial.println((char) finishedCmd->GetResponse()->GetByte(0));
        Serial.println(" Clearing the cmd 15.");
        finishedCmd->ClearTheCommand();
    }

    delay(5000);
}