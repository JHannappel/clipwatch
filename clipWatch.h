#include <QClipboard>
#include <QPlainTextEdit>
#include <QMainWindow>
#include <QRadioButton>
#include <QLabel>

class clipWatch: public QMainWindow {
  Q_OBJECT
 protected:
  QPlainTextEdit* textWidget;
  QToolBar* toolBar;
  QAbstractButton* autoClear;
  QAbstractButton* latin1;
  QAbstractButton* hex;
  QLabel* clipSize;
  QString lastSetByMe;
 public:
  clipWatch();
  virtual ~clipWatch();
  public slots:
    void clipChange(QClipboard::Mode mode);
    void textChange();
};
