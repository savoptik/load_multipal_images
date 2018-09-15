//
//  main.cpp
//  load_multipal_images
//
//  Created by Артём Семёнов on 10/09/2018.
//  Copyright © 2018 Артём Семёнов. All rights reserved.
//

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <dirent.h>

// путь к каталогу с изображениями
const char* dataSetPath = "./dataset/";

int main(int argc, const char * argv[]) {
    // датасет
    std::vector<std::vector<cv::Mat>> dataSet;
    // список папок внутри датасета
    std::vector<std::string> dirNames;
    // открываем поток папки
    auto folder = opendir(dataSetPath);
    struct dirent *entry;;
    // ищем папки
    while ((entry = readdir(folder)) != NULL) {
        // собираем имена папок
        dirNames.push_back(entry->d_name);
    }
    // закрываем поток
    closedir(folder);
    delete entry;
    // обходим найденные папки первые 3 имени к именам папок не относятся
    for (int i = 3; i < dirNames.size(); i++) {
        // вектор, который будет содержать изображения.
        std::vector<cv::Mat> imgClass;
        // собираем путь к папке внутри датосета
        std::string filePath = dataSetPath + dirNames[i] + "/";
        // открываем поток подпапки
        auto subFolder = opendir(filePath.data());
        struct dirent *sdir;
        // на всякий случай выводим путь к папке
        std::cout << filePath.data() << std::endl;
        // ищем файлы внутри подпапки
        while ((sdir = readdir(subFolder)) != NULL) {
            std::string name = sdir->d_name;
            // если имя папки содержит расширение JPG
            if (name.find("JPG") != std::string::npos) {
                                std::cout << name << std::endl;
                // загружаем изображение.
                imgClass.push_back(cv::imread(filePath+name));
            }
        }
        // закрываем поток подпапки
            closedir(subFolder);
            delete sdir;
        // затаскиваем класс в датасет
        dataSet.push_back(imgClass);
    }
    return 0;
}
