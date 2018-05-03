/********************************************************************************
** Form generated from reading UI file 'infodialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFODIALOG_H
#define UI_INFODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_InfoDialog
{
public:
    QGroupBox *groupBox;
    QLabel *info_num_faces;
    QLabel *label_3;
    QLabel *label;
    QLabel *info_num_vertex;
    QGroupBox *groupBox_2;
    QLabel *label_7;
    QLabel *info_pos_camara;
    QLabel *label_8;
    QLabel *info_cam_distance;

    void setupUi(QDialog *InfoDialog)
    {
        if (InfoDialog->objectName().isEmpty())
            InfoDialog->setObjectName(QStringLiteral("InfoDialog"));
        InfoDialog->resize(400, 300);
        groupBox = new QGroupBox(InfoDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 361, 111));
        info_num_faces = new QLabel(groupBox);
        info_num_faces->setObjectName(QStringLiteral("info_num_faces"));
        info_num_faces->setGeometry(QRect(110, 50, 67, 17));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 50, 71, 17));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 91, 17));
        info_num_vertex = new QLabel(groupBox);
        info_num_vertex->setObjectName(QStringLiteral("info_num_vertex"));
        info_num_vertex->setGeometry(QRect(110, 30, 67, 17));
        groupBox_2 = new QGroupBox(InfoDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 150, 361, 101));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 30, 67, 17));
        info_pos_camara = new QLabel(groupBox_2);
        info_pos_camara->setObjectName(QStringLiteral("info_pos_camara"));
        info_pos_camara->setGeometry(QRect(100, 30, 67, 17));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 50, 67, 17));
        info_cam_distance = new QLabel(groupBox_2);
        info_cam_distance->setObjectName(QStringLiteral("info_cam_distance"));
        info_cam_distance->setGeometry(QRect(90, 50, 67, 17));

        retranslateUi(InfoDialog);

        QMetaObject::connectSlotsByName(InfoDialog);
    } // setupUi

    void retranslateUi(QDialog *InfoDialog)
    {
        InfoDialog->setWindowTitle(QApplication::translate("InfoDialog", "Dialog", nullptr));
        groupBox->setTitle(QApplication::translate("InfoDialog", "Malla", nullptr));
        info_num_faces->setText(QApplication::translate("InfoDialog", "N\302\272 Caras:", nullptr));
        label_3->setText(QApplication::translate("InfoDialog", "N\302\272 Caras:", nullptr));
        label->setText(QApplication::translate("InfoDialog", "N\302\272 Vertices:", nullptr));
        info_num_vertex->setText(QApplication::translate("InfoDialog", "TextLabel", nullptr));
        groupBox_2->setTitle(QApplication::translate("InfoDialog", "Camara", nullptr));
        label_7->setText(QApplication::translate("InfoDialog", "Posicion:", nullptr));
        info_pos_camara->setText(QApplication::translate("InfoDialog", "(x,y,z)", nullptr));
        label_8->setText(QApplication::translate("InfoDialog", "Distancia:", nullptr));
        info_cam_distance->setText(QApplication::translate("InfoDialog", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InfoDialog: public Ui_InfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFODIALOG_H
