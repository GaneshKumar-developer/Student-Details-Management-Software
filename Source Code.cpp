#include<iostream>
#include<conio.h>
#include<fstream>
#include<windows.h>
using namespace std;

struct node
{
	int enro;
	char name[20],branch[20],sem[10];
	node *rightchild,*leftchild;
};

class bintree
{
	node *root;
public:
	void insert(node *newnode);
	node* search(int eno);
	void del(int dno);
	void edit(int eno);
	void write(ofstream &out,node *root);
	void write_to_file();

}btree;

void writestruct(node *data);
void title();
void reading_from_file();
void readstruct(node *newnode);
void inputdata();
void menu();
void write_to_file();

void bintree::insert(node *newnode)
{
	node *parent,*child;
	if(root==NULL)
	{
		root=newnode;
		return;
	}
	else
	{
		parent=NULL;
		child=root;
		while(child!=NULL)
		{
			parent=child;
			if(newnode->enro >parent->enro)
			{
				child=child->rightchild;
			}
			else
			{
				child=child->leftchild;
			}
		}
	
		if(parent->enro > newnode->enro)
		{
			parent->leftchild=newnode;
		}
		else
		{
			parent->rightchild=newnode;
		}
	}
}

node* bintree::search(int eno)
{
	node *trail;
	trail=root;
	int flag=0;
	while(trail!=NULL)
	{
		if(trail->enro==eno)
		{
			flag=1;
			break;
		}
		else if(trail->enro>eno)
		{
			trail=trail->leftchild;
		}
		else
		{
			trail=trail->rightchild;
		}
	}
	if(flag==0)
	{
		cout<<"Data not found....try again";
		cout<<endl<<endl<<endl;
		cout<<"Press any key to continue.....";
		getch();
		menu();
	}

	else
	{
		return trail;
	}
	
}

void writestruct(node *data)
{
	cout<<endl<<"Enrollment number:"<<endl<<data->enro;
	cout<<endl<<"Name:"<<endl<<data->name;
	cout<<endl<<"Branch:"<<endl<<data->branch;
	cout<<endl<<"Semester:"<<endl<<data->sem;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"Press any key to continue.....";
	getch();
	
}






void title()
{
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"STUDENT DATA MANAGEMENT SYSTEM"<<endl;
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"Using binary search tree implementation";
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"Press any key to continue......";
	getch();
	system("cls");
}

void reading_from_file()
{
	ifstream in("Studentdetails");
	if(!in)
	{
		cout<<endl<<"No pre existing data"<<endl;
		cout<<endl<<"Enter all students data"<<endl;
		cout<<endl<<"Enter the no of students"<<endl;
		int no;
		cin>>no;
		for(int i=0;i<no;i++)
		{system("cls");
		cout<<"Enter the details of student\t"<<i+1<<":"<<endl;
			inputdata();
		}
	}
	else
	{
		while(!in.eof())
		{
			node *indata;
			indata=(node*)malloc(sizeof(node));
			in.read((char *)indata,sizeof(node));
			indata->leftchild=NULL;
			indata->rightchild=NULL;
			if(indata->enro >=0 && indata->enro <=1000)
			btree.insert(indata);
		}
	}
	in.close();
}
void inputdata()
{
	node *newnode;
	newnode=(node *)malloc(sizeof(node));
	readstruct(newnode);
	btree.insert(newnode);
}

void readstruct(node *newnode)
{
	cout<<endl<<"Enter the enrollment no";
	cin>>newnode->enro;
	cout<<endl<<"Enter the name of the student";
	cin>>newnode->name;
	cout<<endl<<"Enter the Branch";
	cin>>newnode->branch;
	cout<<endl<<"Enter the semester";
	cin>>newnode->sem;
	newnode->leftchild=NULL;
	newnode->rightchild=NULL;
}

void menu()
{
	system("cls");
	cout<<"Enter:"<<endl;
	cout<<"1.Insert"<<endl<<"2.Search"<<endl<<"3.Edit"<<endl<<"4.Exit"<<endl;
	int ch;
	cin>>ch;
	switch(ch)
	{
	case 1:
		cout<<"Enter  the details for new entry"<<endl;
		inputdata();
		menu();
		break;

	case 2:
		int eno;
		system("cls");
		cout<<"Enter the Enrollment no of the student you want to search for"<<endl;
		cin>>eno;
		node *ret;
		ret=btree.search(eno);
		system("cls");
		cout<<"The details of the student";
	writestruct(ret);

	case 3:
		system("cls");
		int e_no;
		cout<<"Enter the Enrollment no of the student you want to edit"<<endl;
		cin>>e_no;
		system("cls");
		btree.edit(e_no);
		menu();
		break;
	case 4:
		remove("studentdetails");
		btree.write_to_file();
		exit(0);
		
	
	
		
	}
}

void bintree::edit(int eno)
{
	node *term;
	term=btree.search(eno);
	cout<<endl<<"Enter the new information"<<endl;
	readstruct(term);
}

void bintree::del(int dno)
{
	node *delnode,*parent,*nextnode,*insuc;
	parent=NULL;
	delnode=root;
	while(delnode)
	{
		if(dno==delnode->enro)
			break;
		parent=delnode;
		if(dno <delnode->enro)
		{
			delnode=delnode->leftchild;
		}
		else
		{
			delnode=delnode->rightchild;
		}
	}
	cout<<"out while";
writestruct(delnode);
	getch();
	if(!delnode)
	{
		cout<<"Not found";
		menu();
	}
	if(!delnode->leftchild && !delnode->rightchild)
	{
		delete delnode;
		return;
	}
	else if(!delnode->leftchild)
	{
		nextnode=delnode->rightchild;
	}
	else if(!delnode->rightchild)
	{
		nextnode=delnode->leftchild;
	}
	else
	{
		insuc=delnode->rightchild;
		while(insuc->leftchild)
		{
			insuc=insuc->leftchild;
		}
		insuc->leftchild=delnode->leftchild;
		nextnode=delnode->rightchild;
	}
		if(!parent)
	{
		root=nextnode;
	}

	if( delnode== parent->leftchild &&parent->leftchild)
	{
		parent->leftchild=nextnode;
		delete delnode;
	}
	else
	{
		parent->rightchild=nextnode;
		delete delnode;
	}
}

void bintree::write_to_file()
{
	ofstream out("Studentdetails");
	btree.write(out,root);
	
}


void bintree::write(ofstream &out,node *root)
{
		
	if(root==NULL)
	{
		return;
	} 
	write(out,root->leftchild);
	out.write((char*)root,sizeof(node));
	write(out,root->rightchild);
}

	

int main()
{
title();
reading_from_file();
menu();
return 0;
}
