
#include <windows.h>
#include "imgui.h"
#include <string>
#include <iostream>

void ExecuteCommand(const char* command) {
    // ʹ�� CreateProcess ����cmd
    std::string cmd = "cmd.exe /K " + std::string(command); // /C ��ʾִ��������˳�
    FILE* fp = _popen(cmd.c_str(), "r");
    if (fp) {
        char buffer[128];
        while (fgets(buffer, sizeof(buffer), fp) != nullptr) {
            // ������ڴ˽����չʾ��ImGui����̨���ı�����
            std::cout << buffer; // ���������̨
        }
        fclose(fp);
    }
}

void RenderConsole() {
            // ��ʾ�������
            ImGui::BeginChild("Console Output", ImVec2(0, -30), true);
            ImGui::Text("Command output will appear here...");
            ImGui::EndChild();

            // �����
            static char command[256] = "";
            if (ImGui::InputText("Command", command, IM_ARRAYSIZE(command), ImGuiInputTextFlags_EnterReturnsTrue)) {
                // ��������
                ExecuteCommand(command);
                memset(command, 0, sizeof(command)); // ��������
            }
}
