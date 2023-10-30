/***************************************************************************
 *   Copyright (C) 2007 by dogangolcuk   *
 *   dogangolcuk@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "ui_anaPencere.h"
#include <QDataWidgetMapper>
#include <QtSql>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QProgressDialog>
class anaPencere : public QMainWindow , Ui::MainWindow
{
   Q_OBJECT
   public:
      	anaPencere(); //constructer
	QSqlQueryModel *model;
	QSqlQueryModel *model2;
	QItemSelectionModel *selectionModel ;
        QDataWidgetMapper *mapper ;
	QString arsivYolu;
	QString aranacakarsiv;
	QString ara;
//    protected:
//    private:

   public slots:
	void Ara(const QString & text );
	void tablodolas(const QModelIndex & index);
	void hakkinda();
	void arsivyap();
	bool arsivle();
        void getArsivYolu();
        void sil();
	void yedekle();
	void geriyukle();
	void geriyuklendi1();
 	void setAranacakArsiv(const QModelIndex & index);
// 	void getAranacakArsiv();
// 	void setDosyaUzantıları();
// 	void getDosyaUzantıları();
    signals:
	void geriyuklendi( );
};