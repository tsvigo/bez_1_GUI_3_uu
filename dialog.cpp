// cycle_of_distinguishing_a_one_with_vectors_GUI_2
#include "dialog.h"
#include "ui_dialog.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Dialog::Dialog
/// \param parent
#include <QTextStream>
#include <QFile>
#include <fstream>

#include <iostream>
using namespace std;
#include <QFileDialog>
#include <vector>
#include <memory> // Для std::unique_ptr
#include <QDebug>
#include <chrono>
#include <thread>
//#include <log4cpp/Category.hh>
//#include <log4cpp/Appender.hh>
//#include <log4cpp/Layout.hh>
//#include <log4cpp/Priority.hh>
//#include <QLogger>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QString    Nazvaniye_fayla_s_neyronami_i_signalom="";
long long variable_error;
int var ;
int variable_synapse_index_counter=0;

 int neuron_index = 0, synapse_index = 0;
 bool all_sinapsi_proydeni=false;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Реализация make_unique для C++11
namespace std {
    template<typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}
//###########################################################################
// Инициализация умного указателя на std::vector<long long>
    std::unique_ptr<std::vector<//unsigned
    long long>> list_of_synapses = std::make_unique<std::vector<
          //  unsigned
            long long>>();
     std::unique_ptr<std::vector<long long>> list_of_neurons = std::make_unique<std::vector<long long>>();
//########################################################################################################
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
//###########################################################################
  //  closeApp() ;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
              // выведем название программы
               std::cout << "bez_1_GUI_3_uu" << std::endl;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// откроем txt нейроны
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Диалог открытия файла
//               QString filePath = QFileDialog::getOpenFileName(this, tr("Выберите файл txt"),
//     //QDir::homePath()
//       "/home/viktor/Загрузки/data/none/300/masshtab/black-white/"
//        , tr("Все файлы txt (*.txt)"));
//         if (!filePath.isEmpty()) {
//          // filePath содержит полный путь выбранного файла
//       Nazvaniye_fayla_s_neyronami_i_signalom=filePath;
//               }
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //########################################################################################################
         ////////////////////////////////////////////// загрузка нейронов и сигнала из файла в вектор
         // читаем нейроны в вектор
          // Открытие файла для чтения
          int chislo_oshibok_neyronov=0;
              std::cout << "читаем нейроны в вектор"<< std::endl;
         //    QFile file(Nazvaniye_fayla_s_neyronami_i_signalom);
         QFile file(
               //      "/home/viktor/Загрузки/data/none/300/masshtab/black-white/1/neurons_and_signal.txt"
                     "/home/viktor/neurons_and_signal.txt"
                   // /home/viktor/neurons_and_signal.txt
                     );
         if (!file.exists()) {
             qDebug() << "File does not exist!";
             return;
         }
         if (!file.open(QIODevice::ReadOnly// | QIODevice::Text
                        )) {
             qDebug() << "Failed to open the file!";
             return;
         }


             // Создание текстового потока для чтения из файла
         QTextStream in(&file);
//###########################################################################
//             while (!in.atEnd()) {
//                 QString line = in.readLine();
//                 bool ok;
//                 long long value = line.toLongLong(&ok);
//                 if (ok) {
//                     list_of_neurons->push_back(value);
//                 } else {
//         //            qDebug() << "Не удалось преобразовать строку в число:" << line;
//                 }
//                  if (ok) {
//         //        qDebug() << "Преобразование в long long прошло успешно:";
//         //        qDebug() << "Значение:" << value;
//             } else {
//         //        qDebug() << "Ошибка преобразования в long long:";
//         //        qDebug() << "Строка не является числовой, или значение выходит за пределы long long";
//                   chislo_oshibok_neyronov++;
//             }
//             }
//             // Закрытие файла
//             file.close();
//###########################################################################

         // Читаем первые 201 строку из файла
         int lineCount = 0;
         while (lineCount < 201 && !in.atEnd()) {
             QString line = in.readLine();
             if (line.trimmed().isEmpty()) {
                 std::cerr << "Line " << (lineCount + 1) << " is empty, skipping." << std::endl;
                 continue;  // Пропускаем пустые строки
             }

             bool ok;
             long long number = line.toLongLong(&ok);
             if (ok) {
                 list_of_neurons->push_back(number);
                 ++lineCount;  // Увеличиваем счетчик только при успешной конвертации
             } else {
                 std::cerr << "Failed to convert line " << (lineCount + 1) << " to number: " << qPrintable(line) << std::endl;
             }
         }

         // Закрываем файл
         file.close();

         // Проверка, что удалось прочитать ровно 201 непустую строку
         if (lineCount != 201) {
             std::cerr << "Error: Only " << lineCount << " valid lines were read from the file." << std::endl;
          //   return 1;
         }
