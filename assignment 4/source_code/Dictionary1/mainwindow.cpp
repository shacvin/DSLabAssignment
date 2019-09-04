#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <bits/stdc++.h>
#include<iostream>
#include<string>
#include <fstream>
using namespace std;


const int ALPHABET_SIZE = 26;


struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];

    bool isEndOfWord;
};



struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}

void insert(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;


    for (string::size_type i = 0; i <key.length() ; i++)
    {
        int index = key[i] - 'A';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }


    pCrawl->isEndOfWord = true;
}

bool search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (string::size_type i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'A';
        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != nullptr && pCrawl->isEndOfWord);
}


struct TrieNode *root;





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     ui->setupUi(this);

    root=getNode();

    vector <string> key;
    string line;


      ifstream myfile ("C:/Users/vinay/Documents/dictionary.csv");
      if (myfile.is_open())
      {
        while ( getline (myfile,line) )
        {

          key.push_back(line);

        }
        myfile.close();
      }

      else {
          cout << "Unable to open file";
      }

       string::size_type n=key.size();
       cout<<n<<endl;


       for(string::size_type i=0;i<key.size();i++)
       {
               int pos = key[i].find_first_of(',');
               string lastname = key[i].substr(pos+1);
                    string firstname = key[i].substr(0, pos);
               cout<<firstname<<endl<<lastname<<endl;
               insert(root, firstname);
       }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSearch_clicked()
{
    vector <string> key;
    unordered_map<string,string> mp;
    string line;


      ifstream myfile ("C:/Users/vinay/Documents/dictionary.csv");
      if (myfile.is_open())
      {
        while ( getline (myfile,line) )
        {

          key.push_back(line);

        }
        myfile.close();
      }



       string::size_type n=key.size();



       for(string::size_type i=0;i<key.size();i++)
       {
               int pos = key[i].find_first_of(',');
               string lastname = key[i].substr(pos+1);
               string firstname = key[i].substr(0, pos);
               mp[firstname]=lastname;
       }

       QString num1 = ui->t1->toPlainText();
       string s=num1.toStdString();

       bool alpha= search(root, s);

       if(alpha==false)
       {
           ui->t2->setPlainText("Not Found");
       }
       else {
           QString str = QString::fromUtf8(mp[s].c_str());
           ui->t2->setPlainText(str);
       }

}
