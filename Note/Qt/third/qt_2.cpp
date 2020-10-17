#include<QApplication>
#include<QLabel>
#include<QPushButton>
int main(int argc,char *argv[])
{
  QApplication app(argc, argv);
  QLabel *label = new QLabel("<h2><i>Hello</i>"
                             "<font color=red>Qt!</font></h2>");
  label->show();
  
  QPushButton *button = new QPushButton("Quit");
  QObject::connect(button,SIGNAL(clicked()),&app,SLOT(quit()));
  button->show();
  
  return app.exec();
  
}