//###########################################################################
               std::cout << "конец чтения нейронов в вектор"<< std::endl;
                 std::cout << "//########################################################################################################"<< std::endl;
                 std::cout << "число ошибок форматов нейронов = "<< chislo_oshibok_neyronov<< std::endl;
                         std::cout << "//########################################################################################################"<< std::endl;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////// загрузка синапсов из файла в вектор
  // Открытие файла для чтения
           int chislo_oshibok_sinapsov=0;
     std::cout << "читаем синапсы в вектор"<< std::endl;
    QFile file2("/home/viktor/my_projects_qt_2/Funktsiya_Resheniya_2/synapses.txt");
              // /home/viktor/my_projects_qt_2/Funktsiya_Resheniya_2/synapses.txt
       if (!file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
      qDebug() << "Не удалось открыть файл!";
                      }

          // Создание текстового потока для чтения из файла
           QTextStream in2(&file2);
 ////###########################################################################

               // Читаем первые 10105 строк из файла
               int lineCount2 = 0;
               while (lineCount2 < 10105 && !in2.atEnd()) {
                   QString line = in2.readLine();
                   if (line.trimmed().isEmpty()) {
                       std::cerr << "Line " << (lineCount2 + 1) << " is empty, skipping." << std::endl;
                       continue;  // Пропускаем пустые строки
                   }

                   bool ok;
                   long long number = line.toLongLong(&ok);
                   if (ok) {
                       list_of_neurons->push_back(number);
                       ++lineCount2;  // Увеличиваем счетчик только при успешной конвертации
                   } else {
                       std::cerr << "Failed to convert line " << (lineCount2 + 1) << " to number: " << qPrintable(line) << std::endl;
                   }
               }

               // Закрываем файл
               file2.close();

               // Проверка, что удалось прочитать ровно 201 непустую строку
               if (lineCount2 != 10105) {
                   std::cerr << "Error: Only " << lineCount2 << " valid lines were read from the file." << std::endl;
                 //  return 1;
               }
 /////###########################################################################
//        while (!in2.atEnd()) {
//         QString line = in2.readLine();
//               bool ok;
//            long long value = line.toLongLong(&ok);
//                 if (ok) {
//                                     list_of_synapses->push_back(value);
//              } else
//                                 {
//                         //            qDebug() << "Не удалось преобразовать строку в число:" << line;
//                                 }
//    if (ok) {
//       //        qDebug() << "Преобразование в long long прошло успешно:";
//          //        qDebug() << "Значение:" << value;
//              } else {
//                         //        qDebug() << "Ошибка преобразования в long long:";
//qDebug() << "Строка не является числовой, или значение выходит за пределы long long: "<< line ;
//                                   chislo_oshibok_sinapsov++;
//                             }

//                             }
//                             // Закрытие файла
//                             file2.close();
//###########################################################################
 std::cout << "конец чтения синапсов в вектор"<< std::endl;
      std::cout << "//########################################################################################################"<< std::endl;
         std::cout << "число ошибок форматов синапсов = "<< chislo_oshibok_sinapsov<< std::endl;
      std::cout << "//########################################################################################################"<< std::endl;
//########################################################################################################
//########################################################################################################
  if (chislo_oshibok_sinapsov!=0 || chislo_oshibok_neyronov!=0)
      // если есть ошибки в форматах синапсов или нейронов останавливаем
 // программу
        // Остановить выполнение программы
                           {
           exit(EXIT_SUCCESS);

              }

//########################################################################################################
  //########################################################################################################
  /////////////   показываем что определила программа
      if
        //  ( variable_error <=0)
          (list_of_neurons->at(200)<0)

      {
          ui->label->setText(Nazvaniye_fayla_s_neyronami_i_signalom+"\n"+"Программа считает что это 1.");
        std::cout << "list_of_neurons->at(200) = "<< list_of_neurons->at(200)<< std::endl;
         // Odin_Programmi=true;
           //  goto d;
      }
                             else {
          ui->label->setText(Nazvaniye_fayla_s_neyronami_i_signalom+"\n"+"Программа считает что это не 1.");
          std::cout << "list_of_neurons->at(200) = "<< list_of_neurons->at(200)<< std::endl;
          goto d;
          //  Odin_Programmi=false;

      }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// Solution function ////////////////////////////////////////////////////////////
/// решение
      b:
     if       (list_of_neurons->at(200)>=0) goto d; // не 1 - на выход
      if (variable_synapse_index_counter==10100)variable_synapse_index_counter=0;
          for ( var = 100;              // первый for
         var < 200

           ; ++var) // This is the range of neurons

          {
  std::cout << "/";
         //     if (list_of_neurons->at(200)>=0) break;
              for ( neuron_index = 0, synapse_index = 0;

                /*,*/ synapse_index < 10100;
                  ++neuron_index, synapse_index = synapse_index + 100)

              { // // ошибка сегментации


              if (neuron_index < 200)

                  list_of_neurons->at(var)
//###########################################################################
                          =
                          list_of_neurons->at(var) //-5310911
                  +
                          (
                          (list_of_neurons->at(neuron_index)
                    //  /   // деление
                           -
                   list_of_synapses->at(synapse_index))
                              )
                              ; // + на -

              } //
            //  if       (list_of_neurons->at(200)>=0) goto d; // не 1 - на выход
          }
      //////////////////////
          for (int   neuron_index = 100, synapse_index = 10000;       // второй for

       synapse_index < 10100
       ;
            ++neuron_index, ++synapse_index)
          {
                   // if (list_of_neurons->at(200)>=0) break;

    //     if (list_of_synapses->at(synapse_index)!=0)
              list_of_neurons->at(200)
//###########################################################################
                      =
                      list_of_neurons->at(200) //-5310911
              +
                      (
                      (list_of_neurons->at(neuron_index)
                     //  / // деление
                       -
                       list_of_synapses->at(synapse_index))
                          )
              ; // + на -
    //     if       (list_of_neurons->at(200)>=0) goto d;
      //   std::cout << "list_of_neurons->at(200)= "  <<list_of_neurons->at(200)  <<std::endl;
          }
