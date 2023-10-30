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
#include "anaPencere.h"
anaPencere::anaPencere()
{
	setupUi ( this );
	model = new QSqlQueryModel;
	model->setQuery ( "SELECT * FROM arsiv" );
	tablo->setModel ( model );

	model2 = new QSqlQueryModel;
	model2->setQuery ( "SELECT DISTINCT arsivad FROM arsiv" );
model2->setHeaderData ( 0, Qt::Horizontal, trUtf8 ( "Arşiv Adı" ) );
arsivadlari->verticalHeader()->hide();
	arsivadlari->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	arsivadlari->setModel ( model2 );

selectionModel = arsivadlari->selectionModel();

	tablo->horizontalHeader()->setResizeMode ( QHeaderView::ResizeToContents );
	model->setHeaderData ( 0, Qt::Horizontal, trUtf8 ( "Arşiv Adı" ) );
	model->setHeaderData ( 1, Qt::Horizontal, trUtf8 ( "Dosya Adı" ) );
	model->setHeaderData ( 2, Qt::Horizontal, trUtf8 ( "Dosya Yolu" ) );
	tablo->show();
//   mapper = new QDataWidgetMapper;
//   mapper->setModel(model);
//   mapper->addMapping(anlam, 1);

	connect ( arama_kutusu,SIGNAL ( textChanged ( const QString & ) ),this,SLOT ( Ara ( const QString & ) ) );
// connect(tablo,SIGNAL(activated ( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));
// connect(tablo,SIGNAL(pressed ( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));
	connect ( tbArsivYap,SIGNAL ( clicked () ),this,SLOT ( arsivyap() ) );
	connect ( tbArsivYeri,SIGNAL ( clicked () ),this,SLOT ( getArsivYolu() ) );
	connect ( tbArsivSil,SIGNAL ( clicked () ),this,SLOT ( sil() ) );
	connect ( pbHakkinda,SIGNAL ( clicked () ),this,SLOT ( hakkinda() ) );
	connect ( PbYedekle,SIGNAL ( clicked () ),this,SLOT ( yedekle() ) );
	connect ( PbGeriYukle,SIGNAL ( clicked () ),this,SLOT ( geriyukle() ) );

	connect(actionArsivolustur,SIGNAL(activated()),this,SLOT(arsivyap() ));
	connect ( actionArsivlenecek,SIGNAL ( activated() ),this,SLOT ( getArsivYolu() ) );
	connect ( actionSil,SIGNAL ( activated() ),this,SLOT ( sil() ) );
	connect ( actionHakkinda,SIGNAL ( activated() ),this,SLOT ( hakkinda() ) );
	connect ( actionYedekle,SIGNAL ( activated() ),this,SLOT ( yedekle() ) );
	connect ( actionGeriyukle,SIGNAL ( activated() ),this,SLOT ( geriyukle() ) );
	connect ( this,SIGNAL ( geriyuklendi() ),this,SLOT ( geriyuklendi1() ) );
 connect(arsivadlari,SIGNAL(activated ( const QModelIndex & )),this,SLOT(setAranacakArsiv(const QModelIndex &)));
connect(arsivadlari,SIGNAL(clicked ( const QModelIndex & )),this,SLOT(setAranacakArsiv(const QModelIndex &)));
}
void anaPencere::Ara ( const QString & text )
{
	QString low = text.toLower();
	QString up = text.toUpper();
	model->clear();
	model->setHeaderData ( 0, Qt::Horizontal, trUtf8 ( "Arşiv Adı" ) );
	model->setHeaderData ( 1, Qt::Horizontal, trUtf8 ( "Dosya Adı" ) );
	model->setHeaderData ( 2, Qt::Horizontal, trUtf8 ( "Dosya Yolu" ) );
	ara.clear();
// text=text.trimmed();
	ara.append ( "lower(arsivad) LIKE '%"+low+"%'" );
	ara.append ( "OR upper(arsivad) LIKE '%"+up+"%'");
	ara.append ( "OR lower(dosyaadi) LIKE '%"+low+"%'" );
	ara.append ( "OR upper(dosyaadi) LIKE '%"+up+"%'");
if(!CbDosyaYolu->isChecked()){
	ara.append ( "OR lower(dosyayolu) LIKE '%"+low+"%'" );
	ara.append ( "OR upper(dosyayolu) LIKE '%"+up+"%'");
}
if(CbHepsiniAra->isChecked()){
	model->setQuery ( "SELECT * FROM arsiv WHERE "+ara);
qDebug()<< ara;
}else {
model->setQuery ( "SELECT * FROM arsiv WHERE ("+ara+") AND arsivad='"+aranacakarsiv+"'" );
	}
	model->query();
}
void anaPencere::tablodolas ( const QModelIndex & index )
{
// aranacakarsiv=model2->data(model2->index(selectionModel->currentIndex().row(), 0)).toString();
// model->setQuery ( "SELECT * FROM arsiv WHERE "+ara+" and arsivad='"+aranacakarsiv+"" );
// // qDebug() << ara;
// model->query();
// mapper->setCurrentModelIndex(index);
}
void anaPencere::setAranacakArsiv(const QModelIndex & index)
{
aranacakarsiv=model2->data(model2->index(selectionModel->currentIndex().row(), 0)).toString();
CbHepsiniAra->setCheckState(Qt::Unchecked);
qDebug() << aranacakarsiv;
Ara(arama_kutusu->text());
arsiv_adi->setText(aranacakarsiv);

}

