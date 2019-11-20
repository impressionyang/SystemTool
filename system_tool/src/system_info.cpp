#include "system_info.h"

System_Info::System_Info()
{
    this->cpu=0;
    this->mem=0;
    this->stor=0;

}

double::System_Info::getcpu(){
    return this->cpu;
}

double::System_Info::getmem(){
    return this->mem;
}

double::System_Info::getstor(){
    return this->stor;
}

void System_Info::value_update(){
        QString temp=nullptr;

        QProcess *process=new QProcess();
        process->start("bash",QStringList() <<"-c" << "df");
        process->waitForFinished();
        temp=process->readAllStandardOutput();
        this->stor=encodedf(temp);
    //    qDebug()<<"temppppppp="<<temp;

        process->start("bash",QStringList() <<"-c" << "free");
        process->waitForFinished();
        temp=process->readAllStandardOutput();
        this->mem=encodemem(temp);

        process->start("bash",QStringList() <<"-c" << "top -b -n 2 -d 0.01 | grep Cpu");
        process->waitForFinished();
        temp=process->readAllStandardOutput();
        this->cpu=encodecpu(temp);
//        qDebug()<<temp<<endl;
}

double System_Info::encodecpu(QString input){
    QList<double> *list=this->getCPUNumberList(input);
    QString result=nullptr;

//    int cpu_n=list->at(2);
//    int cpu_mgh_now=list->at(4);
//    int cpu_mgh_each=list->at(5);
    double free=0;
    int count=0;
    for(double i:*list){
        free=free+i;
//        qDebug()<<"cpu"<<count<<"free="<<i<<endl;
        count++;

    }

    free=free/list->length();
//    qDebug()<<"length="<<list->length()<<endl;


    double cpu=100-free;
//    qDebug()<<"cpu"<<"="<<cpu;
    result=QString::number(cpu);

//    for(int a:*list){
//        qDebug()<<a<<endl;
//    }

    return cpu;
}

double System_Info::encodemem(QString input){
    QList<int> *list=this->getMemNumberList(input);
    QString result=nullptr;
    double mem=((double)list->at(1)/list->at(0))*100;
    result=QString::number(mem);

    return mem;
}

int System_Info::encodedf(QString input){
    QList<int> *list=this->getStorNumberList(input);
    int result=0;
    if(list->length()>1){
        result=list->at(1);
    }else {
        result=list->at(0);
    }

//    for(int i:*list){
//        qDebug()<<i<<endl;
//    }

//    qDebug()<<"result="<<result<<endl;

    return result;
}

QList<int>* System_Info::getMemNumberList(QString get){
    QList<int> *list=new QList<int>();
    for(int i=0;i<get.length();i++){
        if(i!=0&&get.at(i).isNumber()&&get.at(i-1)==" "){
            QString temp=nullptr;
            while(get.at(i).isNumber()){
                temp=temp+get.at(i);
                i++;
            }
            int num=temp.toInt();
            list->append(num);
        }
    }

    return list;
}

QList<double>* System_Info::getCPUNumberList(QString get){
    QList<double> *list=new QList<double>();
    QTextStream in(&get);
    QString get2=nullptr;
    QString temp=in.readLine();
    int cpu_count=0;
    while(temp!=nullptr){
        if(temp.indexOf("Cpu")>=0){
            int i=temp.indexOf("id");
            i=i-6;

            QString temp2=nullptr;
            for(int j=0;j<4;j++){
                temp2=temp2+temp.at(i+j);
            }
            double temp3=temp2.toDouble();
            list->append(temp3);
            cpu_count++;
        }
        temp=in.readLine();
    }
//    for(int i=0;i<get2.length();i++){
//        if(i!=0&&get2.at(i).isNumber()&&get2.at(i-1)==" "){
//            QString temp=nullptr;
//            while(get2.at(i).isNumber()){
//                temp=temp+get2.at(i);
//                i++;
//            }
//            int num=temp.toInt();
//            list->append(num);
//        }
//    }

//    for(int i:*list){
//        qDebug()<<i<<endl;
//    }
    return list;
}


QList<int>* System_Info::getStorNumberList(QString get){
    QList<int> *list=new QList<int>();
    QTextStream in(&get);
    QString get2=nullptr;
    QString temp=in.readLine();
    while(temp!=nullptr){
        if(temp.indexOf("/home")>=0){
//            qDebug()<<"/home="<<temp<<endl;
            int i=temp.indexOf("%");
            i=i-3;

            QString temp2=nullptr;
            for(int j=0;j<3;j++){
                temp2=temp2+temp.at(i+j);
            }
            int temp3=temp2.toInt();
            list->append(temp3);
        }else if (temp.endsWith(" /")) {
//            qDebug()<<"/="<<temp<<endl;
            int i=temp.indexOf("%");
            i=i-3;

            QString temp2=nullptr;
            for(int j=0;j<3;j++){
                temp2=temp2+temp.at(i+j);
            }
            int temp3=temp2.toInt();
            list->append(temp3);
        }
        temp=in.readLine();
    }

    return list;
}


