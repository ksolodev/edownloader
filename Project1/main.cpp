#include <windows.h>
#include <urlmon.h>
#include <thread>
#include <vector>
#include <string>
#include <iostream>
#pragma comment(lib, "urlmon.lib")

// Структура для хранения URL и пути загрузки
struct DownloadTask {
    std::wstring url;
    std::wstring filePath;
};

// Функция для загрузки файла
void downloadFile(const DownloadTask& task) {
    if (SUCCEEDED(URLDownloadToFileW(NULL, task.url.c_str(), task.filePath.c_str(), 0, NULL))) {
        MessageBoxW(NULL, L"File downloaded successfully!", L"Success", MB_OK);
    }
    else {
        MessageBoxW(NULL, L"Failed to download file.", L"Error", MB_OK);
    }
}

int main() {
    // Массив задач на скачивание файлов
    std::vector<DownloadTask> tasks = {
        {L"https://cdn.akamai.steamstatic.com/client/installer/SteamSetup.exe", L"C:\\Users\\pc\\Downloads\\SteamSetup.exe"},
        {L"https://discord.com/api/downloads/distributions/app/installers/latest?channel=stable&platform=win&arch=x64", L"C:\\Users\\pc\\Downloads\\discordsetup.exe"},
        {L"https://telegram.org/dl/desktop/win64", L"C:\\Users\\pc\\Downloads\\tsetup.exe"},
        {L"https://releases.arc.net/windows/ArcInstaller.exe", L"C:\\Users\\pc\\Downloads\\arcinstall.exe"}
    };

    // Вектор потоков для многопоточности
    std::vector<std::thread> threads;

    // Запуск скачивания файлов в отдельных потоках
    for (const auto& task : tasks) {
        threads.emplace_back(downloadFile, task);
    }

    // Ожидание завершения всех потоков
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    return 0;
}
