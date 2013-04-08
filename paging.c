#include<stdio.h>
#include<string.h>
#include<stdlib.h>
 int n;
struct node
{
	char data;
int recent;
struct node * next;
};
struct ref
{
	char str[100];
	int size;
}pro;
struct node * init()
{
struct node * head;
head=(struct node *)malloc (sizeof(struct node));
head->next=NULL;
return head;
}
void insert(struct node * curr,struct node * head)
{
curr->next=head->next;
head->next=curr;
}
void display(struct node * head)
{
struct node *t =head->next;
while(t!=NULL)
{
printf("%c\t",t->data);
t=t->next;
}
printf("\n");
}
void empty(struct node * head)
{
	struct node * t=head->next;
	
	while(t)
	{
		t->data='-';
		t->recent=0;
		t=t->next;
	} 
}


void create(struct node * head)
{
struct node * temp;
int i;
printf("enter the number of frames\n");
scanf("%d",&n);
for(i=0;i<n;i++)
{
	temp=(struct node *)malloc(sizeof(struct node));
temp->recent=0;
temp->data='-';
insert(temp,head);
}
//display(head);
}
void free_recent(struct node * head)
{
	struct node * t=head->next;
while(t)
{
t->recent=0;
t=t->next;
}
	
}
int search(struct node *head,int data )
{
	struct node *temp=head->next;
	while(temp)
{
	if(temp->data == data)
	return 1;
	temp=temp->next;
}
return 0;
}
void fifo(struct node * head)
{
struct node * curr,*temp;
int fault=0,used=0;
int st;
temp=head->next;
int i;
for(i=0;i<pro.size;i++)
{
		st=search(head,pro.str[i]);
if(st==0)
{
fault+=1;
temp->data=pro.str[i];
temp=temp->next;
used+=1;
//printf("%d count",used);
if(used == n )
{
	used=0;
temp=head->next;
}

}
printf("\n");
display(head);
}
printf("%d FAULT:: ",fault);
}
int full(struct node *head)
{
int count=0;
struct node *temp=head->next;

	//printf("here1.1.1\n");
while(temp)
{
	
	//printf("here221\n");
	if(temp->data == '-')
{
	count+=1;
	
	}
temp=temp->next;
}
if(count==0)
return 1;
else
return 0;

	//printf("return\n");
}
int replace(struct node * head,int pos)
{
struct node * t=head->next;
int i,min=999;
free_recent(head);
//printf("%dposs***\n",pos);
while(t)
{

for(i=pos-1;i>=0;i--)
{
if(t->data == pro.str[i] && t->recent!=1)
 {
	 t->recent=1;
 if( i < min) 
{
	
	//printf("hererep22\n");
min=i;

}
}
}
t=t->next;
}

return min;
}
struct node * find_pos(int ele,struct node * head)
{
struct node * t=head->next;
while(t->data!=ele)
t=t->next;
return t;
}


void lru(struct node *head)
{
	int fault=0,used=0;
int i,st,pos;
struct node * temp,*curr;
temp=head->next;
int a;
for(i=0;i<pro.size;i++)
{
st=search(head,pro.str[i]);
if(st==0)
{
	fault+=1;
a=full(head);
	if(a!=1)
{
	temp->data=pro.str[i];
temp=temp->next;
}
else if(a==1)
{
	
	pos=replace(head,i);
curr=find_pos(pro.str[pos],head);
curr->data=pro.str[i];
}
used+=1;
if(used==n)
{
temp=head->next;
used=0;
}
}
printf("\n");
display(head);
}
printf("FAULT:::%d\n",fault);
}
char replace_optimal(struct node * head,int pos)
{
struct node * t=head->next;
int i,min=-1;
int used=0;
free_recent(head);
//printf("%dposs***\n",pos);
if(pos+1==pro.size)
	return -1;
	
while(t)
{
	//printf("%d",t->recent);
	//printf("hererep1\n");
	//printf("%d*****\n",pro.size);
for(i=pos;i<pro.size;i++)
{
	
	//printf("hererep222\n");
if(t->data == pro.str[i]&& t->recent!=1 )
{
	used+=1;
t->recent=1;

if( i > min )
{

min=i;
//printf("min %d\n",min);
//printf("%c ele...\n\n",pro.str[i]);

}
}
}
t=t->next;
}
//printf("used... %d\n\n",used);
if(used!=n)
{ 
	//printf("hereee\n");
	t=head->next;
	while(t)
	{
	if(t->recent==0)
	{
	//printf("t->data %c\n",t->data);
	return t->data;
}
	t=t->next;
	}
}
//else
return pro.str[min];
}
void optimal(struct node *head)
{
	int fault=0,used=0;
int i,st,pos;
struct node * temp,*curr;
temp=head->next;
int a;
for(i=0;i<pro.size;i++)
{
//	printf("here1\n");
st=search(head,pro.str[i]);
if(st==0)
{
	
	//printf("here2\n");
fault+=1;


	//printf("herebef\n");
	a=full(head);
//printf("is ful$$$ %d",a);
	if(a!=1)
{
	
	//printf("here3\n");
	temp->data=pro.str[i];

	//printf("here3.1\n");
	
temp=temp->next;

	//printf("here3.2\n");

}
//if(temp->next==NULL)
//temp=head->next;
else if(a==1)
{
	
	
	//printf("here4\n");
//printf("%diiiiiiiii\n",i);
pos=replace_optimal(head,i);
if(pos==-1)
{
temp->data=pro.str[i];
}
else
{
//printf("%dposs\n",pos);
curr=find_pos(pos,head);
curr->data=pro.str[i];
temp=temp->next;
}
}
used+=1;
if(used==n)
{
temp=head->next;
used=0;
}
}
else if(st!=0)
{
printf("PAGE HIT!!\n");
}
printf("FRAME no %d",i+1);
printf("\n");
display(head);
}
printf("FAULT:::%d\n",fault);
}
int main()
{
	int i=0,ch,ch1;
	//pro.size=0;
struct node * free1;

//create(free);
//int ch=1;
do
{
	printf("1.input\n2.exit\n");
	scanf("%d",&ch1);
if(ch1==1)
{
printf("enter the refernce string\n");
scanf("%s",pro.str);
pro.size=strlen(pro.str);
free1=init();
create(free1);
do
{
printf("1.FIFO\n2.LRU\n3.OPTIMAL");
scanf("%d",&ch);
if(ch==1)
{
	
fifo(free1);
empty(free1);
}
if(ch==2)
{
	
lru(free1);
empty(free1);
}
if(ch==3)
{
	
optimal(free1);
empty(free1);
}
}while(ch!=4);
}
}while(ch!=2);
return 0;
}