//########################################################################################################
   variable_synapse_index_counter++;
//################################# конец решения ###################################################################
/////////////   показываем что определила программа
std::cout << "list_of_neurons->at(200)= "  <<list_of_neurons->at(200)  <<std::endl;
std::cout << "variable_synapse_index_counter= "  <<variable_synapse_index_counter  <<std::endl;
// list_of_synapses->at(variable_synapse_index_counter)
std::cout << "list_of_synapses->at("<<variable_synapse_index_counter<<")= "
          <<list_of_synapses->at(variable_synapse_index_counter)  <<std::endl;
     if       (list_of_neurons->at(200)>=0) goto d;
// list_of_synapses->at(synapse_index)
std::cout << "list_of_synapses->at(0)= "  <<list_of_synapses->at(0) <<std::endl;
/// подстройка //////////////////////////////////////////////////////////////////////////////////////////////
///
          if       (list_of_neurons->at(200)<0) // если Программа считает что это 1.
// начиная с variable_synapse_index_counter=10100 надо менять каждый синапс на 1
//              for (variable_synapse_index_counter=10100;variable_synapse_index_counter>-1;
//                   variable_synapse_index_counter--)
              {
  list_of_synapses->at(variable_synapse_index_counter)
          =
          list_of_synapses->at(variable_synapse_index_counter)
       // -
          +
          1
      //  10
        // 9223372036854775807
      // 1459315198938531889
     // 859689765
          ;

//   if( list_of_synapses->at(0)<=-9223372036854775808)
// // exit(0);
//       goto d;
//   if( list_of_synapses->at(variable_synapse_index_counter)<-9223372036854775808)
//  exit(0);
//   if( list_of_synapses->at(variable_synapse_index_counter)<0//-9223372036854775808
//           )
//       list_of_synapses->at(variable_synapse_index_counter)=0
//             //  -9223372036854775808
//               ;
  if (variable_synapse_index_counter==10105 &&
     list_of_synapses->at(variable_synapse_index_counter)>=9223372036854775807
                      //  -9223372036854775808
          )
  {
all_sinapsi_proydeni=true;
      goto e;
  }
               if(variable_synapse_index_counter==10105)variable_synapse_index_counter=0;
               if(list_of_neurons->at(200)<0) //  1
                  goto b;
               if(list_of_neurons->at(200)>=0) // не 1
                goto d;
              }
          else goto d;
e:
std::cout << "все синапсы пройдены, поставлены на максимумы и ошибка не пропала." << std::endl;
if(all_sinapsi_proydeni==true) exit(0);
////  конец подстройки ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      d:
if (list_of_neurons->at(200)>=0)
{

std::cout << "Программа считает что это не 1."<< std::endl;
}
//###########################################################################//###########################################################################
          // запишем синапсы
              // Имя файла для записи
                  QString filename = "/home/viktor/my_projects_qt_2/Funktsiya_Resheniya_2/synapses.txt";
                  // /home/viktor/my_projects_qt_2/Funktsiya_Resheniya_2/synapses.txt
                  QFile file3(filename);

                  // Открываем файл для записи
                  if (!file3.open(QIODevice::WriteOnly | QIODevice::Text |QIODevice::Truncate)) {
                      std::cerr << "Unable to open file for writing!" << std::endl;

                  }

                  QTextStream out(&file3);

                  // Записываем данные из вектора в файл
                  for (const auto& value : *list_of_synapses) {
                      out << value << "\n";
                  }
                  // Сбрасываем буфер потока
                  out.flush();
                  // Закрываем файл
                  file3.close();

                  std::cout << "Successfully wrote the vector to " << filename.toStdString() << std::endl;
//###########################################################################
                  // Открываем файл снова для проверки размера
                  if (!file3.open(QIODevice::ReadOnly)) {
                      std::cerr << "Cannot open file to check size: " << qPrintable(file3.errorString()) << std::endl;
                    //  return 1;
                  }

                  // Получаем размер файла
                  qint64 fileSize = file3.size();
                  file3.close();

                  // Выводим размер файла
                  std::cout << "The size of the file is: " << fileSize << " bytes." << std::endl;
//###########################################################################
                  // Sleep for 5 seconds
             //     std::this_thread::sleep_for(std::chrono::seconds(5));

                  qDebug() << "Program execution completed.";
//###########################################################################//###########################################################################








}

Dialog::~Dialog()
{
    delete ui;
}





