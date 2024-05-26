#include "dialog.h"
#include "ui_dialog.h"
//########################################################################################################
#include <QCoreApplication>
#include <vector>
#include <iostream>
#include <memory> // Для std::unique_ptr
#include <QFileDialog>
#include <QDebug>
#include <QTextStream>
//########################################################################################################
QString Nazvaniye_fayla_s_neyronami_i_signalom;
//########################################################################################################
// Реализация make_unique для C++11
namespace std {
    template<typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}
//########################################################################################################
//########################################################################################################
// Инициализация умного указателя на std::vector<long long>
    std::unique_ptr<std::vector<long long>> list_of_synapses = std::make_unique<std::vector<long long>>();
     std::unique_ptr<std::vector<long long>> list_of_neurons = std::make_unique<std::vector<long long>>();
//########################################################################################################
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
//########################################################################################################
    std::cout << "bez_1_GUI_3_uu" << std::endl;  
//######################################################################################################## 
/// Сначала укажем какой файл с нейронами подстроить.
     Nazvaniye_fayla_s_neyronami_i_signalom = QFileDialog::getOpenFileName(this,
       tr("Открыть файл neyroni_i_signal.txt без 1 который надо подстроить."), 
       "/home/viktor/my_projects_qt_2/Sgenerirovannye_fayly/", tr("Text Files (*.txt)"));
//########################################################################################################
////////////////////////////////////////////// загрузка нейронов и сигнала из файла в вектор
// читаем нейроны в вектор
 // Открытие файла для чтения
 int chislo_oshibok_neyronov=0;
     std::cout << "читаем нейроны в вектор"<< std::endl;  
    QFile file(Nazvaniye_fayla_s_neyronami_i_signalom);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл!";
           }

    // Создание текстового потока для чтения из файла
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        bool ok;
        long long value = line.toLongLong(&ok);
        if (ok) {
            list_of_neurons->push_back(value);
        } else {
//            qDebug() << "Не удалось преобразовать строку в число:" << line;
        }
         if (ok) {
//        qDebug() << "Преобразование в long long прошло успешно:";
//        qDebug() << "Значение:" << value;
    } else {
//        qDebug() << "Ошибка преобразования в long long:";
//        qDebug() << "Строка не является числовой, или значение выходит за пределы long long";
          chislo_oshibok_neyronov++;
    }
    }
    // Закрытие файла
    file.close();
      std::cout << "конец чтения нейронов в вектор"<< std::endl;  
        std::cout << "//########################################################################################################"<< std::endl;  
        std::cout << "число ошибок форматов нейронов = "<< chislo_oshibok_neyronov<< std::endl; 
                std::cout << "//########################################################################################################"<< std::endl; 














    
}

Dialog::~Dialog()
{
    delete ui;
}

