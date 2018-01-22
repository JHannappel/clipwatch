#include <QApplication>
#include <QToolBar>
#include <QAction>
#include <QMimeData>
#include <iostream>
#include "clipWatch.h"

clipWatch::clipWatch() {
  this->setWindowFlags(this->windowFlags()|Qt::FramelessWindowHint);
  textWidget = new QPlainTextEdit(this);
  setCentralWidget(textWidget);
  textWidget->resize(80,1);
  auto cb = QApplication::clipboard();
  connect(cb, SIGNAL(changed(QClipboard::Mode)), this, SLOT(clipChange(QClipboard::Mode)));
  connect(textWidget->document(), SIGNAL(contentsChanged()), this, SLOT(textChange()));
  toolBar = addToolBar("clipWatch tool bar");
  auto clear = toolBar->addAction("clear");
  connect(clear,SIGNAL(triggered()),textWidget,SLOT(clear()));
  connect(clear,SIGNAL(triggered()),this,SLOT(showMinimized()));
  autoClear = new QRadioButton("auto clear");
  autoClear->setChecked(true);
  autoClear->setAutoExclusive(false);
  toolBar->addWidget(autoClear);
  latin1 = new QRadioButton("only latin1");
  latin1->setChecked(true);
  latin1->setAutoExclusive(false);
  toolBar->addWidget(latin1);
  hex = new QRadioButton("with hex translation");
  hex->setChecked(false);
  hex->setAutoExclusive(false);
  toolBar->addWidget(hex);
  mogrify = new QRadioButton("mogrify selection");
  mogrify->setChecked(true);
  mogrify->setAutoExclusive(false);
  toolBar->addWidget(mogrify);
  clipSize = new QLabel();
  toolBar->addWidget(clipSize);
  setAttribute(Qt::WA_ShowWithoutActivating);
  //  showMinimized();
}
clipWatch::~clipWatch() {
}
void clipWatch::clipChange(QClipboard::Mode mode) {
   auto cb = QApplication::clipboard();

   std::cout << "\n\nnew selection:\n";
   auto md=cb->mimeData(mode);
   for (auto f : md->formats()) {
     std::cout << f.toLocal8Bit().constData() << "\n";
   }
   std::cout << md->data("text/plain").constData() <<"\n";
   if (autoClear->isChecked()) {
     textWidget->clear();
   }
   QString widgetText;
   QString newSelectionText;
   if (latin1->isChecked()) {
     auto text=md->data("text/plain");
     for (unsigned char c:text) {
       if (c<' ') {
	 widgetText.push_back(c+0x2400);
	 if (c=='\t' || c=='\n') {
	   widgetText.push_back(c);
	   newSelectionText.push_back(c);
	 }
       } else if (c==0x7f) {
	 widgetText.push_back(0x2421);
       } else if (c>0x7f && c<0xA0) {
	 widgetText.push_back(c-0x0080+0x2580);
       } else if (c==0xA0) {
	 widgetText.push_back(0x25A1);
       } else if (c>0xA0) {
	 widgetText.push_back(0x25A3);
       } else {
	 widgetText.push_back(c);
	 newSelectionText.push_back(c);
       }
     }
   } else {
     widgetText = cb->text(mode);
     newSelectionText = widgetText;
   }
   widgetText.push_back(0x2327);
   textWidget->appendPlainText(widgetText);

   if (hex->isChecked()) {
     QString hexLine;
     for (auto c:widgetText) {
       hexLine.append(QString::number(c.unicode(),16));
       hexLine.push_back(' ');
     }
     textWidget->appendPlainText(hexLine);
   }
   
   while (newSelectionText.endsWith('\n')) {
       newSelectionText.truncate(newSelectionText.length()-1);
   }
   if (newSelectionText != lastSetByMe) {
     lastSetByMe=newSelectionText;
     if (mogrify->isChecked()) {
       cb->setText(newSelectionText);
     }
   }
   raise();
   show();
}
void clipWatch::textChange() {
  clipSize->setText(QString::number(textWidget->document()->characterCount()-1));
}