void anaPencere::hakkinda()
{
	QMessageBox::information ( this, QString::fromUtf8 ( "Pardus Linux için Cd/Dvd Arşiv" ),
	                           QString::fromUtf8 ( "\ndogangolcuk@gmail.com\n" ),
	                           QMessageBox::Close );
}

bool anaPencere::arsivle()
{

	int numFiles;
	QDirIterator tmp_it ( arsivYolu , QDirIterator::Subdirectories );
	while ( tmp_it.hasNext() )
	{
//      		qDebug() << it.fileName() << it.filePath();
		tmp_it.next();
		numFiles++;
	}
	QProgressDialog progress ( trUtf8 ( "Dizinler Taranıyor" ), "iPtal", 0, numFiles, this );
	progress.setWindowModality ( Qt::WindowModal );
//      QSqlDatabase::database().transaction();
	QSqlQuery insert;
//         QString insertstr;
	QDirIterator it ( arsivYolu , QDirIterator::Subdirectories );
	int i;
	i=0;
	while ( it.hasNext() )
	{
//      		qDebug() << it.fileName() << it.filePath();
		it.next();
		if( !(it.fileName()=="." or it.fileName()=="..") ){
		insert.prepare ( "INSERT INTO arsiv (arsivad, dosyaadi, dosyayolu) "
		                 "VALUES (:1, :2, :3)" );
		insert.bindValue ( ":1", arsiv_adi->text() );
		insert.bindValue ( ":2", it.fileName() );
		insert.bindValue ( ":3", it.filePath() );
		if ( !insert.exec() ) {return false;}

		i++;
		progress.setValue ( i );
		qApp->processEvents();
		if ( progress.wasCanceled() ) {return false;break;}
	}//while it.hasNext()
		}
// 		progress.setValue(numFiles);
	model->clear();
	model->setQuery ( "SELECT * FROM arsiv" );
	model->query();


//         if(QSqlDatabase::database().commit()){//sqlite commit desteklemiyormu?
	return true;
//  	}else	{
//  		qDebug("VeritabanÃÂ±na kayÃÂ±t edilemedi.Hata yada eriÃÂim sorunlarÃÂ±");
//  		return false;
//  	};

}
void anaPencere::arsivyap()
{
	if ( !arsiv_adi->text().isEmpty() )
	{
		if ( arsivle() )
		{
			QMessageBox::information ( this, QString::fromUtf8 ( "Tebrikler" ),
			                           QString::fromUtf8 ( "\nArşiv Oluşturuldu." ),
			                           QMessageBox::Close );
model2->setQuery ( "SELECT DISTINCT arsivad FROM arsiv" );
model2->query();
		}
		else
			QMessageBox::information ( this, QString::fromUtf8 ( "Uyarı" ),
			                           QString::fromUtf8 ( "\nArşiv Oluşturulamadı." ),
			                           QMessageBox::Close );
	}
	else
		QMessageBox::information ( this, QString::fromUtf8 ( "Uyarı" ),
		                           QString::fromUtf8 ( "\nArşiv Adı Giriniz." ),
		                           QMessageBox::Close );
}


