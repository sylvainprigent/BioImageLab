#include <blTool>
#include <QtWidgets>

#include <QApplication>
#include <QDir>

QString loadStyleSheet(QString fileUrl){
    QFile file(fileUrl);
    file.open(QIODevice::ReadOnly);
    QString sty = QString::fromStdString(file.readAll().toStdString());
    //qDebug() << sty;
    return sty;
}

/*
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // get the tool
    blToolParser w;
    blToolInfo* toolInfo = w.getToolInfo("C:\\Users\\Sylvain\\codes\\blTool\\tools\\meanfilter.xml");
    //toolInfo->print();

    // get the inputs
    blioDataInfo *inputsInfo = new blioDataInfo;
    blioDataList dataList;
    dataList.add("inputImage", "c:\\myimage.png");
    inputsInfo->add(dataList);

    // get the parameters
    blioParameters* parameters = new blioParameters();
    parameters->add("windowSize", QString::number(5));

    // run the process
    blToolExec *toolExec = new blToolExec();
    QString outputDir = "C:\\Users\\Sylvain\\codes\\blTool\\tools";
    toolExec->setOutputDir(outputDir);
    toolExec->setToolInfo(toolInfo);
    toolExec->setInputDataInfo(inputsInfo);
    toolExec->setParameters(parameters);
    toolExec->run();

    //load history
    //blToolExecLog history;
    //history.load(outputDir + QDir::separator() + "history.dat");
    //history.print();

    return a.exec();
}
*/

/*
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // get the tool
    blToolParser tp;
    blToolInfo* toolInfo = tp.getToolInfo("C:\\Users\\Sylvain\\codes\\blTool\\tools\\meanfilter.xml");

    // widget
    blToolExecGui w(toolInfo);
    w.show();


    return a.exec();
}
*/

/*
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // get the tool
    blToolHistoryBrowser tp;
    tp.setHistoryDir("C:\\Users\\Sylvain\\codes\\blTool\\tools\\");
    tp.getHistoryAll();


    return a.exec();
}
*/

/*
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // widget
    blToolHistoryBar w;
    w.show();


    return a.exec();
}
*/

/*
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // widget
    QPushButton *button = new QPushButton("Hello world!");
    button->show();

    qDebug() << "hello world!";

    return a.exec();
}
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // widget
    blToolParser pars;
    blToolInfo* toolInfo = pars.getToolInfo("C:\\Users\\sprigent\\Documents\\codes\\BioImageLab_dist\\tools\\blMpp.xml");
    //toolInfo->print();
    QString historyUrl = "C:\\Users\\sprigent\\Documents\\codes\\BioImageLab_dist\\history\\";
    QString viewersUrl = "C:\\Users\\sprigent\\Documents\\codes\\BioImageLab_dist\\viewers\\";

    blToolDefaultWidget w(toolInfo, historyUrl, viewersUrl);
    w.show();

    QString styleFile = "C:\\Users\\sprigent\\Documents\\codes\\BioImageLab\\theme\\stylesheet.css";
    a.setStyleSheet("file:///" + styleFile);
    return a.exec();
}