void anaPencere::getArsivYolu()
{
	QFileDialog dialog;
	dialog.setFileMode ( QFileDialog::DirectoryOnly );
	QString yol = dialog.getExistingDirectory (
	                  this,
	                  QString::fromUtf8 ( "Arşivlenecek Dizin " ),
	                  "/home",
	                  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );
//              tmpop = new xmlop();
//              QFile::copy( tmpop->getSharePath() +"/" + value , s+value);
//              delete tmpop;
	arsivYolu = yol;
	label->setText ( arsivYolu );
// return yol;

}
void anaPencere::sil()
{

	if (
	    QMessageBox::question (
	        0,
	        trUtf8 ( "Uyarı" ),
	        trUtf8 ( "Arşivi silmek istediğinizden emin misiniz?" ),
	        trUtf8 ( "Evet" ),
	        trUtf8 ( "Hayır" ),
	        QString(), 1, 0 | QMessageBox::Default | QMessageBox::Escape ) == 0
	)
	{
		if ( !arsiv_adi->text().isEmpty() )
		{
			QSqlQuery sorgu ( "DELETE FROM arsiv WHERE arsivad='"+ arsiv_adi->text() +"'" );
			sorgu.exec();
			model->clear();
			model->setQuery ( "SELECT * FROM arsiv" );
// 		qDebug() << ara;
			model->query();
model2->setQuery ( "SELECT DISTINCT arsivad FROM arsiv" );
model2->query();
		}
		else
			QMessageBox::information ( this, QString::fromUtf8 ( "Uyarı" ),
			                           QString::fromUtf8 ( "\nArşiv Adı Giriniz." ),
			                           QMessageBox::Close );

	}


}
void anaPencere::yedekle()
{

	QFileDialog dialog;
	dialog.setFileMode ( QFileDialog::DirectoryOnly );
	QString s = dialog.getSaveFileName (
	                this,
	                QString::fromUtf8 ( "Yedeklenecek Dizin " ),
	                "/home" );



// qDebug()<< s;
	if ( QFile::exists ( QDir::homePath() + "/.cdarsiv/arsivdb" ) )
		if ( QFile::copy ( QDir::homePath() + "/.cdarsiv/arsivdb",s ) )
			QMessageBox::information ( this, QString::fromUtf8 ( "Dosya Yedeklendi" ),
			                           QString::fromUtf8 ( "\nDosya Başarıyla Yedeklendi. " ),
			                           QMessageBox::Close );
		else
			QMessageBox::information ( this, QString::fromUtf8 ( "Dosya Yedeklenemedi." ),
			                           QString::fromUtf8 ( "\nDosya Yedeklenirken Hata Oluştu. " ),
			                           QMessageBox::Close );


}
void anaPencere::geriyukle()
{

	QFileDialog dialog;
	dialog.setFileMode ( QFileDialog::DirectoryOnly );
	QString s = dialog.getOpenFileName (
	                this,
	                QString::fromUtf8 ( "Geri Yüklenecek Dosya " ),
	                "/home" );
	qDebug() << s;


	if ( QFile::exists ( QDir::homePath() + "/.cdarsiv/arsivdb" ) )
	{
		if (
		    QMessageBox::question (
		        this,
		        trUtf8 ( "Uyarı" ),
		        trUtf8 ( "Daha Eski Bir Arşiviniz Var.Bu Arşiviniz Kaybolacaktır."
		                 "Buna rağmen devam etmek istiyor musunuz?" ),
		        trUtf8 ( "Evet" ),
		        trUtf8 ( "Hayır" ),
		        QString(), 1, 0 | QMessageBox::Default | QMessageBox::Escape ) == 0
		)
		{
			QFile::remove ( QDir::homePath() + "/.cdarsiv/arsivdb" );
			if ( QFile::copy ( s,QDir::homePath() + "/.cdarsiv/arsivdb" ) ){
				QMessageBox::information ( this, QString::fromUtf8 ( "Dosya Geri Yüklendi." ),
				                           QString::fromUtf8 ( "\nDosya Başarıyla Geri Yüklendi.. " ),
				                           QMessageBox::Close );emit geriyuklendi();}
			else
				QMessageBox::information ( this, QString::fromUtf8 ( "Dosya Geri Yüklenemedi." ),
				                           QString::fromUtf8 ( "\nDosya Geri Yüklenirken Hata Oluştu. " ),
				                           QMessageBox::Close );

		}
	}
	else
	{

		if ( QFile::copy ( s,QDir::homePath() + "/.cdarsiv/arsivdb" ) ){
			QMessageBox::information ( this, QString::fromUtf8 ( "Dosya Geri Yüklendi." ),
			                           QString::fromUtf8 ( "\nDosya Başarıyla Geri Yüklendi.. " ),
			                           QMessageBox::Close );emit geriyuklendi();}
		else
			QMessageBox::information ( this, QString::fromUtf8 ( "Dosya Geri Yüklenemedi." ),
			                           QString::fromUtf8 ( "\nDosya Geri Yüklenirken Hata Oluştu. " ),
			                           QMessageBox::Close );

	}

// 	QSqlDatabase db = QSqlDatabase::addDatabase ( "QSQLITE" );
// 	db.setDatabaseName ( QDir::homePath() + "/.cdarsiv/arsivdb" );
// db.close();
// db.setDatabaseName("/home/dizini/Desktop/arsivdb");
//       db.setUserName("yetkili");
//       db.setPassword("yetkili");
// 	if ( db.open() )
// // 		qDebug ( "Veritabanı bağlandı." );
// 	else
// 		QMessageBox::information ( 0, QString::fromUtf8 ( "Cd Arşiv" ),
// 		                           QString::fromUtf8 ( "Veritabanı Bağlanılamadı." ),
// 		                           QMessageBox::Close );
}
void anaPencere::geriyuklendi1()
{
QMessageBox::information ( this, QString::fromUtf8 ( "Programı Tekrar Başlatın." ),
			                           QString::fromUtf8 ( "\nDeğişikliklerin Etkili Olması İçin Programı Tekrar Başlatın. " ),
			                           QMessageBox::Close );
// 	qDebug() << "dddddd";
}